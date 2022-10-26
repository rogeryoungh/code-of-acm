#include "basic/index.hpp"

template <class D>
struct Edge {
	int to;
	D len;
};

template <class D>
using Graph = vector<vector<Edge<D>>>;