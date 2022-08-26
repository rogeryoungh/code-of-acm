#include "basic/index.hpp"

// @description 质因子(p^k)

auto factor_pii(ll n) {
	vector<ll> ret = factor(n);
	vector<pair<ll, int>> ans;
	if (ret.empty())
		return ans;
	ans.emplace_back(ret[0], 1);
	for (int i = 1; i < ret.size(); i++) {
		if (ret[i] == ret[i - 1])
			ans.back().second++;
		else
		 	ans.emplace_back(ret[i], 1);
	}
	return ans;
}
