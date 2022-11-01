#include "basic/index.hpp"

#include "basic/vec2.cpp"

template <class D>
using Edges = VV<D>; // 默认 x == y

template <class D>
auto get_edges(int n) {
	VV<D> f(n, n, std::numeric_limits<D>::max() / 2);
	for (int i = 0; i < n; i++)
		f[i][i] = 0;
	return f;
}
