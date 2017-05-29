#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <vector>
#include <string>
#include <cstring>
#include <ostream>
class Canvas {
	private:
		int n_, m_;
		int **g_;
	public:
		int lineWid;
		Canvas(int n, int m) {
			this->lineWid = 2;
			this->n_ = n, this->m_ = m;
			this->g_ = new int*[this->n_];
			for (int i = 0; i < this->n_; ++ i) {
				this->g_[i] = new int[this->m_];
				memset(this->g_[i], 0, sizeof(int) * this->m_);
			}
		}
		~Canvas() {
			for (int i = 0; i < this->n_; ++ i) {
				delete[] this->g_[i];
			}
			delete[] this->g_;
		}
		void setPixel(int, int, int);
		void line(int, int, int, int, int);
		void rect(int, int, int, int, int);
		void circ(int, int, int, int);
		void write(std::ostream&);
};
#endif
