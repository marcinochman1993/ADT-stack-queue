#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <iostream>

/*! \brief Abstrakcyjna klasa reprezentująca problem algorytmiczny
 *
 * Definiuje interfejs podstawowych operacji dla problemu tzn. wczytanie danych,
 * przeprowadzenie obliczeń, sprawdzenie poprawności algorytmu
 */
class Problem
{
	public:

		/*!
		 * \brief Wczytuje dane wejściowe algorytmu.
		 *
		 * \param is - strumień z którego mają zostać wczytane dane
		 */
		virtual void readInData(std::istream& is = std::cin) = 0;

		/*!
		 * \brief Wczytuje poprawne dane wyjściowe algorytmu.
		 *
		 * \param is - strumień z którego mają zostać wczytane dane
		 */
		virtual void readOutData(std::istream& is = std::cin) = 0;

		/*!
		 * \brief Sprawdza czy wynik algorytmu jest poprawny
		 *
		 * Dokonuje porównania wczytanych poprawnych danych z
		 * wynikiem algorytmu
		 */
		virtual bool isCorrect() const = 0;

		/*! \brief Rozpoczyna pracę algorytmu.
		 *
		 */
		virtual void compute() = 0;

		/*! \brief Pozwala pobrać rozmiar problemu
		 */
		virtual unsigned int problemSize() const = 0;

		/*! \brief Pozwala ustawić rozmiar problemu
		 */
		virtual void problemSize(unsigned int size) = 0;

		/*! \brief Usuwa wszystkie dane
		 *
		 * Pozbywa się z pamięci wszyskich danych wejsciowych,
		 * poprawnych wyjsciowych itp
		 */
		virtual void clearData() = 0;
		virtual ~Problem() = default;
};

#endif

