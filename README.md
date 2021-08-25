# Code of ACM

我的算法竞赛学习笔记。

目前有

- Archive：代码归档，包含每一题的完整代码，以及做题思路。
- Solution：题解整理，只保留了做题思路，LaTeX 格式。
- Template：代码模板，练习用。打印模板请见我的 Note 仓库。

## 宏

我尽量只使用以下的宏。

```cpp
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define _fora(i, a, n) for (ll i = a; i <= n; i++)
#define _forz(i, a, n) for (ll i = a; i >= n; i--)
#define _fore(i, a) for (ll i = head[a]; i; i = edge[i].nxt)
#define LN putchar('\n')
```