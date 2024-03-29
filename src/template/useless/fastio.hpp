#pragma once
#include "../base.hpp"

// #region snippet
struct Buf {
	FILE *f;
	std::vector<char> buf;
	char *beg, *end, *p;
	Buf(FILE *f_, int size) : f(f_), buf(size), beg(buf.data()), end(beg + size - 1), p(beg) {}
	char top() const {
		return *p;
	}
	char pop() {
		char r = *p++;
		if (p == end)
			reread();
		return r;
	}
	void reread() {
		p = std::move(p, end, beg);
		int r = std::fread(p, 1, end - p, f);
		p[r] = 0, p = beg;
	}
	void write(const char *s, int len) {
		std::fwrite(s, 1, len, f);
	}
	void flush() {
		write(beg, p - beg);
		p = beg;
	}
	void push(char s) {
		*p++ = s;
		if (p == end)
			flush();
	}
	void push(const char *s, int len) {
		if (len < buf.size()) {
			if (end - p <= len)
				flush();
			p = std::copy_n(s, len, p);
		} else {
			flush();
			write(s, len);
		}
	}
	void puts(const char *s) {
		while (*s != 0)
			push(*s++);
	}
};

struct FastI : Buf {
	FastI(FILE *f, int size = 1 << 18) : Buf(f, size) {
		p = end, reread();
	}
	void skipSpace() {
		while (std::isspace(top()))
			pop();
	}
	FastI &operator>>(char &x) {
		skipSpace();
		x = pop();
		return *this;
	}
	FastI &operator>>(std::string &x) {
		x.resize(0);
		skipSpace();
		while (std::isgraph(top()))
			x.push_back(pop());
		return *this;
	}
	template <std::integral T>
	FastI &operator>>(T &x) {
		bool neg = false;
		x = 0;
		skipSpace();
		if constexpr (std::is_signed_v<T>)
			if (top() == '-')
				neg = true, pop();
		while (std::isdigit(top()))
			x = x * 10 + (pop() & 0xf);
		if constexpr (std::is_signed_v<T>)
			x = neg ? -x : x;
		return *this;
	}
};

struct FastO : Buf {
	FastO(FILE *f, int size = 1 << 18) : Buf(f, size) {}
	~FastO() {
		Buf::flush();
	}
	template <std::integral T>
	FastO &operator<<(T x) {
		static std::array<char, 48> u{};
		char *r = u.data() + 40, *s = r;
		bool neg = false;
		if constexpr (std::is_signed_v<T>)
			if (x < 0)
				neg = true, x = -x;
		do
			*--s = x % 10 + '0', x /= 10;
		while (x > 0);
		if constexpr (std::is_signed_v<T>)
			if (neg)
				*--s = '-';
		return push(s, r - s), *this;
	}
	FastO &operator<<(char x) {
		return push(x), *this;
	}
	FastO &operator<<(const char *x) {
		return puts(x), *this;
	}
	FastO &operator<<(const std::string &x) {
		return push(x.c_str(), x.size()), *this;
	}
};
// #endregion snippet
