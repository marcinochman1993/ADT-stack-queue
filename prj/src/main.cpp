#include "Benchmark.hpp"
#include <iostream>
#include <fstream>
#include "Graph.hpp"


int main(int argc, char* argv[])
{
	Graph<int, int> graph1,graph2;
	for (unsigned int i = 1; i <= 7; i++)
		graph1.addVertice(i);
	for (unsigned int i = 1; i <= 5; i++)
			graph2.addVertice(i);
	graph1.addEdge(1, 2, 3);
	graph1.addEdge(2, 3, 3);
	graph1.addEdge(3, 4, 5);
	graph1.addEdge(2, 5, 3);
	graph1.addEdge(5, 6, 4);
	graph1.addEdge(6, 7, 6);
	graph1.addEdge(1, 5, 5);
	graph1.addEdge(5, 3, 5);
	graph1.addEdge(7, 1, 1);
	graph1.addEdge(6, 4, 1);
	graph1.addEdge(7, 4, 0);
	graph2.addEdge(1,2,10);
	graph2.addEdge(2,3,1);
	graph2.addEdge(3,4,4);
	graph2.addEdge(4,3,6);
	graph2.addEdge(5,4,2);
	graph2.addEdge(2,5,3);
	graph2.addEdge(5,3,9);
	graph2.addEdge(4,1,7);
	graph2.addEdge(1,5,5);
	typedef Graph<int, int>::Edge Edge;
	std::cout<<"Graf nr 1:\n\n";
	std::cout<<"A*:\n";
	std::list<int> path = graph1.aStar(1, 4,[](int x) { return 0; });
	for (auto it = path.begin(); it != path.end(); it++)
		if(*it != 4)
			std::cout << *it << "->";
		else
			std::cout << *it << std::endl;

	std::cout<<"DFS:\n";
	path=graph1.dfs(1,4);
	for (auto it = path.begin(); it != path.end(); it++)
		if(*it != 4)
			std::cout << *it << "->";
		else
			std::cout << *it << std::endl;

	std::cout<<"BFS:\n";
	path=graph1.bfs(1,4);
	for (auto it = path.begin(); it != path.end(); it++)
		if(*it != 4)
			std::cout << *it << "->";
		else
			std::cout << *it << std::endl;

	std::cout<<"Best First Search:\n";
	path=graph1.bestFirstSearch(1,4,[](const Edge& e1, const Edge& e2) { return e1.weight>e2.weight;});
	for (auto it = path.begin(); it != path.end(); it++)
		if(*it != 4)
			std::cout << *it << "->";
		else
			std::cout << *it << std::endl;

	std::cout<<"\nGraf 2:\n\n";

	std::cout<<"A*:\n";
	path = graph2.aStar(1, 3,[](int x) { return 0; });
	for (auto it = path.begin(); it != path.end(); it++)
		if(*it != 3)
			std::cout << *it << "->";
		else
			std::cout << *it << std::endl;

	std::cout<<"DFS:\n";
	path=graph2.dfs(1,3);
	for (auto it = path.begin(); it != path.end(); it++)
		if(*it != 3)
			std::cout << *it << "->";
		else
			std::cout << *it << std::endl;

	std::cout<<"BFS:\n";
	path=graph2.bfs(1,3);
	for (auto it = path.begin(); it != path.end(); it++)
		if(*it != 3)
			std::cout << *it << "->";
		else
			std::cout << *it << std::endl;

	std::cout<<"Best First Search:\n";
	path=graph2.bestFirstSearch(1,3,[](const Edge& e1, const Edge& e2) { return e1.weight>e2.weight;});
	for (auto it = path.begin(); it != path.end(); it++)
		if(*it != 3)
			std::cout << *it << "->";
		else
			std::cout << *it << std::endl;
	return 0;
}
