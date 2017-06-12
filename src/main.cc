#include <rulebasedrouter.hh>
#include <textreporter.hh>
#include <detailgraphreporter.hh>
#include <algorithm>
#include <cstdio>

using std::swap;

int main(int argc, char* args[]) {
	int n(30), m(-1);
	int testGridW(0);
	int getdetail(0);
	int outppm(0);
	int outcoor(0);
	char *ppmName(0), *coorName(0);
	for (int i = 1; i < argc; ++ i) {
		if (!strcmp(args[i], "-n") && i + 1 < argc) {
			n = atoi(args[++ i]);
		} else if (!strcmp(args[i], "-m") && i + 1 < argc) {
			m = atoi(args[++ i]);
		} else if (!strcmp(args[i], "--test-grid") && i + 1 < argc) {
			testGridW = atoi(args[++ i]);
		} else if (!strcmp(args[i], "--out-coor")) {
			outcoor = 1;
			getdetail = 1;
			if (i + 1 < argc) {
				coorName = args[++ i];
			}
		} else if (!strcmp(args[i], "--out-ppm")) {
			outppm = 1;
			getdetail = 1;
			if (i + 1 < argc) {
				ppmName = args[++ i];
			}
		} else if (!strcmp(args[i], "-detail")) {
			getdetail = 1;
		}
	}
	if (m == -1) {
		m = n;
	} else if (n > m) {
		swap(n, m);
	}
	printf("n = %d, m = %d\n", n, m);
	int ans, totlen;
	LineArr la;
	RuleBasedRouter rbr(n, m);
	ans = rbr.getMinWidth();
	printf("min width = %d\n", ans);
	if (getdetail) {
		totlen = (la = rbr.getModel()).size();
		printf("total length = %d\n", totlen);
	}
	if (outcoor) {
		fprintf(stderr, "Printing coordinate file\n");
		TextReporter tr(n, m, ans, la);
		tr.print(coorName);
	}
	if (outppm) {
		fprintf(stderr, "Printing graphic file\n");
		DetailGraphReporter dgr(n, m, ans, la);
		dgr.print(ppmName);
	}
}

