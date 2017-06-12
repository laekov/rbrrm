/* Reporter class
 * Can output the result in different ways
 */

#ifndef REPORTER_HH
#define REPORTER_HH

#include <linearr.hh>
#include <string>
#include <map>

class Reporter {
	protected:
		int n, m, w;
		LineArr lines;
	public:
		Reporter(int n_, int m_, int w_, const LineArr& lines_): n(n_), m(m_), w(w_), lines(lines_) {};
		virtual void print(const char* = 0) = 0;
};

#endif // REPORTER_HH
