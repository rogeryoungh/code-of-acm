#include "basic/index.hpp"

// @description 线段树

template <class Val, auto E, auto merge = std::plus()>
struct SegTree {
	struct Seg {
		Val val{};
		Seg(const Val v = {}) : val(v) {}
		Seg *ls = nullptr, *rs = nullptr;
	};
	static Seg *clone(Seg *p, ll len) {
		static std::queue<Seg> pool;
		return &pool.emplace(!p ? E(len) : *p);
	}
	const ll L0, R0;
	SegTree(ll l, ll r) : L0(l), R0(r) {}
	Seg *root() {
		return clone(nullptr, R0 - L0);
	}
	Val val(Seg *p, ll len) {
		return !p ? E(len) : p->val;
	}
	template <bool create>
	Seg *traverse(Seg *p, ll L, ll R, ll l, ll r, auto &&op) {
		if (create || !p)
			p = clone(p, R - L);
		if (l <= L && R <= r) {
			op(p->val);
			return p;
		} else {
			ll M = (L + R) / 2;
			if (l < M)
				p->ls = traverse<create>(p->ls, L, M, l, r, op);
			if (r > M)
				p->rs = traverse<create>(p->rs, M, R, l, r, op);
			if constexpr (!create)
				p->val = merge(val(p->ls, M - L), val(p->rs, R - M));
		}
		return p;
	}
	template <bool create = false>
	Seg *modify(Seg *rt, ll k, auto &&op) {
		return traverse<create>(rt, L0, R0, k, k + 1, op);
	}
	Val query(Seg *rt, ll l, ll r) {
		Val ret{};
		traverse<false>(rt, L0, R0, l, r, [&](const Val &v) {
			ret = merge(ret, v);
		});
		return ret;
	}
};
