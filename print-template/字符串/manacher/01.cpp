char str[MN], st[MN * 2];
ll mp[MN * 2];
void Manacher(char *s, int len) {
    st[0] = st[1] = '#';
    int l = 2;
    for (int i = 0; i < len; i++)
        st[l++] = s[i], st[l++] = '#';
    st[l] = 0;
    int mx = 0, id = 0;
    for (int i = 0; i < l; i++) {
        mp[i] = mx > i ? min(mp[2 * id - i], mx - i) : 1;
        while (st[i + mp[i]] == st[i - mp[i]])
            mp[i]++;
        if (i + mp[i] > mx)
            mx = i + mp[i], id = i;
    }
}

int main() {
    scanf("%s", str);
    int len = strlen(str);
    Manacher(str, len);
    ll ans = 0;
    for (int i = 0; i < 2 * (len + 1); i++)
        ans = max(ans, mp[i] - 1);
    printf("%lld", ans);
    return 0;
}