/*
 * HashTable.hpp
 *
 *  Created on: 11 Apr 2014
 *      Author: mochman
 */

#ifndef HASHTABLE_HPP_
#define HASHTABLE_HPP_

#include <algorithm>
#include <vector>
#include <list>
#include <iostream>

/*!
 * \brief Klasa reprezentująca tablicę mieszającą
 */
template <typename KeyType, typename ValueType>
class HashTable
{
	public:
		/*!
		 * \brief Domyślny konstruktor, tworzy pustą tablicę
		 */
		HashTable(): m_size(0) {}

		/*!
		 * \brief Pozwala dodać parę klucz-wartość do tablicy
		 *
		 * \param key - klucz, który implementuje interfejs Hash
		 * \param value - wartość
		 */
		void add(const KeyType& key, const ValueType& value);

		/*!
		 * \brief Pozwala znaleźć wartość pod podanym kluczem
		 *
		 * Jeśli klucza w tablicy nie ma, zgłaszany jest wyjątek const char*
		 */
		const ValueType& find(const KeyType& key);

		/*!
		 * \brief Przeciążony operator indeksowania
		 *
		 * \param key - klucz
		 */
		const ValueType& operator[](const KeyType& key) { return find(key); }

		/*!
		 * \brief Pozwala ustalić rozmiar tablicy
		 */
		unsigned long size() const { return m_size; }

		/*!
		 * \brief Pozwala usunąć wpis o podanym kluczu
		 *
		 * \param key - klucz
		 */
		void remove(const KeyType& key);

		/*!
		 * \brief Usuwa wszystkie wpisy w tablicy
		 */
		void clear();

	private:
		/*!
		 * \brief Struktura pomocnicza, przechowująca parę klucz-wartość
		 */
		struct Pair
		{
			/*!
			 * \brief Klucz
			 */
			KeyType m_key;

			/*!
			 * \brief Wartość
			 */
			ValueType m_value;
		};

		/*!
		 * \brief Tablica przechowująca listy do par klucz-wartość
		 *
		 * Listy są na wypadek kolizji
		 */
		std::vector<std::list<Pair>> m_tab;

		/*!
		 * \brief Pole przechowuje rozmiar tablicy
		 */
		unsigned long m_size;
};

template <typename KeyType, typename ValueType>
void HashTable<KeyType,ValueType>::add(const KeyType& key, const ValueType& value)
{
	m_size++;
	if(m_tab.size()==0)
		m_tab.resize(key.maxHashValue()+1);
	unsigned long index=key.hash();
	auto itFound=std::find_if(m_tab[index].begin(),m_tab[index].end(),
			[&key](const Pair& pair) { return pair.m_key==key; });
	if(itFound==m_tab[index].end())
	{
		Pair newPair={key,value};
		m_tab[index].push_back(newPair);
	}
	else
		itFound->m_value=value;
}

template <typename KeyType, typename ValueType>
const ValueType& HashTable<KeyType,ValueType>::find(const KeyType& key)
{
	const std::list<Pair>& list=m_tab[key.hash()];
	for(auto it=list.begin();it!=list.end();it++)
		if(it->m_key==key)
			return it->m_value;
	throw "Key not found";
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType,ValueType>::remove(const KeyType& key)
{
	std::list<Pair>& list=m_tab[key.hash()];
	unsigned long index=key.hash();
	auto itFound=std::find_if(list.begin(),list.end(),
			[&key](const Pair& pair) { return pair.m_key==key; });
	if(itFound!=list.end())
		list.erase(itFound);

}
template <typename KeyType, typename ValueType>
void HashTable<KeyType,ValueType>::clear()
{
	for(auto it=m_tab.begin();it!=m_tab.end();it++)
		it->clear();
}

#endif /* HASHTABLE_HPP_ */
