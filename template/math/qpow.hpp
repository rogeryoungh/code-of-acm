int qpow(int a, int b, int m) {
    int ret = m != 1;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = 1ll * ret * a % m;
        a = 1ll * a * a % m;
    }
    return ret;
}
