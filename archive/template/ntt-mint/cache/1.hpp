#ifndef ACM_NTT_CACHE_H
#define ACM_NTT_CACHE_H

#include "template/ntt-mint/poly/0.hpp"

template<class T>
struct NttCache {
    std::map<T, Poly> maps;
    std::function<Poly(T)> exec;
    Poly& get(T key) {
        Poly& ret = maps[key];
        if (ret.empty())
            ret = exec(key);
        return ret;
    }
};

#endif
