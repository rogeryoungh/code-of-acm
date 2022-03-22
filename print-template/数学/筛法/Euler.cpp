vector<char> notp;
vector<int> prime;
void Euler(int n) {
    notp.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!notp[i])
            prime.push_back(i);
        int t = n / i;
        for (auto pj : prime) {
            if (pj > t)
                break;
            notp[i * pj] = true;
            if (i % pj == 0)
                break;
        }
    }
}