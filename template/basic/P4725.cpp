// Problem: P4726 【模板】多项式指数函数（多项式 exp）
// URL: https://www.luogu.com.cn/problem/P4726
//
// Powered by CP Editor (https://cpeditor.org)

#include "template/index.hpp"

#define ACM_MOD 998244353
const ll mod = ACM_MOD;

using poly_t = std::vector<int>;

poly_t ff, ans, Inv, w;

#include "template/basic/qpow.hpp"
#include "template/basic/inv.hpp"
#include "template/basic/mo.hpp"
#include "template/basic/init_inv.hpp"

#include "template/poly-ntt/ntt_init.hpp"
#include "template/poly-ntt/ntt.hpp"
#include "template/poly-ntt/ntt_inv.hpp"

#include "template/poly-ntt/ntt_d.hpp"
#include "template/poly-ntt/ntt_int.hpp"
#include "template/poly-ntt/ntt_ln.hpp"

int main() {
    ll n = rr();
    int lim = ntt_init(n, n);
    ff.resize(lim);

    Inv = init_inv(lim);
    for (int i = 0; i < n; i++) {
        ff[i] = rr();
    }
    ans = ntt_ln(ff, lim);
    for (int i = 0; i < n; i++)
        printf("%d ", ans[i]);
    return 0;
}
