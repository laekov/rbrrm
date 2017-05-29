#include <dinic.h>
#include <cstring>
#include <algorithm>
#include <common.h>

using std::min;

bool DinicFlowRouter::BFS() {
	int hd(0), tl(1);
	memset(this->d, 0, sizeof(int) * this->tn);
	this->d[this->q[hd] = st] = 1;
	while (hd < tl && !this->d[te]) {
		int u(this->q[hd ++]);
		for (Edge* e = this->head[u]; e; e = e->ne) {
			if (e->c && !this->d[e->t]) {
				this->d[e->t] = this->d[u] + 1;
				this->q[tl ++] = e->t;
			}
		}
	}
	return this->d[te];
}

int DinicFlowRouter::DFS(int u, int c) {
	int s(0);
	if (u == this->te) {
		return c;
	}
	for (Edge* e = this->head[u]; e && c; e = e->ne) {
		if (e->c && this->d[e->t] == this->d[u] + 1) {
			int x(this->DFS(e->t, min(c, e->c)));
			e->c -= x, e->rv->c += x;
			s += x, c -= x;
		}
	}
	if (c) {
		this->d[u] = 0;
	}
	return s;
}

void DinicFlowRouter::solve() {
	this->buildGraph();
	this->d = new int[this->tn];
	this->q = new int[this->tn];
	int c(0), s(0);
	while (this->BFS()) {
		c += this->DFS(this->st, this->inf);
	}
	for (int i = 0; i < this->n; ++ i) {
		for (int j = 0; j + 1 < this->m; ++ j) {
			if (!this->et[this->hi[i][j]]->c) {
				++ s;
			}
		}
	}
	for (int i = 0; i + 1 < this->n; ++ i) {
		for (int j = 0; j < this->m; ++ j) {
			if (!this->et[this->vi[i][j]]->c) {
				++ s;
			}
		}
	}
	delete [] this->d;
	delete [] this->q;
}

// REGISTERROUTER("dinic", DinicFlowRouter);
