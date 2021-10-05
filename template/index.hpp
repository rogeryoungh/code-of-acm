#define RYLOCAL

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')

ll rr() {
    ll s = 0, w = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        s = s * 10 + c - '0';
        c = getchar();
    }
    return s * w;
}

// END OF HEADER
