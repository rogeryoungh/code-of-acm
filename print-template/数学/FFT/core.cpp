struct img {
    ld x = 0, y = 0;
    void f(ld xx, ld yy) {
        x = xx, y = yy;
    }
    img operator+(const img &c) {
        return (img){x + c.x, y + c.y};
    }
    img operator-(const img &c) {
        return (img){x - c.x, y - c.y};
    }
    img operator*(const img &c) {
        ld tx = x * c.x - y * c.y;
        ld ty = x * c.y + y * c.x;
        return (img){tx, ty};
    }
    img operator/(ld c) {
        return (img){x / c, y / c};
    }
};

using Poly = vector<img>;

const ld PI = acos(-1.0);
Poly w;

int get_lim(int sum) {
    int lim = 1;
    while (lim < sum)
        lim <<= 1;
    return lim;
}
Poly pre_w(int sum) {
    int lim = get_lim(sum);
    Poly w(lim);
    for (int l = 1; l < lim; l <<= 1) {
        img p; // w[j + l] = w_{2l} ^ j
        p.f(cos(PI / l), sin(PI / l)), w[l].f(1, 0);
        for (int i = 1; i < l; i++)
            w[l + i] = w[l + i - 1] * p;
    }
    return w;
}
void fft(Poly &f) {
    int deg = f.size();
    for (int l = deg >> 1; l; l >>= 1)
        for (int i = 0; i < deg; i += (l << 1))
            for (int j = 0; j < l; j++) {
                img x = f[i + j] + f[i + j + l];
                f[i + j + l] = w[j + l] * (f[i+j] - f[i+j+l]);
                f[i + j] = x;
            }
}
void ifft(Poly &f) {
    int deg = f.size();
    for (int l = 1; l < deg; l <<= 1)
        for (int i = 0; i < deg; i += (l << 1))
            for (int j = 0; j < l; j++) {
                img x = f[i + j], y = f[i + j + l] * w[j + l];
                f[i + j] = x + y, f[i + j + l] = x - y;
            }
    for (int i = 0; i < deg; i++)
        f[i] = f[i] / deg;
    reverse(f.begin() + 1, f.end());
}
vector<int> intmod_mul(vector<int> &a, vector<int> &b,int p) {
    const ll LIM = 1 << 15;
    int n = a.size(), m = b.size();
    int lim = get_lim(n + m - 1);
    Poly A1(lim), A2(lim), Q(lim);
    for (int i = 0; i < n; i++) {
        A1[i].f(a[i] / LIM, a[i] % LIM);
        A2[i].f(a[i] / LIM, -a[i] % LIM);
    }
    for (int i = 0; i < m; i++) {
        Q[i].f(b[i] / LIM, b[i] % LIM);
    }
    fft(A1), fft(A2), fft(Q);
    for (int i = 0; i < lim; i++)
        A1[i] = A1[i] * Q[i];
    for (int i = 0; i < lim; i++)
        A2[i] = A2[i] * Q[i];
    ifft(A1);
    ifft(A2);
    vector<int> ans(n + m - 1);
    for (int i = 0; i < m + n - 1; i++) {
        ll a1b1 = ll((A1[i].x + A2[i].x + 1) / 2) % p;
        ll a1b2 = ll((A1[i].y + A2[i].y + 1) / 2) % p;
        ll a2b1 = ll((A1[i].y - A2[i].y + 1) / 2) % p;
        ll a2b2 = ll((A2[i].x - A1[i].x + 1) / 2) % p;
        ll tans = a1b1 * LIM + a1b2 + a2b1;
        tans = (tans * LIM + a2b2) % p;
        ans[i] = (tans + p) % p;
    }
    return ans;
}