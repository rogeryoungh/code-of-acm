import util


def add_cmake(name):
    n = name.split("/")[-1]
    with open(util.get_root_file('CMakeLists.txt'), 'a+') as f:
        f.write(f'add_executable({n} {name}/main.cpp)\n')
    return ''


if __name__ == '__main__':
    path = util.get_cmd_path().split(util.get_root_path())[1][0:]
    cmds = add_cmake(path)
    # with open(util.get_root_file('end.sh'), 'w+') as f:
    #     f.write(cmds)
