#ifndef VSTACK_HPP
#define VSTACK_HPP

#include "Vector.hpp"

/*!
 * \brief Klasa reprezentująca stos zaimplementany na podstawie tablicy.
 */
template<typename Type>
class VStack
{
	public:
		/*!
		 * \brief Typ określający sposób alokacji pamięci
		 */
		enum class AllocType
		{
			INCREMENT, DOUBLE_QUARTER
		};

		/*!
		 * \brief Konstruktor inicjujący stos.
		 *
		 * Domyślnym typem alokacji jest podwajanie.
		 */
		VStack(AllocType allocType = AllocType::DOUBLE_QUARTER)
				: m_allocType(allocType)
		{
		}

		/*!
		 * \brief Sprawdza czy stos jest pusty.
		 */
		bool isEmpty() const
		{
			return size() == 0;
		}

		/*!
		 * \brief Pozwala pobrać rozmiar stosu
		 */
		unsigned int size()
		{
			return m_vec.size();
		}

		/*!
		 * \brief Pozwala wrzucić na stos element
		 *
		 * \param element - element, który ma zostac wrzucony na stos
		 */
		void push(const Type& element);

		/*!
		 * \brief Ściąga/zwraca ze stosu element
		 *
		 * Jeśli stos jest pusty zgłaszany jest wyjątek.
		 */
		Type pop();

		/*!
		 * \brief Pozwala określic rodzaj alokacji pamięci
		 */
		AllocType allocType() const
		{
			return m_allocType;
		}

		/*!
		 * \brief Pozwala ustawić rodzaj alokacji pamięci
		 *
		 * \param allocType - nowy rodzaj alokacji pamięci
		 */
		void alloctype(AllocType allocType)
		{
			m_allocType = allocType;
		}
	private:

		/*!
		 * \brief Tablica przechowujący dane stosu.
		 */
		Vector<Type> m_vec;

		/*!
		 * \brief Pole określające sposób alokacji pamięci
		 */
		AllocType m_allocType;

		/*!
		 * \brief Wrzuca na stos, wykorzystując strategię podwajania
		 */
		void pushAllocDouble(const Type& element);

		/*!
		 * \brief Ściąga ze stosu wykorzystując strategię podwajania(1/4 rozmiaru)
		 */
		Type popAllocQuarter();

		/*!
		 * \brief Ściąga ze stosu wykorzystując strategię inkrementacji
		 */
		Type popAllocOne();
};

template<typename Type>
void VStack<Type>::push(const Type& element)
{
	switch (m_allocType)
	{
		case AllocType::DOUBLE_QUARTER:
			pushAllocDouble(element);
			break;
		case AllocType::INCREMENT:
			m_vec.push_back(element);
			break;
	}
}

template<typename Type>
void VStack<Type>::pushAllocDouble(const Type& element)
{
	if(size()) //>0
	{
		if(size() == m_vec.allocatedSize())
			m_vec.reserve(2 * (size() + 1));
		m_vec.push_back(element);
	}
	else
		m_vec.push_back(element);
}

template<typename Type>
Type VStack<Type>::pop()
{
	switch (m_allocType)
	{
		case AllocType::INCREMENT:
			return m_vec.pop_back(true);
		case AllocType::DOUBLE_QUARTER:
			return popAllocQuarter();

	}
}

template<typename Type>
Type VStack<Type>::popAllocQuarter()
{
	if(m_vec.allocatedSize() / 4 == size())
	{
		m_vec.reserve(2 * size());
		Type front = m_vec.pop_back();
		return front;
	}
	else
		m_vec.pop_back();
}

#endif
