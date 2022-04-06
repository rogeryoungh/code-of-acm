#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int ____ = (ios::sync_with_stdio(0), cin.tie(0), cout.tie(0), 1);

// END OF HEADER | Author: Roger Young

const ll P = 1e9 + 7;

struct Mtx {
    vector<ll> m;
    int x, y;
    Mtx(int x_, int y_) {
        x = x_, y = y_;
        m.resize(x * y);
    }
    auto operator[](int i) {
        return m.begin() + i * x;
    }
    auto operator[](int i) const {
        return m.begin() + i * x;
    }
    void read() {
        ll t;
        for (int i = 0; i < x * y; i++) {
            cin >> t;
            m[i] = (t + P) % P;
        }
    }
    void print() {
        for (int i = 0; i < x * y; i++) {
            cout << m[i] << " \n"[(i + 1) % x == 0];
        }
    }
};

Mtx operator*(const Mtx &lhs, const Mtx &rhs) {
    assert(lhs.x == rhs.y);
    Mtx u(rhs.x, lhs.y);
    for (int i = 0; i < lhs.y; i++) {
        for (int k = 0; k < lhs.x; k++) {
            ll t = lhs[i][k];
            for (int j = 0; j < rhs.x; j++) {
                u[i][j] += rhs[k][j] * t;
                u[i][j] %= P;
            }
        }
    }
    return u;
}

int main() {
    int n, p, m;
    cin >> n >> p >> m;
    Mtx aa(p, n), bb(m, p);
    aa.read();
    bb.read();
    Mtx cc = aa * bb;
    cc.print();

    return 0;
}
