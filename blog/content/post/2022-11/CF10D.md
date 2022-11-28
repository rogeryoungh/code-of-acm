---
author: "rogeryoungh"
title: "CF10D LCIS"
date: "2022-11-28"
katex: true
showtoc: true
---

## 题目大意

给定两个分别长 $n,m$ 的序列 $\{a\},\{b\}$，求其最长公共上升子序列。

## 分析

设 $DP(i, j)$ 为序列 $a$ 中的前 $i$ 个元素，以 $b_j$ 结尾时的最长子序列长度。

- 如果 $a_i = b_j$，则 $DP(i, j) = \max\limits_{k<j \land b_k < b_j}(DP(i,k)) + 1$
- 否则 $DP(i, j) = DP(i - 1, j)$。

这个东西可以滚动数组优化。

```cpp
int main() {
	int n;
	std::cin >> n;
	V<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	int m;
	std::cin >> m;
	V<int> b(m + 1);
	for (int j = 1; j <= m; j++) {
		std::cin >> b[j];
	}
	V<int> dp(m + 1), pre(m + 1, -1);
	for (int i = 1; i <= n; i++) {
		int p = 0;
		for (int j = 1; j <= m; j++) {
			if (a[i] == b[j]) {
				dp[j] = dp[p] + 1, pre[j] = p;
			} else if (a[i] > b[j] && dp[p] < dp[j]) {
				p = j;
			}
		}
	}
	int p = std::max_element(dp.begin(), dp.end()) - dp.begin();
	V<int> ans;
	while (p > 0) {
		ans.push_back(b[p]);
		p = pre[p];
	}
	std::reverse(ans.begin(), ans.end());
	std::cout << ans.size() << '\n';
	for (auto i : ans) {
		std::cout << i << ' ';
	}
	return 0;
}
```

{{<full-code url="Codeforces/other/10D.cpp">}}
