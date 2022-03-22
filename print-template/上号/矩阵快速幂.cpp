struct QMtx {
    ll m[5][5], n;
    QMtx(ll _n) : n(_n) {
        memset(m, 0, sizeof(m));
    }
    auto operator[](int n) /*const*/ {
        return m[n];
    }
};
QMtx operator*(QMtx &m1, QMtx &m2);
QMtx operator^(QMtx m, ll n) {
    QMtx ret(m.n);
    for (int i = 1; i <= m.n; i++)
        ret[i][i] = 1;
    for(; n > 0; n >>= 1) {
        if(n & 1)
            ret = m * ret;
        m = m * m;
    }
    return ret;
}