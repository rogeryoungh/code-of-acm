# Code of ACM

我的算法竞赛学习笔记。

目前有

- Blog：博客日志，包含每一题的做题思路。
- Src：代码归档，是 AC 代码归档。
- Template：代码模板，练习用。打印模板见我的 Note 仓库。
- Archive：归档，包含旧的模板之类、废弃脚本之类的。

本仓库内代码适用 MIT License。

内容（题目分析等）采用 [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/deed.zh)，转载请署名！

## 文件头

改用 `cin`，更加精简了，虽然在部分 OJ 上有点慢。

```cpp
#include <bits/stdc++.h>

using ll = long long;

int ____ = std::cin.tie(nullptr)->sync_with_stdio(false);

// END OF HEADER | Author: Roger Young
```

## 编译参数

重复定义警告，忽略符号转换。

```bash
-Wall -Wextra -Wshadow -std=c++20 -Wno-unused-parameter -Wno-sign-compare -O2
```

越界 RE。

```bash
-D_GLIBCXX_ASSERTIONS
```

Linux 独有：各种分析检测。

```bash
-fsanitize=address,undefined -g
```

## 模板

除了（可以使用模板的）比赛或多项式，**其余时间避免使用模板**，手敲一遍加深印象。

模板应遵循的原则：

1. 易修改，轻封装。
2. 适当压行，方便抄写。

副产品：[网页版模板](https://docs-cp.rogery.dev/)。打印版请自行编译。
