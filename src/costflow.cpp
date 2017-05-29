#include <costflow.h>
#include <cstring>
#include <algorithm>

using std::min;

#define QCHECK(_x_) { \
	if ((_x_) == this->tn) { \
		_x_ = 0; \
	} \
}
bool CostFlowRouter::SPFA() {
	int hd(0), tl(1);
	memset(this->inq, 0, sizeof(int) * this->tn);
	memset(this->d, 0x3f, sizeof(int) * this->tn);
	this->d[this->q[hd] = this->st] = 0;
	this->inq[this->st] = 1;
	while (hd < tl) {
		int u(this->q[hd ++]);
		this->inq[u] = 0;
		QCHECK(hd);
		for (Edge* e = this->head[u]; e; e = e->ne) {
			if (e->c && this->d[u] + e->w < this->d[e->t]) {
				this->d[e->t] = this->d[u] + e->w;
				this->fr[e->t] = u;
				this->fe[e->t] = e;
				if (!this->inq[e->t]) {
					this->inq[this->q[tl ++] = e->t] = 1;
					QCHECK(tl);
				}
			}
		}
	}
	return this->d[te] < this->inf;
}

void CostFlowRouter::solve() {
	this->buildGraph();
	this->fr = new int[this->tn];
	this->q = new int[this->tn];
	this->inq = new int[this->tn];
	this->d = new int[this->tn];
	this->fe = new Edge*[this->tn];
	int s(0), c(0);
	while (this->SPFA()) {
		int cc(this->inf);
		for (int u = this->te; u != this->st; u = this->fr[u]) {
			cc = min(cc, this->fe[u]->c);
		}
		for (int u = this->te; u != this->st; u = this->fr[u]) {
			this->fe[u]->c -= cc, this->fe[u]->rv->c += cc;
			s += this->fe[u]->w * cc;
		}
		c += cc;
	}
	delete [] this->fr;
	delete [] this->q;
	delete [] this->inq;
	delete [] this->d;
	delete [] this->fe;
}

