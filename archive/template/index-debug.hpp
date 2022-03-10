#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <random>
#include <functional>

using namespace std;
using ll = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define _dbg(...) fprintf(stderr, __VA_ARGS__)

ll rr() {
    ll s = 0, w = false, c = getchar();
    for (; !isdigit(c); c = getchar()) {
        if (c == '-')
            w = true;
    }
    for (; isdigit(c); c = getchar()) {
        s = s * 10 + c - '0';
    }
    return w ? -s : s;
}

// END OF HEADER

