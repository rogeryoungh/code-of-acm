#ifndef ACM_DS_SEGMENTTREE_1_HPP
#define ACM_DS_SEGMENTTREE_1_HPP

// 因为线段树变化太多了，封装不起来
#error "This file cannot be included."

template <class T>
struct SegmentTree {
    const vector<T> &a;
    struct Seg {
        int l, r;
        T val;
    };
    vector<Seg> tr;
    int N;
#define ls (p * 2)
#define rs (p * 2 + 1)

    SegmentTree(const vector<T> &_a, int l, int r) : a(_a) {
        N = (r - l + 1) * 4;
        tr.resize(N);
        build(l, r);
    }
    void pushup(int p) {
        tr[p].val = tr[ls].val + tr[rs].val;
    }
    void build(int l, int r, int p = 1) {
        tr[p] = {l, r, 0};
        if (l == r) {
            tr[p].val = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        pushup(p);
    }
    void modify(int i, int x, int p = 1) {
        if (tr[p].l == tr[p].r) {
            tr[p].val += x;
            return;
        }
        int mid = (tr[p].l + tr[p].r) / 2;
        if (i <= mid)
            modify(i, x, ls);
        else
            modify(i, x, rs);
        pushup(p);
    }
    T query(int l, int r, int p = 1) {
        if (l <= tr[p].l && tr[p].r <= r) {
            return tr[p].val;
        }
        int mid = (tr[p].l + tr[p].r) / 2;
        T v = T();
        if (l <= mid)
            v += query(l, r, ls);
        if (r > mid)
            v += query(l, r, rs);
        return v;
    }
#undef ls
#undef rs
};


#endif
