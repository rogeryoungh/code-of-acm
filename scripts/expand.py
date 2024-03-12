import os, shutil, sys, datetime


# 读文件内容
def read_file(file) -> str:
    with open(file, encoding="UTF-8") as f:
        read_all = f.read()
        f.close()
    return read_all


# 写内容到文件
def rewrite_file(file, data):
    with open(file, "w", encoding="UTF-8") as f:
        f.write(data)
        f.close()


def trim_empty_line(content):
    lines = content.splitlines()
    i = 0
    while i < len(lines):
        lines[i] = lines[i].rstrip()
        if i == 0 and len(lines[i]) == 0:
            del lines[i]
        elif i > 1 and len(lines[i]) == 0 and len(lines[i - 1]) == 0:
            del lines[i]
        else:
            i += 1
    return "\n".join(lines)


def process(src):
    path = os.path.abspath(src)
    tmpfile = "./scripts/pre.full.cpp"
    rewrite_file(tmpfile, f'#include "{path}"')
    ret = os.popen(f"g++ -E -CC -nostdinc++ -nostdinc -P -DRY_EXPAND {tmpfile}")
    ret = (
        ret.read()
        .replace("// #region snippet", "")
        .replace("// #endregion snippet", "")
    )
    sys.stderr.write("success: %.3f KB, %s\n" % (len(ret) / 1024, src))
    return trim_empty_line(ret)


def process_and_write_helper(src):
    src = "src/template/" + src
    rewrite_file(src + ".full", process(src))


def process_all():
    process_and_write_helper("datastruct/sparse-table.hpp")


# print(process(sys.argv[1]))
process_all()
