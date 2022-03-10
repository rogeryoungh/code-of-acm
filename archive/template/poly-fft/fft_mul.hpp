#ifndef ACM_FFT_MUL_H
#define ACM_FFT_MUL_H

#ifndef RYLOCAL
#include "__base.hpp"
#endif

vector<int> mul(const vector<int> &a, const vector<int> &b) {
    int n = a.size(), m = b.size(), lim = get_lim(n + m - 1);
    Poly f(lim);
    for (int i = 0; i < n; i++)
        f[i].x = a[i];
    for (int i = 0; i < m; i++)
        f[i].y = b[i];
    fft(f);
    for (int i = 0; i < lim; i++)
        f[i] = f[i] * f[i];
    ifft(f);
    vector<int> ans(n + m - 1);
    for (int i = 0; i < n + m - 1; i++)
        ans[i] = int(f[i].y / 2 + 0.5);
    return ans;
}

vector<i128> int_mul(const vector<int> &a, const vector<int> &b) {
    const int LIM = 1 << 15;
    int n = a.size(), m = b.size(), lim = get_lim(n + m - 1);
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
    vector<i128> ans(n + m - 1);

    for (int i = 0; i < m + n - 1; i++) {
        i128 a1b1 = (A1[i].x + A2[i].x + 1) / 2;
        i128 a1b2 = (A1[i].y + A2[i].y + 1) / 2;
        i128 a2b1 = (A1[i].y - A2[i].y + 1) / 2;
        i128 a2b2 = (A2[i].x - A1[i].x + 1) / 2;
        ans[i] = (a1b1 * LIM + a1b2 + a2b1) * LIM + a2b2;
    }
    return ans;
}

#endif