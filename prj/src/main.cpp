 
#include "Benchmark.hpp"
#include <iostream>
#include <fstream>
#include "Graph.hpp"
#include <ctime>

int main(int argc, char* argv[])
{
	Graph<int,int> graf;
	for(unsigned int i=1;i<=4;i++)
		graf.addVertice(i);
	graf.addEdge(1,3,5);
	graf.addEdge(3,2,2);
	graf.addEdge(3,4,3);
	graf.addEdge(4,1,4);
	graf.dfs(4,[](int i){std::cout<<i<<std::endl;});
	return 0;
}
