int addup(int n, int x) {
    int ans = 0, m = 1;
    while (m <= n){
        int a = n / (m * 10), b = n / m % 10, c = n % m;
        if (x > 0){
            if (b > x) ans += m;
            else if (b == x) ans += c + 1;
        } else if (b == 0) {
            ans += c + 1 - m;
        }  ans += a * m, m *= 10;
    }  return ans;
}