#include <briefgraphreporter.hh>
#include <canvas.hh>
#include <fstream>
#include <algorithm>
#include <cstdio>

using std::min;
using std::max;
using std::ofstream;

void BriefGraphReporter::print(const char* fileName) {
	if (max(n, m) * (w + 1) < 400) {
		fprintf(stderr, "Data scale not suitable to print brief picture. Not processing.\n");
		return;
	}
	const char* outFileName(fileName ? fileName : "out.pnm");
	fprintf(stderr, "Processing brief picture to %s\n", outFileName);
	int blc(min(1366, ((w + 1) * max(n, m))));
	int grs(max((w + 1) * max(n, m) / blc + 1, 4));
	fprintf(stderr, "blc = %d grs = %d\n", blc, grs);
	int bn(n * (w + 1) / grs + 3);
	int bm(m * (w + 1) / grs + 3);
	this->g = SimpleMM::i2alloc(bn, bm);
	for (int i = 0; i < bn; ++ i) {
		for (int j = 0; j < bm; ++ j) {
			g[i][j] = 0;
		}
	}
	for (LineArr::iterator it = this->lines.begin(); it != this->lines.end(); ++ it) {
		int x1(POSX(it->first)), y1(POSY(it->first));
		++ g[x1 / grs][y1 / grs];
	}
	int gmax(0);
	for (int i = 0; i < bn; ++ i) {
		for (int j = 0; j < bm; ++ j) {
			if (g[i][j] > gmax) {
				gmax = g[i][j];
			}
		}
	}
	int bls(1366 / blc);
	int rr = max(max(bls / (w + 1), 4) / 5, 0);
	int picx(bls * bn), picy(bls * bm);
	Canvas c(picx, picy);
	c.lineWid = min(c.lineWid, bls / 2);
	for (int i = 0; i < bn; ++ i) {
		for (int j = 0; j < bm; ++ j) {
			if (g[i][j]) {
				c.rect(i * bls, j * bls, (i + 1)* bls, (j + 1)* bls, -(double)g[i][j] * 255 / gmax);
			}
		}
	}
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			int xo((double)i * picx / n), yo((double)j * picy / m);
			c.circ(xo, yo, rr, 4);
		}
	}
	ofstream fout(outFileName);
	c.write(fout);
	fout.close();
	fprintf(stderr, "Brief picture written to %s\n", outFileName);
	SimpleMM::i2delete(this->g, bn);
}

