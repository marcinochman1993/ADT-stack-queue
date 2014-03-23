 
#include "Benchmark.hpp"
#include "QuickSortProblem.hpp"
#include "MergeSortProblem.hpp"
#include "HeapSortProblem.hpp"
#include <fstream>

int main(int argc, char* argv[])
{
	std::ifstream randomInputFile("randomInput.txt");
	std::ifstream quickSortWorstInputFile("worstQuickSortInput.txt");
	if(!quickSortWorstInputFile || !randomInputFile)
	{
		std::cerr<<"Error while opening input files\n";
		return -1;
	}
	std::ofstream mergeSortBenchOutput("output/mergeSortBench.csv");
	std::ofstream quickSortBenchOutput("output/quickSortBench.csv");
	std::ofstream quickSortWorstBenchOutput("output/quickSortWorstBench.csv");
	std::ofstream heapSortBenchOutput("output/heapSortBench.csv");
	if(!heapSortBenchOutput || !quickSortBenchOutput ||
			!mergeSortBenchOutput || !quickSortWorstBenchOutput)
	{
		std::cerr<<"Error while opening output files\n";
		return -2;
	}
	std::cout<<"MergeSort...\n";
	Benchmark<MergeSortProblem<double>> mergeSortBench;
	mergeSortBench.start(randomInputFile,randomInputFile);
	mergeSortBench.saveAsCSV(mergeSortBenchOutput);
	randomInputFile.clear();
	randomInputFile.seekg(0,std::ios::beg);
	std::cout<<"QuickSort...\n";
	Benchmark<QuickSortProblem<double>> quickSortAverageBench;
	quickSortAverageBench.start(randomInputFile,randomInputFile);
	quickSortAverageBench.saveAsCSV(quickSortBenchOutput);
	randomInputFile.clear();
	randomInputFile.seekg(0,std::ios::beg);
	std::cout<<"HeapSort...\n";
	Benchmark<HeapSortProblem<double>> heapSortBench;
	heapSortBench.start(randomInputFile,randomInputFile);
	heapSortBench.saveAsCSV(heapSortBenchOutput);
	std::cout<<"QuickSort Worst.\n";
	Benchmark<QuickSortProblem<double>> quickSortWorstBench;
	quickSortWorstBench.start(quickSortWorstInputFile,quickSortWorstInputFile);
	quickSortWorstBench.saveAsCSV(quickSortWorstBenchOutput);
}
