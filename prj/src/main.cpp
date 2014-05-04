#include "Benchmark.hpp"
#include <iostream>
#include <fstream>
#include "Graph.hpp"

int main(int argc, char* argv[])
{
	Graph<int, int> graf;
	for (unsigned int i = 1; i <= 7; i++)
		graf.addVertice(i);
	graf.addEdge(1, 2, 3);
	graf.addEdge(2, 3, 3);
	graf.addEdge(3, 4, 5);
	graf.addEdge(2, 5, 4);
	graf.addEdge(5, 6, 4);
	graf.addEdge(6, 7, 6);
	graf.addEdge(1, 5, 5);
	graf.addEdge(5, 3, 5);
	graf.addEdge(7, 1, 1);
	typedef Graph<int, int>::Edge Edge;
	std::ofstream file("graf.gv");
	graf.genGVFile(file);
	std::list<int> path = graf.dfs(1, 4);
	std::cout << "DFS:\n";
	for (auto it = path.begin(); it != path.end(); it++)
		if(*it != 4)
			std::cout << *it << "->";
		else
			std::cout << *it << std::endl;
	path = graf.bfs(1, 4);
	std::cout << "\nBFS:\n";
	for (auto it = path.begin(); it != path.end(); it++)
		if(*it != 4)
			std::cout << *it << "->";
		else
			std::cout << *it << std::endl;
	path = graf.bestFirstSearch(1, 4,[](const Edge& e1, const Edge& e2) { return e1.weight>e2.weight;});
	std::cout << "\nBest First Search:\n";
	for (auto it = path.begin(); it != path.end(); it++)
		if(*it != 4)
			std::cout << *it << "->";
		else
			std::cout << *it << std::endl;
	return 0;
}
