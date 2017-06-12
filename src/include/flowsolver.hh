/* Network flow solver
 * Provide both min-cut and min-cost models
 */
#ifndef FLOW_SOLVER_HH
#define FLOW_SOLVER_HH

#include <cstring>
#include <vector>

class FlowSolver {
	protected:
		static const int inf = 0x3f3f3f3f;
		static const int epoolsize = 1023;
		struct Edge {
			int t, c, w, d;
			Edge *ne, *rv;
		};
		Edge *epool, *ebuf, **head, **fe;
		std::vector<Edge*> pools;
		int *vis, tvis;
		int *d, *fr, st, te, *inq;
		int delooped, tn;
		inline Edge* newEdge(int u, int v, int c, int w) {
			if (ebuf - epool == epoolsize) {
				this->pools.push_back(ebuf = epool = new Edge[FlowSolver::epoolsize]);
			}
			ebuf->t = v;
			ebuf->c = c;
			ebuf->w = w;
			ebuf->ne = head[u];
			return head[u] = ebuf ++;
		}
		FlowSolver(const FlowSolver&) {}
		bool SPFA();
		bool BFS(int = 0);
		int DFS(int, int);
	public:
		FlowSolver(int totNodes) {
			this->tn = totNodes += 7;
			this->ebuf = this->epool = new Edge[FlowSolver::epoolsize];
			this->head = new Edge*[totNodes];
			memset(this->head, 0, totNodes * sizeof(Edge*));
			this->fe = new Edge*[totNodes];
			this->tvis = 0;
			this->vis = new int[totNodes];
			memset(this->vis, 0, totNodes * sizeof(int));
			this->d = new int[totNodes];
			this->fr = new int[totNodes];
			this->inq = new int[totNodes];
			memset(this->inq, 0, totNodes * sizeof(int));
		}
		~FlowSolver() {
			for (std::vector<Edge*>::iterator it = this->pools.begin(); it != this->pools.end(); ++ it) {
				delete [] *it;
			}
			delete [] this->head;
			delete [] this->fe;
			delete [] this->vis;
			delete [] this->d;
			delete [] this->fr;
			delete [] this->inq;
		}
		int* addEdge(int, int, int, int = 0);
		int maxFlow(int, int);
		int minCost(int, int);
		inline int isEdgeUsed(int* ep, int u) {
			if (!this->delooped) {
				BFS(true);
				this->delooped = true;
			}
			if (vis[u] != tvis) {
				return 0;
			}
			return ((Edge*)ep)->rv->c;
		};
		inline int getEdgeTarget(int* ep) {
			return ((Edge*)ep)->t;
		}
		friend class RuleBasedRouter;
};

#endif // FLOW_SOLVER_HH
