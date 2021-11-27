#include "template/index-debug.hpp"
#include "template/debug.hpp"

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
