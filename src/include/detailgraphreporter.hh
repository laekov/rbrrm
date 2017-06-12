/* Text Reporter class
 * Output the answer in text format
 */

#ifndef DETAIL_GRAPH_REPORTER_HH
#define DETAIL_GRAPH_REPORTER_HH

#include <reporter.hh>

class DetailGraphReporter: public Reporter {
	public:
		void print(const char* = 0);
		DetailGraphReporter(int n_, int m_, int w_, const LineArr& lines_): Reporter(n_, m_, w_, lines_) {};
};

#endif // DETAIL_GRAPH_REPORTER_HH
