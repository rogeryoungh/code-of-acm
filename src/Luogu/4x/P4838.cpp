#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const int P = 19260817;

struct QMtx {
    vector<ll> m;
    int n;
    QMtx(int n_)  {
        n = n_;
        m.resize(n * n);
    }
    auto operator[](int i) {
        return m.begin() + i * n;
    }
    auto operator[](int i) const {
        return m.begin() + i * n;
    }
    static QMtx E(int n) {
        QMtx e(n);
        for (int i = 0; i < n; i++) {
            e[i][i] = 1;
        }
        return e;
    }
    QMtx pow(ll w);
};

QMtx operator*(const QMtx &lhs, const QMtx &rhs){
    assert(lhs.n == rhs.n);
    int n = lhs.n;
    QMtx u(n);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            ll t = lhs[i][k];
            for (int j = 0; j < n; j++) {
                u[i][j] += rhs[k][j] * t;
                u[i][j] %= P;
            }
        }
    }
    return u;
}

QMtx QMtx::pow(ll w) {
    QMtx ret = QMtx::E(n), a = *this;
    for(; w > 0; w >>= 1) {
        if(w & 1)
            ret = a * ret;
        a = a * a;
    }
    return ret;
}

int main() {
    QMtx mtx(3);
    mtx.m = {1, 1, 1, 1, 0, 0, 0, 1, 0};
    int T;
    cin >> T;
    while (T--) {
        ll n;
        cin >> n;
        QMtx t = mtx.pow(n);
        ll ans = t[0][0] + t[1][0] + t[2][0];
        cout << ans % P << "\n";
    }
	return 0;
}
