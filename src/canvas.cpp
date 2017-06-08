#include <canvas.h>
#include <algorithm>
using std::swap;
void Canvas::setPixel(int x, int y, int c) {
	if (x >= 0 && x < this->n_ && y >= 0 && y < this->m_) {
		this->g_[x][y] = c;
	}
}
void Canvas::rect(int xa, int ya, int xb, int yb, int c) {
	for (int i = xa; i <= xb; ++ i) {
		for (int j = ya; j <= yb; ++ j) {
			this->setPixel(i, j, c);
		}
	}
}
void Canvas::line(int xa, int ya, int xb, int yb, int c) {
	if (xa > xb) {
		swap(xa, xb);
	}
	if (ya > yb) {
		swap(ya, yb);
	}
	this->rect(xa - this->lineWid, ya - this->lineWid, xb + this->lineWid, yb + this->lineWid, c);
}

void Canvas::circ(int x, int y, int r, int c) {
	for (int i = -r; i <= r; ++ i) {
		for (int j = -r; j <= r; ++ j) {
			if (i * i + j * j <= r * r) {
				this->setPixel(x + i, y + j, c);
			}
		}
	}
}

void Canvas::write(std::ostream& fout) {
	static const int colors[][3] = {
		{ 0x33, 0x33, 0x33 }, // black
		{ 0xff, 0xff, 0xff }, // white
		{ 0x00, 0xff, 0x00 }, // green
		{ 0xa0, 0xa0, 0xff }, // blue
		{ 0xf0, 0x00, 0x00 } // red
	};
	fout << "P3\n" << this->m_ << " " << this->n_ << "\n255\n";
	for (int i = 0; i < this->n_; ++ i) {
		for (int j = 0; j < this->m_; ++ j) {
			for (int k = 0; k < 3; ++ k) {
				fout << colors[this->g_[i][j]][k] << " ";
			}
		}
	}
}

