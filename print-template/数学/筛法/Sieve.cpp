vector<char> notp;
vector<int> prime, mu, phi;
void sieve(int n) {
    notp.resize(n + 1), mu.resize(n + 1), phi.resize(n + 1);
    phi[1] = mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!notp[i]) {
            prime.push_back(i);
            phi[i] = i - 1, mu[i] = -1;
        }
        int t = n / i;
        for (auto pj : prime) {
            int ti = i * pj;
            if (pj > t) break;
            notp[ti] = true;
            if (i % pj == 0) {
                phi[ti] = phi[i] * pj;
                mu[ti] = 0;
                break;
            }
            phi[ti] = phi[i] * (pj - 1);
            mu[ti] = - mu[i];
        }
    }
}