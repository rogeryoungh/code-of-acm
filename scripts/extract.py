#!/usr/bin/python3
import os
import shutil
import tempfile

import sys
import datetime
import re

from typing import List

template_dir = "./template/src/"

links = "// GENERATE FROM https://github.com/rogeryoungh/code-of-acm"
date = f"// GENERATE DATE: {datetime.datetime.now()}"


# 读文件内容

def read_file(file_name: str) -> str:
    with open(file_name, encoding="UTF-8") as f:
        return f.read()


# 写内容到文件

def write_file(file_name: str, content: str):
    with open(file_name, "w", encoding="UTF-8") as f:
        f.write(content)


maps = set()


# 将旧内容中的 include 替换为文件内容

def replace_dfs(content: List[str], is_test: bool):
    index = 0
    while index < len(content):
        line = content[index]
        # print(f'{index} {line}')
        if line.startswith(r'#include "'):
            path = line.split('"')[1]
            content_split = []
            if path not in maps:
                header = ''
                if path != 'basic/index.hpp' or is_test:
                    header = read_file(template_dir + path)
                maps.add(path)
                content_split = replace_dfs(header.splitlines(), is_test)
            content[index:index + 1] = content_split
            index -= 1
        index += 1
    return content


def process(file_name: str, is_test: bool):
    print('PROCESS ' + file_name)
    maps.clear()
    before = read_file(file_name)
    after = replace_dfs(before.splitlines(), is_test)
    while len(after) > 0 and after[0] == "":
        del after[0]
    i = 1
    while i < len(after):
        if after[i] == "" and after[i - 1] == "":
            del after[i]
        else:
            i += 1
    print("success: %.3f KB" % (len(after) / 1024))
    write_file(file_name + '.full', '\n'.join(after))


def process_all(dir_name: str, is_test: bool):
    for root, dirs, files in os.walk(dir_name):
        for f in files:
            if f.endswith('.cpp'):
                path = os.path.join(root, f)
                process(path, is_test)


if __name__ == '__main__':
    # process('./template/src/math/pollard-rho.cpp', False)
    process_all('./template/src', False)
