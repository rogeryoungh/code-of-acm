# Code of ACM

我的算法竞赛学习笔记。

目前有

- Archive：代码归档，包含每一题的完整代码，以及做题思路。
- Solution：题解整理，只保留了做题思路，LaTeX 格式。
- Scripts：工具脚本，比如展开引入的本地模板。
- Template：代码模板，练习用。打印模板见我的 Note 仓库。

本仓库内代码适用 MIT License。

内容（题目分析等）采用 [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/deed.zh)，转载请署名！

## 宏

我尽量只使用以下的宏。

```cpp
using namespace std;
using ll = long long;
using u64 = unsigned long long;

#define _fore(i, a) for (ll i = head[a]; i; i = edge[i].nxt)
#define LN putchar('\n')
```
