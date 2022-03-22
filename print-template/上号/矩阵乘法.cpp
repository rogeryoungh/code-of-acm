struct Mtx {
    ll m[505][505], p, q;
    Mtx(ll xx, ll yy) {
        p = xx, q = yy;
        memset(m, 0, sizeof(m));
    }
    auto operator[](int n) /*const*/ {
        return m[n];
    }
};
Mtx operator*(Mtx &m1, Mtx &m2) {
    Mtx c(m1.p, m2.q);
    for (int i = 1; i <= m1.p; i++) {
        for (int k = 1; k <= m1.q; k++) {
            ll t = m1[i][k];
            for (int j = 1; j <= m2.q; j++)
                c[i][j] = (c[i][j] + m2[k][j] * t) % P;
        }
    }
    return c;
}