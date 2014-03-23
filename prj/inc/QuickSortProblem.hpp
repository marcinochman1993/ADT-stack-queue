/*
 * QuickSortProblem.hpp
 *
 *  Created on: Mar 19, 2014
 *      Author: mochman
 */

#ifndef QUICKSORTPROBLEM_HPP_
#define QUICKSORTPROBLEM_HPP_

#include "StandardProblem.hpp"
#include "SortingAlgorithms.hpp"

/*!
 * \brief Reprezentuje problem sortowania poprzez QuickSort
 */
template <typename DataType>
class QuickSortProblem: public StandardProblem<DataType,DataType>
{
public:
	/*!
	 * \brief Wykonuje sortowanie szybkie dla określonych danych wejściowych
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
void QuickSortProblem<DataType>::compute()
{
	quickSort(StandardProblem<DataType,DataType>::m_outputData.begin(),
			StandardProblem<DataType,DataType>::m_outputData.end());
}

template <typename DataType>
void QuickSortProblem<DataType>::readInData(std::istream& is)
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

#endif /* QUICKSORTPROBLEM_HPP_ */
