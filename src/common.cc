#include <common.hh>

namespace SimpleMM {
	int *ialloc(int n) {
		return new int[n];
	}

	void idelete(int* a) {
		delete [] a;
	}

	int **ipalloc(int n) {
		return new int*[n];
	}

	void ipdelete(int** a) {
		delete [] a;
	}

	int **i2alloc(int n, int m) {
		if (m == -1) {
			m = n;
		}
		int **s(new int*[n]);
		for (int i = 0; i < n; ++ i) {
			s[i] = new int[m];
		}
		return s;
	}

	void i2delete(int** a, int n) {
		for (int i = 0; i < n; ++ i) {
			delete [] a[i];
		}
		delete [] a;
	}
};
