/*
 * StringHash.hpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#ifndef STRINGHASH_HPP_
#define STRINGHASH_HPP_

#include "Hash.hpp"
#include <string>
#include <iostream>

/*!
 * \brief Reprezentuje łańcuch znakowy z możliwością haszowania
 */
class StringHash: public std::string, public Hash
{
	public:
		/*!
		 * \brief Domyślny konstruktor
		 */
		StringHash() =default;

		/*!
		 * \brief Konstruktor pozwalający na inicjalizację typem std::string
		 */
		StringHash(const std::string& str): std::string(str) {}

		/*!
		 * \brief Konstruktor pozwalający na inicjalizację łańcuchem w stylu C
		 */
		StringHash(const char* str): std::string(str) {}

		/*!
		 * \brief Funkcja haszująca
		 *
		 * Każda litera zrzutowana na typ całkowitoliczbowy
		 * jest mnożona przez wagę, którą jest pozycja w łańuchu -
		 * jest ona liczona od 1
		 */
		unsigned long hash() const;
		/*!
		 * \brief Definiuje maksymalną wartość funkcji haszującej.
		 *
		 * Zwraca 10000.
		 */
		unsigned long maxHashValue() const { return 10000; }
};

std::istream& operator>>(std::istream& is, StringHash& sh);

#endif /* STRINGHASH_HPP_ */
