/*
 * VQueueIncAddProblem.cpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */

#include "VQueueIncAddProblem.hpp"
#include "VQueue.hpp"

void VQueueIncAddProblem::compute()
{
	VQueue<double> queue(VQueue<double>::AllocType::INCREMENT);
	m_outputData.clear();
	for (auto it = m_inputData.begin(); it != m_inputData.end(); it++)
		queue.enqueue(*it);
}

bool VQueueIncAddProblem::isCorrect() const
{
	return true; //zawsze jest, bo algorytm tylko dodaje do kolejki kolejne elementy
	//nie ma elementów wyjściowych
}

void VQueueIncAddProblem::readOutData(std::istream& is)
{
//nic nie robi bo nie ma wyjściowych danych
}



