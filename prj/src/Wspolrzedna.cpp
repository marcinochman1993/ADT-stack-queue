#include "Wspolrzedna.hpp"
#include <map>

std::map<char,unsigned int> Wspolrzedna::s_zamianaCharUint=
{
		{'a',1}, {'b',2}, {'c',3}, {'d',4}, {'e',5},
		{'f',6}, {'g',7}, {'h',8}, {'i',9},{'j',10},
		{'k',11},{'l',12},{'m',13},{'n',14},{'o',15},
		{'p',16},{'q',17},{'r',18},{'s',19},{'t',20},
		{'u',21},{'v',22},{'w',23},{'x',24},{'y',25},
		{'z',26}
};

std::map<unsigned int,char> Wspolrzedna::s_zamianaUintChar=
{
		{1,'a'}, {2,'b'}, {3,'c'}, {4,'d'}, {5,'e'},
		{6,'f'}, {7,'g'}, {8,'h'}, {9,'i'},{10,'j'},
		{11,'k'},{12,'l'},{13,'m'},{14,'n'},{15,'o'},
		{16,'p'},{17,'q'},{18,'r'},{19,'s'},{20,'t'},
		{21,'u'},{22,'v'},{23,'w'},{24,'x'},{25,'y'},
		{26,'z'}
};

unsigned int Wspolrzedna::wierszLiczba() const
{
	return s_zamianaCharUint[m_wiersz];
}

void Wspolrzedna::wierszLiczba(unsigned int nowyWiersz)
{
	std::map<unsigned int,char>::iterator it=s_zamianaUintChar.find(nowyWiersz);
	if(it!=s_zamianaUintChar.end())
		m_wiersz=it->second;
	else
		throw "Niepoprawny indeks wiersza";
}

void Wspolrzedna::wiersz(char nowyWiersz)
{
	std::map<char,unsigned int>::iterator it=s_zamianaCharUint.find(nowyWiersz);
	if(it!=s_zamianaCharUint.end())
		m_wiersz=nowyWiersz;
	else
		throw "Niepoprawny indeks wierszaaaaa";
}

std::ostream& operator<<(std::ostream& os,const Wspolrzedna& wsp)
{
	os<<wsp.wiersz()<<wsp.kolumna();
	return os;
}
