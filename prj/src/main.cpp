#include <iostream>
#include "LQueueAddProblem.hpp"
#include "VQueueDoubleAddProblem.hpp"
#include "VQueueIncAddProblem.hpp"
#include "LStackAddProblem.hpp"
#include "VStackDoubleAddProblem.hpp"
#include "VStackIncAddProblem.hpp"
#include "Benchmark.hpp"

#include <fstream>


/* UWAGA!!
 *
 * Program wykonuje się długo ze względu na testy kolejki/stosu
 * zaimplementowanej na podstawie tablicy ze strategią inkrementacyjną alokacji
 * pamięci
 */

int main(int argc, char* argv[])
{
	Benchmark<LQueueAddProblem> benchLQueue;
	Benchmark<VQueueDoubleAddProblem> benchVQueueDouble;
	Benchmark<VQueueIncAddProblem> benchVQueueInc;
	Benchmark<LStackAddProblem> benchLStack;
	Benchmark<VStackDoubleAddProblem> benchVStackDouble;
	Benchmark<VStackIncAddProblem> benchVStackInc;

	std::ofstream benchLQueueOutputFile("wyniki/LQueue.csv");
	std::ofstream benchVQueueDoubleOutputFile("wyniki/VQueueDouble.csv");
	std::ofstream benchVQueueIncOutputFile("wyniki/VQueueInc.csv");
	std::ofstream benchLStackOutputFile("wyniki/LStack.csv");
	std::ofstream benchVStackDoubleOutputFile("wyniki/VStackDouble.csv");
	std::ofstream benchVStackIncOutputFile("wyniki/VStackInc.csv");

	if(!benchLQueueOutputFile || !benchVQueueDoubleOutputFile
			|| !benchVQueueIncOutputFile || !benchLStackOutputFile
			|| !benchVStackDoubleOutputFile || !benchVStackIncOutputFile)
	{
		std::cerr << "Nie mozna otworzyc plikow wyjsciowych\n";
		return -1;
	}

	std::ifstream benchDataInputFile("input.txt");

	if(!benchDataInputFile)
	{
		std::cerr << "Nie mozna otworzyc pliku wejsciowego\n";
		return -2;
	}
	benchLQueue.start(benchDataInputFile, benchDataInputFile);
	benchLQueue.saveAsCSV(benchLQueueOutputFile);
	benchDataInputFile.clear();
	benchDataInputFile.seekg(0, std::ios::beg);
	benchVQueueDouble.start(benchDataInputFile,benchDataInputFile);
	benchVQueueDouble.saveAsCSV(benchVQueueDoubleOutputFile);
	benchDataInputFile.clear();
	benchDataInputFile.seekg(0, std::ios::beg);
	benchVQueueInc.start(benchDataInputFile,benchDataInputFile);
	benchVQueueInc.saveAsCSV(benchVQueueIncOutputFile);
	benchDataInputFile.clear();
	benchDataInputFile.seekg(0, std::ios::beg);
	benchLStack.start(benchDataInputFile,benchDataInputFile);
	benchLStack.saveAsCSV(benchLStackOutputFile);
	benchDataInputFile.clear();
	benchDataInputFile.seekg(0, std::ios::beg);
	benchVStackDouble.start(benchDataInputFile,benchDataInputFile);
	benchVStackDouble.saveAsCSV(benchVStackDoubleOutputFile);
	benchDataInputFile.clear();
	benchDataInputFile.seekg(0, std::ios::beg);
	benchVStackInc.start(benchDataInputFile,benchDataInputFile);
	benchVStackInc.saveAsCSV(benchVStackIncOutputFile);
}
