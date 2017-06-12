#include <flowsolver.hh>
#include <queue>
#include <algorithm>

using std::queue;
using std::max;
using std::min;

bool FlowSolver::SPFA() {
	queue<int> q;
	d[st] = 0;
	inq[st] = 1;
	q.push(st);
	vis[st] = ++ tvis;
	while (!q.empty()) {
		int u(q.front());
		q.pop();
		inq[u] = 0;
		for (Edge* e = head[u]; e; e = e->ne) {
			if (e->c && (vis[e->t] < tvis || d[u] + e->w < d[e->t])) {
				vis[e->t] = tvis;
				d[e->t] = d[u] + e->w;
				fr[e->t] = u;
				fe[e->t] = e;
				inq[e->t] = 1;
				q.push(e->t);
			}
		}
	}
	return vis[te] == tvis;
}

bool FlowSolver::BFS(int reqAll) {
	queue<int> q;
	++ tvis;
	q.push(st);
	d[st] = 1;
	vis[st] = tvis;
	while (!q.empty() && (vis[te] < tvis || reqAll)) {
		int u(q.front());
		q.pop();
		for (Edge* e = head[u]; e; e = e->ne) {
			if (((bool)e->c != (bool)reqAll) && (!reqAll || e->d) && vis[e->t] < tvis) {
				d[e->t] = d[u] + 1;
				vis[e->t] = tvis;
				fr[e->t] = u;
				q.push(e->t);
			}
		}
	}
	return vis[te] == tvis;
}
 
int FlowSolver::DFS(int u, int c) {
	int s(0);
	if (u == te) {
		return c;
	}
	for (Edge* e = head[u]; e && c; e = e->ne) {
		if (e->c && vis[e->t] == tvis && d[e->t] == d[u] + 1) {
			int x(DFS(e->t, min(c, e->c)));
			e->c -= x, e->rv->c += x;
			s += x, c -= x;
		}
	}
	if (c) {
		d[u] = 0;
	}
	return s;
}

int* FlowSolver::addEdge(int u, int v, int c, int w) {
	FlowSolver::Edge *a(this->newEdge(u, v, c, w)), *b(this->newEdge(v, u, 0, -w));
	a->d = 1, b->d = 0;
	a->rv = b, b->rv = a;
	return (int*)a;
}

int FlowSolver::maxFlow(int st_, int te_) {
	st = st_, te = te_;
	this->delooped = false;
	int c(0);
	while (BFS()) {
		c += DFS(st, inf);
	}
	return c;
}

int FlowSolver::minCost(int st_, int te_) {
	int s(0), c(0);
	while (SPFA()) {
		int cc(FlowSolver::inf);
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

