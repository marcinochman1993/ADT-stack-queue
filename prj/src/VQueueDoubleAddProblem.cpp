/*
 * VQueueDoubleAddProblem.cpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */

#include "VQueueDoubleAddProblem.hpp"
#include "VQueue.hpp"

void VQueueDoubleAddProblem::compute()
{
	VQueue<double> queue;
	m_outputData.clear();
	for (auto it = m_inputData.begin(); it != m_inputData.end(); it++)
		queue.enqueue(*it);
}

bool VQueueDoubleAddProblem::isCorrect() const
{
	return true; //zawsze jest, bo algorytm tylko dodaje do kolejki kolejne elementy
	//nie ma elementów wyjściowych
}

void VQueueDoubleAddProblem::readOutData(std::istream& is)
{
//nic nie robi bo nie ma wyjściowych danych
}
