/*
 * Constraint.hpp
 *
 *  Created on: 15 May 2014
 *      Author: mochman
 */

#ifndef CONSTRAINT_HPP_
#define CONSTRAINT_HPP_

#include <vector>
#include <iostream>

/*!
 * \brief Klasa reprezentuje ograniczenie dla programowania liniowego
 */
template<typename T>
class Constraint
{
	public:
		unsigned long size() const
		{
			return m_coeffs.size();
		}
		void size(unsigned long newSize)
		{
			m_coeffs.resize(newSize);
		}
		const T& getCoeff(unsigned long index) const;
		void setCoeff(unsigned long index, const T& newCoeff);
		const T& getB() const
		{
			return m_b;
		}
		void setB(const T& newB)
		{
			m_b = newB;
		}
	private:
		std::vector<T> m_coeffs;
		T m_b;
};

template<typename T>
const T& Constraint<T>::getCoeff(unsigned long index) const
{
	if(index < size())
		return m_coeffs[index];
	throw "Index out of bound";
}

template<typename T>
void Constraint<T>::setCoeff(unsigned long index, const T& newCoeff)
{
	if(index < size())
		m_coeffs[index] = newCoeff;
	else
		throw "Index out of bound";
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Constraint<T>& constraint)
{
	if(constraint.size() > 0)
	{
		for (unsigned long i = 0; i < constraint.size() - 1; i++)
			if(constraint.getCoeff(i+1)>=0)
				os << constraint.getCoeff(i) << "*x" << i << '+';
			else
				os << constraint.getCoeff(i) << "*x" << i;
		os << constraint.getCoeff(constraint.size() - 1) << "*x"
				<< constraint.size() - 1 << "<=" << constraint.getB();
	}
	return os;
}

#endif /* CONSTRAINT_HPP_ */
