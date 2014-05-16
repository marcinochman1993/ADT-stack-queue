/*
 * FunctionArguments.hpp
 *
 *  Created on: May 7, 2014
 *      Author: mochman
 */

#ifndef FUNCTIONARGUMENTS_HPP_
#define FUNCTIONARGUMENTS_HPP_

#include <vector>
#include <algorithm>
#include <initializer_list>
#include <iostream>

/*!
 * \brief Klasa reprezentująca argumenty funkcji
 */
template<typename T>
class FunctionArguments
{
	public:
		/*!
		 * \brief Domyślny konstruktor klasy FunctionArguments
		 *
		 * Ustawia ilość argumentów na 0
		 */
		FunctionArguments() = default;

		/*!
		 * \brief Pozwala ustawić argumenty na podstawie listy inicjalizacyjnej
		 *
		 * \param args - lista inicjalizacyjna
		 */
		FunctionArguments(const std::initializer_list<T>& args)
				: m_args(args)
		{
		}

		/*!
		 * \brief Konstruktor budujący argumenty funkcji na podstawie iteratorów
		 *
		 * \param begin - początkowy iterator na argument x0
		 * \param end - końcowy iterator
		 */
		template<typename Iterator>
		FunctionArguments(Iterator begin, Iterator end)
		{
			set(begin, end);
		}

		/*!
		 * \brief Pozwala pobrać argument o indeksie index
		 *
		 * \param index - indeks argumentu
		 */
		const T& getArg(unsigned long index) const;

		/*!
		 * \brief Pozwala ustawić argument o indeksie index
		 *
		 * \param index - indeks argumentu
		 * \param arg - nowa wartość argumentu
		 */
		void setArg(unsigned long index, const T& arg);

		/*!
		 * \brief Zwraca ilość argumentów
		 */
		unsigned long size() const
		{
			return m_args.size();
		}

		/*!
		 * brief Pozwala ustawić ilość argumentów
		 *
		 * \param newSize - nowa ilość argumentów
		 */
		void size(unsigned long newSize)
		{
			m_args.resize(newSize,0);
		}

		/*!
		 * \brief Metoda kopiująca argumenty funkcji na podstawie iteratorów
		 *
		 * \param begin - początkowy iterator na argument x0
		 * \param end - końcowy iterator
		 */
		template<typename Iterator>
		void set(Iterator begin, Iterator end);

		/*!
		 * \brief Przeciążony operator indeksu
		 *
		 * Pozwala pobrać argument o odpowiednim indeksie
		 *
		 * \param index - indeks argumentu
		 */
		const T& operator[](unsigned long index) const
		{
			return getArg(index);
		}

	private:

		/*!
		 * \brief Przechowuje wartości argumentów
		 */
		std::vector<T> m_args;
};

template<typename T>
const T& FunctionArguments<T>::getArg(unsigned long index) const
{
	if(index < size())
		return m_args[index];
	throw "Index out of bounds";
}

template<typename T>
void FunctionArguments<T>::setArg(unsigned long index, const T& arg)
{
	if(index < size())
		m_args[index] = arg;
	else
		throw "Index out of bounds";
}

template<typename T>
template<typename Iterator>
void FunctionArguments<T>::set(Iterator begin, Iterator end)
{
	m_args.resize(std::distance(begin, end));
	std::copy(begin, end, m_args.begin());
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const FunctionArguments<T> fArgs)
{
	if(fArgs.size() == 0)
		os << "()";
	else
	{
		os << '(';
		for (unsigned long i = 0; i < fArgs.size() - 1; i++)
			os << fArgs.getArg(i)<<", ";
		os<<fArgs.getArg(fArgs.size()-1)<<')';
	}
	return os;
}

#endif /* FUNCTIONARGUMENTS_HPP_ */
