#include <bits/stdc++.h>
#include <canvas.h>

using namespace std;

const int maxa = 203;
const int maxn = maxa * maxa * 13;
const int maxe = maxn * 10;
const int inf = 0x3f3f3f3f;

struct Edge {
	int t, c, w;
	Edge *ne, *rv;
};
Edge epool[maxe], *ebuf, *head[maxn], *et[maxn];
int vis[maxn], tvis;
int st, te, tn, n, d[maxn];
int ni[maxa][maxa], hi[maxa][maxa], vi[maxa][maxa], pi[maxa][maxa], si[maxa][maxa];
int osa[maxn], ose[maxn];

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
	++ tvis;
	d[q[hd] = st] = 1;
	vis[st] = tvis;
	while (hd < tl && vis[te] < tvis) {
		int u(q[hd ++]);
		for (Edge* e = head[u]; e; e = e->ne) {
			if (e->c && vis[e->t] < tvis) {
				d[e->t] = d[u] + 1;
				vis[q[tl ++] = e->t] = tvis;
			}
		}
	}
	return vis[te] == tvis;
}

int dinicDFS(int u, int c) {
	int s(0);
	if (u == te) {
		return c;
	}
	for (Edge* e = head[u]; e && c; e = e->ne) {
		if (e->c && vis[e->t] == tvis && d[e->t] == d[u] + 1) {
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
	fprintf(stderr, "Checking w = %d, expected = %d", w, (n - 1) * (m - 1));
	while (dinicBFS()) {
		c += dinicDFS(st, inf);
	}
	int res(c == (n - 1) * (m - 1));
	fprintf(stderr, ", escaped = %d, status = %s\n", c, res ? "Escaped" : "Died");
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

const int maxb = 53;
int di[maxb][maxb], ga[maxb][maxb], gb[maxb][maxb], dv[maxb][maxb], dh[maxb][maxb];

inline void addDoubleEdge(int u, int v, int c, int w = 0) {
	addEdge(u + 1, v, c, w);
	addEdge(v + 1, u, c, w);
}

void printGrid(Canvas& c, int w, int bx, int by, int bls, int rr, int* dz, int* dp, int rv) {
	memset(dv, 0, sizeof(dv));
	memset(dh, 0, sizeof(dh));
	int tno(tn);
	int sto(st), teo(te);
	Edge* ebufo(ebuf);
	head[st = ++ tn] = 0;
	head[te = ++ tn] = 0;
	for (int i = 0; i < w; ++ i) {
		for (int j = 0; j < w; ++ j) {
			head[di[i][j] = ++ tn] = 0, head[++ tn] = 0;
			addEdge(di[i][j], di[i][j] + 1, 1);
		}
	}
	for (int i = 0; i < w; ++ i) {
		for (int j = 0; j + 1 < w; ++ j) {
			head[ga[i][j] = ++ tn] = 0, head[++ tn] = 0;
			et[ga[i][j]] = addEdge(ga[i][j], ga[i][j] + 1, 1);
			addDoubleEdge(di[i][j], ga[i][j], 1);
			addDoubleEdge(di[i][j + 1], ga[i][j], 1);
		}
	}
	for (int i = 0; i + 1 < w; ++ i) {
		for (int j = 0; j < w; ++ j) {
			head[gb[i][j] = ++ tn] = 0, head[++ tn] = 0;
			et[gb[i][j]] = addEdge(gb[i][j], gb[i][j] + 1, 1);
			addDoubleEdge(gb[i][j], di[i + 1][j], 1);
			addDoubleEdge(gb[i][j], di[i][j], 1);
		}
	}
	static const int bxs[2][4] = { { 0, 1, 1, 0 }, { 0, 1, 0, 1 } };
	static const int bys[2][4] = { { 0, 1, 0, 1 }, { 1, 0, 0, 1 } };
	static const int mxs[2][4] = { { 0, 0, -1, 1 }, { 0, 0, 1, -1 } };
	static const int mys[2][4] = { { 1, -1, 0, 0 }, { -1, 1, 0, 0 } };
	for (int i = 0; i < 4; ++ i) {
		int x(bxs[rv][i] * (w - 1)), y(bys[rv][i] * (w - 1));
		int *osap(osa), *osep(ose);
		if (mxs[rv][i] == -1 || mys[rv][i] == -1) {
			swap(osap, osep);
		}
		int e = max(dz[i], dz[i + 4]);
		if (dz[i + 4]) {
			if (osap[dp[i]]) {
				++ e;
			}
			if (osep[dp[i]]) {
				++ e;
			}
		}
		for (int j = 0; j < e; ++ j) {
			if (dz[i] || !((osap[dp[i]] && j == 0) || (osep[dp[i]] && j == e - 1))) {
				if (dz[i]) {
					addEdge(st, di[x][y], 1);
				} else if (dz[i + 4]) {
					addEdge(di[x][y] + 1, te, 1);
				}
				if (i == 0) {
					dv[x][y] = 1;
				} else if (i == 1) {
					dv[x + 1][y] = 1;
				} else if (i == 2) {
					dh[x][y] = 1;
				} else if (i == 3) {
					dh[x][y + 1] = 1;
				}
			} else if (dz[i]) {
				addEdge(st, di[x][y], 1);
			}
			x += mxs[rv][i];
			y += mys[rv][i];
		}
		if (dz[i]) {
			if (osap[dp[i]]) {
				osap[dp[i]] = 1;
			}
			if (osep[dp[i]]) {
				osep[dp[i]] = w + 1 - max(dz[i], dz[i + 4]);
			}
		}
	}
	while (dinicBFS()) {
		dinicDFS(st, inf);
	}
	for (int i = 0; i < w; ++ i) {
		for (int j = 0; j + 1 < w; ++ j) {
			if (et[ga[i][j]]->rv->c) {
				dh[i][j + 1] = 1;
			}
		}
	}
	for (int i = 0; i + 1 < w; ++ i) {
		for (int j = 0; j < w; ++ j) {
			if (et[gb[i][j]]->rv->c) {
				dv[i + 1][j] = 1;
			}
		}
	}
	for (int i = 0; i < w; ++ i) {
		for (int j = 0; j <= w; ++ j) {
			if (dh[i][j]) {
				c.line(bx + (i + 1) * bls, by + j * bls, bx + (i + 1) * bls, by + (j + 1) * bls, 2);
			}
		}
	}
	for (int i = 0; i <= w; ++ i) {
		for (int j = 0; j < w; ++ j) {
			if (dv[i][j]) {
				c.line(bx + i * bls, by + (j + 1) * bls, bx + (i + 1) * bls, by + (j + 1) * bls, 2);
			}
		}
	}
	tn = tno, ebuf = ebufo;
	st = sto, te = teo;
}

void printPPM(int n, int w) {
	ofstream fout("out.ppm");
	int bls(max(1366, n * (w + 1) * 2) / (n * (w + 1))), m(n);
	int rr = max(bls / 5, 1);
	Canvas c(bls * n * (w + 1) + 3, bls * n * (w + 1) + 3);
	c.lineWid = min(c.lineWid, rr / 2);
	for (int i = 0; i <= n * (w + 1); ++ i) {
		c.circ(i * bls, 0, rr, 3);
		c.circ(0, i * bls, rr, 3);
		c.circ(i * bls, m * (w + 1) * bls, rr, 3);
		c.circ(n * (w + 1) * bls, i * bls, rr, 3);
	}
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			c.circ(i * (w + 1) * bls, j * (w + 1) * bls, rr, 4);
		}
	}
	memset(osa, 0, sizeof(osa));
	memset(ose, 0, sizeof(ose));
	for (int i = 1; i < n; ++ i) {
		for (int j = 1; j < m; ++ j) {
			for (Edge* e = head[si[i][j]]; e; e = e->ne) {
				if (e->t != st && e->rv->c) {
					if (e->t == vi[i - 1][j]) {
						ose[vi[i - 1][j]] = -1;
					} else if (e->t == hi[i][j]) {
						osa[hi[i][j]] = -1;
					} else if (e->t == vi[i][j]) {
						osa[vi[i][j]] = -1;
					} else if (e->t == hi[i][j - 1]) {
						ose[hi[i][j - 1]] = -1;
					}
				}
			}
		}
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < m; ++ j) {
			int dz[8], dp[4];
			for (Edge* e = head[ni[i][j]]; e; e = e->ne) {
				if (e->t == hi[i][j] + 1) {
					dz[0] = e->c;
				} else if (e->t == hi[i + 1][j] + 1) {
					dz[1] = e->c;
				} else if (e->t == vi[i][j] + 1) {
					dz[2] = e->c;
				} else if (e->t == vi[i][j + 1] + 1) {
					dz[3] = e->c;
				}
			}
			for (Edge* e = head[ni[i][j] + 1]; e; e = e->ne) {
				if (e->t == hi[i][j]) {
					dz[4] = e->rv->c;
				} else if (e->t == hi[i + 1][j]) {
					dz[5] = e->rv->c;
				} else if (e->t == vi[i][j]) {
					dz[6] = e->rv->c;
				} else if (e->t == vi[i][j + 1]) {
					dz[7] = e->rv->c;
				}
			}
			dp[0] = hi[i][j];
			dp[1] = hi[i + 1][j];
			dp[2] = vi[i][j];
			dp[3] = vi[i][j + 1];
			printGrid(c, w, i * (w + 1) * bls, j * (w + 1) * bls, bls, rr, dz, dp, (i ^ j)& 1);
		}
		fprintf(stderr, "Processing grid line %d\n", i);
	}
	for (int i = 1; i < n; ++ i) {
		for (int j = 1; j < m; ++ j) {
			for (Edge* e = head[si[i][j]]; e; e = e->ne) {
				if (e->t != st && e->rv->c) {
					int px(0), py(0), le(0);
					if (e->t == vi[i - 1][j]) {
						px = -1;
						le = ose[vi[i - 1][j]];
					} else if (e->t == hi[i][j]) {
						py = 1;
						le = osa[hi[i][j]];
					} else if (e->t == vi[i][j]) {
						px = 1;
						le = osa[vi[i][j]];
					} else if (e->t == hi[i][j - 1]) {
						py = -1;
						le = ose[hi[i][j - 1]];
					}
					c.line(i * (w + 1) * bls + bls * px * le, j * (w + 1) * bls + bls * py * le, i * (w + 1) * bls, j * (w + 1) * bls, 2);
				}
			}
		}
	}
	c.write(fout);
	fout.close();
}

int main(int argc, char* args[]) {
	int n(30);
	memset(vis, 0, sizeof(vis));
	tvis = 0;
	for (int i = 1; i < argc; ++ i) {
		if (!strcmp(args[i], "-n") && i + 1 < argc) {
			n = atoi(args[++ i]);
		}
	}
	int ans;
	printf("n = %d, gridlines = %d\n", n, (ans = binarySearch(n)));
	check(ans, n);
	printPPM(n, ans);
}

