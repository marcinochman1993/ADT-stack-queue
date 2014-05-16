/*
 * Simplex.hpp
 *
 *  Created on: May 13, 2014
 *      Author: mochman
 */

#ifndef SIMPLEX_HPP_
#define SIMPLEX_HPP_

#include "FunctionArguments.hpp"
#include "ObjectiveFunction.hpp"
#include "Matrix.hpp"
#include "Constraint.hpp"

/*!
 * \brief Funkcja generuje tablicę simpleksową, na podstawie ograniczeń i funkcji celu
 *
 * \param constraints - ograniczenia
 * \param function - funkcja celu
 * \param [out] simplexTab - macierz, która zostanie wypełniona odpowiednimi liczbami
 */
template<typename ArgType = double, typename RetType = double,
		typename CoeffType = double>
void generateSimplexTab(const std::vector<Constraint<ArgType>>& constraints,
		const ObjectiveFunction<ArgType, RetType, CoeffType>& function,
		Matrix<CoeffType>& simplexTab)
{
	unsigned long cols = simplexTab.getColumnsNumber(), rows =
			simplexTab.getRowsNumber(), constrNum = constraints.size(), argsNum =
			function.size();
	if(constrNum + 1 != rows || argsNum + constrNum + 2 != cols)
		throw "simplexTab has not proper size";
	for (unsigned long i = 0; i < constrNum; i++) //generuje część odpowiedzialna za ograniczenia pod argumentami
		for (unsigned long j = 0; j < argsNum; j++)
			simplexTab(i, j) = constraints[i].getCoeff(j);
	for (unsigned long j = 0; j < argsNum; j++) // generuje dolną część tablicy pod argumentami
		simplexTab(rows - 1, j) = -function.getCoeff(j);
	for (unsigned long j = 0; j < constrNum; j++) // generuje część związaną ze zmiennymi dodatkowymi
		simplexTab(j, j + argsNum) = 1;
	for (unsigned long j = 0; j < constrNum; j++) // część pod p - same zera
		simplexTab(j, argsNum + constrNum) = 0;
	for (unsigned long j = 0; j < constrNum; j++) // ostatnia kolumna, kolumna B
		simplexTab(j, argsNum + constrNum + 1) = constraints[j].getB();
	for (unsigned long j = argsNum; j < argsNum + constrNum - 1; j++) //ostatni wiersz pod zmienn. dodatk. - same zera
		simplexTab(rows - 1, j) = 0;
	simplexTab(rows - 1, cols - 2) = 1;
	simplexTab(rows - 1, cols - 1) = 0;
}

/*!
 * \brief Funkcja pomocnicza dla algorytmu simplex.
 *
 * Wyszukuje minimalny element z ostatniej kolumny dzielony przez
 * element z kolumny piwotu. Zwraca numer wiersza minimalnej znalezionej
 * wartości.
 *
 * \param simplexTab - tablica simpleksowa
 * \param pivotColumn - aktualna kolumna piwotu
 *
 */
template<typename CoeffType = double>
static unsigned long findMinInColumnBDiv(const Matrix<CoeffType>& simplexTab,
		unsigned long pivotColumn)
{
	unsigned long minRow = 0, rows = simplexTab.getRowsNumber(), cols =
			simplexTab.getColumnsNumber();
	CoeffType maxValue = simplexTab(minRow, cols - 1)
			/ simplexTab(minRow, pivotColumn);
	for (unsigned long j = 1; j <= rows - 2; j++)
		if(simplexTab(j, cols - 1) / simplexTab(j, pivotColumn)
				< simplexTab(minRow, cols - 1) / simplexTab(minRow, pivotColumn))
		{
			minRow = j;
			maxValue = simplexTab(j, cols - 1) / simplexTab(j, pivotColumn);
		}
	return minRow;
}

/*!
 * \brief Funkcja, która przeprowadza algorytm SIMPLEX
 *
 * Funkcja rozwiązuje problem maksymalizacji funkcji celu dla ograniczeń
 * typu Ax<=b
 *
 * \param constraints - ograniczenia
 * \param function - funkcja celu
 */
template<typename ArgType = double, typename RetType = double,
		typename CoeffType = double>
FunctionArguments<ArgType> simplex(
		const std::vector<Constraint<ArgType>>& constraints,
		const ObjectiveFunction<ArgType, RetType, CoeffType>& function)
{
	if(constraints.size() == 0)
		throw "No constraints";
	if(constraints[0].size() != function.size())
		throw "Size of constraints not equal to function size";
	Matrix<CoeffType> simplexTab(constraints.size() + 1,
			function.size() + constraints.size() + 2);
	unsigned long cols = simplexTab.getColumnsNumber(), rows =
			simplexTab.getRowsNumber(), constrNum = constraints.size(), argsNum =
			function.size();
	generateSimplexTab(constraints, function, simplexTab);
	std::map<unsigned long,unsigned long> slackSwaped;
	while (simplexTab.countIfInRange(rows - 1, 0, rows - 1, cols - 1,
			[](const CoeffType& x)
			{	return x<0;}))
	{
		unsigned long pivotColumn, row;
		simplexTab.findMinimumInRange(rows - 1, 0, rows - 1, cols - 3, row,
				pivotColumn);
		row = findMinInColumnBDiv(simplexTab, pivotColumn);
		slackSwaped[row]=pivotColumn;
		simplexTab.multiplyRow(1/simplexTab(row,pivotColumn),row);
		for(unsigned long j=0;j<rows;j++)
			if(j!=row)
				simplexTab.addRow(-simplexTab(j,pivotColumn),row,j);
	}
	std::cout<<simplexTab;
	FunctionArguments<ArgType> bestSolution;
	bestSolution.size(argsNum);
	for(unsigned long j=0;j<constrNum;j++)
		bestSolution.setArg(slackSwaped[j],simplexTab(j,cols-1));
	return bestSolution;
}

#endif /* SIMPLEX_HPP_ */
