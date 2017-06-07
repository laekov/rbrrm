#include <bits/stdc++.h>

using namespace std;

const int maxa = 103;
const int maxn = maxa * maxa * 13;
const int maxe = maxn * 10;
const int inf = 0x3f3f3f3f;

struct Edge {
	int t, c, w;
	Edge *ne, *rv;
};
Edge epool[maxe], *ebuf, *head[maxn], *et[maxn];
int st, te, tn, n, d[maxn];
int ni[maxa][maxa], hi[maxa][maxa], vi[maxa][maxa], pi[maxa][maxa], si[maxa][maxa];

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

bool check(int w, int n) {
	int m(n);
	ebuf = epool;
	memset(head, 0, sizeof(head));
	tn = 0;
	st = ++ tn, te = ++ tn;
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < m; ++ j) {
			ni[i][j] = ++ tn, ++ tn;
			et[ni[i][j]] = addEdge(ni[i][j], ni[i][j] + 1, w);
		}
	}
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j < m; ++ j) {
			hi[i][j] = ++ tn, ++ tn;
			et[hi[i][j]] = addEdge(hi[i][j], hi[i][j] + 1, w);
			if (i > 0) {
				addEdge(ni[i - 1][j] + 1, hi[i][j], inf);
				addEdge(hi[i][j] + 1, ni[i - 1][j], inf);
			} else {
				addEdge(hi[i][j] + 1, te, inf);
			}
			if (i < n) {
				addEdge(ni[i][j] + 1, hi[i][j], inf);
				addEdge(hi[i][j] + 1, ni[i][j], inf);
			} else {
				addEdge(hi[i][j] + 1, te, inf);
			}
		}
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			vi[i][j] = ++ tn, ++ tn;
			et[vi[i][j]] = addEdge(vi[i][j], vi[i][j] + 1, w);
			if (j > 0) {
				addEdge(ni[i][j - 1] + 1, vi[i][j], inf);
				addEdge(vi[i][j] + 1, ni[i][j - 1], inf);
			} else {
				addEdge(vi[i][j] + 1, te, inf);
			}
			if (j < m) {
				addEdge(ni[i][j] + 1, vi[i][j], inf);
				addEdge(vi[i][j] + 1, ni[i][j], inf);
			} else {
				addEdge(vi[i][j] + 1, te, inf);
			}
		}
	}
	for (int i = 1; i < n; ++ i) {
		for (int j = 1; j < m; ++ j) {
			si[i][j] = ++ tn;
			et[si[i][j]] = addEdge(st, tn, 1);
			addEdge(si[i][j], vi[i - 1][j], 1);
			addEdge(si[i][j], vi[i][j], 1);
			addEdge(si[i][j], hi[i][j - 1], 1);
			addEdge(si[i][j], hi[i][j], 1);
		}
	}
	int c(0);
	while (dinicBFS()) {
		c += dinicDFS(st, inf);
	}
	int res(c == (n - 1) * (m - 1));
	fprintf(stderr, "Checking w = %d, expected = %d, escaped = %d, status = %s\n", w, (n - 1) * (m - 1), c, res ? "Escaped" : "Died");
	if (0) {
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < m; ++ j) {
				if (i && j) {
					printf("%c ", et[si[i][j]]->rv->c ? '.' : 'x');
				} else {
					printf("  ");
				}
				printf("%d ", et[hi[i][j]]->rv->c);
			}
			putchar(10);
			for (int j = 0; j < m; ++ j) {
				printf("%d %d ", et[vi[i][j]]->rv->c, et[ni[i][j]]->rv->c);
			}
			printf("%d", et[vi[i][m]]->rv->c);
			putchar(10);
		} {
			for (int j = 0; j < m; ++ j) {
				printf("  %d ", et[hi[n][j]]->rv->c);
			}
			putchar(10);
		}
	}
	return res;
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
	return l;
}

int main(int argc, char* args[]) {
	int n(30);
	for (int i = 1; i < argc; ++ i) {
		if (!strcmp(args[i], "-n") && i + 1 < argc) {
			n = atoi(args[++ i]);
		}
	}
	printf("n = %d, gridlines = %d\n", n, binarySearch(n));
}

