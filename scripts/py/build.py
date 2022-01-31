import util
import configs


def main():
    config = configs.read_root_config()
    problem_config = configs.read_problem_config('problem.toml')
    cc = config['cc']
    cc_flags = config['cc_flags']
    src_file = problem_config.get('src', 'main.cpp')
    return f'{cc} {src_file} {cc_flags}'


if __name__ == '__main__':
    cmds = main()
    # print(cmds)
    with open(util.get_script_file('end.sh'), 'w+') as f:
        f.write(cmds)
