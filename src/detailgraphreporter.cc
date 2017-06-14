#include <detailgraphreporter.hh>
#include <canvas.hh>
#include <fstream>
#include <algorithm>

using std::ofstream;
using std::endl;
using std::min;
using std::max;

void DetailGraphReporter::print(const char* fileName) {
	if (max(n, m) * (w + 1) > 2800) {
		fprintf(stderr, "Data scale not suitable to print detail picture. Not processing.\n");
		return;
	}
	const char* outFileName(fileName ? fileName : "out.pnm");
	fprintf(stderr, "Writing picture to %s\n", fileName ? fileName : "out.ppm");
	ofstream fout(fileName ? fileName : "out.ppm");
	int bls(max(1366, n * (w + 1) * 2) / (n * (w + 1)));
	int rr = max(bls / 5, 1);
	Canvas c(bls * n * (w + 1) + 3, bls * m * (w + 1) + 3);
	c.lineWid = min(c.lineWid, rr / 2);
	for (int i = 0; i <= n * (w + 1); ++ i) {
		c.circ(i * bls, 0, rr, 3);
		c.circ(0, i * bls, rr, 3);
		c.circ(i * bls, m * (w + 1) * bls, rr, 3);
		c.circ(n * (w + 1) * bls, i * bls, rr, 3);
	}
	for (int i = 0; i <= n; ++ i) {
		for (int j = 0; j <= m; ++ j) {
			c.circ(i * (w + 1) * bls, j * (w + 1) * bls, rr, 4);
		}
	}
	for (LineArr::const_iterator it = lines.begin(); it != lines.end(); ++ it) {
		c.line(POSX(it->first) * bls, POSY(it->first) * bls, POSX(it->second) * bls, POSY(it->second) * bls, 2);
	}
	c.write(fout);
	fout.close();
	fprintf(stderr, "Picture written to %s\n", fileName ? fileName : "out.ppm");
}
