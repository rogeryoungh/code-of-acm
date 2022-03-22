for (int i = 1; i <= n; i++)
    for (int j = v[i]; j <= m; j++)
        dp[j] = max(dp[j], dp[j-v[i]] + w[i]);
for (int j = 1; j <= m; j++)
    ans = max(ans, dp[j]);