/*
 * LQueue.hpp
 *
 *  Created on: Mar 12, 2014
 *      Author: mochman
 */

#ifndef LQUEUE_HPP_
#define LQUEUE_HPP_

#include <list>

/*!
 *  \brief Klasa reprezentuje kolejkę.
 *
 *  Jest zaimplementowana na podstawie listy
 */
template<typename Type>
class LQueue
{
	public:
		/*!
		 *  \brief Sprawdza czy kolejka jest pusta
		 */
		bool isEmpty() const
		{
			return m_list.empty();
		}

		/*!
		 * \brief Pobiera rozmiar kolejki.
		 */
		unsigned int size() const
		{
			return m_list.size();
		}

		/*!
		 * \brief Dodaj na koniec kolejki.
		 *
		 * \param element - element, który będzie dodany na koniec
		 */
		void enqueue(const Type& element);

		/*!
		 * \brief Pozwala usunąć/zwrócić pierwszego w kolejce.
		 *
		 */
		Type dequeue();
	private:
		/*!
		 * \brief Lista przechowująca dane.
		 */
		std::list<Type> m_list;
};

template<typename Type>
void LQueue<Type>::enqueue(const Type& element)
{
	m_list.push_front(element);
}

template<typename Type>
Type LQueue<Type>::dequeue()
{
	Type back = m_list.back();
	m_list.pop_back();
	return back;
}

#endif /* LQUEUE_HPP_ */
