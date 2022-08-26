#include "basic/index.hpp"

// @description 矩阵快速幂

template <class T>
struct QMtx {
	int n;
	vector<T> m;
	QMtx(int a) : n(a), m(n * n) {}
	auto operator[](int i) {
		return m.begin() + i * n;
	}
	auto operator[](int i) const {
		return m.begin() + i * n;
	}
	static QMtx E(int n) {
		QMtx e(n);
		for (int i = 0; i < n; i++) {
			e[i][i] = 1;
		}
		return e;
	}
	QMtx pow(ll w);
};

template <class T>
QMtx<T> operator*(const QMtx<T> &lhs, const QMtx<T> &rhs) {
	assert(lhs.n == rhs.n);
	int n = lhs.n;
	QMtx<T> u(n);
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			T t = lhs[i][k];
			for (int j = 0; j < rhs.n; j++) {
				u[i][j] += rhs[k][j] * t;
			}
		}
	}
	return u;
}

template <class T>
QMtx<T> QMtx<T>::pow(ll w) {
	QMtx ret = QMtx::E(n), a = *this;
	for (; w > 0; w >>= 1) {
		if (w & 1)
			ret = a * ret;
		a = a * a;
	}
	return ret;
}

template <class T>
istream &operator>>(istream &is, QMtx<T> &m) {
	for (int i = 0; i < m.n * m.n; i++)
		is >> m.m[i];
	return is;
}

template <class T>
ostream &operator<<(ostream &os, const QMtx<T> &m) {
	for (int i = 0; i < m.n * m.n; i++)
		os << m.m[i] << " \n"[(i + 1) % m.n == 0];
	return os;
}
