Object.assign(window.search, {"doc_urls":["intro/index.html#介绍","basic/index.html#介绍","math/index.html#数学","math/lower-upper.html#二分","math/lower-upper.html#测试例题","math/matrix.html#矩阵","math/matrix.html#测试例题","math/miller-rabbin.html#miller-rabbin-素性测试","math/miller-rabbin.html#测试例题","math/pollard-rho.html#pollard-rho-因式分解","math/pollard-rho.html#测试例题","math/floor-sum.html#floor-sum","math/floor-sum.html#测试例题","math/cipolla.html#cipolla-二次剩余","math/cipolla.html#测试例题"],"index":{"documentStore":{"docInfo":{"0":{"body":29,"breadcrumbs":0,"title":0},"1":{"body":0,"breadcrumbs":0,"title":0},"10":{"body":3,"breadcrumbs":2,"title":0},"11":{"body":3,"breadcrumbs":4,"title":2},"12":{"body":2,"breadcrumbs":2,"title":0},"13":{"body":2,"breadcrumbs":2,"title":1},"14":{"body":1,"breadcrumbs":1,"title":0},"2":{"body":0,"breadcrumbs":0,"title":0},"3":{"body":73,"breadcrumbs":0,"title":0},"4":{"body":2,"breadcrumbs":0,"title":0},"5":{"body":2,"breadcrumbs":0,"title":0},"6":{"body":1,"breadcrumbs":0,"title":0},"7":{"body":3,"breadcrumbs":4,"title":2},"8":{"body":1,"breadcrumbs":2,"title":0},"9":{"body":3,"breadcrumbs":4,"title":2}},"docs":{"0":{"body":"我的初始文件。 #include <bits/stdc++.h>\nusing namespace std;\nusing ll = int64_t; int ____ = cin.tie(nullptr)->sync_with_stdio(false); // END OF HEADER | Author: Roger Young int main() { int T; cin >> T; while (T--) { cout << \"X\" << '\\n'; } return 0;\n}","breadcrumbs":"介绍 » 介绍","id":"0","title":"介绍"},"1":{"body":"","breadcrumbs":"杂项 » 介绍","id":"1","title":"介绍"},"10":{"body":"P4718 Pollard-Rho算法","breadcrumbs":"数学 » Pollard Rho 因式分解 » 测试例题","id":"10","title":"测试例题"},"11":{"body":"{{#include floor-sum.cpp.full}}","breadcrumbs":"数学 » Floor Sum » Floor Sum","id":"11","title":"Floor Sum"},"12":{"body":"P5171 Earthquake","breadcrumbs":"数学 » Floor Sum » 测试例题","id":"12","title":"测试例题"},"13":{"body":"{{#include cipolla.cpp.full}}","breadcrumbs":"数学 » Cipolla 二次剩余 » Cipolla 二次剩余","id":"13","title":"Cipolla 二次剩余"},"14":{"body":"P5491 二次剩余","breadcrumbs":"数学 » Cipolla 二次剩余 » 测试例题","id":"14","title":"测试例题"},"2":{"body":"","breadcrumbs":"数学 » 数学","id":"2","title":"数学"},"3":{"body":"using ll = long long; // @description 二分\n// @problem https://www.luogu.com.cn/problem/P1873 template <class Comp> // last true\nll lower(ll l, ll r, Comp check) { if (l >= r or not check(l)) return r; while (r - l > 1) { ll m = l + (r - l) / 2; (check(m) ? l : r) = m; } return l;\n} template <class Comp> // first true\nll upper(ll l, ll r, Comp check) { if (l >= r or not check(r - 1)) return r; while (r - l > 1) { ll m = l + (r - l) / 2; (check(m - 1) ? r : l) = m; } return l;\n}","breadcrumbs":"数学 » 二分 » 二分","id":"3","title":"二分"},"4":{"body":"P1873 EKO / 砍树","breadcrumbs":"数学 » 二分 » 测试例题","id":"4","title":"测试例题"},"5":{"body":"{{#include matrix.cpp.full}}","breadcrumbs":"数学 » 矩阵 » 矩阵","id":"5","title":"矩阵"},"6":{"body":"LOJ100 矩阵乘法","breadcrumbs":"数学 » 矩阵 » 测试例题","id":"6","title":"测试例题"},"7":{"body":"{{#include miller-rabbin.cpp.full}}","breadcrumbs":"数学 » Miller Rabbin 素性测试 » Miller Rabbin 素性测试","id":"7","title":"Miller Rabbin 素性测试"},"8":{"body":"LOJ143 质数判定","breadcrumbs":"数学 » Miller Rabbin 素性测试 » 测试例题","id":"8","title":"测试例题"},"9":{"body":"{{#include pollard-rho.cpp.full}}","breadcrumbs":"数学 » Pollard Rho 因式分解 » Pollard Rho 因式分解","id":"9","title":"Pollard Rho 因式分解"}},"length":15,"save":true},"fields":["title","body","breadcrumbs"],"index":{"body":{"root":{"0":{"df":1,"docs":{"0":{"tf":1.0}}},"1":{"df":1,"docs":{"3":{"tf":2.0}}},"2":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}},"_":{"_":{"_":{"_":{"df":1,"docs":{"0":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"a":{"df":0,"docs":{},"u":{"df":0,"docs":{},"t":{"df":0,"docs":{},"h":{"df":0,"docs":{},"o":{"df":0,"docs":{},"r":{"df":1,"docs":{"0":{"tf":1.0}}}}}}}},"b":{"df":0,"docs":{},"i":{"df":0,"docs":{},"t":{"df":0,"docs":{},"s":{"/":{"df":0,"docs":{},"s":{"df":0,"docs":{},"t":{"d":{"c":{"+":{"+":{".":{"df":0,"docs":{},"h":{"df":1,"docs":{"0":{"tf":1.0}}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}}}},"df":0,"docs":{}}}}},"c":{"df":0,"docs":{},"h":{"df":0,"docs":{},"e":{"c":{"df":0,"docs":{},"k":{"(":{"df":0,"docs":{},"l":{"df":1,"docs":{"3":{"tf":1.0}}},"m":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}},"r":{"df":1,"docs":{"3":{"tf":1.0}}}},"df":1,"docs":{"3":{"tf":1.4142135623730951}}}},"df":0,"docs":{}}},"i":{"df":0,"docs":{},"n":{".":{"df":0,"docs":{},"t":{"df":0,"docs":{},"i":{"df":0,"docs":{},"e":{"(":{"df":0,"docs":{},"n":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":0,"docs":{},"l":{"df":0,"docs":{},"p":{"df":0,"docs":{},"t":{"df":0,"docs":{},"r":{"df":1,"docs":{"0":{"tf":1.0}}}}}}}}}},"df":0,"docs":{}}}}},"df":1,"docs":{"0":{"tf":1.0}}},"p":{"df":0,"docs":{},"o":{"df":0,"docs":{},"l":{"df":0,"docs":{},"l":{"a":{".":{"c":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{".":{"df":0,"docs":{},"f":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":1,"docs":{"13":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":1,"docs":{"13":{"tf":1.0}}},"df":0,"docs":{}}}}}},"l":{"a":{"df":0,"docs":{},"s":{"df":0,"docs":{},"s":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}}}},"df":0,"docs":{}},"o":{"df":0,"docs":{},"m":{"df":0,"docs":{},"p":{"df":1,"docs":{"3":{"tf":2.0}}}},"u":{"df":0,"docs":{},"t":{"df":1,"docs":{"0":{"tf":1.0}}}}}},"d":{"df":0,"docs":{},"e":{"df":0,"docs":{},"s":{"c":{"df":0,"docs":{},"r":{"df":0,"docs":{},"i":{"df":0,"docs":{},"p":{"df":0,"docs":{},"t":{"df":1,"docs":{"3":{"tf":1.0}}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{},"e":{"a":{"df":0,"docs":{},"r":{"df":0,"docs":{},"t":{"df":0,"docs":{},"h":{"df":0,"docs":{},"q":{"df":0,"docs":{},"u":{"a":{"df":0,"docs":{},"k":{"df":1,"docs":{"12":{"tf":1.0}}}},"df":0,"docs":{}}}}}}},"df":0,"docs":{},"k":{"df":0,"docs":{},"o":{"df":1,"docs":{"4":{"tf":1.0}}}},"n":{"d":{"df":1,"docs":{"0":{"tf":1.0}}},"df":0,"docs":{}}},"f":{"df":0,"docs":{},"i":{"df":0,"docs":{},"r":{"df":0,"docs":{},"s":{"df":0,"docs":{},"t":{"df":1,"docs":{"3":{"tf":1.0}}}}}},"l":{"df":0,"docs":{},"o":{"df":0,"docs":{},"o":{"df":0,"docs":{},"r":{"df":1,"docs":{"11":{"tf":1.4142135623730951}}}}}}},"h":{"df":0,"docs":{},"e":{"a":{"d":{"df":0,"docs":{},"e":{"df":0,"docs":{},"r":{"df":1,"docs":{"0":{"tf":1.0}}}}},"df":0,"docs":{}},"df":0,"docs":{}},"t":{"df":0,"docs":{},"t":{"df":0,"docs":{},"p":{"df":0,"docs":{},"s":{":":{"/":{"/":{"df":0,"docs":{},"w":{"df":0,"docs":{},"w":{"df":0,"docs":{},"w":{".":{"df":0,"docs":{},"l":{"df":0,"docs":{},"u":{"df":0,"docs":{},"o":{"df":0,"docs":{},"g":{"df":0,"docs":{},"u":{".":{"c":{"df":0,"docs":{},"o":{"df":0,"docs":{},"m":{".":{"c":{"df":0,"docs":{},"n":{"/":{"df":0,"docs":{},"p":{"df":0,"docs":{},"r":{"df":0,"docs":{},"o":{"b":{"df":0,"docs":{},"l":{"df":0,"docs":{},"e":{"df":0,"docs":{},"m":{"/":{"df":0,"docs":{},"p":{"1":{"8":{"7":{"3":{"df":1,"docs":{"3":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}}},"df":0,"docs":{}}}}},"df":0,"docs":{}}}}},"df":0,"docs":{}}},"df":0,"docs":{}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":0,"docs":{}}}}}}},"df":0,"docs":{}}}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}}}}}},"i":{"df":0,"docs":{},"n":{"c":{"df":0,"docs":{},"l":{"df":0,"docs":{},"u":{"d":{"df":6,"docs":{"0":{"tf":1.0},"11":{"tf":1.0},"13":{"tf":1.0},"5":{"tf":1.0},"7":{"tf":1.0},"9":{"tf":1.0}}},"df":0,"docs":{}}}},"df":0,"docs":{},"t":{"6":{"4":{"_":{"df":0,"docs":{},"t":{"df":1,"docs":{"0":{"tf":1.0}}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":1,"docs":{"0":{"tf":1.7320508075688772}}}}},"l":{"a":{"df":0,"docs":{},"s":{"df":0,"docs":{},"t":{"df":1,"docs":{"3":{"tf":1.0}}}}},"df":1,"docs":{"3":{"tf":3.7416573867739413}},"l":{"df":2,"docs":{"0":{"tf":1.0},"3":{"tf":2.6457513110645907}}},"o":{"df":0,"docs":{},"j":{"1":{"0":{"0":{"df":1,"docs":{"6":{"tf":1.0}}},"df":0,"docs":{}},"4":{"3":{"df":1,"docs":{"8":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"n":{"df":0,"docs":{},"g":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}}},"w":{"df":0,"docs":{},"e":{"df":0,"docs":{},"r":{"(":{"df":0,"docs":{},"l":{"df":1,"docs":{"3":{"tf":1.0}}}},"df":0,"docs":{}}}}}},"m":{"a":{"df":0,"docs":{},"i":{"df":0,"docs":{},"n":{"df":1,"docs":{"0":{"tf":1.0}}}},"t":{"df":0,"docs":{},"r":{"df":0,"docs":{},"i":{"df":0,"docs":{},"x":{".":{"c":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{".":{"df":0,"docs":{},"f":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":1,"docs":{"5":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":0,"docs":{}}}}}},"df":1,"docs":{"3":{"tf":2.0}},"i":{"df":0,"docs":{},"l":{"df":0,"docs":{},"l":{"df":0,"docs":{},"e":{"df":0,"docs":{},"r":{"df":1,"docs":{"7":{"tf":1.4142135623730951}}}}}}}},"n":{"a":{"df":0,"docs":{},"m":{"df":0,"docs":{},"e":{"df":0,"docs":{},"s":{"df":0,"docs":{},"p":{"a":{"c":{"df":1,"docs":{"0":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}}}}}},"df":1,"docs":{"0":{"tf":1.0}}},"p":{"1":{"8":{"7":{"3":{"df":1,"docs":{"4":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"4":{"7":{"1":{"8":{"df":1,"docs":{"10":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"5":{"1":{"7":{"1":{"df":1,"docs":{"12":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"4":{"9":{"1":{"df":1,"docs":{"14":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{},"o":{"df":0,"docs":{},"l":{"df":0,"docs":{},"l":{"a":{"df":0,"docs":{},"r":{"d":{"df":2,"docs":{"10":{"tf":1.0},"9":{"tf":1.4142135623730951}}},"df":0,"docs":{}}},"df":0,"docs":{}}}},"r":{"df":0,"docs":{},"o":{"b":{"df":0,"docs":{},"l":{"df":0,"docs":{},"e":{"df":0,"docs":{},"m":{"df":1,"docs":{"3":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"r":{"a":{"b":{"b":{"df":0,"docs":{},"i":{"df":0,"docs":{},"n":{".":{"c":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{".":{"df":0,"docs":{},"f":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":1,"docs":{"7":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":1,"docs":{"7":{"tf":1.0}}}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":1,"docs":{"3":{"tf":3.4641016151377544}},"e":{"df":0,"docs":{},"t":{"df":0,"docs":{},"u":{"df":0,"docs":{},"r":{"df":0,"docs":{},"n":{"df":2,"docs":{"0":{"tf":1.0},"3":{"tf":2.0}}}}}}},"h":{"df":0,"docs":{},"o":{".":{"c":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{".":{"df":0,"docs":{},"f":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":1,"docs":{"9":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":2,"docs":{"10":{"tf":1.0},"9":{"tf":1.0}}}},"o":{"df":0,"docs":{},"g":{"df":0,"docs":{},"e":{"df":0,"docs":{},"r":{"df":1,"docs":{"0":{"tf":1.0}}}}}}},"s":{"df":0,"docs":{},"t":{"d":{"df":1,"docs":{"0":{"tf":1.0}}},"df":0,"docs":{}},"u":{"df":0,"docs":{},"m":{".":{"c":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{".":{"df":0,"docs":{},"f":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":1,"docs":{"11":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":1,"docs":{"11":{"tf":1.0}}}},"y":{"df":0,"docs":{},"n":{"c":{"_":{"df":0,"docs":{},"w":{"df":0,"docs":{},"i":{"df":0,"docs":{},"t":{"df":0,"docs":{},"h":{"_":{"df":0,"docs":{},"s":{"df":0,"docs":{},"t":{"d":{"df":0,"docs":{},"i":{"df":0,"docs":{},"o":{"(":{"df":0,"docs":{},"f":{"a":{"df":0,"docs":{},"l":{"df":0,"docs":{},"s":{"df":1,"docs":{"0":{"tf":1.0}}}}},"df":0,"docs":{}}},"df":0,"docs":{}}}},"df":0,"docs":{}}}},"df":0,"docs":{}}}}}},"df":0,"docs":{}},"df":0,"docs":{}}}},"t":{"df":1,"docs":{"0":{"tf":1.7320508075688772}},"e":{"df":0,"docs":{},"m":{"df":0,"docs":{},"p":{"df":0,"docs":{},"l":{"a":{"df":0,"docs":{},"t":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}}},"df":0,"docs":{}}}}},"r":{"df":0,"docs":{},"u":{"df":0,"docs":{},"e":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}}}}},"u":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{"df":0,"docs":{},"e":{"df":0,"docs":{},"r":{"(":{"df":0,"docs":{},"l":{"df":1,"docs":{"3":{"tf":1.0}}}},"df":0,"docs":{}}}}},"s":{"df":2,"docs":{"0":{"tf":1.4142135623730951},"3":{"tf":1.0}}}},"x":{"df":1,"docs":{"0":{"tf":1.0}}},"y":{"df":0,"docs":{},"o":{"df":0,"docs":{},"u":{"df":0,"docs":{},"n":{"df":0,"docs":{},"g":{"df":1,"docs":{"0":{"tf":1.0}}}}}}}}},"breadcrumbs":{"root":{"0":{"df":1,"docs":{"0":{"tf":1.0}}},"1":{"df":1,"docs":{"3":{"tf":2.0}}},"2":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}},"_":{"_":{"_":{"_":{"df":1,"docs":{"0":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"a":{"df":0,"docs":{},"u":{"df":0,"docs":{},"t":{"df":0,"docs":{},"h":{"df":0,"docs":{},"o":{"df":0,"docs":{},"r":{"df":1,"docs":{"0":{"tf":1.0}}}}}}}},"b":{"df":0,"docs":{},"i":{"df":0,"docs":{},"t":{"df":0,"docs":{},"s":{"/":{"df":0,"docs":{},"s":{"df":0,"docs":{},"t":{"d":{"c":{"+":{"+":{".":{"df":0,"docs":{},"h":{"df":1,"docs":{"0":{"tf":1.0}}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}}}},"df":0,"docs":{}}}}},"c":{"df":0,"docs":{},"h":{"df":0,"docs":{},"e":{"c":{"df":0,"docs":{},"k":{"(":{"df":0,"docs":{},"l":{"df":1,"docs":{"3":{"tf":1.0}}},"m":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}},"r":{"df":1,"docs":{"3":{"tf":1.0}}}},"df":1,"docs":{"3":{"tf":1.4142135623730951}}}},"df":0,"docs":{}}},"i":{"df":0,"docs":{},"n":{".":{"df":0,"docs":{},"t":{"df":0,"docs":{},"i":{"df":0,"docs":{},"e":{"(":{"df":0,"docs":{},"n":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":0,"docs":{},"l":{"df":0,"docs":{},"p":{"df":0,"docs":{},"t":{"df":0,"docs":{},"r":{"df":1,"docs":{"0":{"tf":1.0}}}}}}}}}},"df":0,"docs":{}}}}},"df":1,"docs":{"0":{"tf":1.0}}},"p":{"df":0,"docs":{},"o":{"df":0,"docs":{},"l":{"df":0,"docs":{},"l":{"a":{".":{"c":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{".":{"df":0,"docs":{},"f":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":1,"docs":{"13":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":2,"docs":{"13":{"tf":1.7320508075688772},"14":{"tf":1.0}}},"df":0,"docs":{}}}}}},"l":{"a":{"df":0,"docs":{},"s":{"df":0,"docs":{},"s":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}}}},"df":0,"docs":{}},"o":{"df":0,"docs":{},"m":{"df":0,"docs":{},"p":{"df":1,"docs":{"3":{"tf":2.0}}}},"u":{"df":0,"docs":{},"t":{"df":1,"docs":{"0":{"tf":1.0}}}}}},"d":{"df":0,"docs":{},"e":{"df":0,"docs":{},"s":{"c":{"df":0,"docs":{},"r":{"df":0,"docs":{},"i":{"df":0,"docs":{},"p":{"df":0,"docs":{},"t":{"df":1,"docs":{"3":{"tf":1.0}}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{},"e":{"a":{"df":0,"docs":{},"r":{"df":0,"docs":{},"t":{"df":0,"docs":{},"h":{"df":0,"docs":{},"q":{"df":0,"docs":{},"u":{"a":{"df":0,"docs":{},"k":{"df":1,"docs":{"12":{"tf":1.0}}}},"df":0,"docs":{}}}}}}},"df":0,"docs":{},"k":{"df":0,"docs":{},"o":{"df":1,"docs":{"4":{"tf":1.0}}}},"n":{"d":{"df":1,"docs":{"0":{"tf":1.0}}},"df":0,"docs":{}}},"f":{"df":0,"docs":{},"i":{"df":0,"docs":{},"r":{"df":0,"docs":{},"s":{"df":0,"docs":{},"t":{"df":1,"docs":{"3":{"tf":1.0}}}}}},"l":{"df":0,"docs":{},"o":{"df":0,"docs":{},"o":{"df":0,"docs":{},"r":{"df":2,"docs":{"11":{"tf":2.0},"12":{"tf":1.0}}}}}}},"h":{"df":0,"docs":{},"e":{"a":{"d":{"df":0,"docs":{},"e":{"df":0,"docs":{},"r":{"df":1,"docs":{"0":{"tf":1.0}}}}},"df":0,"docs":{}},"df":0,"docs":{}},"t":{"df":0,"docs":{},"t":{"df":0,"docs":{},"p":{"df":0,"docs":{},"s":{":":{"/":{"/":{"df":0,"docs":{},"w":{"df":0,"docs":{},"w":{"df":0,"docs":{},"w":{".":{"df":0,"docs":{},"l":{"df":0,"docs":{},"u":{"df":0,"docs":{},"o":{"df":0,"docs":{},"g":{"df":0,"docs":{},"u":{".":{"c":{"df":0,"docs":{},"o":{"df":0,"docs":{},"m":{".":{"c":{"df":0,"docs":{},"n":{"/":{"df":0,"docs":{},"p":{"df":0,"docs":{},"r":{"df":0,"docs":{},"o":{"b":{"df":0,"docs":{},"l":{"df":0,"docs":{},"e":{"df":0,"docs":{},"m":{"/":{"df":0,"docs":{},"p":{"1":{"8":{"7":{"3":{"df":1,"docs":{"3":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}}},"df":0,"docs":{}}}}},"df":0,"docs":{}}}}},"df":0,"docs":{}}},"df":0,"docs":{}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":0,"docs":{}}}}}}},"df":0,"docs":{}}}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}}}}}},"i":{"df":0,"docs":{},"n":{"c":{"df":0,"docs":{},"l":{"df":0,"docs":{},"u":{"d":{"df":6,"docs":{"0":{"tf":1.0},"11":{"tf":1.0},"13":{"tf":1.0},"5":{"tf":1.0},"7":{"tf":1.0},"9":{"tf":1.0}}},"df":0,"docs":{}}}},"df":0,"docs":{},"t":{"6":{"4":{"_":{"df":0,"docs":{},"t":{"df":1,"docs":{"0":{"tf":1.0}}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":1,"docs":{"0":{"tf":1.7320508075688772}}}}},"l":{"a":{"df":0,"docs":{},"s":{"df":0,"docs":{},"t":{"df":1,"docs":{"3":{"tf":1.0}}}}},"df":1,"docs":{"3":{"tf":3.7416573867739413}},"l":{"df":2,"docs":{"0":{"tf":1.0},"3":{"tf":2.6457513110645907}}},"o":{"df":0,"docs":{},"j":{"1":{"0":{"0":{"df":1,"docs":{"6":{"tf":1.0}}},"df":0,"docs":{}},"4":{"3":{"df":1,"docs":{"8":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"n":{"df":0,"docs":{},"g":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}}},"w":{"df":0,"docs":{},"e":{"df":0,"docs":{},"r":{"(":{"df":0,"docs":{},"l":{"df":1,"docs":{"3":{"tf":1.0}}}},"df":0,"docs":{}}}}}},"m":{"a":{"df":0,"docs":{},"i":{"df":0,"docs":{},"n":{"df":1,"docs":{"0":{"tf":1.0}}}},"t":{"df":0,"docs":{},"r":{"df":0,"docs":{},"i":{"df":0,"docs":{},"x":{".":{"c":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{".":{"df":0,"docs":{},"f":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":1,"docs":{"5":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":0,"docs":{}}}}}},"df":1,"docs":{"3":{"tf":2.0}},"i":{"df":0,"docs":{},"l":{"df":0,"docs":{},"l":{"df":0,"docs":{},"e":{"df":0,"docs":{},"r":{"df":2,"docs":{"7":{"tf":2.0},"8":{"tf":1.0}}}}}}}},"n":{"a":{"df":0,"docs":{},"m":{"df":0,"docs":{},"e":{"df":0,"docs":{},"s":{"df":0,"docs":{},"p":{"a":{"c":{"df":1,"docs":{"0":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}}}}}},"df":1,"docs":{"0":{"tf":1.0}}},"p":{"1":{"8":{"7":{"3":{"df":1,"docs":{"4":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"4":{"7":{"1":{"8":{"df":1,"docs":{"10":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"5":{"1":{"7":{"1":{"df":1,"docs":{"12":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"4":{"9":{"1":{"df":1,"docs":{"14":{"tf":1.0}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{},"o":{"df":0,"docs":{},"l":{"df":0,"docs":{},"l":{"a":{"df":0,"docs":{},"r":{"d":{"df":2,"docs":{"10":{"tf":1.4142135623730951},"9":{"tf":2.0}}},"df":0,"docs":{}}},"df":0,"docs":{}}}},"r":{"df":0,"docs":{},"o":{"b":{"df":0,"docs":{},"l":{"df":0,"docs":{},"e":{"df":0,"docs":{},"m":{"df":1,"docs":{"3":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"r":{"a":{"b":{"b":{"df":0,"docs":{},"i":{"df":0,"docs":{},"n":{".":{"c":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{".":{"df":0,"docs":{},"f":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":1,"docs":{"7":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":2,"docs":{"7":{"tf":1.7320508075688772},"8":{"tf":1.0}}}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":1,"docs":{"3":{"tf":3.4641016151377544}},"e":{"df":0,"docs":{},"t":{"df":0,"docs":{},"u":{"df":0,"docs":{},"r":{"df":0,"docs":{},"n":{"df":2,"docs":{"0":{"tf":1.0},"3":{"tf":2.0}}}}}}},"h":{"df":0,"docs":{},"o":{".":{"c":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{".":{"df":0,"docs":{},"f":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":1,"docs":{"9":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":2,"docs":{"10":{"tf":1.4142135623730951},"9":{"tf":1.7320508075688772}}}},"o":{"df":0,"docs":{},"g":{"df":0,"docs":{},"e":{"df":0,"docs":{},"r":{"df":1,"docs":{"0":{"tf":1.0}}}}}}},"s":{"df":0,"docs":{},"t":{"d":{"df":1,"docs":{"0":{"tf":1.0}}},"df":0,"docs":{}},"u":{"df":0,"docs":{},"m":{".":{"c":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{".":{"df":0,"docs":{},"f":{"df":0,"docs":{},"u":{"df":0,"docs":{},"l":{"df":1,"docs":{"11":{"tf":1.0}}}}}},"df":0,"docs":{}}}},"df":0,"docs":{}},"df":2,"docs":{"11":{"tf":1.7320508075688772},"12":{"tf":1.0}}}},"y":{"df":0,"docs":{},"n":{"c":{"_":{"df":0,"docs":{},"w":{"df":0,"docs":{},"i":{"df":0,"docs":{},"t":{"df":0,"docs":{},"h":{"_":{"df":0,"docs":{},"s":{"df":0,"docs":{},"t":{"d":{"df":0,"docs":{},"i":{"df":0,"docs":{},"o":{"(":{"df":0,"docs":{},"f":{"a":{"df":0,"docs":{},"l":{"df":0,"docs":{},"s":{"df":1,"docs":{"0":{"tf":1.0}}}}},"df":0,"docs":{}}},"df":0,"docs":{}}}},"df":0,"docs":{}}}},"df":0,"docs":{}}}}}},"df":0,"docs":{}},"df":0,"docs":{}}}},"t":{"df":1,"docs":{"0":{"tf":1.7320508075688772}},"e":{"df":0,"docs":{},"m":{"df":0,"docs":{},"p":{"df":0,"docs":{},"l":{"a":{"df":0,"docs":{},"t":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}}},"df":0,"docs":{}}}}},"r":{"df":0,"docs":{},"u":{"df":0,"docs":{},"e":{"df":1,"docs":{"3":{"tf":1.4142135623730951}}}}}},"u":{"df":0,"docs":{},"p":{"df":0,"docs":{},"p":{"df":0,"docs":{},"e":{"df":0,"docs":{},"r":{"(":{"df":0,"docs":{},"l":{"df":1,"docs":{"3":{"tf":1.0}}}},"df":0,"docs":{}}}}},"s":{"df":2,"docs":{"0":{"tf":1.4142135623730951},"3":{"tf":1.0}}}},"x":{"df":1,"docs":{"0":{"tf":1.0}}},"y":{"df":0,"docs":{},"o":{"df":0,"docs":{},"u":{"df":0,"docs":{},"n":{"df":0,"docs":{},"g":{"df":1,"docs":{"0":{"tf":1.0}}}}}}}}},"title":{"root":{"c":{"df":0,"docs":{},"i":{"df":0,"docs":{},"p":{"df":0,"docs":{},"o":{"df":0,"docs":{},"l":{"df":0,"docs":{},"l":{"a":{"df":1,"docs":{"13":{"tf":1.0}}},"df":0,"docs":{}}}}}}},"df":0,"docs":{},"f":{"df":0,"docs":{},"l":{"df":0,"docs":{},"o":{"df":0,"docs":{},"o":{"df":0,"docs":{},"r":{"df":1,"docs":{"11":{"tf":1.0}}}}}}},"m":{"df":0,"docs":{},"i":{"df":0,"docs":{},"l":{"df":0,"docs":{},"l":{"df":0,"docs":{},"e":{"df":0,"docs":{},"r":{"df":1,"docs":{"7":{"tf":1.0}}}}}}}},"p":{"df":0,"docs":{},"o":{"df":0,"docs":{},"l":{"df":0,"docs":{},"l":{"a":{"df":0,"docs":{},"r":{"d":{"df":1,"docs":{"9":{"tf":1.0}}},"df":0,"docs":{}}},"df":0,"docs":{}}}}},"r":{"a":{"b":{"b":{"df":0,"docs":{},"i":{"df":0,"docs":{},"n":{"df":1,"docs":{"7":{"tf":1.0}}}}},"df":0,"docs":{}},"df":0,"docs":{}},"df":0,"docs":{},"h":{"df":0,"docs":{},"o":{"df":1,"docs":{"9":{"tf":1.0}}}}},"s":{"df":0,"docs":{},"u":{"df":0,"docs":{},"m":{"df":1,"docs":{"11":{"tf":1.0}}}}}}}},"lang":"English","pipeline":["trimmer","stopWordFilter","stemmer"],"ref":"id","version":"0.9.5"},"results_options":{"limit_results":30,"teaser_word_count":30},"search_options":{"bool":"OR","expand":true,"fields":{"body":{"boost":1},"breadcrumbs":{"boost":1},"title":{"boost":2}}}});