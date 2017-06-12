#ifndef COMMON_H
#define COMMON_H
#define INSTANCECLASS(__name__, __loader__) class __name__ { \
	private: \
		__name__() { \
			__loader__; \
		} \
		__name__(const __name__&); \
		static __name__ instance; \
}; __name__  __name__::instance;
namespace SimpleMM {
	int *ialloc(int);
	int **i2alloc(int, int = -1);
	int **ipalloc(int);
	void idelete(int*);
	void i2delete(int**, int);
	void ipdelete(int**);
};
#endif
