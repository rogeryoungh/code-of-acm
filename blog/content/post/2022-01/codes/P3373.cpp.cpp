// Author: Roger Young
// Date: 2022-01-29 18:57:59.717564

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using i128 = __int128_t;
using u64 = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define _dbg(...) 1
#define dbg(x) 1

ll rr() {
    ll s = 0, w = false, c = getchar();
    for (; !isdigit(c); c = getchar())
        w = w || c == '-';
    for (; isdigit(c); c = getchar())
        s = s * 10 + c - '0';
    return w ? -s : s;
}

// END OF HEADER

const int P = 571373;

template <class T>
struct SegmentTree {
    const vector<T> &a;
    struct Seg {
        int l, r;
        T val, m, k;
    };
    vector<Seg> tr;
#define ls (p * 2)
#define rs (p * 2 + 1)

    SegmentTree(const vector<T> &_a, int l, int r) : a(_a) {
        int N = r - l + 1;
        tr.resize(N * 4);
        build(l, r);
    }
    void pushup(int p) {
        tr[p].val = (tr[ls].val + tr[rs].val) % P;
    }
    inline ll len(int p) {
        return tr[p].r - tr[p].l + 1;
    }
    void pushdown(int p) {
        ll &m = tr[p].m, &k = tr[p].k;
        if (m != 0 || k != 1) {
            tr[ls].k = tr[ls].k * k % P;
            tr[rs].k = tr[rs].k * k % P;
            tr[ls].m = (tr[ls].m * k + m) % P;
            tr[rs].m = (tr[rs].m * k + m) % P;
            tr[ls].val = (tr[ls].val * k + m * len(ls)) % P;
            tr[rs].val = (tr[rs].val * k + m * len(rs)) % P;
            m = 0, k = 1;
        }
    }
    void build(int l, int r, int p = 1) {
        tr[p] = {l, r, 0, 0, 1};
        if (l == r) {
            tr[p].val = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        pushup(p);
    }
    void modify(int l, int r, T k, T m, int p = 1) { // do  kx + m
        if (l <= tr[p].l && tr[p].r <= r) {
            tr[p].val = (k * tr[p].val + m * len(p)) % P;
            tr[p].k = tr[p].k * k % P;
            tr[p].m = (tr[p].m * k + m) % P;
            return;
        }
        pushdown(p);
        int mid = (tr[p].l + tr[p].r) / 2;
        if (l <= mid)
            modify(l, r, k, m, ls);
        if (r > mid)
            modify(l, r, k, m, rs);
        pushup(p);
    }
    T query(int l, int r, int p = 1) {
        if (l <= tr[p].l && tr[p].r <= r) {
            return tr[p].val;
        }
        pushdown(p);
        int mid = (tr[p].l + tr[p].r) / 2;
        T v = T();
        if (l <= mid)
            v += query(l, r, ls);
        if (r > mid)
            v += query(l, r, rs);
        return v % P;
    }
#undef ls
#undef rs
};

int main() {
    int n = rr(), m = rr(), tp = rr();
    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++)
        v[i] = rr();
    SegmentTree<ll> st(v, 1, n);
    while (m--) {
        int op = rr();
        if (op == 1) {
            ll x = rr(), y = rr(), k = rr();
            st.modify(x, y, k, 0);
        } else if (op == 2) {
            ll x = rr(), y = rr(), k = rr();
            st.modify(x, y, 1, k);
        } else {
            int x = rr(), y = rr();
            printf("%lld\n", st.query(x, y));
        }
    }
    return 0;
}
