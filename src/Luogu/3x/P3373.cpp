#include <bits/stdc++.h>

#define V std::vector
using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

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
	void traverse(int p, int L, int R, int l, int r, auto &&op) {
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
				traverse<with_pull>(lson, L, M, l, r, op);
			if (r > M)
				traverse<with_pull>(rson, M, R, l, r, op);
			if constexpr (with_pull)
				pull(p);
		}
	}
	void pull(int p) {
		tr[p].val = merge(tr[lson].val, tr[rson].val);
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

constexpr int P = 571373;

struct Val {
	int sum = 0, len = 0;
};
struct Tag {
	int k = 1, m = 0;
	void to(Tag &t) const {
		t.m = (1ll * t.m * k + m) % P;
		t.k = (1ll * t.k * k) % P;
	}
	void to(Val &v) const {
		v.sum = (1ll * k * v.sum + 1ll * m * v.len) % P;
	}
};
static Val merge(const Val &l, const Val &r) {
	return {(l.sum + r.sum) % P, l.len + r.len};
}
// static Val init(ll len) {
// 	return {0, int(len)};
// }

int main() {
	int n, m, _P;
	std::cin >> n >> m >> _P;
	SegTree<Val, Tag, merge> tr(n + 1);
	auto leaf = tr.leaf();
	for (int i = 1; i <= n; ++i) {
		int t;
		std::cin >> t;
		leaf[i].val = {t, 1};
	}
	tr.build();
	while (m--) {
		int op, l, r;
		std::cin >> op >> l >> r;
		if (op == 1) {
			int k;
			std::cin >> k;
			tr.modify(l, r + 1, {k, 0});
		} else if (op == 2) {
			int k;
			std::cin >> k;
			tr.modify(l, r + 1, {1, k});
		} else {
			std::cout << tr.query(l, r + 1).sum << '\n';
		}
	}
	return 0;
}
