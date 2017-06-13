#include <briefgraphreporter.hh>
#include <canvas.hh>
#include <fstream>
#include <algorithm>
#include <cstdio>

using std::min;
using std::max;
using std::ofstream;

void BriefGraphReporter::print(const char* fileName) {
	const char* outFileName(fileName ? fileName : "out.pnm");
	fprintf(stderr, "Processing brief picture to %s\n", outFileName);
	int grs(max((w + 1) * max(n, m) / 1366 + 1, 4));
	int bn(n * (w + 1) / grs + 2);
	int bm(m * (w + 1) / grs + 2);
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
	int bls(max(1366 / max(n, m) + 1, 5));
	int rr = max(max(bls / (w + 1), 5) / 5, 1);
	int picx(grs * bn), picy(grs * bm);
	Canvas c(picx, picy);
	c.lineWid = min(c.lineWid, grs / 2);
	for (int i = 0; i < bn; ++ i) {
		for (int j = 0; j < bm; ++ j) {
			if (g[i][j]) {
				c.rect(i * grs, j * grs, (i + 1)* grs, (j + 1)* grs, -(double)g[i][j] * 255 / gmax);
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

