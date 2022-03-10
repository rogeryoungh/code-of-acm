import util, configs

import os

import util
import shutil

import configs
import crawler_cf

problem_config = {
    'testcase': 0,
    'test_only': '',
    'url': '',
    'io_prefix': '',
    'src': 'main.cpp',
}


def simple_name(group: str, url: str, name: str):
    if group.startswith('Luogu'):
        return name.split(' ')[0]
    elif group.startswith('Codeforces'):
        contest = url.split('/')
        if contest[3] == "contest":
            return f'CF{contest[4]}/{name[0]}'
        else:
            return f'CF{contest[5]}/{name[0]}'
    return name.split(' ')[0]


def write_to_file(file, str):
    with open(file, "w+") as f:
        f.write(str)


def main():
    config = configs.read_root_config()
    lst = util.Listener(config['port'])
    data = lst.get_data()
    # print(data)

    sname = simple_name(data['group'], data['url'], data['name'])
    print(f"create {sname}")
    # exit(0)

    problem_path = util.get_problem_path(sname)
    if os.path.exists(problem_path):
        print(f'ERROR: problem `{sname}` exists')
        return ''

    os.makedirs(problem_path, exist_ok=True)

    config = configs.read_root_config()

    template_cpp_file = config.get('template_source', '')
    if template_cpp_file == '':
        template_cpp_file = util.get_res_file('main.cpp')
    shutil.copy(template_cpp_file, f'{problem_path}/main.cpp')

    problem_config['testcase'] = len(data['tests'])
    problem_config['url'] = data['url']
    configs.write_config(problem_config, f'{problem_path}/problem.toml')

    #add_cmake.add_cmake(sname)

    if len(data['tests']) == 0:
        return

    os.mkdir(f'{problem_path}/testcase')

    index = 1
    for io in data['tests']:
        write_to_file(f'{problem_path}/testcase/{index}.in', io['input'])
        write_to_file(f'{problem_path}/testcase/{index}.out', io['output'])
        index += 1
    
    # if data['group'].startswith('Codeforces'):
    #     contest = data['url'].split('/')
    #     content = crawler_cf.getCodeForces(contest[4], data['name'][0])
    #     content = crawler_cf.CodeForcesToMD(content)
    #     write_to_file(f'{problem_path}/problem.md', content)

    


if __name__ == '__main__':
    cmds = main()
