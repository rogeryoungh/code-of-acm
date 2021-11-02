import util


def add_cmake(name):
    with open(util.get_root_file('CMakeLists.txt'), 'a+') as f:
        f.write(f'add_executable({name}_M src/{name}/main.cpp)\n')
    return ''


# if __name__ == '__main__':
#     cmds = add_cmake()
#     with open(util.get_root_file('end.sh'), 'w+') as f:
#         f.write(cmds)
