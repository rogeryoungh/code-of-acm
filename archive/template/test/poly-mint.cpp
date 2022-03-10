#include "template/index-debug.hpp"

#define ACM_MOD 998244353
const int P = ACM_MOD;

#include "template/basic/qpow.hpp"
#include "template/basic/mint/0.hpp"

#include "template/ntt-mint/poly.hpp"
Poly w, Inv;

#include "template/ntt-mint/pre-w/0.hpp"
#include "template/ntt-mint/pre-inv/0.hpp"
#include "template/ntt-mint/ntt/0.hpp"
#include "template/ntt-mint/mul/0.hpp"

#include "template/debug.hpp"

#include "template/ntt-mint/inv/0.hpp"

#include "template/ntt-mint/deriv/0.hpp"
#include "template/ntt-mint/integr/0.hpp"
#include "template/ntt-mint/ln/0.hpp"
#include "template/ntt-mint/ntt_exp.hpp"
#include "template/ntt-mint/ntt_sqrt.hpp"
#include "template/ntt-mint/ntt_pow.hpp"

#include "template/ntt-mint/ntt_quo.hpp"

#include "template/ntt-mint/ntt_cdq.hpp"

bool operator==(Mint a, Mint b) {
    return a.v == b.v;
}

void poly_ntt_test() {
    Poly f = {1, 2, 3, 4};
    f.ntt(4);
    Poly corret = {10, 998244351, 173167434, 825076915};
    bool check = f == corret;
    if (!check) {
        cerr << "NTT #1 ERROR" << endl;
        dbg(f), dbg(corret);
    }
}

void poly_intt_test() {
    Poly f = {10, 998244351, 173167434, 825076915};
    f.intt(4);
    Poly corret = {1, 2, 3, 4};
    bool check = f == corret;
    if (!check) {
        cerr << "INTT #1 ERROR" << endl;
        dbg(f), dbg(corret);
    }
}

void poly_mul_test() {
    Poly f = {1, 2, 3};
    f = f * f;
    Poly correct = {1, 4, 10, 12, 9};
    bool check = f == correct;
    if (!check) {
        cerr << "NTT-MUL #1 ERROR" << endl;
        dbg(f), dbg(correct);
    }
}

void poly_inv_test() {
    Poly f = {1, 6, 3, 4, 9};
    f = f.inv();
    Poly correct = {1, 998244347, 33, 998244169, 1020};
    bool check = f == correct;
    if (!check) {
        cerr << "NTT-INV #1 ERROR" << endl;
        dbg(f), dbg(correct);
    }
}

void poly_cdq_inv_test() {
    Poly f = {1, 6, 3, 4, 9};
    f = f.inv();
    Poly correct = {1, 998244347, 33, 998244169, 1020};
    bool check = f == correct;
    if (!check) {
        cerr << "NTT-CDQ-INV #1 ERROR" << endl;
        dbg(f), dbg(correct);
    }
    f = f * f, f = f * f, f = f * f, f = f * f, f = f * f, f = f * f;
    f[0] = 0;
    correct = f.inv();
    f = PolyCDQ(f).inv();
    check = f == correct;
    if (!check) {
        cerr << "NTT-CDQ-INV #2 ERROR" << endl;
        dbg(f), dbg(correct);
    }
}

void poly_deriv_test() {
    Poly f = {1, 1, 1, 1, 1};
    f = f.deriv();
    Poly correct = {1, 2, 3, 4};
    bool check = f == correct;
    if (!check) {
        cerr << "NTT-DERIV #1 ERROR" << endl;
        dbg(f), dbg(correct);
    }
}

void poly_integr_test() {
    Poly f = {1, 2, 3, 4};
    f = f.integr();
    Poly correct = {0, 1, 1, 1, 1};
    bool check = f == correct;
    if (!check) {
        cerr << "NTT-INTEGR #1 ERROR" << endl;
        dbg(f), dbg(correct);
    }
}

void poly_ln_test() {
    Poly f = {1, 927384623, 878326372, 3882, 273455637, 998233543};
    f = f.ln();
    Poly correct = {0, 927384623, 817976920, 427326948, 149643566, 610586717};
    bool check = f == correct;
    if (!check) {
        cerr << "NTT-LN #1 ERROR" << endl;
        dbg(f), dbg(correct);
    }
}

void poly_exp_test() {
    Poly f = {0, 927384623, 817976920, 427326948, 149643566, 610586717};
    f = f.exp();
    Poly correct = {1, 927384623, 878326372, 3882, 273455637, 998233543};
    bool check = f == correct;
    if (!check) {
        cerr << "NTT-EXP #1 ERROR" << endl;
        dbg(f), dbg(correct);
    }
}

void poly_cdq_exp_test() {
    Poly f = {0, 927384623, 817976920, 427326948, 149643566, 610586717};
    f = PolyCDQ(f).exp();
    Poly correct = {1, 927384623, 878326372, 3882, 273455637, 998233543};
    bool check = f == correct;
    if (!check) {
        cerr << "NTT-CDQ-EXP #1 ERROR" << endl;
        dbg(f), dbg(correct);
    }
    f = f * f, f = f * f, f = f * f, f = f * f, f = f * f, f = f * f;
    f[0] = 0;
    correct = f.exp();
    f = PolyCDQ(f).exp();
    check = f == correct;
    if (!check) {
        cerr << "NTT-CDQ-EXP #2 ERROR" << endl;
        dbg(f), dbg(correct);
    }
}

void poly_sqrt_test() {
    Poly f = {1, 8596489, 489489, 4894, 1564, 489, 35789489};
    f = f.sqrt();
    Poly correct = {1, 503420421, 924499237, 13354513, 217017417, 707895465, 411020414};
    bool check = f == correct;
    if (!check) {
        cerr << "NTT-SQRT #1 ERROR" << endl;
        dbg(f), dbg(correct);
    }
}

void poly_pow_test() {
    Poly f = {1, 1, 0, 0};
    f = f.pow(3);
    Poly correct = {1, 3, 3, 1};
    bool check = f == correct;
    if (!check) {
        cerr << "NTT-POW #1 ERROR" << endl;
        dbg(f), dbg(correct);
    }
}

void poly_quo_test() {
    Poly f = {1, 9, 2, 6, 0, 8};
    Poly g = {1, 7};
    auto [Q, R] = f % g;
    Poly C1 = {237340659, 335104102, 649004347, 448191342, 855638018};
    Poly C2 = {760903695};
    bool check = Q == C1 && R == C2 ;
    if (!check) {
        cerr << "NTT-QUO #1 ERROR" << endl;
        dbg(Q), dbg(C1);
        dbg(R), dbg(C2);
    }
}

int main() {
    poly_ntt_test();
    poly_intt_test();
    poly_mul_test();
    poly_inv_test();
    poly_cdq_inv_test();
    poly_deriv_test();
    poly_integr_test();
    poly_ln_test();
    poly_exp_test();
    poly_cdq_exp_test();
    poly_sqrt_test();
    poly_pow_test();
    poly_quo_test();
    return 0;
}
