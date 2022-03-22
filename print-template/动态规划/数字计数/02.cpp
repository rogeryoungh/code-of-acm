// 预计算
ll dp[20], m = 1;
for (int i = 1; i <= 9; i++) {
    dp[i] = dp[i - 1] * 9 + m;
    m *= 10;
}
ll addup(ll n, ll x) {
    ll m = 1, i = 0;
    while (m <= n)  i++, m *= 10;
    ll ans = 0, t;
    while (m) {
        t = n / m, n = n % m;
        ans += t * dp[i];
        if (t == x) {
            ans += n + 1;
            break;
        } else if (t > x) {
            ans += - dp[i] + m;
        }  i--, m /= 10;
    }  return ans;
}