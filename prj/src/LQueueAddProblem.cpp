/*
 * LQueueAddProblem.cpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */

#include "LQueueAddProblem.hpp"
#include "LQueue.hpp"

void LQueueAddProblem::compute()
{
	LQueue<double> queue;
	m_outputData.clear();
	for (auto it = m_inputData.begin(); it != m_inputData.end(); it++)
		queue.enqueue(*it);
}

bool LQueueAddProblem::isCorrect() const
{
	return true; //zawsze jest, bo algorytm tylko dodaje do kolejki kolejne elementy
	//nie ma elementów wyjściowych
}

void LQueueAddProblem::readOutData(std::istream& is)
{
//nic nie robi bo nie ma wyjściowych danych
}
