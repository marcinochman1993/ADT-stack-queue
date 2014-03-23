#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <vector>
#include <iostream>
#include "Timer.hpp"

/*! \brief Struktura przechowująca informacje o pojedynczym teście wydajności
 *
 */
struct BenchmarkData
{
		/*! \brief Pole zawierające rozmiar problemu
		 *
		 * Z reguły jest to ilość danych wejściowych
		 * np. ilość liczb do posortowania
		 */
		unsigned int problemSize;

		/*! \brief Pole przechowujące numer porządkowy testu.
		 *
		 *  Jest to liczba określająca, który raz jest testowany algorytm
		 *  z takim samym rozmiarem problemu
		 */
		unsigned int number;

		/*! \brief Pole przechowujące czas wykonania algorytmu
		 *
		 *  Jednostką interwału jest mikrosekunda
		 */
		double usInterval;

		/*! \brief Pole przechowujące liczbę określającą ilość powtórzeń.
		 *
		 * Ilość powtórzeń jest rozumiana jako ilość wykonań algorytmu dla
		 * tego samego rozmiaru danych
		 *
		 */
};

/*! \brief Pozwala wyświetlić zawartość struktury.
 *
 *  Format jest następujący: rozmiar problemu,numer porządkowy,czas wykonania
 */
std::ostream& operator<<(std::ostream& os, BenchmarkData& benchData);

/*! \brief Klasa pozwalająca na testowanie algorytmów.
 *
 *  ProblemType musi udostępniać określony interfejs tzn. musi implementować
 *  następujące metody:
 *  void readInData(std::istream& is = std::cin)
 *  void readOutData(std::istream& is = std::cin)
 *  bool isCorrect() const
 *  void compute()
 *  void clearData()
 *
 *  Zalecane jest, aby dziedziczył on po klasie Problem
 */
template<typename ProblemType>
class Benchmark
{
	public:
		/*! \brief Konstruktor pozwalający na wybór ilości powtórzeń algorytmu dla danego rozmiaru problemu
		 *
		 */
		Benchmark(int repeatNum = 10)
				: m_repeatNum(repeatNum)
		{
		}

		/*! \brief Rozpoczyna testowanie algorytmu.
		 *
		 * Metoda wczytuje dane wejściowe dla algorytmu,
		 * nastęnie poprawne dane wyjściowe.
		 * Wykonuje algorytm oraz sprawdza dane.
		 * Jeśli jest rozbieżność pomiędzy danymi wynikowymi
		 * zgłaszany jest wyjątek "Algorytm jest niepoprawny".
		 */
		void start(std::istream& isInputData = std::cin,
				std::istream& isCorrectOutData = std::cin);

		/*!
		 * \brief Metoda pozwala zapisać wyniki testów wydajnościowych do strumienia.
		 *
		 * Format jest zgodny z CSV.
		 *
		 * \param os - strumień wyjściowy, do którego mają zostać przekierowane wyniki
		 */
		bool saveAsCSV(std::ostream& os = std::cout);
	private:

		/*! \brief Przechowuje obiekt, odpowiedzialny za algorytm
		 *
		 * Musi implementować metody, które zostały wspomniane w opisie klasy
		 */
		ProblemType m_problem;

		/*! \brief Wektor przechowujący informacje o przeprowadzonych testach
		 *
		 */
		std::vector<BenchmarkData> m_allBenchmarks;

		unsigned int m_repeatNum;
};

std::ostream& operator<<(std::ostream& os, BenchmarkData& benchData)
{
	os << benchData.problemSize << ',' << benchData.number << ','
			<< benchData.usInterval;
	return os;
}

template<typename ProblemType>
void Benchmark<ProblemType>::start(std::istream& isInputData,
		std::istream& isCorrectOutData)
{
	isInputData >> m_repeatNum;
	if(!isInputData)
		throw "Blad wczytywania wartosci powtorzen";
	while (isInputData.good() && isCorrectOutData.good())
	{
		unsigned int problemSize;
		isInputData >> problemSize;
		if(!isInputData)
			throw "Blad wczytywania rozmiaru problemu";
		m_problem.problemSize(problemSize);
		Timer t;
		for (unsigned i = 1; i <= m_repeatNum; i++)
		{
			m_problem.clearData();
			m_problem.readInData(isInputData);
			t.start();
			m_problem.compute();
			t.stop();
			m_problem.readOutData(isCorrectOutData);
			if(!m_problem.isCorrect())
				throw "Algorytm jest niepoprawny";
			BenchmarkData benchData = { m_problem.problemSize(), i, t.usInterval() };
			m_allBenchmarks.push_back(benchData);
		}
	}
}

template<typename ProblemType>
bool Benchmark<ProblemType>::saveAsCSV(std::ostream& os)
{
	os << "Rozmiar,Nr,Czas_us\n";
	for (auto it = m_allBenchmarks.begin(); it != m_allBenchmarks.end(); it++)
	{
		if(!os)
			return false;
		os << *it << std::endl;
	}
	return true;
}

#endif
