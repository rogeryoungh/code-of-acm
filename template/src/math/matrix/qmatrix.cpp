#include "basic/index.hpp"

#include "math/matrix/matrix.cpp"

// @description 矩阵快速幂

template <class T>
auto make_matrix_E(int n) {
	VV<T> ret(n, n);
	for (int i = 0; i < n; i++)
		ret[i][i] = 1;
	return ret;
}

template <class T>
auto matrix_pow(VV<T> a, ll w) {
	auto ret = make_matrix_E<T>(a.x);
	for (; w > 0; w /= 2) {
		if (w % 2 == 1)
			ret = a * ret;
		a = a * a;
	}
	return ret;
}
