constexpr double phi = (sqrt(5.0) + 1) / 2;
int Wythoff(ll a, ll b) {  // 判先手输赢
    if (a > b) swap(a, b);
    ll t = (ll) (b - a) * phi;
    return t != a;
}