#include <forcerouter.hh>
#include <flowsolver.hh>

FlowSolver* ForceRouter::buildGraph(int w) {
	++ w;
	int n(this->n * w), m(this->m * w);
	int tn(0);
	this->st = ++ tn, this->te = ++ tn;
	FlowSolver *fs(new FlowSolver(this->tn));
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			ni[i][j] = ++ tn, ++ tn;
			fs->addEdge(ni[i][j], ni[i][j] + 1, 1);
			if (i == 0 || i == n || j == 0 || j == m) {
				fs->addEdge(ni[i][j] + 1, te, 1);
			}
			if (i % w == 0 && j % w == 0) {
				fs->addEdge(st, ni[i][j], 1);
			}
		}
	}
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j < m; ++ j) {
			hi[i][j] = ++ tn, ++ tn;
			et[hi[i][j]] = fs->addEdge(hi[i][j], hi[i][j] + 1, 1, 1);
			fs->addEdge(ni[i][j] + 1, hi[i][j], inf);
			fs->addEdge(hi[i][j] + 1, ni[i][j], inf);
			fs->addEdge(ni[i][j + 1] + 1, hi[i][j], inf);
			fs->addEdge(hi[i][j] + 1, ni[i][j + 1], inf);
		}
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			vi[i][j] = ++ tn, ++ tn;
			et[vi[i][j]] = fs->addEdge(vi[i][j], vi[i][j] + 1, 1, 1);
			fs->addEdge(ni[i][j] + 1, vi[i][j], inf);
			fs->addEdge(vi[i][j] + 1, ni[i][j], inf);
			fs->addEdge(ni[i + 1][j] + 1, vi[i][j], inf);
			fs->addEdge(vi[i][j] + 1, ni[i + 1][j], inf);
		}
	}
	return fs;
}

bool ForceRouter::check(int w) {
	FlowSolver* fs(this->buildGraph(this->w));
	int expectedFlow((n + 1) * (m + 1));
	return fs->maxFlow(this->st, this->te) == expectedFlow;
}

int ForceRouter::getMinWidth() {
	int l(n / 16), r((m + 7)/ 2);
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

LineArr ForceRouter::getModel() {
	LineArr res;
	FlowSolver* fs(this->buildGraph(this->w));
	fs->minCost(this->st, this->te);
	for (int i = 0; i <= n * (w + 1); ++ i) {
		for (int j = 0; j < m * (w + 1); ++ j) {
			if (fs->isEdgeUsed(et[hi[i][j]], hi[i][j])) {
				res.push_back(LINEMK(POSMK(i, j), POSMK(i, j + 1)));
			}
		}
	}
	for (int i = 0; i < n * (w + 1); ++ i) {
		for (int j = 0; j <= m * (w + 1); ++ j) {
			if (fs->isEdgeUsed(et[vi[i][j]], vi[i][j])) {
				res.push_back(LINEMK(POSMK(i, j), POSMK(i + 1, j)));
			}
		}
	}
	delete fs;
	return res;
}

