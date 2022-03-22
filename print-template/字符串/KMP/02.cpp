void kmp(char* s, ll lens, char* t, ll lent) {
    pre_kmp(s, lens);
    ll p = 0;
    for (int i = 0; i < lent; i++) {
        ll j = p;
        while(j && t[i] != s[j])
            j = pi[j-1];
        p = j + (t[i] == s[j]);
        if(p == lens)
            // 出现起始 i-lens+2       
    }
}