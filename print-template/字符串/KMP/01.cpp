ll pi[MN];
void pre_kmp(char* s, ll lens) {
    for (int i = 1; i < lens; i++) {
        ll j = pi[i-1];
        while(j && s[i] != s[j])
            j = pi[j-1];
        pi[i] = j + (s[i] == s[j]);
    }
}