#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

using std::cerr;
using std::endl;
using std::ifstream;
using std::string;

namespace fs = std::filesystem;

#error EDIT HERE
const fs::path TMP_PATH;
const fs::path CXX_PATH = "/usr/bin/g++";

const fs::path CACHE_PATH = TMP_PATH / "cache";
const fs::path INCLUDE_PATH = TMP_PATH / "include";
const fs::path BITS_STDCPP_PATH = INCLUDE_PATH / "bits" / "stdc++.h";

string read_file(const fs::path &path) {
	ifstream input_file(path);
	if (!input_file.is_open()) {
		cerr << "Could not open the file - '" << path << "'" << endl;
		exit(EXIT_FAILURE);
	}
	auto start = std::istreambuf_iterator<char>(input_file);
	auto finish = std::istreambuf_iterator<char>();
	return {start, finish};
}

string HEADER(const string &name) {
	return "#include <" + name + ">\n";
}

string pre_header(const string &content) {
	auto contains = [&](const string &pattern) {
		return content.find(pattern) != string::npos;
	};

	string header = HEADER("personal_config.hpp");

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
	add_if_need("un_orderedmap");
	add_if_need("list");
	add_if_need("set");
	add_if_need("stack");
	add_if_need("array");
	add_if_need("complex");
	add_if_need("tuple");

	if (contains("mt19937")) {
		header += HEADER("random");
	}

	if (contains("iota")) {
		header += HEADER("numeric");
	}

	if (contains("function")) {
		header += HEADER("functional");
	}

	if (contains("memset")) {
		header += HEADER("memory.h");
	}

	if (contains("assert")) {
		header += HEADER("cassert");
	}

	return header;
}

int main(int argc, const char *argv[]) {
	if (argc <= 3) {
		cerr << "usage: cp-g++ <src> -o <out> [option]" << endl;
		std::exit(1);
	}
	fs::path source_path = argv[1];
	fs::path target_path = argv[3];

	const string content = read_file(source_path);

	const string source_hash = std::to_string(std::hash<string>()(content));
	const fs::path cache_bin_path = CACHE_PATH / (source_hash + ".out");

	if (not std::filesystem::exists(cache_bin_path)) {
		std::ofstream(BITS_STDCPP_PATH) << pre_header(content);

		auto surround_with_quote = [](const string &s) {
			return '"' + s + '"';
		};
		const char space = ' ';
		string command = CXX_PATH.string();
		command += space + surround_with_quote(source_path.string());
		command += space + string("-o");
		command += space + surround_with_quote(cache_bin_path.string());
		for (int i = 4; i < argc; i++) {
			command += space + surround_with_quote(argv[i]);
		}
		int ret = std::system(command.c_str());
		if (ret != 0) {
			cerr << "COMPILE FAILED" << endl;
			std::exit(1);
		}
	}
	std::filesystem::copy_file(cache_bin_path, target_path, fs::copy_options::overwrite_existing);
	return 0;
}
