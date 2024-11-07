#include <bits/stdc++.h>

#define V std::vector
using i64 = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young

const int N = 5E5 + 5;

struct fwtree {
  std::vector<int> v;
  fwtree(int n) : v(n) {}
  void add(int i, int x) {
    while (i <= v.size()) {
      v[i] += x;
      i += i & -i;
    }
  }
  int query(int i) {
    int sum = 0;
    while (i > 0) {
      sum += v[i];
      i -= i & -i;
    }
    return sum;
  }
};

int main() {
  int n;
  std::cin >> n;
  std::vector<int> v(n + 1), rank(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> v[i];
    rank[i] = i;
  }
  fwtree tr(n + 1);
  std::sort(rank.begin() + 1, rank.begin() + n + 1, [&](int l, int r) {
    if (v[l] == v[r])
      return l < r;
    else
      return v[l] < v[r];
  });

  i64 ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += i - tr.query(rank[i]) - 1;
    tr.add(rank[i], 1);
  }
  std::cout << ans;

  return 0;
}
