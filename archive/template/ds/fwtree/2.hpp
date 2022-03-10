#ifndef ACM_DS_FWTREE_2_HPP
#define ACM_DS_FWTREE_2_HPP

template<class T>
struct fwtree_2 {
    int len;
    vector <T> v1, v2, u;

    fwtree_2(int l = 0) : len(l), u(len), v1(len), v2(len) {}

    fwtree_2(const vector <T> &_v) : fwtree_2(_v.size()) {
        for (int i = 1; i < len; i++) {
            u[i] += _v[i];
            int j = i + (i & -i);
            if (j < len)
                u[j] += u[i];
        }
    }

    void modify(int l, int r, T k) {
        modify(v1, l, k);
        modify(v1, r + 1, -k);
        modify(v2, l, l * k);
        modify(v2, r + 1, -(r + 1) * k);
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }

  private:
    void modify(vector <T> &v, int i, T x) {
        for (; i < len; i += i & -i)
            v[i] += x;
    }
    T query(vector <T> &v, int i) {
        T sum = 0;
        for (; i > 0; i -= i & -i)
            sum += v[i];
        return sum;
    }

    T query(int i) {
        return T(i + 1) * query(v1, i) + query(u, i) - query(v2, i);
    }
};


#endif
