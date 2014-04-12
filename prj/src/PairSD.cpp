/*
 * PairSD.cpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#include "PairSD.hpp"


std::istream& operator>>(std::istream& is, PairSD& pair)
{
	is>>pair.m_key>>pair.m_value;
	return is;
}


