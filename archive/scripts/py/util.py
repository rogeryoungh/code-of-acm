import os, json, socket

config_path = os.getenv('R_HELPER_ROOT')


def get_root_path():
    return config_path


def get_cmd_path():
    return os.getcwd()


def get_res_file(name=''):
    return f'{get_root_path()}/ret/{name}'


def get_script_file(name=''):
    return f'{get_root_path()}/scripts/{name}'


def get_root_file(name=''):
    return os.path.join(get_root_path(), name)


def get_problem_path(name=''):
    return os.path.join(get_root_path(), 'src', name)

class Listener:
    def __init__(self, port):
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        try:
            self.sock.bind(("0.0.0.0", port))
        except OSError:
            print("port is already in use")
            exit(0)
        self.sock.listen(0)
        print(f'start listening at {port}')
        self.client, cltadd = self.sock.accept()

    def get_response(self):
        response = ""
        while True:
            data = self.client.recv(1024)
            if data:
                string = bytes.decode(data, 'utf-8')
                response += string
            else:
                break
        return response

    def get_data(self):
        response = self.get_response()
        body = response.split('\r\n\r\n', 1)[1]
        return json.loads(body)
