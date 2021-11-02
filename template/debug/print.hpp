#ifndef ACM_DEBUG_PRINT_H
#define ACM_DEBUG_PRINT_H

#define dbg(x) debug(x, #x)

void debug(ll f, const char* s) {
    _dbg("[ll] %s = %lld\n", s, f);
}

void debug(int f, const char* s) {
    _dbg("[int] %s = %d\n", s, f);
}

#ifdef ACM_NTT_PRE_W_H
void debug(const poly_t& f, const char* s) {
    _dbg("[vec<Mint>] %s = (%zu) ", s, f.size());
    for (auto &m : f) {
        int v = m.v;
        if (v >= mod / 2) {
            v = v - mod;
        }
        _dbg("%d ", v);
    }
    _dbg("\n");
}
#endif

void debug(const vector<int>& f, const char* s) {
    _dbg("[vec<int>] %s = (%zu) ", s, f.size());
    for (auto &i : f)
        _dbg("%d ", i);
    _dbg("\n");
}

#endif