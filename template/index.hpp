#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
    ll s = 0, w = false, c = getchar();
    for (; !isdigit(c); c = getchar())
        w = w || c == '-';
    for (; isdigit(c); c = getchar())
        s = s * 10 + c - '0';
    return w ? -s : s;
}

// END OF HEADER
