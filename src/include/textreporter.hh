/* Text Reporter class
 * Output the answer in text format
 */

#ifndef TEXT_REPORTER_HH
#define TEXT_REPORTER_HH

#include <reporter.hh>

class TextReporter: public Reporter {
	public:
		void print(const char* = 0);
		TextReporter(int n_, int m_, int w_, const LineArr& lines_): Reporter(n_, m_, w_, lines_) {};
};

#endif // TEXT_REPORTER_HH
