/*
 * HashTableGetProblem.cpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#include "HashTableGetProblem.hpp"
#include "HashTable.hpp"

void HashTableGetProblem::compute()
{
	m_outputData.push_back(m_hashTable.find(m_inputData[m_inputData.size()-1].m_key));
}

bool HashTableGetProblem::isCorrect() const
{
	return m_correctOutputData[0]==m_outputData[0];
}

void HashTableGetProblem::readOutData(std::istream& is)
{
	double value;
	is >> value;
	if(!is)
		throw "Blad wczytywania danych";
	m_correctOutputData.push_back(value);
}

void HashTableGetProblem::readInData(std::istream& is)
{
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
			m_hashTable.add(key,value);
		}
}

void HashTableGetProblem::clearData()
{
	StandardProblem<PairSD,double>::clearData();
	m_hashTable.clear();
}
