/*
 * Map.hpp
 *
 *  Created on: Apr 2, 2014
 *      Author: mochman
 */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <algorithm>

/*!
 * \brief Klasa reprezentuje tablicę asocjacyjną.
 * Jest to właściwie szablon klasy,
 * pierwszy typ to typ klucza, drugi to typ wartości.
 */
template <typename KeyType, typename ValueType>
class Map
{
	public:

		/*!
		 * \brief Jest to pomocnicza struktura, która przechowuje parę klucz-wartość
		 */
		struct Pair
		{
			Pair()=default;
			Pair(KeyType key, ValueType value):m_key(key),m_value(value){}
			KeyType m_key;
			ValueType m_value;
		};

		/*!
		 * \brief Jest to typ iteratora
		 * Zdefiniowany jako iterator listy
		 * przechowującej pary klucz-wartość
		 */
		typedef typename std::vector<Pair>::iterator iterator;

		/*!
		 * \brief Zdefiniowany typ stałego iteratora
		 *
		 * Jest to stały iterator listy przechowującej
		 * pary klucz-wartość
		 */
		typedef typename std::vector<Pair>::const_iterator const_iterator;

		/*!
		 * \brief Pozwala dodać wartość przechowywaną pod podanym kluczem.
		 *
		 * Jeśli klucz występuje w tablicy, wartość jest podmieniana.
		 *
		 * \param key - klucz
		 * \param value - wartość, która będzie przechowywana pod zadanym kluczem
		 */
		void add(KeyType key, ValueType value);

		/*!
		 * \brief Pozwala usunąć wpis pod podanym kluczem.
		 *
		 * Jeśli klucz nie zostanie znaleziony, metoda kończy działanie
		 */
		void remove(KeyType key);

		/*!
		 * \brief Pobiera wartość przechowywaną pod zadanym kluczem
		 *
		 * Jeśli metoda nie znajdzie odpowiedniego klucza, zostanie
		 * zgłoszony wyjątek const char*. Przed wywołaniem tej metody
		 * zaleca się sprawdzenie metodą contains czy istnieje wartość
		 * przechowywana pod podanym kluczem.
		 *
		 * \param key - klucz, pod którym jest przechowywana wartość
		 */
		const ValueType& getValue(KeyType key) const;

		/*!
		 * \brief Pobiera wartość przechowywaną pod zadanym kluczem
		 *
		 * Jeśli operator nie znajdzie odpowiedniego klucza, zostanie
		 * zgłoszony wyjątek const char*. Przed wywołaniem zaleca się
		 * sprawdzenie metodą contains czy istnieje wartość
		 * przechowywana pod podanym kluczem.
		 *
		 * \param key - klucz, pod którym jest przechowywana wartość
		 */
		const ValueType& operator[](const KeyType& key) const { return getValue(key); }

		/*!
		 * \brief Sprawdza czy tablica jest pusta.
		 */
		bool isEmpty() const { return size()==0; }

		/*!
		 * \brief Pozwala pobrać rozmiar tablicy
		 */
		unsigned long size() const { return m_pairs.size(); }

		unsigned long reserved() const { return m_pairs.capacity(); }

		/*!
		 * \brief Pozwala przekonać się czy istnieje wpis pod podanym kluczem
		 *
		 * \param key - klucz, który będzie sprawdzony
		 *
		 * \return true - jeśli istnieje wpis, w.p.p false
		 */
		bool contains(KeyType key) const { return cend()!=find(key); }

		/*!
		 * \brief Pobiera początkowy iterator.
		 */
		iterator begin() { return m_pairs.begin(); }

		/*!
		 * \brief Pobiera końcowy (pierwszy za ostatnim) iterator.
		 */
		iterator end() { return m_pairs.end(); }

		/*!
		 * \brief Pobiera początkowy stały iterator.
		 */
		const_iterator cbegin() const { return m_pairs.cbegin(); }

		/*!
		 * \brief Pobiera końcowy stały iterator.
		 */
		const_iterator cend() const { return m_pairs.cend(); }
	private:

		/*!
		 * \brief Służy do przechowywania par klucz-wartość
		 */
		std::vector<Pair> m_pairs;
		/*!
		 * \brief Pozwala wyszukać iterator na parę klucz-wartość o podanym kluczu.
		 *
		 * \return zwracany jest iterator na znalezioną parę, jeśli nie została znaleziona jest to end()
		 */
		iterator find(KeyType key);

		/*!
		 * \brief Pozwala wyszukać iterator na parę klucz-wartość o podanym kluczu.
		 *
		 * \param key - wyszukiwany klucz
		 *
		 * \return zwracany jest stały iterator na znalezioną parę, jeśli nie została znaleziona jest to cend()
		 */
		const_iterator find(KeyType key) const;
};

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::add(KeyType key, ValueType value)
{
	iterator pairIt=find(key);
	if(pairIt!=end() && pairIt->m_key==key)
		pairIt->m_value=value;
	else
		m_pairs.insert(pairIt,Pair(key,value));
}

template <typename KeyType, typename ValueType>
auto Map<KeyType,ValueType>::find(KeyType key) -> iterator
{
	Pair pair;
	pair.m_key=key;
	return std::lower_bound(begin(),end(),pair,[](const Pair& pair1,const Pair& pair2)
			{ return pair1.m_key<pair2.m_key; } );
}

template <typename KeyType, typename ValueType>
auto Map<KeyType,ValueType>::find(KeyType key) const -> const_iterator
{
	Pair pair;
	pair.m_key=key;
	return std::lower_bound(cbegin(),cend(),pair,[](const Pair& pair1,const Pair& pair2)
			{ return pair1.m_key<pair2.m_key; } );
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::remove(KeyType key)
{
	iterator foundIt=find(key);
	if(foundIt!=end())
		m_pairs.erase(foundIt);
}

template <typename KeyType, typename ValueType>
const ValueType& Map<KeyType,ValueType>::getValue(KeyType key) const
{
	const_iterator foundIt=find(key);
	if(foundIt!=cend())
		return foundIt->m_value;
	throw "Key was not found";
}

#endif /* MAP_HPP_ */
