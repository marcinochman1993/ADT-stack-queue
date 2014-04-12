/*
 * PairSD.hpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#ifndef PAIRSD_HPP_
#define PAIRSD_HPP_

#include "StringHash.hpp"

/*!
 * \brief Struktura wykorzystywana do testów tablic asocjacyjnych
 *
 * Przechowuję typ lańcuchowy oraz liczbę typu double
 */
struct PairSD
{
		/*!
		 * \brief Klucz
		 */
		StringHash m_key;

		/*!
		 * \brief Wartość
		 */
		double m_value;
};

/*!
 * \brief Przeciążony operator wczytywania ze strumienia
 *
 * \param is - strumień wejściowy
 * \param pair - zmienna, do której mają być wczytane dane
 */
std::istream& operator>>(std::istream& is, PairSD& pair);

#endif /* PAIRSD_HPP_ */
