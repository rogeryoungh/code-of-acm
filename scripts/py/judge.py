import os
import util
import time
import subprocess

import configs


def cmp_bin(f1, f2):
    st1 = os.stat(f1)
    st2 = os.stat(f2)

    # 比较文件大小
    if st1.st_size != st2.st_size:
        return False

    bsize = 8 * 1024
    with open(f1, 'rb') as fp1, open(f2, 'rb') as fp2:
        while True:
            b1 = fp1.read(bsize)  # 读取指定大小的数据进行比较
            b2 = fp2.read(bsize)
            if b1 != b2:
                return False
            if not b1:
                return True


def cmp_line(f1, f2):
    with open(f1, 'r') as fp1, open(f2, 'r') as fp2:
        while True:
            l1 = fp1.readline().strip()
            l2 = fp2.readline().strip()
            if l1 != l2:
                return False
            elif l1 == '':
                return True


def judge(number):
    file_in = f'testcase/main_{number}.in'
    file_ans = f'testcase/main_{number}.out'
    file_out = f'testcase/main_{number}.out.t'
    flag = ''
    try:
        with open(file_in, 'r') as f_in:
            with open(file_out, 'w+') as f_out:
                T1 = time.perf_counter_ns()
                p = subprocess.Popen(args='./a.out', stdin=f_in, stdout=f_out)
                stdout, stderr = p.communicate(timeout=24)
                if p.returncode != 0:
                    flag = 'RE'
    except subprocess.TimeoutExpired:
        flag = 'TE'
    T2 = time.perf_counter_ns()
    run_time = (T2 - T1) / 1e6
    if flag == '':
        if cmp_line(file_out, file_ans):
            flag = 'AC'
        else:
            flag = 'WA'
    print(f'CASE #{number}: \033[31m[{flag}]\033[0m in {run_time} ms')


def main():
    problem_config = configs.read_problem_config('problem.toml')
    sums = problem_config['testcase']
    only = problem_config['test_only'].split(' ')
    if only[0] == '':
        for i in range(1, int(sums) + 1):
            judge(i)
    else:
        for i in only:
            judge(i)
    return ''


if __name__ == '__main__':
    cmds = main()
    with open(util.get_root_file('end.sh'), 'w+') as f:
        f.write(cmds)
