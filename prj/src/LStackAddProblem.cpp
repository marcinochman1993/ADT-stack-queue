/*
 * LStackAddProblem.cpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */

#include "LStackAddProblem.hpp"
#include "LStack.hpp"

void LStackAddProblem::compute()
{
	LStack<double> queue;
	m_outputData.clear();
	for (auto it = m_inputData.begin(); it != m_inputData.end(); it++)
		queue.push(*it);
}

bool LStackAddProblem::isCorrect() const
{
	return true; //zawsze jest, bo algorytm tylko dodaje do kolejki kolejne elementy
	//nie ma elementów wyjściowych
}

void LStackAddProblem::readOutData(std::istream& is)
{
//nic nie robi bo nie ma wyjściowych danych
}

