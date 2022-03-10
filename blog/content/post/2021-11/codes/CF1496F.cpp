#include "template/index-debug.hpp"
#include "template/debug.hpp"

const int P = 998244353, N = 400 + 5;

vector<int> G[N];
int f[N][N], ans[N][N];

int main() {
    ll n = rr(), m = rr();
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
        f[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int x = rr(), y = rr();
        G[x].push_back(y), G[y].push_back(x);
        f[x][y] = f[y][x] = 1;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (i == k || f[i][k] == 0x3f3f3f3f)
                continue;
            for (int j = 1; j <= n; j++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ll tans = 1, cnt = 0;
            for (int k = 1; k <= n; k++) {
                if (f[i][k] + f[j][k] == f[i][j]) {
                    cnt++;
                } else {
                    int s = 0;
                    for (auto e : G[k]) {
                        s += f[i][e] + 1 == f[i][k] && f[j][e] + 1 == f[j][k];
                    }
                    tans = tans * s % P;
                }
            }
            if (cnt != f[i][j] + 1) {
                tans = 0;
            }
            ans[i][j] = ans[j][i] = tans;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}
