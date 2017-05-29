#include <router.h>

void Router::init(std::istream& fin) {
	fin >> n >> m;
	g = new char*[n];
	for (int i = 0; i < this->n; ++ i) {
		g[i] = new char[this->m + 1];
		fin >> g[i];
	}
}
