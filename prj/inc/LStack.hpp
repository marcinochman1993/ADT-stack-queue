#ifndef LSTACK_HPP
#define LSTACK_HPP

#include <list>

/*!
 * \brief Klasa reprezentująca stos zaimplementowany na podstawie listy
 */
template<typename Type>
class LStack
{
	public:

		/*!
		 * \brief Sprawdza czy stos jest pusty.
		 */
		bool isEmpty() const
		{
			return m_list.empty();
		}

		/*!
		 * \brief Pozwala pobrać rozmiar stosu.
		 */
		unsigned int size() const
		{
			return m_list.size();
		}

		/*!
		 * \brief Odkłada na stos element.
		 */
		void push(const Type& element)
		{
			m_list.push_front(element);
		}

		/*!
		 * \brief Sciąga ze stosu element zwracając go.
		 *
		 */
		Type pop();
	private:
		/*!
		 * \brief Lista przechowująca dane.
		 */
		std::list<Type> m_list;
};

template<typename Type>
Type LStack<Type>::pop()
{
	if(isEmpty())
		throw "Stack is empty";

	Type front = m_list.front();
	m_list.pop_front();
	return front;
}

#endif
