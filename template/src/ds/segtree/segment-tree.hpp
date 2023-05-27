#include "basic/index.hpp"

// @description 线段树

template <class Val, auto merge = std::plus()>
struct SegTree {
	const int N;
	std::vector<Val> tr;
	SegTree(std::uint32_t n) : N(std::bit_ceil(n)), tr(N * 2) {}
	auto leaf() {
		return std::span(tr.begin() + N, tr.end());
	}
	void pull(int p) {
		tr[p] = merge(tr[p * 2], tr[p * 2 + 1]);
	}
	void build() {
		for (int i = N - 1; i >= 1; i--)
			pull(i);
	}
	void modify(int i, auto &&op) {
		i += N, op(tr[i]);
		for (i /= 2; i > 0; i /= 2)
			pull(i);
	}
	Val query(int l, int r) {
		Val vl{}, vr{};
		int pl = l + N, pr = r + N;
		while (pr - pl >= 1) {
			if (pl % 2 == 1)
				vl = merge(vl, tr[pl]);
			if (pr % 2 == 1)
				vr = merge(tr[pr - 1], vr);
			pl = (pl + 1) / 2, pr /= 2;
		}
		return merge(vl, vr);
	}
};
