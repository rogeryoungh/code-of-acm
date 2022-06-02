#ifndef ACM_DEBUG
#define ACM_DEBUG

#include <string>
#include <iostream>
#include <vector>

#define dbg(x) debugPrompt(__FUNCTION__, __LINE__, #x), debugOutput(x)

void debugPrompt(const std::string &functionName, int lineNumber, const std::string &varName) {
	std::cerr << "[" << functionName << ":" << lineNumber << "] " << varName << " = ";
}

template <class S, class T>
std::ostream &operator<<(std::ostream &os, const std::pair<S, T> &p) {
	return os << "(" << p.first << ", " << p.second << ")";
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
	os << "[";
	for (int i = 0; i < v.size(); i++) {
		os << v[i] << (i == v.size() - 1 ? "" : ", ");
	}
	return os << "]";
}

template <class T>
void debugOutput(const T &v) {
	std::cerr << v << '\n';
}

#endif
