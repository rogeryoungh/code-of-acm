#!/usr/bin/python3

import sys
import pyperclip
import datetime

template_dir = "/home/roger/Code/ACM/cl/"

links = "// GENERATE FROM https://github.com/rogeryoungh/code-of-acm"
date = f"// GENERATE DATE: {datetime.datetime.now()}"


# 读文件内容
def read_file(file):
    with open(file, encoding="UTF-8") as f:
        read_all = f.read()
        f.close()
    return read_all


maps = {}


# 同一个算法的不同实现，不应当重复引入
def same_file(path: str):
    flag = False
    if path.startswith("template/ntt-mint") and not path.endswith("0.hpp"):
        flag = True
    if path.startswith("template/basic/mint") and not path.endswith("0.hpp"):
        flag = True
    if flag:
        right = path.rindex("/")
        return path[:right]

    return path


def include_file(path: str):
    content_split = []
    m_path = same_file(path)
    if m_path not in maps:
        content = read_file(template_dir + path)
        if path != 'template/index.hpp':
            # 裁掉代码前后的宏，假设会主动空两行
            left = content.index("\n\n")
            right = content.rindex("\n\n")
            content = content[left:right]
        maps[m_path] = "HAHAHA"
        content_split = replace_dfs(content.splitlines())
    # print("path = ", path, "split = ", content_split)
    return content_split


def replace_dfs(content: list[str]):
    index = 0
    while index < len(content):
        line = content[index]
        if line.startswith(r'#include "template/'):
            path = line.split('"')[1]
            content[index:index + 1] = include_file(path)
            index -= 1
        # print(index, line)
        index += 1
    return content


def main(file):
    # print(file)
    # 引入文件并替换调试信息
    content = f'{links}\n{date}\n\n' + read_file(file)
    content = content.replace('#include "template/index-debug.hpp"',
                              '#include "template/index.hpp"')
    content = content.replace('#include "template/debug.hpp"', '')

    # 递归的处理文件
    content_split = replace_dfs(content.splitlines())

    # 替换连续的换行
    i = 1
    while i < len(content_split):
        if content_split[i] == "" and content_split[i - 1] == "":
            del content_split[i]
        else:
            i += 1

    content = "\n".join(content_split)

    pyperclip.copy(content)
    print("success: already in clipboard.")
    # rewrite_file(file + '.cpp', content)


if __name__ == '__main__':
    if len(sys.argv) != 2:
        main('main.cpp')
    else:
        main(sys.argv[1])
