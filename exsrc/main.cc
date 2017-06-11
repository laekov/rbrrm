#include <bits/stdc++.h>
#include <canvas.h>

using namespace std;

typedef vector<pair<int, int> > LineArr;

#define POSMK(_a_,_b_) (((_a_)<<16)|(_b_))
#define POSX(_a_) ((_a_)>>16)
#define POSY(_a_) ((_a_)&0xffff)

const int maxa = 203;
const int maxn = maxa * maxa * 13;
const int maxe = maxn * 30;
const int inf = 0x3f3f3f3f;

struct Edge {
	int t, c, w, d;
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
	a->d = 1, b->d = 0;
	a->rv = b, b->rv = a;
	return a;
}

bool dinicBFS(int reqAll = 0) {
	static int q[maxn], fr[maxn];
	int hd(0), tl(1);
	++ tvis;
	d[q[hd] = st] = 1;
	vis[st] = tvis;
	while (hd < tl && (vis[te] < tvis || reqAll)) {
		int u(q[hd ++]);
		for (Edge* e = head[u]; e; e = e->ne) {
			if (((bool)e->c != (bool)reqAll) && (!reqAll || e->d) && vis[e->t] < tvis) {
				d[e->t] = d[u] + 1;
				vis[q[tl ++] = e->t] = tvis;
				fr[e->t] = u;
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

bool check(int w, int n, int m) {
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
			if ((i ^ j)& 1) {
				addEdge(si[i][j], hi[i][j - 1], 1);
				addEdge(si[i][j], hi[i][j], 1);
			} else {
				addEdge(si[i][j], vi[i - 1][j], 1);
				addEdge(si[i][j], vi[i][j], 1);
			}
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

int binarySearch(int n, int m) {
	int l(n / 16), r((m + 4) / 2);
	while (l < r) {
		int mid((l + r)>> 1);
		if (check(mid, n, m)) {
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

void detailBlock(LineArr& c, int w, int bx, int by, int* dz, int* dp, int rv) {
	for (int i = 0; i < 4; ++ i) {
		int t(min(dz[i], dz[i + 4]));
		dz[i] -= t, dz[i + 4] -= t;
	}
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
	int totc(0);
	while (dinicBFS()) {
		totc += dinicDFS(st, inf);
	}
	dinicBFS(1);
	if (totc < dz[0] + dz[1] + dz[2] + dz[3]) {
		fprintf(stderr, "Block error at (%d, %d)\n", bx / (w + 1), by / (w + 1));
		return;
	}
	for (int i = 0; i < w; ++ i) {
		for (int j = 0; j + 1 < w; ++ j) {
			if (vis[ga[i][j]] == tvis && et[ga[i][j]]->rv->c) {
				dh[i][j + 1] = 1;
			}
		}
	}
	for (int i = 0; i + 1 < w; ++ i) {
		for (int j = 0; j < w; ++ j) {
			if (vis[gb[i][j]] == tvis && et[gb[i][j]]->rv->c) {
				dv[i + 1][j] = 1;
			}
		}
	}
	for (int i = 0; i < w; ++ i) {
		for (int j = 0; j <= w; ++ j) {
			if (dh[i][j]) {
				c.push_back(pair<int, int>(POSMK(bx + i + 1, by + j), POSMK(bx + i + 1, by + j + 1)));
			}
		}
	}
	for (int i = 0; i <= w; ++ i) {
		for (int j = 0; j < w; ++ j) {
			if (dv[i][j]) {
				c.push_back(pair<int, int>(POSMK(bx + i, by + j + 1), POSMK(bx + i + 1, by + j + 1)));
			}
		}
	}
	tn = tno, ebuf = ebufo;
	st = sto, te = teo;
}

void detailAllBlocks(LineArr& res, int n, int m, int w) {
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
			detailBlock(res, w, i * (w + 1), j * (w + 1), dz, dp, (i ^ j)& 1);
		}
		if ((i & 13) == 0) {
			fprintf(stderr, "Processing line %d / %d\n", i, n);
		}
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
					res.push_back(pair<int, int>(POSMK(i * (w + 1) + px * le, j * (w + 1) + py * le), POSMK(i * (w + 1), j * (w + 1))));
				}
			}
		}
	}
}

void printPPM(int n, int m, int w, const LineArr& res) {
	fprintf(stderr, "Writing picture\n");
	ofstream fout("out.ppm");
	int bls(max(1366, n * (w + 1) * 2) / (n * (w + 1)));
	int rr = max(bls / 5, 1);
	Canvas c(bls * n * (w + 1) + 3, bls * m * (w + 1) + 3);
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
	for (LineArr::const_iterator it = res.begin(); it != res.end(); ++ it) {
		c.line(POSX(it->first) * bls, POSY(it->first) * bls, POSX(it->second) * bls, POSY(it->second) * bls, 2);
	}
	c.write(fout);
	fout.close();
	fprintf(stderr, "Picture written to out.ppm\n");
}

void testGrid(int n, int w) {
	ebuf = epool;
	int m(n);
	ofstream fout("gridout.ppm");
	int bls(max(1366, n * (w + 1) * 2) / (n * (w + 1)));
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
	int dz[8], dp[4];
	memset(dz, 0, sizeof(dz));
	dz[0] = 13;
	dz[6] = 3;
	dz[3] = 3;
	dz[5] = 15;
	memset(dp, 0, sizeof(dp));
	//printGrid(c, w, 0, 0, dz, dp, (0 ^ 1)& 1);
	c.write(fout);
	fout.close();
}

void printCoor(int n, int m, int w, const LineArr& ans) {
	fprintf(stderr, "Writing coordinates\n");
	FILE* fout(fopen("out.txt", "w"));
	fprintf(fout, "%d %d %d\n", n, m, w);
	for (LineArr::const_iterator it = ans.begin(); it != ans.end(); ++ it) {
		fprintf(fout, "%d %d\n", it->first, it->second);
	}
	fclose(fout);
	fprintf(stderr, "Written coordinates to out.txt\n");
}

int main(int argc, char* args[]) {
	int n(30), m(-1);
	int testGridW(0);
	int printPic(0);
	int outppm(0);
	int outcoor(0);
	memset(vis, 0, sizeof(vis));
	tvis = 0;
	for (int i = 1; i < argc; ++ i) {
		if (!strcmp(args[i], "-n") && i + 1 < argc) {
			n = atoi(args[++ i]);
		} else if (!strcmp(args[i], "-m") && i + 1 < argc) {
			m = atoi(args[++ i]);
		} else if (!strcmp(args[i], "--no-pic")) {
			printPic = 0;
		} else if (!strcmp(args[i], "--test-grid") && i + 1 < argc) {
			testGridW = atoi(args[++ i]);
		} else if (!strcmp(args[i], "--out-coor")) {
			outcoor = 1;
			printPic = 1;
		} else if (!strcmp(args[i], "--out-ppm")) {
			outppm = 1;
			printPic = 1;
		}
	}
	if (m == -1) {
		m = n;
	} else if (n > m) {
		swap(n, m);
	}
	if (testGridW) {
		n = 1;
		testGrid(n, testGridW);
	} else {
		int ans;
		printf("n = %d, m = %d, gridlines = %d\n", n, m, (ans = binarySearch(n, m)));
		LineArr res;
		if (printPic) {
			check(ans, n, m);
			detailAllBlocks(res, n, m, ans);
		}
		if (outppm) {
			printPPM(n, m, ans, res);
		}
		if (outcoor) {
			printCoor(n, m, ans, res);
		}
	}
}

