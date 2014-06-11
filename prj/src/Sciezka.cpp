/*
 * Sciezka.cpp
 *
 *  Created on: 24 May 2014
 *      Author: mochman
 */

#include "Sciezka.hpp"


bool Sciezka::dolaczSciezke(const Sciezka& sciezka)
{
	if(sciezka.iloscPol()==0)
	{
		m_listaPol.insert(m_listaPol.end(),sciezka.m_listaPol.begin(),
				sciezka.m_listaPol.end());
		return true;
	}
	if(ostatniePole()==sciezka.pierwszePole())
	{
		m_listaPol.insert(m_listaPol.end(),++sciezka.m_listaPol.begin(),
				sciezka.m_listaPol.end());
		return true;
	}
	else
	{
		m_listaPol.insert(m_listaPol.end(),sciezka.m_listaPol.begin(),
				sciezka.m_listaPol.end());
		return true;
	}
	return false;
}


std::ostream& operator<<(std::ostream& os, const Sciezka& sciezka)
{
	const std::list<Wspolrzedna> listaPol=sciezka.listaPol();
	auto it=listaPol.begin();

	unsigned int i=0;
	while(i<listaPol.size())
	{
		if(i!=listaPol.size()-1)
			os<<*it<<"->";
		else
			os<<*it;
		it++;
		i++;
	}
	return os;
}
