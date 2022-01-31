import toml
import util

root_config = {
    'path': 'none',
    'template_source': '',
    'cc': 'clang++',
    'cc_flags': '',
    'port': 10045
}

problem_config = {
    'testcase': 0,
    'test_only': 0,
    'url': '',
    'src': 'main.cpp',
}


def read_root_config():
    file = util.get_root_file('rhelper.toml')
    try:
        config = toml.load(file)
        return config
    except FileNotFoundError:
        print("Not found `rhelper.toml`.")
    return root_config


def read_problem_config(file):
    try:
        config = toml.load(file)
        return config
    except FileNotFoundError:
        print("Not found `problem.toml`.")
    return problem_config


def write_config(config, file):
    with open(file, 'w+') as f:
        toml.dump(config, f)
