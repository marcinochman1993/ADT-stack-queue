/*
 * BinarySTGetProblem.cpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#include "BinarySTGetProblem.hpp"

void BinarySTGetProblem::compute()
{
	m_outputData.push_back(m_binaryST.find(m_inputData[m_inputData.size()-1].m_key));
}

bool BinarySTGetProblem::isCorrect() const
{
	return m_correctOutputData[0]==m_outputData[0];
}

void BinarySTGetProblem::readOutData(std::istream& is)
{
	double value;
	is >> value;
	if(!is)
		throw "Blad wczytywania danych";
	m_correctOutputData.push_back(value);
}

void BinarySTGetProblem::readInData(std::istream& is)
{
	for (unsigned int i = 1; i <= problemSize(); i++)
		{
			std::string key;
			double value;
			is >> key>>value;
			if(!is)
				throw "Blad wczytywania danych";
			PairSD pair={key,value};
			m_inputData.push_back(pair);
			m_binaryST.add(key,value);
		}
}

void BinarySTGetProblem::clearData()
{
	StandardProblem<PairSD,double>::clearData();
	m_binaryST.clear();
}
