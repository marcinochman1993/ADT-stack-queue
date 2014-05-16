/*
 * ObjectiveFunction.hpp
 *
 *  Created on: May 7, 2014
 *      Author: mochman
 */

#ifndef OBJECTIVEFUNCTION_HPP_
#define OBJECTIVEFUNCTION_HPP_

#include <vector>
#include <initializer_list>
#include "FunctionArguments.hpp"


/*!
 * \brief Klasa reprezeentująca funkcję celu
 *
 * Postać tej funkcji to f(x)=a0*x0+a1*x1+...
 */
template<typename ArgType = double, typename RetType = double,
		typename CoeffType = double>
class ObjectiveFunction
{
	public:

		/*!
		 * \brief Domyślny konstruktor klasy ObjectiveFunction
		 *
		 * Funkcja ma rozmiar 0, nie ma żadnych zmiennych
		 */
		ObjectiveFunction() = default;

		/*!
		 * \brief Na podstawie list inicjalizacyjnych jest tworzona funkcja
		 *
		 * W liście inicjalizacyjnej znajdują się odpowiednie współczynniki,
		 * kolejno a0,a1,...
		 */
		ObjectiveFunction(const std::initializer_list<ArgType>& coeffs):m_coeffs(coeffs) {}

		/*!
		 * \brief Konstruktor, który pozwala skonstruować funkcję na podstawie iteratorów
		 *
		 * Każdy iterator to współczynniki, kolejno a0,a1...
		 *
		 * \param coeffBegin - początkowy iterator na współczynniki funkcji
		 * \param coeffEnd - końcowy iterator na współczynniki funkcji
		 */
		template<typename Iterator>
		ObjectiveFunction(Iterator coeffBegin, Iterator coeffEnd);

		/*!
		 * \brief Pozwala obliczyć wartość funkcji dla podanych argumentów
		 *
		 * Ilość zmiennych musi być równa ilości przyjmowanych zmiennych
		 * przez funkcję, inaczej zgłaszany jest wyjątek const char*
		 *
		 * \param args - argumenty funkcji
		 *
		 */
		ArgType calculate(const FunctionArguments<ArgType>& args) const;

		/*!
		 * \brief Zwraca ilość argumentów przyjmowanych przez funkcję
		 */
		unsigned long size() const
		{
			return m_coeffs.size();
		}

		/*!
		 * \brief Pozwala ustawić ilość argumentów przyjmowanych przez funkcję
		 *
		 * \param newSize - nowa ilość argumentów przyjmowanych przez funkcję
		 */
		void size(unsigned long newSize);

		/*!
		 * \brief Pozwala pobrać współczynnik przy odpowiedniej zmiennej
		 *
		 * Zmienne są liczone od 0
		 *
		 * \param index - indeks zmiennej, przy którym stoi współczynnik
		 */
		const CoeffType& getCoeff(unsigned long index) const;

		/*!
		 * \brief Pozwala ustawić współczynnik przy odpowiedniej zmiennej
		 *
		 * Zmienne są liczone od 0
		 *
		 * \param index - indeks zmiennej, przy którym stoi współczynnik
		 * \param coeff - nowa wartość współczynnika
		 */
		void setCoeff(unsigned long index, const CoeffType& coeff) const;
	private:

		/*!
		 * \brief Tablica współczynników
		 */
		std::vector<CoeffType> m_coeffs;
};

template<typename ArgType, typename RetType, typename CoeffType>
template<typename Iterator>
ObjectiveFunction<ArgType, RetType, CoeffType>::ObjectiveFunction(
		Iterator coeffBegin, Iterator coeffEnd)
{
	m_coeffs.resize(std::distance(coeffBegin, coeffEnd));
	std::copy(coeffBegin, coeffEnd, m_coeffs.begin());
}

template<typename ArgType, typename RetType, typename CoeffType>
ArgType ObjectiveFunction<ArgType, RetType, CoeffType>::calculate(
		const FunctionArguments<ArgType>& args) const
{
	if(args.size() != size())
		throw "Args num and coeff num are not equal";
	RetType retValue = 0;
	for (unsigned long index = 0; index < size(); index++)
		retValue += args[index] * getCoeff(index);
	return retValue;
}

template<typename ArgType, typename RetType, typename CoeffType>
const CoeffType& ObjectiveFunction<ArgType, RetType, CoeffType>::getCoeff(
		unsigned long index) const
{
	if(index < size())
		return m_coeffs[index];
	throw "Index out of bounds";
}

template<typename ArgType, typename RetType, typename CoeffType>
void ObjectiveFunction<ArgType, RetType, CoeffType>::setCoeff(
		unsigned long index, const CoeffType& coeff) const
{
	if(index<size())
		m_coeffs[index]=coeff;
	else
		throw "Index out of bounds";
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const ObjectiveFunction<T>& function)
{
	if(function.size() > 0)
	{
		os<<"f(";
		for (unsigned long i = 0; i < function.size() - 1; i++)
			os<<"x"<<i<<", ";
		os<<"x"<<function.size()-1<<")=";
		for (unsigned long i = 0; i < function.size() - 1; i++)
			if(function.getCoeff(i+1)>=0)
				os << function.getCoeff(i) << "*x" << i << '+';
			else
				os << function.getCoeff(i) << "*x" << i;
		os << function.getCoeff(function.size() - 1) << "*x"
				<< function.size() - 1;
	}
	return os;
}
#endif /* OBJECTIVEFUNCTION_HPP_ */
