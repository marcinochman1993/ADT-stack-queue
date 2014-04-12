/*
 * Hash.hpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#ifndef HASH_HPP_
#define HASH_HPP_

/*!
 * \brief Klasa abstrakcyjna definiująca interfejs dla typów haszujących
 */
class Hash
{
	public:
		/*!
		 * \brief Funkcja haszująca
		 */
		virtual unsigned long hash() const=0;

		/*!
		 * \brief Maksymalna wartość jaką może przybierać funkcja haszująca
		 *
		 * Zaklada się, że minimalną wartościa funkcji mieszającej jest 0,
		 * dlatego funkcja ta może służyć do ustawiania wielkości tablicy
		 * mieszającej
		 */
		virtual unsigned long maxHashValue() const=0;

		/*!
		 * \brief Wirtualny destruktor
		 *
		 * Nic nie robi
		 */
		virtual ~Hash() {};
};


#endif /* HASH_HPP_ */
