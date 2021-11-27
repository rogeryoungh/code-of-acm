// GENERATE FROM https://github.com/rogeryoungh/code-of-acm
// GENERATE DATE: 2021-11-18 21:04:40.415830

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int, int>;

#define _fore(i, a) for (ll i = head[(a)]; i; i = edge[i].nxt)
#define LN putchar('\n')
#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
    ll s = 0, w = 1;
    char c = getchar();
    while (!isdigit(c))
        w = 1 - 2 * (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return s * w;
}

// END OF HEADER



char ss[505][505];

int main() {
    ll T = rr();
    while (T--) {
        ll n = rr(), m = rr();
        for (int i = 0; i < n; i++) {
            scanf("%s", ss[i]);
        }
        ll begin = 1;
        if (n % 3 == 1) {
            begin = 0;
        }
        for (int i = begin; i < n; i += 3) {
            for (int j = 0; ss[i][j] != 0; j++) {
                ss[i][j] = 'X';
            }
            if (i + 2 < n) {
                if (ss[i + 1][1] == 'X' || ss[i + 2][1] == 'X') {
                    ss[i + 1][1] = ss[i + 2][1] = 'X';
                } else {
                    ss[i + 1][0] = ss[i + 2][0] = 'X';
                }
            }
        }
        for (int i = 0; i < n; i++) {
            printf("%s\n", ss[i]);
        }
    }
    return 0;
}
