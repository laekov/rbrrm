#ifndef FLOW_H
#define FLOW_H
#include <router.h>
#include <map>
class FlowRouter: public Router {
	protected:
		static const int inf = 0x3f3f3f3f;
		class Edge {
			public:
				int t, c, w;
				Edge *ne, *rv;
		};
		Edge *epool, *ebuf, **head, **et;
		int st, te, tn;
		int **ni, **hi, **vi;
		Edge* newEdge(int, int, int, int);
		Edge* addEdge(int, int, int, int = 0);
		void buildGraph();
	public:
		void print(std::ostream&);
		FlowRouter(): epool(0) {}
		~FlowRouter() {
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
			}
		}
};
#endif

