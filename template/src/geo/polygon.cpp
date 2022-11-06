#include "basic/index.hpp"

#include "geo/fpoint.cpp"

using VP = V<P>;

template <class RET>
RET ring_act(const auto &v, auto &&func) {
	RET ret{};
	for (int i = 0; i < v.size() - 1; i++)
		ret += func(v[i], v[i + 1]);
	if (v.size() >= 2)
		ret += func(v.back(), v.front());
	return ret;
}

D area(const VP &v) {
	return ring_act<D>(v, crs) / 2;
}

// 必须排序且去重！
VP convex_down(const VP &ps) {
	assert(ps.size() >= 2);
	VP dw;
	for (P d : ps) {
		for (int n = dw.size(); n > 1; n--, dw.pop_back()) {
			if (ccw(dw[n - 2], dw[n - 1], d) == 1)
				break;
		}
		dw.push_back(d);
	}
	return dw;
}

VP convex(VP ps) {
	std::sort(ps.begin(), ps.end());
	ps.erase(std::unique(ps.begin(), ps.end()), ps.end());
	if (ps.size() <= 1)
		return ps;
	VP dw = convex_down(ps);
	std::reverse(ps.begin(), ps.end());
	VP up = convex_down(ps);
	dw.insert(dw.begin(), up.begin() + 1, up.end() - 1);
	return dw;
}
