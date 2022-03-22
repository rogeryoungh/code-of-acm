for (int j = 0; j < lg2n; j++) {
    ll tj = 1 << j;
    ll ti = n - (1 << (j+1)) + 1;
    for (int i = 1; i <= ti; i++)
        ST[i][j + 1] = max(ST[i][j], ST[i + tj][j]);
}