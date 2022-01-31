#ifndef ACM_DS_SEGMENTTREE_1_HPP
#define ACM_DS_SEGMENTTREE_1_HPP

template <class T>
struct SegmentTree {
    const vector<T> &a;
    vector<T> tr;
    int N;
#define ls (i * 2)
#define rs (i * 2 + 1)

    SegmentTree(const vector<T> &_a, int l, int r)
            : a(_a) {
        int n = r - l + 1;
        N = 2 << std::__lg(n);
        tr.resize(N * 2 + 2);
        for (int i = N; i <= N + n; i++)
            tr[i] = a[i - N];
        for (int i = N; i > 0; i--)
            pushdown(i);
    }
    void pushdown(int i) {
        tr[i] = tr[ls] + tr[rs];
    }
    void modify(int i, T x) {
        tr[i += N] += x;
        for (i /= 2; i; i /= 2) {
            pushdown(i);
        }
    }
    T query(int l, int r) {
        T v = T();
        for (l += N - 1, r += N + 1; l ^ r ^ 1; l /= 2, r /= 2) {
            if (~l & 1)
                v += tr[l ^ 1];
            if (r & 1)
                v += tr[r ^ 1];
        }
        return v;
    }
#undef ls
#undef rs
};


#endif
