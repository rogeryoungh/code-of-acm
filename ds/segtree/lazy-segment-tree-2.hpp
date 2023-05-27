#include "basic/index.hpp"

// @description 线段树(懒标记)

template <class Val, class Tag, auto E, auto merge = std::plus()>
struct SegTree {
	struct Seg {
		Val val{};
		std::optional<Tag> tag{};
		Seg *ls = nullptr, *rs = nullptr;
		Seg(const Val &v) : val(v) {}
		void apply(const Tag &t) {
			t.to(val);
			if (tag.has_value())
				t.to(tag.value());
			else
				tag = t;
		}
	};
	const ll L0, R0;
	Seg *rt = nullptr;
	SegTree(ll l, ll r) : L0(l), R0(r) {}
	static Seg *alloc(ll len) {
		static std::queue<Seg> pool;
		return &pool.emplace(E(len));
	}
	Val val(Seg *p, ll len) {
		return !p ? E(len) : p->val;
	}
	template <bool with_pull>
	Seg *traverse(Seg *s, ll l, ll r, auto &&op) {
		auto dfs = [&](auto &&self, Seg *p, ll L, ll R) -> Seg * {
			if (!p) {
				p = alloc(R - L);
			}
			if (l <= L && R <= r) {
				op(p);
			} else {
				int M = (L + R) / 2;
				auto &tt = p->tag;
				if (tt.has_value()) {
					if (!p->ls)
						p->ls = alloc(M - L);
					if (!p->rs)
						p->rs = alloc(R - M);
					p->ls->apply(tt.value());
					p->rs->apply(tt.value());
					tt.reset();
				}
				if (l < M)
					p->ls = self(self, p->ls, L, M);
				if (r > M)
					p->rs = self(self, p->rs, M, R);
				if constexpr (with_pull)
					p->val = merge(val(p->ls, M - L), val(p->rs, R - M));
			}
			return p;
		};
		return dfs(dfs, s, L0, R0);
	}
	void modify(ll l, ll r, const Tag &t) {
		rt = traverse<true>(rt, l, r, [&](Seg *p) {
			p->apply(t);
		});
	}
	Val query(ll l, ll r) {
		Val ret{};
		rt = traverse<false>(rt, l, r, [&](Seg *p) {
			ret = merge(ret, p->val);
		});
		return ret;
	}
};
