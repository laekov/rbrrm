/* Rule based router
 * core class of this project
 */
#ifndef FORCE_ROUTER_HH
#define FORCE_ROUTER_HH

#include <router.hh>
#include <flowsolver.hh>
#include <common.hh>

class ForceRouter: public Router {
	private:
		static const int inf = 0x3f3f3f3f;
		FlowSolver* buildGraph(int);
		bool check(int);
		int tn, ta, st, te;
		int **ni, **hi, **vi, **et;
	public:
		int getMinWidth();
		LineArr getModel();
		ForceRouter(int n_, int m_ = -1): Router(n_, m_) {
			this->tn = (this->m / 3 + 2) * (this->m / 3 + 1) * this->n * this->m * 6 + 3;
			this->ta = (this->m / 3 + 2) * this->m;
			this->ni = SimpleMM::i2alloc(this->ta);
			this->hi = SimpleMM::i2alloc(this->ta);
			this->vi = SimpleMM::i2alloc(this->ta);
			this->et = SimpleMM::ipalloc(this->tn);
		}
		~ForceRouter() {
			SimpleMM::ipdelete(this->et);
			SimpleMM::i2delete(this->ni, this->ta);
			SimpleMM::i2delete(this->hi, this->ta);
			SimpleMM::i2delete(this->vi, this->ta);
		}
};

#endif // FORCE_ROUTER_HH
