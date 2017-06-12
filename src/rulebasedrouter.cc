#include <rulebasedrouter.hh>
#include <flowsolver.hh>
#include <algorithm>

using std::max;
using std::min;
using std::swap;

FlowSolver* RuleBasedRouter::buildGraph(int w) {
	FlowSolver *fs(new FlowSolver(this->tn));
	int tn(0);
	this->st = ++ tn, this->te = ++ tn;
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

bool RuleBasedRouter::check(int w) {
	FlowSolver* fs(this->buildGraph(w));
	bool ret(fs->maxFlow(this->st, this->te) == (n - 1) * (m - 1));
	delete [] fs;
}

int RuleBasedRouter::getMinWidth() {
	int l(n / 16), r((m + 4) / 2);
	while (l < r) {
		int mid((l + r)>> 1);
		if (check(mid)) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}
	return this->w = l;
}

#define addDoubleEdge(u, v, c) { \
	fs.addEdge(u + 1, v, c, 0); \
	fs.addEdge(v + 1, u, c, 0); \
}

void RuleBasedRouter::detailBlock(LineArr& res, int bx, int by, int* dz, int* dp, int rv) {
	for (int i = 0; i < 4; ++ i) {
		int t(min(dz[i], dz[i + 4]));
		dz[i] -= t, dz[i + 4] -= t;
	}
	FlowSolver fs((w + 2)*(w + 2)* 8 + 7);
	int tn(0), st(++ tn), te(++ tn);
	for (int i = 0; i < w; ++ i) {
		for (int j = 0; j < w; ++ j) {
			di[i][j] = ++ tn, ++ tn;
			fs.addEdge(di[i][j], di[i][j] + 1, 1);
		}
	}
	for (int i = 0; i < w; ++ i) {
		for (int j = 0; j + 1 < w; ++ j) {
			ga[i][j] = ++ tn, ++ tn;
			et[ga[i][j]] = fs.addEdge(ga[i][j], ga[i][j] + 1, 1);
			addDoubleEdge(di[i][j], ga[i][j], 1);
			addDoubleEdge(di[i][j + 1], ga[i][j], 1);
		}
	}
	for (int i = 0; i + 1 < w; ++ i) {
		for (int j = 0; j < w; ++ j) {
			gb[i][j] = ++ tn, ++ tn;
			et[gb[i][j]] = fs.addEdge(gb[i][j], gb[i][j] + 1, 1);
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
					fs.addEdge(st, di[x][y], 1);
				} else if (dz[i + 4]) {
					fs.addEdge(di[x][y] + 1, te, 1);
				}
				if (i == 0) {
					res.push_back(LINEMK(POSMK(bx + x + 1, by + y), POSMK(bx + x + 1, by + y + 1)));
				} else if (i == 1) {
					res.push_back(LINEMK(POSMK(bx + x + 2, by + y), POSMK(bx + x + 2, by + y + 1)));
				} else if (i == 2) {
					res.push_back(LINEMK(POSMK(bx + x, by + y + 1), POSMK(bx + x + 1, by + y + 1)));
				} else if (i == 3) {
					res.push_back(LINEMK(POSMK(bx + x, by + y + 2), POSMK(bx + x + 1, by + y + 2)));
				}
			} else if (dz[i]) {
				fs.addEdge(st, di[x][y], 1);
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
	fs.minCost(st, te);
	for (int i = 0; i < w; ++ i) {
		for (int j = 0; j + 1 < w; ++ j) {
			if (fs.isEdgeUsed(et[ga[i][j]], ga[i][j])) {
				res.push_back(LINEMK(POSMK(bx + i + 1, by + j), POSMK(bx + i + 1, by + j + 1)));
			}
		}
	}
	for (int i = 0; i + 1 < w; ++ i) {
		for (int j = 0; j < w; ++ j) {
			if (fs.isEdgeUsed(et[gb[i][j]], gb[i][j])) {
				res.push_back(LINEMK(POSMK(bx + i, by + j + 1), POSMK(bx + i + 1, by + j + 1)));
			}
		}
	}
}

LineArr RuleBasedRouter::getModel() {
	LineArr res;
	FlowSolver* fs(this->buildGraph(this->w));
	fs->maxFlow(this->st, this->te);
	memset(osa, 0, sizeof(int) * this->tn);
	memset(ose, 0, sizeof(int) * this->tn);
	for (int i = 1; i < n; ++ i) {
		for (int j = 1; j < m; ++ j) {
			for (int k = 0; k < 2; ++ k) {
				int* e(eh[k][si[i][j]]);
				int tt(fs->getEdgeTarget(e));
				if (fs->isEdgeUsed(e, si[i][j])) {
					if (tt == vi[i - 1][j]) {
						ose[vi[i - 1][j]] = -1;
					} else if (tt == hi[i][j]) {
						osa[hi[i][j]] = -1;
					} else if (tt == vi[i][j]) {
						osa[vi[i][j]] = -1;
					} else if (tt == hi[i][j - 1]) {
						ose[hi[i][j - 1]] = -1;
					}
				}
			}
		}
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < m; ++ j) {
			int dz[8], dp[4];
			for (FlowSolver::Edge* e = fs->head[ni[i][j]]; e; e = e->ne) {
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
			for (FlowSolver::Edge* e = fs->head[ni[i][j] + 1]; e; e = e->ne) {
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
			detailBlock(res, i * (w + 1), j * (w + 1), dz, dp, (i ^ j)& 1);
		}
	}
	for (int i = 1; i < n; ++ i) {
		for (int j = 1; j < m; ++ j) {
			for (FlowSolver::Edge* e = fs->head[si[i][j]]; e; e = e->ne) {
				if (e->t != this->st && e->rv->c) {
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
					res.push_back(LINEMK(POSMK(i * (w + 1) + px * le, j * (w + 1) + py * le), POSMK(i * (w + 1), j * (w + 1))));
				}
			}
		}
	}
	return res;
}

