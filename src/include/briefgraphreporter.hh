/* Text Reporter class
 * Output the answer in brief mode
 * Alternative way when data is large
 */

#ifndef BRIEF_GRAPH_REPORTER_HH
#define BRIEF_GRAPH_REPORTER_HH

#include <reporter.hh>
#include <common.hh>

class BriefGraphReporter: public Reporter {
	private:
		int** g;
	public:
		void print(const char* = 0);
		BriefGraphReporter(int n_, int m_, int w_, const LineArr& lines_): Reporter(n_, m_, w_, lines_) {
		}
		~BriefGraphReporter() {}
};

#endif // BRIEF_GRAPH_REPORTER_HH
