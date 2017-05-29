#ifndef ROUTER_H
#define ROUTER_H
#include <istream>
#include <ostream>
class Router {
	protected:
		int n, m;
		char **g;
	public:
		void init(std::istream&);
		virtual void print(std::ostream&) = 0;
		virtual void solve() = 0;
		Router(): g(0) {}
		~Router() {
			if (this->g) {
				for (int i = 0; i < this->n; ++ i) {
					delete [] this->g[i];
				}
				delete [] this->g;
			}
		}
};
#endif
