/*
 * VQueueIncAddProblem.hpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */

#ifndef VQUEUEINCADDPROBLEM_HPP_
#define VQUEUEINCADDPROBLEM_HPP_

#include "StandardProblem.hpp"

/*!
 * \brief Klasa reprezentująca problem dodawania do kolejki zaimplementowanej na tablicy.
 *
 * Sposób alokacji pamięci to inkrementacja.
 */
class VQueueIncAddProblem: public StandardProblem<>
{
	public:
			/*!
			 * \brief Patrz StandardProblem::compute
			 *
			 * Wrzuca elementy do kolejki.
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

#endif /* VQUEUEINCADDPROBLEM_HPP_ */
