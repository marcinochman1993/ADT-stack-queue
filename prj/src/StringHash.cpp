/*
 * StringHash.cpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#include "StringHash.hpp"

unsigned long StringHash::hash() const
{
	unsigned long index=0;
	for(unsigned long i=0;i<size();i++)
		index+=(i+1)*(*this)[i];
	index%=maxHashValue()+1;
	return index;
}


std::istream& operator>>(std::istream& is, StringHash& sh)
{
	std::string str;
	is>>str;
	sh=str;
	return is;
}
