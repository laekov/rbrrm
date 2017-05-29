#include <flow.h>
#include <canvas.h>
#include <algorithm>

using std::max;
using std::min;

void FlowRouter::print(std::ostream& fout) {
	int bls = 1366 / max(this->n, this->m);
	int rr = max(bls / 7, 1);
	Canvas c(bls * (n - 1) + rr * 2, bls * (m - 1) + rr * 2);
	c.lineWid = min(c.lineWid, rr / 2);
	for (int i = 0; i < this->n; ++ i) {
		for (int j = 0; j < this->m; ++ j) {
			int co(1);
			if (this->g[i][j] == 'i') {
				co = 4;
			} else if (this->g[i][j] == 'o') {
				co = 3;
			}
			c.circ(i * bls + rr, j * bls + rr, rr, co);
		}
	}
	for (int i = 0; i < this->n; ++ i) {
		for (int j = 0; j + 1 < this->m; ++ j) {
			if (!this->et[this->hi[i][j]]->c) {
				c.line(i * bls + rr, j * bls + rr * 2, i * bls + rr, j * bls + bls, 2);
			}
		}
	}
	for (int i = 0; i + 1 < this->n; ++ i) {
		for (int j = 0; j < this->m; ++ j) {
			if (!this->et[this->vi[i][j]]->c) {
				c.line(i * bls + rr * 2, j * bls + rr, i * bls + bls, j * bls + rr, 2);
			}
		}
	}
	c.write(fout);
}

FlowRouter::Edge* FlowRouter::newEdge(int u, int v, int c, int w) {
	this->ebuf->t = v;
	this->ebuf->c = c;
	this->ebuf->w = w;
	this->ebuf->ne = this->head[u];
	return this->head[u] = this->ebuf ++;
}

FlowRouter::Edge* FlowRouter::addEdge(int u, int v, int c, int w) {
	Edge *a(this->newEdge(u, v, c, w)), *b(this->newEdge(v, u, 0, -w));
	a->rv = b, b->rv = a;
	return a;
}

void FlowRouter::buildGraph() {
	this->clean();
	this->ebuf = this->epool = new Edge[n * m * 24];
	this->head = new Edge*[n * m * 6 + 3];
	this->et = new Edge*[n * m * 6 + 3];
	int tn(0);
	memset(head, 0, sizeof(Edge*) * (n * m * 6 + 3));
	this->st = ++ tn, this->te = ++ tn;
	this->ni = new int*[this->n];
	for (int i = 0; i < this->n; ++ i) {
		this->ni[i] = new int[this->m];
		for (int j = 0; j < this->m; ++ j) {
			this->ni[i][j] = ++ tn, ++ tn;
			this->addEdge(this->ni[i][j], this->ni[i][j] + 1, 1);
			if (this->g[i][j] == 'i') {
				this->addEdge(this->st, this->ni[i][j], 1);
			} else if (this->g[i][j] == 'o') {
				this->addEdge(this->ni[i][j] + 1, this->te, 1);
			}
		}
	}
	this->hi = new int*[this->n];
	for (int i = 0; i < this->n; ++ i) {
		this->hi[i] = new int[this->m - 1];
		for (int j = 0; j + 1 < this->m; ++ j) {
			this->hi[i][j] = ++ tn, ++ tn;
			this->et[this->hi[i][j]] = this->addEdge(this->hi[i][j], this->hi[i][j] + 1, 1, 1);
			this->addEdge(this->ni[i][j] + 1, this->hi[i][j], 1);
			this->addEdge(this->hi[i][j] + 1, this->ni[i][j], 1);
			this->addEdge(this->ni[i][j + 1] + 1, this->hi[i][j], 1);
			this->addEdge(this->hi[i][j] + 1, this->ni[i][j + 1], 1);
		}
	}
	this->vi = new int*[this->n - 1];
	for (int i = 0; i + 1 < this->n; ++ i) {
		this->vi[i] = new int[this->m];
		for (int j = 0; j < this->m; ++ j) {
			this->vi[i][j] = ++ tn, ++ tn;
			this->et[this->vi[i][j]] = this->addEdge(this->vi[i][j], this->vi[i][j] + 1, 1, 1);
			this->addEdge(this->ni[i][j] + 1, this->vi[i][j], 1);
			this->addEdge(this->vi[i][j] + 1, this->ni[i][j], 1);
			this->addEdge(this->ni[i + 1][j] + 1, this->vi[i][j], 1);
			this->addEdge(this->vi[i][j] + 1, this->ni[i + 1][j], 1);
		}
	}
	this->tn = tn + 1;
}

void FlowRouter::clean() {
	if (this->epool) {
		delete [] this->epool;
		delete [] this->head;
		delete [] this->et;
		for (int i = 0; i < this->n; ++ i) {
			delete [] this->ni[i];
		}
		delete [] this->ni;
		for (int i = 0; i < this->n; ++ i) {
			delete [] this->hi[i];
		}
		delete [] this->hi;
		for (int i = 0; i + 1 < this->n; ++ i) {
			delete [] this->vi[i];
		}
		delete [] this->vi;
		this->epool = 0;
	}
}
