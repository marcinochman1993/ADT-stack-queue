/*
 * VQueue.hpp
 *
 *  Created on: Mar 12, 2014
 *      Author: mochman
 */

#ifndef VQUEUE_HPP_
#define VQUEUE_HPP_

#include "Vector.hpp"

/*!
 * \brief Klasa reprezentująca kolejkę zaimiplementowaną na podstawie tablicy.
 */
template<typename Type>
class VQueue
{
	public:
		/*!
		 * \brief Rodzaj alokacji pamięci.
		 */
		enum class AllocType
		{
			INCREMENT, DOUBLE_QUARTER
		};

		/*!
		 * \brief Konstruktor inicjalizujący pola na 0 i nullptr.
		 *
		 * Domyślnym typem alokacji jest AllocType::DOUBLE_QUARTER
		 *
		 * \param allocType - sposób alokacji
		 */
		VQueue(AllocType allocType = AllocType::DOUBLE_QUARTER)
				: m_allocType(allocType), m_end(0), m_begin(0)
		{
		}

		/*!
		 * \brief Sprawdza czy kolejka jest pusta.
		 */
		bool isEmpty()
		{
			return size() == 0;
		}

		/*!
		 * \brief Pozwala na pobranie rozmiaru kolejki
		 */
		unsigned int size() const;

		/*!
		 * \brief Dokonuje operacji dodawania elementu na koniec kolejki
		 */
		void enqueue(const Type& element);

		/*!
		 *  \brief Ściąga/zwraca z kolejki pierwszy element(który był dodany zostal najwcześniej)
		 */
		Type dequeue();

		/*!
		 * \brief Pozwala zorientować się jaki rodzaj alokacji jest używany.
		 */
		AllocType allocType() const
		{
			return m_allocType;
		}

		/*!
		 * \brief Pozwala ustawić rodzaj alokacji
		 *
		 * \param allocType - nowy sposób alokacji
		 */
		void alloctype(AllocType allocType)
		{
			m_allocType = allocType;
		}

	private:
		/*!
		 * \brief Tablica przechowująca dane
		 */
		Vector<Type> m_vec;

		/*!
		 * \brief Indeks początku kolejki
		 */
		unsigned int m_begin;

		/*!
		 * \brief Indeks ostatniego elementu w kolejce
		 */
		unsigned int m_end;

		/*!
		 * \brief Sposób alokacji pamięci
		 */
		AllocType m_allocType;

		/*!
		 * \brief Dodaje do kolejki jeden element alokując na 1 nowe miejsce
		 *
		 * Jest tutaj wykonywana operacja kopiowania za każdym razem.
		 */
		void enqueueIncrement(const Type& element);

		/*!
		 *\brief Dodaje do kolejki element, stosując zasadę podwajania miejsca (gdy go zabraknie)
		 */
		void enqueueDouble(const Type& element);

		/*!
		 * \brief Zwraca/ściąga z kolejki pierwszy element dokonując realokacji miejsca (rozmiar mniejszy o 1)
		 *
		 * Kopiowanie odbywa się za każdym razem.
		 */
		Type dequeueIncrement();

		/*!
		 * \brief Zwraca/ściąga z kolejki pierwszy element dokonując realokacji.
		 *
		 * Realokacja odbywa się wtedy gdy rozmiar jest mniejszy niz 0.25 rozmiaru całej
		 * zaalokowanej pamięci
		 */
		Type dequeueQuarter();
};

template<typename Type>
unsigned int VQueue<Type>::size() const
{
	if(m_begin > m_end)
		return (m_vec.size() - (m_begin - m_end)) % m_vec.size();
	if(m_begin < m_end)
		return m_end - m_begin;
	return 0;
}

template<typename Type>
void VQueue<Type>::enqueue(const Type& element)
{
	switch (m_allocType)
	{
		case AllocType::INCREMENT:
			enqueueIncrement(element);
			break;
		case AllocType::DOUBLE_QUARTER:
			enqueueDouble(element);
			break;
	}
}

