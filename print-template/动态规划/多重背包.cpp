int tm = 1;
for (int i = 1; i <= n; i++) {
    int vi = rr(), ci = rr(), wi = rr();
    if (wi == 0)
        wi = 99999;
    int b = 1;
    for (int b = 1; b < wi; b *= 2) {
        v[tm] = vi * b, w[tm] = ci * b;
        wi -= b, tm++;
    }
    v[tm] = vi * wi, w[tm] = ci * wi;
    tm++;
}
for (int i = 1; i <= tm - 1; i++)
    for (int j = tsum; j >= v[i]; j--)
        dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
ll ans = 0;
for (int i  = 0; i <= tsum; i++)
    ans = max(dp[i], ans);