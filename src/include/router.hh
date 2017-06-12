/* Router class defineation
 * Base interface for solver
 */
#ifndef ROUTER_HH
#define ROUTER_HH

#include <linearr.hh>
#include <algorithm>

class Router {
	protected:
		int n, m, w;
		Router(const Router&) {}
	public:
		Router(int n_, int m_ = -1) {
			this->init(n_, m_);
		}
		inline void init(int n_, int m_ = -1) {
			this->n = n_;
			this->m = (m_ > -1) ? m_ : n_;
			this->w = -1;
			if (this->n > this->m) {
				std::swap(this->n, this->m);
			}
		}
		virtual int getMinWidth() = 0;
		virtual LineArr getModel() = 0;
};

#endif // ROUTER_HH
