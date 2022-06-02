#include <iostream>
#include <fstream>
#include <string>

using std::cerr;
using std::endl;
using std::ifstream;
using std::string;

#error EDIT HERE
#define TMP_PATH "<tmp-path>/fast-g++"
#define CXX_FLAG

const char *bits_stdcpp_path = TMP_PATH "/bits/stdc++.h";

string read_file(const string &path) {
	ifstream input_file(path);
	if (!input_file.is_open()) {
		cerr << "Could not open the file - '" << path << "'" << endl;
		exit(EXIT_FAILURE);
	}
	auto start = std::istreambuf_iterator<char>(input_file);
	auto finish = std::istreambuf_iterator<char>();
	return string(start, finish);
}

string HEADER(const string &name) {
	return "#include <" + name + ">\n";
}

string pre_header(const string &content) {
	auto contains = [&](const string &pattern) {
		return content.find(pattern) != string::npos;
	};

	string header = HEADER("iostream") + HEADER("algorithm");

	auto add_if_need = [&](const string &pattern) {
		if (contains(pattern)) {
			header += HEADER(pattern);
		}
	};

	add_if_need("vector");
	add_if_need("string");
	add_if_need("queue");
	add_if_need("deque");
	add_if_need("map");
	add_if_need("un_ordermap");
	add_if_need("list");
	add_if_need("set");
	add_if_need("stack");
	add_if_need("array");
	add_if_need("complex");

	if (contains("mt19937")) {
		header += HEADER("random");
	}

	return header;
}

int main(int argc, const char *argv[]) {
	if (argc == 1) {
		cerr << "usage: cp-g++ <file> [option]" << endl;
		return 1;
	}
	const string content = read_file(argv[1]);
	std::ofstream(bits_stdcpp_path) << pre_header(content);
	string command = "g++";
	for (int i = 1; i < argc; i++) {
		command.push_back(' ');
		command += argv[i];
	}
	command += " -I" TMP_PATH;
	// cerr << command;
	system(command.c_str());
	return 0;
}
