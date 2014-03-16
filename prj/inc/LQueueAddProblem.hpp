/*
 * LQueueAddProblem.hpp
 *
 *  Created on: 14 Mar 2014
 *      Author: mochman
 */

#ifndef LQUEUEADDPROBLEM_HPP_
#define LQUEUEADDPROBLEM_HPP_


#include "StandardProblem.hpp"

/*!
 * \brief Klasa reprezentująca problem dodawania do kolejki zaimplementowanej na liście.
 */
class LQueueAddProblem: public StandardProblem<>
{
	public:
		/*!
		 * \brief Patrz StandardProblem::compute
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




#endif /* LQUEUEADDPROBLEM_HPP_ */
