#include <bits/stdc++.h>
#include <canvas.h>

using namespace std;

const int maxa = 503;
const int maxn = maxa * maxa * 13;
const int maxe = maxn * 10;
const int inf = 0x3f3f3f3f;

struct Edge {
	int t, c, w;
	Edge *ne, *rv;
};
Edge epool[maxe], *ebuf, *head[maxn], *et[maxn], *fe[maxn];
int st, te, tn, n, d[maxn], fr[maxn];
int ni[maxa][maxa], hi[maxa][maxa], vi[maxa][maxa], pi[maxa][maxa];

Edge* newEdge(int u, int v, int c, int w) {
	ebuf->t = v;
	ebuf->c = c;
	ebuf->w = w;
	ebuf->ne = head[u];
	return head[u] = ebuf ++;
}

Edge* addEdge(int u, int v, int c, int w = 0) {
	Edge *a(newEdge(u, v, c, w)), *b(newEdge(v, u, 0, -w));
	a->rv = b, b->rv = a;
	return a;
}

bool dinicBFS() {
	static int q[maxn];
	int hd(0), tl(1);
	memset(d, 0, sizeof(d));
	d[q[hd] = st] = 1;
	while (hd < tl && !d[te]) {
		int u(q[hd ++]);
		for (Edge* e = head[u]; e; e = e->ne) {
			if (e->c && !d[e->t]) {
				d[e->t] = d[u] + 1;
				q[tl ++] = e->t;
			}
		}
	}
	return d[te];
}

int dinicDFS(int u, int c) {
	int s(0);
	if (u == te) {
		return c;
	}
	for (Edge* e = head[u]; e && c; e = e->ne) {
		if (e->c && d[e->t] == d[u] + 1) {
			int x(dinicDFS(e->t, min(c, e->c)));
			e->c -= x, e->rv->c += x;
			s += x, c -= x;
		}
	}
	if (c) {
		d[u] = 0;
	}
	return s;
}

#define QCHECK(_x_) { \
	if ((_x_) == maxn) { \
		(_x_) = 0; \
	} \
}

bool SPFA() {
	static int inq[maxn], q[maxn];
	int hd(0), tl(1);
	memset(inq, 0, sizeof(inq));
	memset(d, 0x3f, sizeof(d));
	d[q[hd] = st] = 0;
	inq[st] = 1;
	while (hd < tl) {
		int u(q[hd ++]);
		inq[u] = 0;
		QCHECK(hd);
		for (Edge* e = head[u]; e; e = e->ne) {
			if (e->c && d[u] + e->w < d[e->t]) {
				d[e->t] = d[u] + e->w;
				fr[e->t] = u;
				fe[e->t] = e;
				if (!inq[e->t]) {
					inq[q[tl ++] = e->t] = 1;
					QCHECK(tl);
				}
			}
		}
	}
	return d[te] < inf;
}

void buildGraph(int w, int nx) {
	++ w;
	int n(nx * w), m(n);
	ebuf = epool;
	memset(head, 0, sizeof(head));
	tn = 0;
	st = ++ tn, te = ++ tn;
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			ni[i][j] = ++ tn, ++ tn;
			addEdge(ni[i][j], ni[i][j] + 1, 1);
			if (i == 0 || i == n || j == 0 || j == m) {
				addEdge(ni[i][j] + 1, te, 1);
			}
			if (i % w == 0 && j % w == 0) {
				addEdge(st, ni[i][j], 1);
			}
		}
	}
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j < m; ++ j) {
			hi[i][j] = ++ tn, ++ tn;
			et[hi[i][j]] = addEdge(hi[i][j], hi[i][j] + 1, 1, 1);
			addEdge(ni[i][j] + 1, hi[i][j], inf);
			addEdge(hi[i][j] + 1, ni[i][j], inf);
			addEdge(ni[i][j + 1] + 1, hi[i][j], inf);
			addEdge(hi[i][j] + 1, ni[i][j + 1], inf);
		}
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			vi[i][j] = ++ tn, ++ tn;
			et[vi[i][j]] = addEdge(vi[i][j], vi[i][j] + 1, 1, 1);
			addEdge(ni[i][j] + 1, vi[i][j], inf);
			addEdge(vi[i][j] + 1, ni[i][j], inf);
			addEdge(ni[i + 1][j] + 1, vi[i][j], inf);
			addEdge(vi[i][j] + 1, ni[i + 1][j], inf);
		}
	}
}

int costFlow(int w, int nx) {
	buildGraph(w, nx);
	int s(0), c(0);
	while (SPFA()) {
		int cc(inf);
		for (int u = te; u != st; u = fr[u]) {
			cc = min(cc, fe[u]->c);
		}
		for (int u = te; u != st; u = fr[u]) {
			fe[u]->c -= cc, fe[u]->rv->c += cc;
			s += fe[u]->w * cc;
		}
		c += cc;
	}
	return s;
}

bool check(int w, int nx) {
	buildGraph(w, nx);
	int c(0);
	while (dinicBFS()) {
		c += dinicDFS(st, inf);
	}
	int res(c == (nx + 1) * (nx + 1));
	fprintf(stderr, "Checking w = %d, expected = %d, escaped = %d, status = %s\n", w, (nx + 1) * (nx + 1), c, res ? "Escaped" : "Died");
	return res;
}

void print(int n, int m, int w) {
	ofstream fout("out.ppm");
	int bls = 1366 / max(n, m);
	int rr = max(bls / 7, 1);
	Canvas c(bls * n + rr * 2, bls * n + rr * 2);
	c.lineWid = min(c.lineWid, rr / 2);
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			int co(1);
			if (i % w == 0 && j % w == 0) {
				co = 4;
			} else if (i == 0 || i == n || j == 0 || j == m) {
				co = 3;
			}
			c.circ(i * bls + rr, j * bls + rr, rr, co);
		}
	}
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j + 1 <= m; ++ j) {
			if (et[hi[i][j]]->rv->c) {
				c.line(i * bls + rr, j * bls + rr * 2, i * bls + rr, j * bls + bls, 2);
			}
		}
	}
	for (int i = 0; i + 1 <= n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			if (et[vi[i][j]]->rv->c) {
				c.line(i * bls + rr * 2, j * bls + rr, i * bls + bls, j * bls + rr, 2);
			}
		}
	}
	c.write(fout);
}

int binarySearch(int n) {
	int l(n / 16), r((n + 1));
	while (l < r) {
		int mid((l + r)>> 1);
		if (check(mid, n)) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}
//	check(l, n);
//	print((l + 1) * n + 1, (l + 1) * n + 1, l + 1);
	return l;
}

int main(int argc, char* args[]) {
	int n(10);
	for (int i = 1; i < argc; ++ i) {
		if (!strcmp(args[i], "-n") && i + 1 < argc) {
			n = atoi(args[++ i]);
		}
	}
	int ans;
	printf("n = %d, gridlines = %d\n", n, (ans = binarySearch(n)));
	int totlen(costFlow(ans, n));
	printf("total length = %d\n", totlen);
	print(n * (ans + 1), n * (ans + 1), ans + 1);
}

