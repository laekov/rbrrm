#include <router.h>
#include <map>
#include <string>

using std::string;
using std::map;

void Router::init(std::istream& fin) {
	fin >> this->n >> this->m;
	this->g = new char*[this->n];
	for (int i = 0; i < this->n; ++ i) {
		this->g[i] = new char[this->m + 1];
		fin >> this->g[i];
	}
}

Router* Router::createRouter(string routerName) {
	extern map<string, RouterCreator> g_routers;
	RouterCreator cr(g_routers[routerName]);
	if (cr) {
		return cr();
	} else {
		return 0;
	}
}
