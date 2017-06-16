#include <rulebasedrouter.hh>
#include <textreporter.hh>
#include <detailgraphreporter.hh>
#include <briefgraphreporter.hh>
#include <algorithm>
#include <cstdio>

using std::swap;

int main(int argc, char* args[]) {
	int n(30), m(-1);
	int getdetail(0);
	int outdetail(0);
	int outbrief(0);
	int outcoor(0);
	int blx(-1), bly(-1);
	char *briefName(0), *detailName(0), *coorName(0);
	for (int i = 1; i < argc; ++ i) {
		if (!strcmp(args[i], "-n") && i + 1 < argc) {
			n = atoi(args[++ i]);
		} else if (!strcmp(args[i], "-m") && i + 1 < argc) {
			m = atoi(args[++ i]);
		} else if (!strcmp(args[i], "--out-coor")) {
			outcoor = 1;
			getdetail = 1;
			if (i + 1 < argc) {
				coorName = args[++ i];
			}
		} else if (!strcmp(args[i], "--out-detail")) {
			outdetail = 1;
			getdetail = 1;
			if (i + 1 < argc) {
				detailName = args[++ i];
			}
		} else if (!strcmp(args[i], "--out-brief")) {
			outbrief = 1;
			getdetail = 1;
			if (i + 1 < argc) {
				briefName = args[++ i];
			}
		} else if (!strcmp(args[i], "--out-block") && i + 3 < argc) {
			getdetail = 2;
			blx = atoi(args[++ i]);
			bly = atoi(args[++ i]);
			detailName = args[++ i];
		} else if (!strcmp(args[i], "--detail")) {
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
	RuleBasedRouter* rbr(new RuleBasedRouter(n, m));
	ans = rbr->getMinWidth();
	printf("min width = %d\n", ans);
	if (getdetail == 1) {
		totlen = (la = rbr->getModel()).size();
		printf("total length = %d\n", totlen);
	} else if (getdetail == 2) {
		la = rbr->getBlockModel(blx, bly);
		DetailGraphReporter dgr(1, 1, ans, la);
		dgr.print(detailName);
	}
	if (outcoor) {
		fprintf(stderr, "Printing coordinate file\n");
		TextReporter tr(n, m, ans, la);
		tr.print(coorName);
	}
	if (outdetail) {
		fprintf(stderr, "Printing graphic file\n");
		DetailGraphReporter dgr(n, m, ans, la);
		dgr.print(detailName);
	}
	if (outbrief) {
		fprintf(stderr, "Printing brief graphic file\n");
		BriefGraphReporter dgr(n, m, ans, la);
		dgr.print(briefName);
	}
	delete rbr;
}

