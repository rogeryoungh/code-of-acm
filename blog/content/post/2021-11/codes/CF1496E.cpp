#include "template/index-debug.hpp"
#include "template/debug.hpp"

vector<int> p, v;

void pre(ll n) {
    p.resize(n);
    for (int i = 0; i < n; i++)
        p[i] = rr();
    ll u = 1, tend = p[1] - p[0];
    for (int i = 1; i < n; i++) {
        ll mul = (p[i] - p[i - 1]) * tend;
        if (mul > 0)
            continue;
        v.push_back(i - u + 1);
        tend = -tend, u = i;
    }
    v.push_back(n - u + 1);
}

int main() {
    ll n = rr();
    pre(n);

    ll ml = 0, mr = 0;
    ll tend = p[1] - p[0], flag = tend;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] > v[ml])
            ml = mr = i, flag = tend;
        else if (v[i] == v[ml])
            mr = i;
        tend = -tend;
    }

    if (mr - ml == 1 && flag > 0 && v[ml] % 2 == 1) {
        printf("1");
    } else {
        printf("0");
    }
    return 0;
}
