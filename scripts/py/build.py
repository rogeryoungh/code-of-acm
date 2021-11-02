import util
import configs


def main():
    config = configs.read_root_config()
    cc = config['cc']
    cc_flags = config['cc_flags']
    return f'{cc} main.cpp {cc_flags}'


if __name__ == '__main__':
    cmds = main()
    # print(cmds)
    with open(util.get_script_file('end.sh'), 'w+') as f:
        f.write(cmds)
