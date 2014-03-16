/*
 * VStackIncAddProblem.hpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */

#ifndef VSTACKINCADDPROBLEM_HPP_
#define VSTACKINCADDPROBLEM_HPP_

#include "StandardProblem.hpp"

/*!
 * \brief Klasa reprezentująca problem wrzucania na stos zaimplementowanego na tablicy.
 *
 * Sposób alokacji pamięci to inkrementacja.
 */
class VStackIncAddProblem: public StandardProblem<>
{
	public:
			/*!
			 * \brief Patrz StandardProblem::compute
			 *
			 * Wrzuca na stos elementy stosując strategię inkrementacji.
			 */
			void compute();

			/*!
			 * \brief Patrz StandardProblem::isCorrect
			 *
			 * Zawsze zwraca true
			 */
			bool isCorrect() const;

			/*
			 * \brief Patrz StandardProblem::readOutData
			 *
			 * Nic nie robi
			 */
			void readOutData(std::istream& is=std::cin);
};



#endif /* VSTACKINCADDPROBLEM_HPP_ */
