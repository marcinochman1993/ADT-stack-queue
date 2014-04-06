 
#include "Benchmark.hpp"
#include "QuickSortWorseProblem.hpp"
#include "QuickSortBetterProblem.hpp"
#include "MergeSortProblem.hpp"
#include "HeapSortProblem.hpp"
#include <fstream>
#include "Map.hpp"

int main(int argc, char* argv[])
{
	std::string key;
	double value;
	Map<std::string, double>  map;
	for(int i=0;i<5;i++)
	{
		std::cin>>key>>value;
		map.add(key,value);
	}

	for(auto it=map.begin();it!=map.end();it++)
		std::cout<<"Klucz:"<<it->m_key<<" Wartość: "<<it->m_value<<std::endl;

	std::cout<<"Do usuniecia: ";
	std::cin>>key;
	map.remove(key);

	for(auto it=map.begin();it!=map.end();it++)
			std::cout<<"Klucz:"<<it->m_key<<" Wartość: "<<it->m_value<<std::endl;

	std::cout<<"Klucz do wyświetlenia: ";
	std::cin>>key;
	try
	{
		std::cout<<map[key];
	}
	catch(const char* err)
	{
		std::cout<<"Nie znaleziono klucza\n";
	}
	return 0;
}
