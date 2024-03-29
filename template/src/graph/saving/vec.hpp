#include "basic/index.hpp"

template <class D>
struct Edge {
	int to;
	D len;
};

template <class D>
using Edges = std::vector<std::vector<Edge<D>>>;
