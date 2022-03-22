vector<char> notp;
vector<int> prime;
void Eratosthenes(int n) {
    notp.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!notp[i]) {
            prime.push_back(i);
            int tn = n / i;
            for (int j = i; j < tn; j++)
                notp[i * j] = true;
        }
    }
}