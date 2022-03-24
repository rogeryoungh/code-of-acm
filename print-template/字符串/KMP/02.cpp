string s, t;
auto pi = pre_kmp(s);
int p = 0, n = t.length();
for (int i = 0; i < n; i++) {
    int j = p;
    while (j > 0 && t[i] != s[j]) {
        j = pi[j - 1];
    }
    p = j + (t[i] == s[j]);
    if(p == s.len())
        // 出现起始 i - s.len() + 2
}
