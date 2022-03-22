void Floyd() {
    _fora (k, 1, n) {  _fora (i, 1, n) {
        if (i == k || f[i][k] == 0x3f3f3f3f)
            continue;
        _fora (j, 1, n)
            f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    } }
}