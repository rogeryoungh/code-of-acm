import os
import util

import configs


def main():
    problem_config = configs.read_problem_config('problem.toml')
    sum = problem_config['testcase']
    sum += 1
    if not os.path.exists('testcase'):
        os.makedirs('testcase')
    with open(f'testcase/{sum}.in', 'w+') as f:
        f.write('\n')
    with open(f'testcase/{sum}.out', 'w+') as f:
        f.write('\n')
    problem_config['testcase'] = sum
    configs.write_config(problem_config, 'problem.toml')
    return ''


if __name__ == '__main__':
    cmds = main()
    with open(util.get_root_file('end.sh'), 'w+') as f:
        f.write(cmds)
