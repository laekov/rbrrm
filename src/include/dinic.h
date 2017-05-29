#ifndef DINIC_H
#define DINIC_H
#include <flow.h>
class DinicFlowRouter: public FlowRouter {
	private:
		int *d, *q;
		int DFS(int, int);
		bool BFS();
	public:
		void solve();
};
#endif