template<typename Type>
void VQueue<Type>::enqueueIncrement(const Type& element)
{
	if(m_begin > m_end)
	{
		Vector<Type> temp;
		temp.reserve(size() + 1);
		for (auto it = m_vec.begin() + m_begin; it != m_vec.end(); it++)
			temp.push_back(*it);
		for (auto it = m_vec.begin(); it != m_vec.begin() + m_end; it++)
			temp.push_back(*it);
		temp.push_back(element);
		m_vec = std::move(temp); // nie trzeba tracić czasu na kopiowanie
		m_end++;
	}
	else
	{
		m_vec.push_back(element);
		m_end++;
	}
}

template<typename Type>
void VQueue<Type>::enqueueDouble(const Type& element)
{
	if(size() + 1 > m_vec.allocatedSize()) //trzeba alokować
	{
		Vector<Type> temp;
		temp.reserve(2 * (size() + 1));
		if(m_begin > m_end) // tablica "pocięta"
		{
			for (auto it = m_vec.begin() + m_begin; it != m_vec.end(); it++)
				temp.push_back(*it);
			for (auto it = m_vec.begin(); it != m_vec.begin() + m_end; it++)
				temp.push_back(*it);
		}
		else // tablica ciągła
		{
			for (auto it = m_vec.begin() + m_begin; it != m_vec.begin() + m_end; it++)
				temp.push_back(*it);
		}
		temp.push_back(element);
		m_vec = std::move(temp);
		m_begin = 0;
		m_end = m_vec.size();
	}
	else // nie trzeba alokować
	{
		if(m_end < m_vec.allocatedSize()) // można dodać na koniec
		{
			m_vec.push_back(element);
			m_end++;
		}
		else
		{
			if(m_end == m_vec.allocatedSize()) //m_end na samym koncu tablicy, musi być przeskok
			{
				m_end = 0;
				m_vec[m_end] = element;
			}
			else
				m_vec[m_end++];
		}

	}
}

template<typename Type>
Type VQueue<Type>::dequeue()
{
	switch (m_allocType)
	{
		case AllocType::INCREMENT:
			return dequeueIncrement();

		case AllocType::DOUBLE_QUARTER:
			return dequeueQuarter();
	}
}

template<typename Type>
Type VQueue<Type>::dequeueIncrement()
{
	if(size())
	{
		Vector<Type> temp;
		temp.reserve(size() - 1);
		Type element = m_vec[m_begin];
		if(m_begin < m_end)
		{
			for (unsigned int i = m_begin + 1; i < m_end; i++)
				temp.push_back(m_vec[i]);
			m_vec = std::move(temp);
			m_begin = 0;
			m_end = m_vec.size();
		}
		else
		{
			for (auto it = m_vec.begin() + m_begin + 1; it != m_vec.end(); it++)
				temp.push_back(*it);
			for (auto it = m_vec.begin(); it != m_vec.begin() + m_end; it++)
				temp.push_back(*it);
		}
		return element;
	}
	throw "VQueue is empty! ";
}

template<typename Type>
Type VQueue<Type>::dequeueQuarter()
{
	if(size())
	{
		Type element = m_vec[m_begin];
		if(size() - 1 <= m_vec.allocatedSize() / 4)
		{
			Vector<Type> temp;
			temp.reserve(2 * (size() - 1));
			if(m_begin > m_end)
			{
				for (auto it = m_vec.begin() + m_begin + 1; it != m_vec.end(); it++)
					temp.push_back(*it);
				for (auto it = m_vec.begin(); it != m_vec.begin() + m_end; it++)
					temp.push_back(*it);
				m_vec = std::move(temp);
				m_begin = 0;
				m_end = m_vec.size();
			}
			else
			{
				for (auto it = m_vec.begin() + m_begin + 1; it != m_vec.begin() + m_end;
						it++)
					temp.push_back(*it);
				m_vec = std::move(temp);
				m_begin = 0;
				m_end = m_vec.size();
			}
		}
		else
		{
			if(m_begin == m_vec.size())
				m_begin = 0;
			else
				m_begin++;
		}
		return element;
	}
	throw "VQueue is empty! ";
}

#endif /* VQUEUE_HPP_ */
