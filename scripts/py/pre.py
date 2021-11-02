#!/usr/bin/python3

import sys
import pyperclip

template_dir = "/home/roger/Code/ACM/cl/template/"

links = "// GENERATE FROM https://github.com/rogeryoungh/code-of-acm\n\n"


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
    if file == "debug.hpp":
        return content.replace("#include \"template/debug.hpp\"", "")
    include_file = read_file(template_dir + file)
    if flag:
        left = include_file.index("endif") + len("endif") + 1
        right = include_file.rindex("endif") - len("#") - 1
        include_file = include_file[left: right]
    if file == "index.hpp":
        content = content.replace("#include \"template/index-debug.hpp\"", include_file)
    else:
        content = content.replace("#include \"template/" + file + "\"", include_file)
    return content


def main(file):
    # print(file)
    content = links + read_file(file)
    content = replace(content, "index.hpp", False)
    content = replace(content, "debug.hpp", False)

    content = replace(content, "basic/complex.hpp")
    content = replace(content, "basic/exgcd.hpp")
    content = replace(content, "basic/gcd.hpp")
    content = replace(content, "basic/pre_inv.hpp")
    content = replace(content, "basic/inv.hpp")
    content = replace(content, "basic/mint.hpp")
    content = replace(content, "basic/qpow.hpp")

    content = replace(content, "math/cipolla.hpp")

    content = replace(content, "poly-fft/fft_init.hpp")
    content = replace(content, "poly-fft/fft.hpp")

    content = replace(content, "poly-ntt/ntt.hpp")
    content = replace(content, "poly-ntt/pre_w.hpp")
    content = replace(content, "poly-ntt/pre_fac.hpp")
    content = replace(content, "poly-ntt/pre_inv.hpp")
    content = replace(content, "poly-ntt/ntt_d.hpp")
    content = replace(content, "poly-ntt/ntt_exp.hpp")
    content = replace(content, "poly-ntt/ntt_cdq_exp.hpp")
    content = replace(content, "poly-ntt/ntt_cdq_inv.hpp")
    content = replace(content, "poly-ntt/ntt_int.hpp")
    content = replace(content, "poly-ntt/ntt_inv.hpp")
    content = replace(content, "poly-ntt/ntt_ln.hpp")
    content = replace(content, "poly-ntt/ntt_sqrt.hpp")
    content = replace(content, "poly-ntt/ntt_egf.hpp")

    pyperclip.copy(content)
    print("success: already in clipboard.")
    # rewrite_file(file + '.cpp', content)


if __name__ == '__main__':
    if len(sys.argv) != 2:
        main('main.cpp')
    else:
        main(sys.argv[1])
