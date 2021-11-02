import os

config_path = os.getenv('R_HELPER_ROOT')


def get_root_path():
    return os.path.join(config_path)


def get_cmd_path():
    return os.getcwd()


def get_res_file(name=''):
    return f'{get_root_path()}/res/{name}'


def get_script_file(name=''):
    return f'{get_root_path()}/scripts/{name}'


def get_root_file(name=''):
    return os.path.join(get_root_path(), name)


def get_problem_path(name=''):
    return os.path.join(get_root_path(), 'src', name)
