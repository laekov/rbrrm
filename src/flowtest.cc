#include <cstdio>
#include <flowsolver.hh>

const int maxa = 203;
const int maxn = maxa * maxa * 13;
const int maxe = maxn * 30;
const int inf = 0x3f3f3f3f;

int n, m;
int ni[maxa][maxa], hi[maxa][maxa], vi[maxa][maxa], pi[maxa][maxa], si[maxa][maxa];
int osa[maxn], ose[maxn], *eh[2][maxn], *et[maxn], st, te;

FlowSolver* buildGraph(int w) {
	FlowSolver *fs(new FlowSolver(n * m * 9));
	int tn(0);
	st = ++ tn, te = ++ tn;
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < m; ++ j) {
			ni[i][j] = ++ tn, ++ tn;
			et[ni[i][j]] = fs->addEdge(ni[i][j], ni[i][j] + 1, w);
		}
	}
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j < m; ++ j) {
			hi[i][j] = ++ tn, ++ tn;
			et[hi[i][j]] = fs->addEdge(hi[i][j], hi[i][j] + 1, w);
			if (i > 0) {
				fs->addEdge(ni[i - 1][j] + 1, hi[i][j], inf);
				fs->addEdge(hi[i][j] + 1, ni[i - 1][j], inf);
			} else {
				fs->addEdge(hi[i][j] + 1, te, inf);
			}
			if (i < n) {
				fs->addEdge(ni[i][j] + 1, hi[i][j], inf);
				fs->addEdge(hi[i][j] + 1, ni[i][j], inf);
			} else {
				fs->addEdge(hi[i][j] + 1, te, inf);
			}
		}
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			vi[i][j] = ++ tn, ++ tn;
			et[vi[i][j]] = fs->addEdge(vi[i][j], vi[i][j] + 1, w);
			if (j > 0) {
				fs->addEdge(ni[i][j - 1] + 1, vi[i][j], inf);
				fs->addEdge(vi[i][j] + 1, ni[i][j - 1], inf);
			} else {
				fs->addEdge(vi[i][j] + 1, te, inf);
			}
			if (j < m) {
				fs->addEdge(ni[i][j] + 1, vi[i][j], inf);
				fs->addEdge(vi[i][j] + 1, ni[i][j], inf);
			} else {
				fs->addEdge(vi[i][j] + 1, te, inf);
			}
		}
	}
	for (int i = 1; i < n; ++ i) {
		for (int j = 1; j < m; ++ j) {
			si[i][j] = ++ tn;
			et[si[i][j]] = fs->addEdge(st, tn, 1);
			if ((i ^ j)& 1) {
				eh[0][si[i][j]] = fs->addEdge(si[i][j], hi[i][j - 1], 1);
				eh[1][si[i][j]] = fs->addEdge(si[i][j], hi[i][j], 1);
			} else {
				eh[0][si[i][j]] = fs->addEdge(si[i][j], vi[i - 1][j], 1);
				eh[1][si[i][j]] = fs->addEdge(si[i][j], vi[i][j], 1);
			}
		}
	}
	return fs;
}

void solve() {
	n = m = 3;
	FlowSolver* fs(buildGraph(3));
	printf("%d\n", fs->maxFlow(st, te));
	delete fs;
	printf("Done\n");
}

int main() {
	solve();
}
