Poly Poly::mulT(Poly b) const {
    if (b.size() == 0)
        return Poly();
    int n = b.size();
    reverse(b.a.begin(), b.a.end());
    return ((*this) * b).divxk(n - 1);
}
vector<int> Poly::eval(vector<int> x) const {
    if (size() == 0)
        return vector<int>(x.size(), 0);
    const int n = max(int(x.size()), size());
    vector<Poly> q(4 * n);
    vector<int> ans(x.size());
    x.resize(n);
    function<void(int, int, int)> build = [&](int p, int l, int r) {
        if (r - l == 1) {
            q[p] = vector<int>{1, (P - x[l]) % P};
        } else {
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            q[p] = q[2 * p] * q[2 * p + 1];
        }
    };
    build(1, 0, n);
    function<void(int, int, int, const Poly &)> work
            = [&](int p, int l, int r, const Poly &num) {
        if (r - l == 1) {
            if (l < int(ans.size()))
                ans[l] = num[0];
        } else {
            int m = (l + r) / 2, ls = 2 * p, rs = ls + 1;
            work(ls, l, m, num.mulT(q[rs]).modxk(m - l));
            work(rs, m, r, num.mulT(q[ls]).modxk(r - m));
        }
    };
    work(1, 0, n, mulT(q[1].inv(n)));
    return ans;
}
vector<int> Poly::inter(vector<int> x) const; // 咕咕咕