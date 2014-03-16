/*
 * VStackDoubleAddProblem.hpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */

#ifndef VSTACKDOUBLEADDPROBLEM_HPP_
#define VSTACKDOUBLEADDPROBLEM_HPP_

#include "StandardProblem.hpp"

/*!
 * \brief Klasa reprezentująca problem wrzucania na stos zaimplementowanego na tablicy.
 *
 * Sposób alokacji pamięci to podwajanie.
 */
class VStackDoubleAddProblem: public StandardProblem<>
{
	public:
			/*!
			 * \brief Patrz StandardProblem::compute
			 *
			 * Wrzuca na stos elementy stosując strategię podwajania pamięci.
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




#endif /* VSTACKDOUBLEADDPROBLEM_HPP_ */
