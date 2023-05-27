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
#define lson p * 2
#define rson p * 2 + 1
	template <bool with_pull>
	void traverse(int l, int r, auto &&op) {
		auto dfs = [&](auto &&self, int p, int L, int R) -> void {
			if (l <= L && R <= r) {
				op(tr[p]);
			} else {
				int M = (L + R) / 2;
				auto &t = tr[p].tag;
				if (t.has_value()) {
					tr[lson].apply(t.value());
					tr[rson].apply(t.value());
					t.reset();
				}
				if (l < M)
					self(self, lson, L, M);
				if (r > M)
					self(self, rson, M, R);
				if constexpr (with_pull)
					pull(p);
			}
		};
		dfs(dfs, 1, 0, N);
	}
	void pull(int p) {
		tr[p].val = merge(tr[lson].val, tr[rson].val);
	}
	void modify(int l, int r, const Tag &t) {
		traverse<true>(l, r, [&](Seg &cur) {
			cur.apply(t);
		});
	}
	Val query(int l, int r) {
		Val ret{};
		traverse<false>(l, r, [&](const Seg &cur) {
			ret = merge(ret, cur.val);
		});
		return ret;
	}
};
