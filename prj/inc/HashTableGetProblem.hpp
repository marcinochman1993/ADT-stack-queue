/*
 * HashTableAddProblem.hpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#ifndef HASHTABLEADDPROBLEM_HPP_
#define HASHTABLEADDPROBLEM_HPP_

#include "StandardProblem.hpp"
#include "HashTable.hpp"
#include "PairSD.hpp"

/*!
 * \brief Reprezentuje problem odczytu danych z tablicy mieszającej
 */
class HashTableGetProblem: public StandardProblem<PairSD,double>
{
	public:
		/*!
		 * \brief Patrz StandardProblem::compute
		 *
		 * Pobiera z tablicy mieszającej element
		 */
		void compute();

		/*!
		 * \brief Patrz StandardProblem::isCorrect
		 *
		 * Zwraca true jeśli wynik pobierania z tablicy
		 * mieszającej jest poprawny
		 */
		bool isCorrect() const;

		/*
		 * \brief Patrz StandardProblem::readOutData
		 *
		 * Wczytuje liczbę double, która jest przechowywana wartością
		 * pod podanym kluczem
		 */
		void readOutData(std::istream& is=std::cin);


		/*!
		 * \brief Patrz StandardProblem::readInData
		 *
		 * Wczytuje, parę klucz-wartość i dodaje dodatkowo do tablicy mieszającej
		 */
		void readInData(std::istream& is=std::cin);

		/*!
		 * \brief Czyści wszystkie dane, łącznie z tablicą mieszającą
		 */
		void clearData();

	private:
		HashTable<StringHash,double> m_hashTable;
};

#endif /* HASHTABLEADDPROBLEM_HPP_ */
