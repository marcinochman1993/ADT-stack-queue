/*
 * LStackAddProblem.hpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */

#ifndef LSTACKADDPROBLEM_HPP_
#define LSTACKADDPROBLEM_HPP_

#include "StandardProblem.hpp"

/*!
 * \brief Klasa reprezentująca problem dodawania na stos elementów.
 */
class LStackAddProblem: public StandardProblem<>
{
	public:
		/*!
		 * \brief Patrz StandardProblem::compute
		 *
		 * Dodaje na stos elementy z dannych wejściowych
		 */
		void compute();

		/*!
		 * \brief Patrz StandardProblem::isCorrect
		 *
		 * Zwraca zawsze true
		 */
		bool isCorrect() const;

		/*!
		 * \brief Patrz StandardProblem::readOutData
		 *
		 * Nic nie robi
		 */
		void readOutData(std::istream& is = std::cin);
};

#endif /* LSTACKADDPROBLEM_HPP_ */
