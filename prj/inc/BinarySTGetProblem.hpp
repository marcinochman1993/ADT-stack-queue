/*
 * BinarySTGetProblem.hpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#ifndef BINARYSTGETPROBLEM_HPP_
#define BINARYSTGETPROBLEM_HPP_

#include "PairSD.hpp"
#include "StandardProblem.hpp"
#include "BinaryST.hpp"

/*!
 * \brief Reprezentuje problem odczytu danych z tablicy aqsocjacyjnej zbudowanej na drzewie
 */
class BinarySTGetProblem: public StandardProblem<PairSD,double >
{
	public:
			/*!
			 * \brief Patrz StandardProblem::compute
			 *
			 * Pobiera z tablicy asocjacyjnej element
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
			 * Wczytuje, parę klucz-wartość i dodaje dodatkowo do tablicy asocjacyjnej
			 */
			void readInData(std::istream& is=std::cin);

			/*!
			 * \brief Czyści wszystkie dane, łącznie z drzewem
			 */
			void clearData();

		private:
			/*!
			 * \brief Przechowuje drzewo do testów
			 */
			BinaryST<StringHash,double> m_binaryST;
};


#endif /* BINARYSTGETPROBLEM_HPP_ */
