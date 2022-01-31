#ifndef ACM_DS_FWTREE_1_HPP
#define ACM_DS_FWTREE_1_HPP

template <class T>
struct fwtree_1 {
    int len;
    vector<T> v;
    fwtree_1(int l = 0) : len(l), v(len) {}

    fwtree_1(const vector<T> &_v) : fwtree_1(_v.size()) {
        for (int i = 1; i < len; i++) {
            v[i] += _v[i];
            int j = i + (i & -i);
            if (j < len)
                v[j] += v[i];
        }
    }
    void modify(int i, T x) {
        for (; i < len; i += i & -i)
            v[i] += x;
    }
    T query(int i) {
        T sum = 0;
        for (; i > 0; i -= i & -i)
            sum += v[i];
        return sum;
    }
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};


#endif
