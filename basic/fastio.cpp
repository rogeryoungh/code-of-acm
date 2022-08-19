#include "basic/index.hpp"

struct FastI {
	char s[1 << 20], *t = s;
	FastI() {
		fread(s, 1, sizeof(s), stdin);
	}
	template <class T, bool is_int = is_integral<T>::value>
	FastI &operator>>(T &x) {
		x = 0;
		while (!isdigit(*t))
			t++;
		while (isdigit(*t))
			x = x * 10 + *t++ - '0';
		return *this;
	}
};

struct FastO {
	char s[1 << 20], *t = s;
	~FastO() {
		fwrite(s, 1, t - s, stdout);
	}
	void puts(const char *x) {
		while (*x != 0)
			*t++ = *x++;
	}
	void output(uint64_t x) {
		static char u[22];
		char *i = u + 20;
		do {
			*--i = x % 10 + '0', x /= 10;
		} while (x > 0);
		puts(i);
	}
	FastO &operator<<(uint64_t x) {
		return output(x), *this;
	}
	FastO &operator<<(char x) {
		return *t++ = x, *this;
	}
	FastO &operator<<(int64_t x) {
		if (x < 0) {
			*--t = '-', x = -x;
		}
		return output(x), *this;
	}
	FastO &operator<<(const char *x) {
		return puts(x), *this;
	}
};

FastI fin;
FastO fout;
