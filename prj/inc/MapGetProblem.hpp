/*
 * MapGetProblem.hpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#ifndef MAPGETPROBLEM_HPP_
#define MAPGETPROBLEM_HPP_

#include "StandardProblem.hpp"
#include "PairSD.hpp"
#include "Map.hpp"

/*!
 * \brief Reprezentuje problem odczytu z tablicy asocjacyjnej zaimplementowanej na std::vector
 */
class MapGetProblem: public StandardProblem<PairSD,double >
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
			 * asocjacyjnej jest poprawny
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
			 * \brief Czyści wszystkie dane, łącznie z tablicą asocjacyjną
			 */
			void clearData();

		private:
			Map<StringHash,double> m_map;
};


#endif /* MAPGETPROBLEM_HPP_ */
