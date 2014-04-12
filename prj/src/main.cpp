 
#include "Benchmark.hpp"
#include <iostream>
#include "BinaryST.hpp"
#include "HashTableGetProblem.hpp"
#include "MapGetProblem.hpp"
#include "BinarySTGetProblem.hpp"
#include "Benchmark.hpp"
#include <fstream>

int main(int argc, char* argv[])
{

	try
	{
		std::ifstream inputFileBig("inputBig.txt"), inputFileSmall("inputSmall.txt");
		std::ofstream binOutputFile("output/binSTOutput.csv");
		std::ofstream mapOutputFile("output/mapOutput.csv");
		std::ofstream hashOutputFile("output/hashOutput.csv");
		if(!inputFileBig || !inputFileSmall)
		{
			std::cerr<<"Blad otwierania plikow z danymi";
			return -1;
		}

		if(!hashOutputFile || !mapOutputFile || !binOutputFile)
		{
			std::cerr<<"Blad otwierania plikow wyjsciowych";
			return -2;
		}

		Benchmark<BinarySTGetProblem> binSTBench;
		Benchmark<MapGetProblem> mapBench;
		Benchmark<HashTableGetProblem> hashBench;
		std::cout<<"Binary Tree\n";
		binSTBench.start(inputFileBig,inputFileBig);
		binSTBench.saveAsCSV(binOutputFile);

		std::cout<<"Map\n";
		mapBench.start(inputFileSmall,inputFileSmall);
		mapBench.saveAsCSV(mapOutputFile);

		inputFileBig.clear();
		inputFileBig.seekg(0,std::ios::beg);

		std::cout<<"Hash Table\n";
		hashBench.start(inputFileBig,inputFileBig);
		hashBench.saveAsCSV(hashOutputFile);
	}
	catch(const char* err)
	{
		std::cerr<<err;
	}
	return 0;
}
