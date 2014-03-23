/*
 * SortingAlgorithms.hpp
 *
 *  Created on: Mar 19, 2014
 *      Author: mochman
 */

#ifndef SORTINGALGORITHMS_HPP_
#define SORTINGALGORITHMS_HPP_

#include "Vector.hpp"

/*!
 * \brief Jest to funkcja pomocnicza dla quickSort.
 *
 * Dzieli odpowiednio tablicę na część elementów mniejszych od piwotu
 * oraz część elementów większych od piwotu
 *
 * \param begin o dostępie swobodnym na pierwszy element tablicy
 * \param end o dostępie swobodnym na pierwszy element za ostatnim elementem tablicy
 */
template <typename Iterator>
Iterator partition(Iterator begin, Iterator end)
{
	Iterator i=begin-1;
	for(Iterator j=begin;j<end-1;j++)
	{
		if(*j<=*(end-1))
		{
			i++;
			std::swap(*i,*j);
		}
	}
	std::swap(*(i+1),*(end-1));
	return i+1;
}


/*!
 * \brief Przeprowadza sortowanie przy pomocy algorytmu quickSort
 *
 * Elementy są sortowane w tablicy [begin,end)
 *
 * \param begin - iterator o dostępie swobodnym  do pierwszego elementu
 * \param end - iterator o dostępie swobodnym do pierwszego elementu za ostatnim elementem tablicy
 */
template <typename Iterator>
void quickSort(Iterator begin, Iterator end)
{
	if(begin<end-1)
	{
		Iterator q=partition(begin,end);
		quickSort(begin,q);
		quickSort(q,end);
	}
}


/*!
 * \brief Funkcja pomocnicza dla mergeSort
 *
 * Scala posortowane tablice, łącząc je w całość tak, że
 * cała tablica będzie posortowana
 *
 * \param begin - iterator na początek pierwszej tablicy
 * \param mid - iterator na środkowy element tablicy
 * \param end - iterator na pierwszy element za ostatnim elementem tablicy
 */
template <typename Iterator>
void merge(Iterator begin, Iterator mid, Iterator end)
{
	Vector<typename Iterator::value_type> left(begin,mid);
	Vector<typename Iterator::value_type> right(mid,end);
	auto l=left.begin(),r=right.begin();
	while(l!=left.end() || r!=right.end())
	{
		if(l==left.end())
		{
			*begin=*r;
			r++;
		}
		else
			if(r==right.end())
			{
				*begin=*l;
				l++;
			}
			else
				if(*l<*r)
				{
					*begin=*l;
					l++;
				}
				else
				{
					*begin=*r;
					r++;
				}
		begin++;
	}
}


/*!
 * \brief Przeprowadza sortowanie przez scalania
 *
 * Elementy są sortowane w tablicy [begin,end)
 *
 * \param begin - iterator o dostępie swobodnym  do pierwszego elementu
 * \param end - iterator o dostępie swobodnym  do pierwszego elementu za ostatnim elementem tablicy
 */
template <typename Iterator>
void mergeSort(Iterator begin, Iterator end)
{
	if(begin<end-1)
	{
		auto mid=begin+std::distance(begin,end)/2;
		mergeSort(begin,mid);
		mergeSort(mid,end);
		merge(begin,mid,end);
	}
}


/*!
 * \brief Funkcja pomocnicza dla buildMaxHeap
 *
 * Zmienia elementy w tablicy tak, że poddrzewo będzie spełniać
 * warunki kopca typu max
 *
 * \param begin - iterator na początek tablicy
 * \param i - iterator na korzeń poddrzewa
 * \param end - iterator na pierwszy element za tablicą
 */
template <typename Iterator>
void maxHeapify(Iterator begin, Iterator i, Iterator end)
{
	unsigned long index=std::distance(begin,i+1);
	Iterator  left=begin+2*(index-1)+1,right=left+1,largest;
	if(left<end)
	{
		if(*left>*i)
			largest=left;
		else
			largest=i;
	}
	else
		largest=i;
	if(right<end)
	{
		if(*right>*largest)
			largest=right;
	}
	if(largest!=i)
	{
		std::swap(*i,*largest);
		maxHeapify(begin,largest,end);
	}
}


/*!
 * \brief Funkcja pomocnicza dla heapSort
 *
 * Przeprowadza operacje budowania kopca na tablicy
 *
 * \param begin - iterator na początek tablicy
 * \param end - iterator na pierwszy element za tablicą
 */
template <typename Iterator>
void buildMaxHeap(Iterator begin, Iterator end)
{
	for(auto it=begin+std::distance(begin,end)/2;it!=begin-1;it--)
		maxHeapify(begin,it,end);
}
/*!
 * \brief Przeprowadza sortowanie przez kopcowanie
 *
 * Elementy są sortowane w tablicy [begin,end)
 *
 * \param begin - iterator o dostępie swobodnym do pierwszego elementu
 * \param end - iterator o dostępie swobodnym  do pierwszego elementu za ostatnim elementem struktury danych
 */
template <typename Iterator>
void heapSort(Iterator begin, Iterator end)
{
	buildMaxHeap(begin,end);
	for(auto it=end-1;it!=begin;it--)
	{
		std::swap(*begin,*it);
		maxHeapify(begin,begin,--end);
	}
}

#endif /* SORTINGALGORITHMS_HPP_ */
