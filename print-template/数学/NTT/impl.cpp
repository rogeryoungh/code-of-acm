Poly deriv() const {
    Poly f(deg() - 1);
    for (int i = 1; i < deg(); i++)
        f[i - 1] = 1ll * i * T[i] % P;
    return f;
}
Poly integr() const {
    Poly f(deg() + 1);
    pre_inv(deg() + 1);
    for (int i = deg(); i > 0; --i)
        f[i] = 1ll * Inv[i] * T[i - 1] % P;
    return f;
}
Poly inv(int m) const { // 12E
    Poly x = {qpow(T[0])};
    for (int t = 2; t < m * 2; t *= 2) {
        Poly u = cut(t).ntt(t * 2);
        x.ntt(t * 2);
        for (int i = 0; i < t * 2; i++)
            x[i] = (P + 2 - 1ll * u[i] * x[i] % P) * x[i] % P;
        x.intt(t * 2).redeg(t);
    }
    return x.redeg(m);
}
Poly div(int m, const Poly &g) const { // 18E
    if (deg() == 0)
        return {};
    return (cut(m) * g.inv(m)).redeg(m);
}
Poly ln(int m) const {
    return deriv().div(m - 1, cut(m)).integr();
}
Poly exp(int m) const { // 48E
    Poly x = {1};
    for (int t = 2; t < m * 2; t *= 2) {
        x = x * (cut(t) - x.ln(t) + Poly{1}), x.redeg(t);
    }
    return x.redeg(m);
}
Poly sqrt(int m) const { // 36E
    Poly x = {1};
#ifdef ACM_MATH_CIPOLLA_H
    x[0] = Cipolla(front(), P).first;
#endif
    for (int t = 2; t < m * 2; t *= 2) {
        x = (x + cut(t).div(t, x)) * qpow(2);
    }
    return x.redeg(m);
}
Poly pow(int m, int k) const {
    return (ln(m) * k).exp(m);
}
Poly rev() const {
    return {rbegin(), rend()};
}
friend Poly operator/(const Poly &f, const Poly &g) {
    int m = f.deg() - g.deg() + 1;
    return f.rev().div(m, g.rev()).rev();
}
