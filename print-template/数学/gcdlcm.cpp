ll gcd(ll a, ll b) 
    return a ? gcd(b % a, a) : b;
ll lcm(ll a, ll b)
    return a / gcd(b % a, a) * b;
ll gcd(ll a, ll b)
    while(b) { ll t=a%b; a=b; b=t; } return a;