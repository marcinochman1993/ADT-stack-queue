/*
 * StandardProblem.hpp
 *
 *  Created on: 28 Feb 2014
 *      Author: mochman
 */

#ifndef STANDARDPROBLEM_HPP_
#define STANDARDPROBLEM_HPP_

#include <vector>
#include "Problem.hpp"

/*! \brief Klasa definiuje standardowy problem algorytmiczny
 *
 * Poprzez standardowy problem algorytmiczny rozumiem problem, w którym
 * wczytuje się rozmiar problemu a następnie tablicę tego samego typu.
 * Wynikiem jest zbiór liczb tego samego typu o tej samej liczności
 * Przykładem może być np. mnożenie tablicy przez stałą, sortowanie itp.
 */
template<typename InputDataType = double, typename OutputDataType = double>
class StandardProblem: public Problem
{
	public:
		/*! \brief Patrz Problem::readInData
		 */
		virtual void readInData(std::istream& is = std::cin);

		/*! \brief Patrz Problem::readOutData
		 */
		virtual void readOutData(std::istream& is = std::cin);

		/*! \brief Patrz Problem::isCorrect
		 */
		virtual bool isCorrect() const;

		/*! \brief Patrz Problem::compute
		 */
		virtual void compute() = 0;

		/*! \brief Patrz Problem::problemSize
		 */
		virtual unsigned int problemSize() const
		{
			return m_problemSize;
		}
		/*! \brief Patrz Problem::problemSize(unsigned int)
		 *
		 * Dodatkowo zmiana powoduje wyczyszczenie wszystkich danych
		 * oraz rezerwację pamięci o odpowiedniej wielkości
		 */
		virtual void problemSize(unsigned int size)
		{
			m_problemSize = size;
			clearData();
		}

		virtual void clearData();
	protected:
		/*! \brief Wektor przechowujący dane wejściowe
		 *
		 */
		std::vector<InputDataType> m_inputData;

		/*! \brief Wektor przechowujący dane wyjściowe
		 *
		 *  Są to dane wygenerowane poprzez metodę compute()
		 */
		std::vector<OutputDataType> m_outputData;

		/*! \brief Wektor przechowujący poprawne dane wyjściowe
		 *
		 *  Z tymi danymi jest porównywane wyjście algorytmu i sprawdzana
		 *  poprawność algorytmu.
		 */
		std::vector<OutputDataType> m_correctOutputData;
	private:
		/*! \brief Pole przechowujące rozmiar problemu
		 */
		unsigned int m_problemSize;
};

template<typename InputDataType, typename OutputDataType>
void StandardProblem<InputDataType, OutputDataType>::readInData(
		std::istream& is)
{
	for (unsigned int i = 1; i <= problemSize(); i++)
	{
		InputDataType temp;
		is >> temp;
		if(!is)
			throw "Blad wczytywania danych";
		m_inputData.push_back(temp);
	}
}

template<typename InputDataType, typename OutputDataType>
void StandardProblem<InputDataType, OutputDataType>::readOutData(
		std::istream& is)
{
	for (unsigned int i = 1; i <= problemSize(); i++)
	{
		OutputDataType temp;
		is >> temp;
		if(!is)
			throw "Blad wczytywania danych";
		m_correctOutputData.push_back(temp);
	}
}

template<typename InputDataType, typename OutputDataType>
void StandardProblem<InputDataType, OutputDataType>::clearData()
{
	m_inputData.clear();
	m_inputData.reserve(m_problemSize);
	m_correctOutputData.clear();
	m_correctOutputData.reserve(m_problemSize);
	m_outputData.clear();
	m_outputData.reserve(m_problemSize);
}

template<typename InputDataType, typename OutputDataType>
bool StandardProblem<InputDataType, OutputDataType>::isCorrect() const
{
	if(m_outputData.size() != m_correctOutputData.size())
		return false;

	for (unsigned i = 0; i < m_outputData.size(); i++)
		if(m_outputData[i] != m_correctOutputData[i])
			return false;
	return true;
}

#endif /* STANDARDPROBLEM_HPP_ */
