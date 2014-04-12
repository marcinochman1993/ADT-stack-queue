/*
 * MapGetProblem.cpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#include "MapGetProblem.hpp"

void MapGetProblem::compute()
{
	m_outputData.push_back(m_map.getValue(m_inputData[m_inputData.size()-1].m_key));
}

bool MapGetProblem::isCorrect() const
{
	return m_correctOutputData[0]==m_outputData[0];
}

void MapGetProblem::readOutData(std::istream& is)
{
	double value;
	is >> value;
	if(!is)
		throw "Blad wczytywania danych";
	m_correctOutputData.push_back(value);
}

void MapGetProblem::readInData(std::istream& is)
{
	m_map.reserve(problemSize());
	std::cout<<problemSize()<<std::endl;
	for (unsigned int i = 1; i <= problemSize(); i++)
		{
			std::string key;
			double value;
			is >> key>>value;
			if(!is)
				throw "Blad wczytywania danych";
			PairSD pair={key,value};
			m_inputData.push_back(pair);
			m_map.add(key,value);
		}
}


void MapGetProblem::clearData()
{
	StandardProblem<PairSD,double>::clearData();
	m_map.clear();
}
