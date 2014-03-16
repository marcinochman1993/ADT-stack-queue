/*
 * VStackIncAddProblem.cpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */

#include "VStackIncAddProblem.hpp"
#include "VStack.hpp"

void VStackIncAddProblem::compute()
{
	VStack<double> vstack(VStack<double>::AllocType::INCREMENT);
	m_outputData.clear();
	for (auto it = m_inputData.begin(); it != m_inputData.end(); it++)
		vstack.push(*it);
}

bool VStackIncAddProblem::isCorrect() const
{
	return true; //zawsze jest, bo algorytm tylko dodaje do kolejki kolejne elementy
	//nie ma elementów wyjściowych
}

void VStackIncAddProblem::readOutData(std::istream& is)
{
//nic nie robi bo nie ma wyjściowych danych
}

