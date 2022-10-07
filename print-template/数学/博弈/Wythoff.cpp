const double phi = (sqrt(5.0) + 1) / 2;
bool Wythoff(ll a, ll b) {  // 判先手输赢
    return ll(abs(b - a) * phi) != a;
}