/*
 * HeapSortProblem.hpp
 *
 *  Created on: 21 Mar 2014
 *      Author: mochman
 */

#ifndef HEAPSORTPROBLEM_HPP_
#define HEAPSORTPROBLEM_HPP_

#include "StandardProblem.hpp"
#include "SortingAlgorithms.hpp"

/*!
 * \brief Reprezentuje problem sortowania przez kopcowanie
 */
template <typename DataType>
class HeapSortProblem: public StandardProblem<DataType,DataType>
{
public:
	/*!
	 * \brief Wykonuje sortowanie przez kopcowanie dla określonych danych wejściowych
	 */
	void compute();

	/*!
	 * \brief Patrz StandardProblem::reaInData
	 *
	 * Dodatkowo zapełnia wektor wyjścia, tak aby później
	 * można było posortować dane
	 */
	void readInData(std::istream& is = std::cin);
};

template <typename DataType>
void HeapSortProblem<DataType>::compute()
{
	heapSort(StandardProblem<DataType,DataType>::m_outputData.begin(),
			StandardProblem<DataType,DataType>::m_outputData.end());
}

template <typename DataType>
void HeapSortProblem<DataType>::readInData(std::istream& is)
{
	for (unsigned int i = 1; i <= StandardProblem<DataType,DataType>::problemSize(); i++)
	{
		DataType temp;
		is >> temp;
		if(!is)
			throw "Blad wczytywania danych";
		StandardProblem<DataType,DataType>::m_inputData.push_back(temp);
		StandardProblem<DataType,DataType>::m_outputData.push_back(temp);
	}
}



#endif /* HEAPSORTPROBLEM_HPP_ */
