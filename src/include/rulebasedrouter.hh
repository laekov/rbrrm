/* Rule based router
 * core class of this project
 */
#ifndef RULE_BASED_ROUTER_HH
#define RULE_BASED_ROUTER_HH

#include <router.hh>
#include <flowsolver.hh>
#include <common.hh>

class RuleBasedRouter: public Router {
	private:
		static const int inf = 0x3f3f3f3f;
		int **ni, **hi, **vi, **pi, **si, **et, *osa, *ose;
		int **di, **ga, **gb, **eh[2];
		int tn, ta, st, te;
		FlowSolver* buildGraph(int);
		bool check(int);
		void detailBlock(LineArr&, int, int, int*, int*, int);
	public:
		int getMinWidth();
		LineArr getModel();
		LineArr getBlockModel(int, int);
		RuleBasedRouter(int n_, int m_ = -1): Router(n_, m_) {
			this->tn = (this->n + 1)*(this->m + 1)* 7 + 3;
			this->ta = this->m + 3;
			this->ni = SimpleMM::i2alloc(this->ta);
			this->hi = SimpleMM::i2alloc(this->ta);
			this->vi = SimpleMM::i2alloc(this->ta);
			this->pi = SimpleMM::i2alloc(this->ta);
			this->si = SimpleMM::i2alloc(this->ta);
			this->osa = SimpleMM::ialloc(this->tn);
			this->ose = SimpleMM::ialloc(this->tn);
			this->et = SimpleMM::ipalloc(this->tn);
			this->di = SimpleMM::i2alloc(this->ta);
			this->ga = SimpleMM::i2alloc(this->ta);
			this->gb = SimpleMM::i2alloc(this->ta);
			this->eh[0] = SimpleMM::ipalloc(this->tn);
			this->eh[1] = SimpleMM::ipalloc(this->tn);
		}
		~RuleBasedRouter() {
			SimpleMM::i2delete(this->ni, this->ta);
			SimpleMM::i2delete(this->hi, this->ta);
			SimpleMM::i2delete(this->vi, this->ta);
			SimpleMM::i2delete(this->pi, this->ta);
			SimpleMM::i2delete(this->si, this->ta);
			SimpleMM::idelete(this->osa);
			SimpleMM::idelete(this->ose);
			SimpleMM::ipdelete(this->et);
			SimpleMM::i2delete(this->di, this->ta);
			SimpleMM::i2delete(this->ga, this->ta);
			SimpleMM::i2delete(this->gb, this->ta);
			SimpleMM::ipdelete(this->eh[0]);
			SimpleMM::ipdelete(this->eh[1]);
		}
};

#endif // RULE_BASED_ROUTER_HH
