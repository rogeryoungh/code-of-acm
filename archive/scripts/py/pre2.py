#!/usr/bin/python3
import os
import shutil
import tempfile

import sys
import pyperclip
import datetime
import re
import configs

template_dir = "/home/roger/Code/ACM/cl/template/"

links = "// GENERATE FROM https://github.com/rogeryoungh/code-of-acm"
date = f"// GENERATE DATE: {datetime.datetime.now()}"


# 读文件内容
def read_file(file):
    with open(file, encoding="UTF-8") as f:
        read_all = f.read()
        f.close()

    return read_all


# 写内容到文件
def rewrite_file(file, data):
    with open(file, "w", encoding="UTF-8") as f:
        f.write(data)
        f.close()


# 传入文件(file),将旧内容(old_content)替换为新内容(new_content)
def replace(content, file, flag=True):
    include_file = read_file(template_dir + file)
    if flag:
        left = include_file.index("endif") + len("endif") + 1
        right = include_file.rindex("endif") - len("#") - 1
        include_file = include_file[left: right]
    content = content.replace(f'#include "template/{file}"', include_file)
    return content


def clang_format(content):
    with tempfile.NamedTemporaryFile() as temp:
        temp.write(content.encode('utf-8'))
        format_config = "/home/roger/Code/ACM/cl/.clang-format"
        print(temp.name)
        shutil.copy(format_config, tempfile.gettempdir())
        content = os.popen(f'clang-format -style=file "{temp.name}"').read()
    return content


def replace2(content, file, num):
    for n in range(0, num + 1):
        content = replace(content, f"{file}/{n}.hpp")
    return content


def main(file):
    # print(file)
    content = f'{links}\n{date}\n\n' + read_file(file)
    content = content.replace('#include "template/index-debug.hpp"',
                              '#include "template/index.hpp"')
    content = content.replace('#include "template/debug.hpp"', '')

    content = replace(content, "index.hpp", False)

    content = replace(content, "basic/complex.hpp")
    content = replace(content, "basic/pre_inv.hpp")
    content = replace(content, "basic/mint.hpp")
    content = replace(content, "basic/p2int.hpp")
    content = replace(content, "basic/qpow.hpp")

    content = replace(content, "math/gcd.hpp")
    content = replace(content, "math/cipolla.hpp")
    content = replace(content, "math/bsgs.hpp")
    content = replace(content, "math/miller_rabbin.hpp")
    content = replace(content, "math/pollard_rho.hpp")

    content = replace(content, "poly-fft/pre_w.hpp")
    content = replace(content, "poly-fft/fft.hpp")
    content = replace(content, "poly-fft/fft_mul.hpp")

    # NTT MODINT

    content = replace2(content, "ntt-mint/poly", 2)

    content = replace2(content, "ntt-mint/pre-w", 1)
    content = replace2(content, "ntt-mint/pre-inv", 1)
    content = replace2(content, "ntt-mint/pre-fac", 1)

    content = replace2(content, "ntt-mint/ntt", 2)
    content = replace2(content, "ntt-mint/add", 1)
    content = replace2(content, "ntt-mint/mul", 1)
    content = replace2(content, "ntt-mint/inv", 7)
    content = replace2(content, "ntt-mint/deriv", 1)
    content = replace2(content, "ntt-mint/integr", 1)
    content = replace2(content, "ntt-mint/ln", 2)
    content = replace2(content, "ntt-mint/exp", 6)
    content = replace2(content, "ntt-mint/pow", 1)
    content = replace2(content, "ntt-mint/sqrt", 5)
    content = replace2(content, "ntt-mint/quo", 1)
    content = replace2(content, "ntt-mint/divat", 2)

    content = replace2(content, "ntt-mint/cdq", 7)
    content = replace2(content, "ntt-mint/oc", 1)
    content = replace2(content, "ntt-mint/semi", 1)
    content = replace2(content, "ntt-mint/eval", 1)
    content = replace2(content, "ntt-mint/cache", 1)

    # NTT INT

    content = replace(content, "ntt-int/ntt_simp.hpp")
    content = replace(content, "ntt-int/ntt_simpF.hpp")
    content = replace(content, "ntt-int/ntt_simpF2.hpp")
    content = replace(content, "ntt-int/ntt_simpF3.hpp")
    content = replace(content, "ntt-int/ntt_extra.hpp")

    content = clang_format(content)
    pyperclip.copy(content)
    print("success: already in clipboard.")
    # rewrite_file(file + '.cpp', content)


if __name__ == '__main__':
    if len(sys.argv) != 2:
        main('main.cpp')
    else:
        main(sys.argv[1])
