import os.path
import sys
import util


def main():
    if len(sys.argv) > 1:
        name = sys.argv[1]
        path = util.get_problem_path(name)
        if name == 'root':
            path = util.get_root_path()
        if os.path.exists(path):
            return f'cd {path}'
        else:
            print(f'ERROR: directory `{sys.argv[1]}` didn\'t exist.')
    else:
        print('usage: switch <problem>')
    return ''


if __name__ == '__main__':
    cmds = main()
    with open(util.get_script_file('end.sh'), 'w+') as f:
        f.write(cmds)
