/*
 * VStackDoubleAddProblem.cpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */


#include "VStackDoubleAddProblem.hpp"
#include "VStack.hpp"

void VStackDoubleAddProblem::compute()
{
	VStack<double> vstack;
	m_outputData.clear();
	for (auto it = m_inputData.begin(); it != m_inputData.end(); it++)
		vstack.push(*it);
}

bool VStackDoubleAddProblem::isCorrect() const
{
	return true; //zawsze jest, bo algorytm tylko dodaje do kolejki kolejne elementy
	//nie ma elementów wyjściowych
}

void VStackDoubleAddProblem::readOutData(std::istream& is)
{
//nic nie robi bo nie ma wyjściowych danych
}

