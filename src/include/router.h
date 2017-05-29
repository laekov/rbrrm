#ifndef ROUTER_H
#define ROUTER_H
#include <common.h>
#include <istream>
#include <ostream>
#include <cstdio>
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
	public:
		static Router* createRouter(std::string);
};
typedef Router*(*RouterCreator)();
#define REGISTERROUTER(__routername__, __routerclassname__) \
	Router* create##__routerclassname__() { \
		return new __routerclassname__; \
	} \
	class __routerclassname__##Creator { \
		private: \
			__routerclassname__##Creator() { \
				extern std::map<std::string, RouterCreator> g_routers; \
				g_routers[__routername__] = create##__routerclassname__; \
			} \
			__routerclassname__##Creator(const __routerclassname__##Creator&) {} \
			static __routerclassname__##Creator instance; \
	}; __routerclassname__##Creator __routerclassname__##Creator::instance;
#endif
