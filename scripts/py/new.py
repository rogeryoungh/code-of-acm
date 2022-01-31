import os
import sys

import toml

import util
import shutil

import configs
import add_cmake

problem_config = {
    'testcase': 0,
    'test_only': '',
}


def main(name):
    problem_path = util.get_problem_path(name)
    if os.path.exists(problem_path):
        print(f'ERROR: problem `{name}` exists')
        return ''

    os.mkdir(problem_path)

    config = configs.read_root_config()

    template_cpp_file = config.get('template_source', '')
    if template_cpp_file == '':
        template_cpp_file = util.get_res_file('main.cpp')
    shutil.copy(template_cpp_file, f'{problem_path}/main.cpp')
    configs.write_config(problem_config, f'{problem_path}/problem.toml')

    # add_cmake.add_cmake(name)
    return problem_path


if __name__ == '__main__':
    if len(sys.argv) == 1:
        print('usage: new <problem>')
    else:
        name = sys.argv[1]
        cmds = main(name)
        with open(util.get_script_file('end.sh'), 'w+') as f:
            f.write(f'cd {cmds}')
