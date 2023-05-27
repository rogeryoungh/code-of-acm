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
	template <bool create = false>
	Seg *modify(Seg *rt, ll k, auto &&op) {
		auto dfs = [&](auto &&self, Seg *p, ll L, ll R) -> Seg * {
			if (create || !p)
				p = clone(p, R - L);
			if (R - L == 1) {
				op(p->val);
			} else {
				ll M = (L + R) / 2;
				if (k < M)
					p->ls = self(self, p->ls, L, M);
				else
					p->rs = self(self, p->rs, M, R);
				p->val = merge(val(p->ls, M - L), val(p->rs, R - M));
			}
			return p;
		};
		return dfs(dfs, rt, L0, R0);
	}
	Val query(Seg *rt, ll l, ll r) {
		Val ret{};
		auto dfs = [&](auto &&self, Seg *p, ll L, ll R) -> void {
			if (l <= L && R <= r) {
				ret = merge(ret, val(p, R - L));
			} else {
				ll M = (L + R) / 2;
				if (l < M)
					self(self, !p ? p : p->ls, L, M);
				if (r > M)
					self(self, !p ? p : p->rs, M, R);
			}
		};
		dfs(dfs, rt, L0, R0);
		return ret;
	}
};
