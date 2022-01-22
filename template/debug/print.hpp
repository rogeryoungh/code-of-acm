#ifndef ACM_DEBUG_PRINT_H
#define ACM_DEBUG_PRINT_H

#define dbg(x) debug(x, #x)

//void debug(ll f, const char* s) {
//    _dbg("[ll] %s = %lld\n", s, f);
//}

void debug(int f, const char* s) {
    _dbg("[int] %s = %d\n", s, f);
}

void debug(pii f, const char* s) {
    _dbg("[pii] %s = (%d, %d)\n", s, f.first, f.second);
}

#ifdef ACM_NTT_POLY_H
void debug(const Poly& f, const char* s) {
    _dbg("[vec<m32>] %s = (%zu) ", s, f.size());
    for (auto &m : f) {
        int v = m.v;
//        if (v >= P / 2) {
//            v = v - P;
//        }
//        auto p = simp(v);
//        _dbg("%d/%d ", p.first, p.second);
        _dbg("%d ", v);
    }
    _dbg("\n");
}
#endif

#ifdef ACM_BASIC_MO_H
void debug(const m32& m, const char* s) {
    _dbg("[int] %s = %d\n", s, m.v);
}
#endif

void debug(const vector<int>& f, const char* s) {
    _dbg("[vec<int>] %s = (%zu) ", s, f.size());
    for (auto &i : f)
        _dbg("%d ", i);
    _dbg("\n");
}

void debug(const vector<ll>& f, const char* s) {
    _dbg("[vec<int>] %s = (%zu) ", s, f.size());
    for (auto &i : f)
        _dbg("%lld ", i);
    _dbg("\n");
}

#endif