Poly Poly::deriv() const {
    if (a.empty())
        return Poly();
    vector<int> res(size() - 1);
    for (int i = 0; i < size() - 1; ++i)
        res[i] = 1ll * (i + 1) * a[i + 1] % P;
    return Poly(res);
}
Poly Poly::integr() const {
    if (a.empty())
        return Poly();
    vector<int> res(size() + 1);
    for (int i = 0; i < size(); ++i)
        res[i + 1] = 1ll * a[i] * qpow(i + 1, P - 2) % P;
    return Poly(res);
}
Poly Poly::inv(int m) const {
    Poly x(qpow(a[0], P - 2));
    int k = 1;
    while (k < m) {
        k *= 2;
        x = (x * (2 - modxk(k) * x)).modxk(k);
    }
    return x.modxk(m);
}
Poly Poly::ln(int m) const {
    return (deriv() * inv(m)).integr().modxk(m);
}
Poly Poly::exp(int m) const {
    Poly x(1);
    int k = 1;
    while (k < m) {
        k *= 2;
        x = (x * (1 - x.ln(k) + modxk(k))).modxk(k);
    }
    return x.modxk(m);
}

Poly Poly::pow(int m, int k) const {
    return (ln(m) * k).exp(m);
}
Poly Poly::sqrt(int m) const {
    Poly x(1);
    int k = 1, inv2 = (P + 1) / 2;
    while (k < m) {
        k *= 2;
        x = (x + (modxk(k) * x.inv(k)).modxk(k)) * inv2;
    }
    return x.modxk(m);
}