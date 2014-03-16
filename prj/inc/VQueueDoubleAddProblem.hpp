/*
 * VQueueAddProblem.hpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */

#ifndef VQUEUEADDPROBLEM_HPP_
#define VQUEUEADDPROBLEM_HPP_

#include "StandardProblem.hpp"

/*!
 * \brief Klasa reprezentująca problem dodawania do kolejki zaimplementowanej na tablicy.
 *
 * Sposób alokacji pamięci to podwajanie.
 */
class VQueueDoubleAddProblem: public StandardProblem<>
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

#endif /* VQUEUEADDPROBLEM_HPP_ */
