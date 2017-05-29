#ifndef COSTFLOW_H
#define COSTFLOW_H
#include <flow.h>
class CostFlowRouter: public FlowRouter {
	private:
		int *fr, *q, *inq, *d;
		Edge** fe;
		bool SPFA();
	public:
		void solve();
};
#endif
