#include "basic/index.hpp"

// @description 线段树(懒标记)

template <class Val, class Tag, auto merge = std::plus()>
struct SegTree {
	const int N;
	struct Seg {
		Val val;
		std::optional<Tag> tag;
		void apply(const Tag &t) {
			t.to(val);
			if (tag.has_value())
				t.to(tag.value());
			else
				tag = t;
		}
	};
	std::vector<Seg> tr;
	SegTree(std::uint32_t n) : N(std::bit_ceil(n)), tr(N * 2) {}
	auto leaf() {
		return std::span(tr.begin() + N, tr.end());
	}
	void build() {
		for (int i = N - 1; i >= 1; i--)
			pull(i);
	}
	template <bool with_pull>
	void traverse(int p, int L, int R, int l, int r, auto &&op) {
		if (l <= L && R <= r) {
			op(tr[p]);
		} else {
			int M = (L + R) / 2;
			auto &t = tr[p].tag;
			if (t.has_value()) {
				tr[p * 2 + 0].apply(t.value());
				tr[p * 2 + 1].apply(t.value());
				t.reset();
			}
			if (l < M)
				traverse<with_pull>(p * 2 + 0, L, M, l, r, op);
			if (r > M)
				traverse<with_pull>(p * 2 + 1, M, R, l, r, op);
			if constexpr (with_pull)
				pull(p);
		}
	}
	void pull(int p) {
		tr[p].val = merge(tr[p * 2].val, tr[p * 2 + 1].val);
	}
	void modify(int l, int r, const Tag &t) {
		traverse<true>(1, 0, N, l, r, [&](Seg &cur) {
			cur.apply(t);
		});
	}
	Val query(int l, int r) {
		Val ret{};
		traverse<false>(1, 0, N, l, r, [&](const Seg &cur) {
			ret = merge(ret, cur.val);
		});
		return ret;
	}
};
