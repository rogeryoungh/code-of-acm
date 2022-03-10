#ifndef ACM_DS_SPARSETABLE_2_HPP
#define ACM_DS_SPARSETABLE_2_HPP

template <class T, class Merge>
struct SparseTable {
    using VT = vector<T>;
    VT st[32];
    SparseTable(const VT& v) {
        int n = v.size(), lgn = std::__lg(n);
        st[0] = v;
        for (int j = 1; j <= lgn; j++) {
            st[j].resize(n);
            int tj = 1 << (j - 1);
            for (int i = 0; i <= n - tj * 2; i++) {
                st[j][i] = Merge()(st[j - 1][i], st[j - 1][i + tj]);
            }
        }
    }
    T query(int l, int r) {
        int s = std::__lg(r - l + 1);
        return Merge()(st[s][l], st[s][r - (1 << s) + 1]);
    }
};

#endif
