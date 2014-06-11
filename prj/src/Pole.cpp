/*
 * Pole.cpp
 *
 *  Created on: May 20, 2014
 *      Author: mochman
 */

#include "Pole.hpp"


void Pole::awansPionka()
{
	if(m_stan==STAN_POLA::BIALY_PIONEK)
		m_stan=STAN_POLA::BIALA_MATKA;
	else
		if(m_stan==STAN_POLA::CZARNY_PIONEK)
			m_stan=STAN_POLA::CZARNA_MATKA;
}

std::ostream& operator<<(std::ostream& os, const Pole& pole)
{
	char tab[]="bc BC";
	os<<tab[static_cast<int>(pole.stan())];
	return os;
}
