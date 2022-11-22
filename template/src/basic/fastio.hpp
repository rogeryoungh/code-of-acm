#include "basic/index.hpp"

struct BasicBuffer {
	std::vector<char> s;
	BasicBuffer() : s(1 << 18) {}
	char *p = s.data(), *beg = p, *end = p + s.size();
	inline char getc() {
		if (p == end)
			readAll();
		return *p++;
	}
	inline void putc(char c) {
		if (p == end)
			writeAll();
		*p++ = c;
	}
	inline void puts(const char *x) {
		while (*x != 0)
			putc(*x++);
	}
	void readAll() {
		std::fread(beg, 1, end - beg, stdin);
		p = s.data();
	}
	void writeAll() {
		std::fwrite(beg, 1, p - beg, stdout);
		p = s.data();
	}
};

struct FastI : BasicBuffer {
	FastI() {
		readAll();
	}
	ll read() {
		ll x = 0;
		char c = getc();
		bool sgn = true;
		while (!std::isdigit(c))
			sgn = sgn && c != '-', c = getc();
		while (std::isdigit(c))
			x = x * 10 + c - '0', c = getc();
		return sgn ? x : -x;
	}
	template <class T>
	FastI &operator>>(T &x) {
		return x = read(), *this;
	}
	FastI &operator>>(char &x) {
		return x = getc(), *this;
	}
};

struct FastO : BasicBuffer {
	std::array<char, 32> u{};
	~FastO() {
		writeAll();
	}
	void output(ll x) {
		char *i = u.data() + 20;
		if (x < 0)
			putc('-'), x = -x;
		do
			*--i = x % 10 + '0', x /= 10;
		while (x > 0);
		puts(i);
	}
	template <class T>
	FastO &operator<<(const T &x) {
		return output(x), *this;
	}
	FastO &operator<<(char x) {
		return putc(x), *this;
	}
	FastO &operator<<(const char *x) {
		return puts(x), *this;
	}
	FastO &operator<<(const std::string &x) {
		return puts(x.c_str()), *this;
	}
};

FastI fin;
FastO fout;
