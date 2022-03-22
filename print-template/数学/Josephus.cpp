int Josephus(int n, int k) {
    int rst = 0;
    for (int i = 1; i <= n; i++)
        rst = (rst + k) % i;
    return rst;
}