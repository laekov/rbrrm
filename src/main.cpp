#include <router.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using std::ifstream;
using std::ofstream;

int main() {
	Router* r = Router::createRouter("dinic");
	if (!r) {
		fprintf(stderr, "No such router strategy\n");
		return -1;
	}
	ifstream fin(".in");
	r->init(fin);
	fin.close();
	r->solve();
	ofstream fout("1.ppm");
	r->print(fout);
	fout.close();
	system("ppmtojpeg 1.ppm >1.jpg");
}
