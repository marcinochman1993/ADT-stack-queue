#ifndef MATRIX_CPP
#define MATRIX_CPP
#include "Vector.hpp"
#include <vector>
#include <algorithm>

/*!
 * \file
 * \brief Plik zawiera deklarację klasy Matrix.
 */
template<typename T>
class Matrix;

template<typename T>
std::istream& operator>>(std::istream& inStrm, Matrix<T>& matrix);

template<typename T>
std::ostream& operator<<(std::ostream& outStrm, const Matrix<T>& matrix);
/*!
 * \brief Klasa modeluje pojęcie macierzy.
 * 
 * Klasa Matrix reprezentuje macierz elementów typu zależnego od T.
 */
template<typename T>
class Matrix
{
	private:

		/*!
		 * \brief Przechowuje ilość wierszy.
		 */
		unsigned int rows;

		/*!
		 * \brief Przechowuje ilość kolumn.
		 */
		unsigned int columns;

		/*!
		 * \brief Przechowuje wskaźnik na elementy macierzy.
		 */
		T* tab;

		/*!
		 \brief Pomocnicza metoda, która kopiuje zawartość jednej tablicy do drugiej.
		 *
		 * Metoda kopiuje zawartość tablic.
		 *
		 * \param[in] tab1 - tablica, z której będą kopiowane dane.
		 * \param[out] tab2 - tablica do której będą kopiowane dane.
		 */
		void copy(const T* tab1, T* tab2);

	public:

		/*!
		 * \brief Metoda pozwalająca dodawać wielokrotnośc wiersza do drugiego.
		 *
		 * Metoda pozwala dodawać pomnożony wiersz przez stałą do drugiego wiersza -
		 * operacja typowa dla eliminacji Gaussa.
		 *
		 * \param[in] mult - współczynik, przez który mnożony jest dodawany wiersz
		 * \param[in] w1Index - indeks wiersza, który będzie dodawany - przemnożony
		 *                      przez stałą
		 * \param[in] w2Index - indeks wiersza, do któreg będzie dodawany drugi wiersz
		 */
		void addRow(T mult, unsigned int w1Index, unsigned int w2Index);

		/*!
		 * \brief Metoda, która zamienia ze sobą dwa wiersze.
		 *
		 * Metoda pozwala na zamianę dwóch wierszy ze sobą - operacja typowa
		 * dla eliminacji Gaussa.
		 *
		 * \param[in] w1Index - indeks pierwszego wiersza
		 * \param[in] w2Index - indeks drugiego wiersza
		 */
		void changeRows(unsigned int w1Index, unsigned int w2Index);

		/*!
		 * \brief Metoda mnoży wiersz przez stała.
		 *
		 * Metoda pozwala pomnożyć wiersz przez stałą - operacja typowa
		 * dla eliminacji Gaussa.
		 *
		 * \param[in] mult - współczynnik, przez który zostanie pomnożony wiersz
		 * \param[in] rowIndex - indeks wiersza
		 */
		void multiplyRow(T mult, unsigned int rowIndex);

		/*!
		 * \brief Domyślny konstruktor klasy \link Matrix \endlink
		 *
		 * Konstruktor domyślny tworzy macierz pustą.
		 */
		Matrix();

		/*!
		 * \brief Konstruktor kopiujący dla klasy Matrix.
		 *
		 * Konstruktor pozwala na stworzenie macierzy na podstawie istniejącej.
		 */
		Matrix(const Matrix<T>& matrix);

		/*!
		 * \brief Konstruktor pozwalający podać rozmiar macierzy.
		 *
		 * Konstruktor pozwala na utworzenie macierzy o dowolnym rozmiarze.
		 */
		Matrix(unsigned int rowsNumber, unsigned int columnsNumber);

		/*!
		 * \brief Destruktor klasy Matrix.
		 *
		 * Destruktor zwalnia pamięć zajętą przez macierz.
		 */
		~Matrix();

		/*!
		 * \brief Metoda pobierająca ilość wierszy macierzy.
		 *
		 * Metoda pobiera ilość wierszy macierzy.
		 *
		 * \return Zwracana jest ilość wierszy w macierzy.
		 */
		unsigned int getRowsNumber() const;

		/*!
		 * \brief Metoda pobierająca ilość kolumn macierzy.
		 *
		 * Metoda pobiera ilość kolumn macierzy.
		 *
		 * \return Zwracana jest ilość kolumn w macierzy.
		 */
		unsigned int getColumnsNumber() const;

		/*!
		 * \brief Metoda przeciążająca operator (), który pozwala na
		 *        pobranie wartości elementu z odpowidniego
		 *        wiersza i kolumny.
		 *
		 * Pozwala na pobranie wartości elementu znajdującego się na
		 * odpowiedniej pozycji w macierzy. Metoda może zgłosić
		 * wyjątek typu \e const \e char* jeśli macierz nie będzie miała
		 * takiego indeksu.
		 *
		 * \param[in] rowIndex - numer wiersza(numeracja od 1).
		 * \param[in] columnIndex - numer kolumny(numeracja od 1).
		 *
		 * \return Zwraca wartość elementu na odpowiednim miejscu.
		 */
		T operator()(unsigned int rowIndex, unsigned int columnIndex) const
				throw (const char*);

		/*!
		 * \brief Metoda przeciążająca operator (), który pozwala na
		 *        pobranie wartości elementu z odpowidniego
		 *        wiersza i kolumny.
		 *
		 * Pozwala na pobranie wartości elementu znajdującego się na
		 * odpowiedniej pozycji w macierzy. Metoda może zgłosić
		 * wyjątek typu \e const \e char* jeśli macierz nie będzie miała
		 * takiego indeksu.
		 *
		 * \param[in] rowIndex - numer wiersza(numeracja od 1).
		 * \param[in] columnIndex - numer kolumny(numeracja od 1).
		 *
		 * \return Zwraca wartość elementu na odpowiednim miejscu.
		 */
		T& operator()(unsigned int rowIndex, unsigned int columnIndex)
				throw (const char*);

		/*!
		 * \brief Metoda oblicza macierz odwrotną do macierzy.
		 *
		 * Metoda na podstawie eliminacji Gaussa oblicza
		 * macierz odwrotną. Jeśli macierz nie jest kwadratowa,
		 * lub nie istnieje macierz odwrotna zgłaszany jest wyjątek
		 * typu \e const \e char*.
		 *
		 * \return Zwracana jest macierz odwrotna.
		 */
		Matrix<T> inverseMatrix() const throw (const char*);

		/*!
		 * \brief Metoda pozwala ustawić wartość elementu.
		 *
		 * Metoda pozwala przypisać wartość elementu o odpowiednim indeksie.
		 * Jeśli podany indeks nie istnieje żadne czynności nie są wykonywane.
		 *
		 * \param[in] element - wartość, na który ma zostać ustawiony
		 *                      odpowiedni element.
		 * \param[in] row - numer wiersza elementu.
		 * \param[in] column - numer kolumny elementu.
		 */
		void setElement(T element, unsigned int row, unsigned int column);

		/*!
		 * \brief Przeciążony operator mnożenia macierzy z wektorami.
		 *
		 * Pozwala na mnożenie macierzy z wektorem. Jeśli nie można przeprowadzić
		 * operacji mnożenia - nie zgadzają sie odpowiednie wymiary, to
		 * zgłaszany jest wyjątek typu \e const \e char*.
		 *
		 * \param[in] vector - wektor będący drugim czynnikiem iloczynu.
		 *
		 *  \return Zwracany jest wektor, który jest wynikiem iloczynu
		 *          macierzy i wektora.
		 */
		Vector<T> operator*(const Vector<T>& vector) const throw (const char*);

		/*!
		 * \brief Przeciążony operator mnożenia macierzy z macierzą.
		 *
		 * Pozwala na mnożenie dwóch macierzy. Jeśli nie można przeprowadzić
		 * operacji mnożenia - nie zgadzają się odpowiednie wymiary, to
		 * zgłaszany jest wyjątek typu \e const \e char*.
		 *
		 * \param[in] matrix - macierz będąca drugim czynnikiem iloczynu.
		 *
		 * \return Zwracana jest macierz, która jest wynikiem iloczynu macierzy.
		 */
		Matrix<T> operator*(const Matrix<T>& matrix) const throw (const char*);

		/*!
		 * \brief Operator przypisania dla klasy Matrix.
		 *
		 * Pozwala przypisać do siebie dwie macierze.
		 *
		 * \return Zwracana jest macierz do której nastąpiło przypisanie.
		 */
		Matrix<T>& operator=(const Matrix<T>& matrix);

		/*!
		 * \brief Przeciążony operator przesunięcia bitowego w lewo,
		 *        pozwalający wypisywać zawartość macierzy
		 *        do strumienia wyjściowego.
		 *
		 * Funkcja przeciążająca operator << wyświetla macierz na
		 * strumieniu wyjściowym. Na przykład dla liczb:
		 \verbatim
		 1 2 3
		 4 5 6
		 \endverbatim
		 * zostanie wyświetlona macierz:

		 \verbatim
		 |1 2 3|
		 |4 5 6|
		 \endverbatim

		 *
		 * \param matrix - macierz z której mają być wypisane dane.
		 * \param outStrm - strumień wejściowy.
		 *
		 * \return Zwracany jest strumień wyjściowy, który został pobrany
		 *         jako argument.
		 */
		friend std::ostream& operator<<<T>(std::ostream& outStrm,
				const Matrix<T>& matrix);

		/*!
		 * \brief Przeciążony operator przesunięcia bitowego w prawo,
		 *        pozwalający wczytywać zawartość macierzy
		 *        ze strumienia wejściowego.
		 *
		 * Funkcja przeciążająca operator >> wczytuję macierz
		 * ze strumienia wejściowego. Poprawny format to
		 * wiersze pod sobą, a każdy wiersz zaczyna się i kończy
		 * znakiem '|'. Na przykład poprawny zapisem jest:
		 \verbatim
		 |1 2 3|
		 |4 5 6|
		 |7 8 9|
		 \endverbatim
		 *
		 * \param inStrm - strumień wejściowy.
		 * \param matrix - macierz, do której mają być wczytane dane.
		 *
		 * \return Zwracany jest strumień wejściowy, który został
		 *         pobrany jako argument.
		 */
		friend std::istream& operator>><T>(std::istream& inStrm, Matrix<T>& matrix);

		/*!
		 * \brief Zlicza elementy z określonej podmacierzy, które spełniają odpowiedni warunek
		 *
		 * \param x1 - indeks górnego wiersza podmacierzy
		 * \param x2 - indeks dolnego wiersza podmacierz
		 * \param y1 - indeks górnej kolumny podmacierzy
		 * \param y2 - indeks dolnej kolumny podmacierzy
		 * \param function - funkcja testująca
		 */
		template<typename F>
		unsigned long countIfInRange(unsigned long x1, unsigned long y1,
				unsigned long x2, unsigned long y2, F function) const;

		/*!
		 * \brief Znajduje indeksy minimalnego elementu w podmacierzy
		 * \param x1 - indeks górnego wiersza podmacierzy
		 * \param x2 - indeks dolnego wiersza podmacierz
		 * \param y1 - indeks górnej kolumny podmacierzy
		 * \param y2 - indeks dolnej kolumny podmacierzy
		 * \param row [out] - indeks wiersza minimalnego elementu
		 * \param column [out] - indeks kolumny minimalnego elementu
		 */
		void findMinimumInRange(unsigned long x1, unsigned long y1,
				unsigned long x2, unsigned long y2, unsigned long& row,
				unsigned long& column) const;
};

/*!
 * \file
 * \brief Plik zawiera definicję klasy Matrix oraz funkcji z nią powiązanych.
 *
 * Plik definuje klasę Matrix oraz funkcję, które tworzą jej interfejs.
 */

template<typename T>
Matrix<T>::Matrix()
{
	tab = NULL;
	rows = 0;
	columns = 0;
}

template<typename T>
Matrix<T>::Matrix(unsigned int rowsNumber, unsigned int columnsNumber)
{

	rows = rowsNumber;
	columns = columnsNumber;
	tab = new T[rows * columns];
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix)
{
	tab = new T[matrix.columns * matrix.rows];
	columns = matrix.columns;
	rows = matrix.rows;
	copy(matrix.tab, tab);
}
template<typename T>
Matrix<T>::~Matrix()
{
	delete[] tab;
}

template<typename T>
std::ostream& operator<<(std::ostream& outStrm, const Matrix<T>& matrix)
{
	if(matrix.tab != NULL)
	{
		for (unsigned int r = 0; r < matrix.rows; r++)
		{
			outStrm << "| ";
			for (unsigned int c = 0; c < matrix.columns; c++)
				outStrm << matrix.tab[r * matrix.columns + c] << ' ';
			outStrm << '|' << std::endl;
		}
	}
	return outStrm;
}

template<typename T>
std::istream& operator>>(std::istream& inStrm, Matrix<T>& matrix)
{
	delete[] matrix.tab;
	char temp;
	inStrm >> temp;

	if(temp == '|')
	{
		matrix.rows = 1;
		do
		{
			T* tab2 = new T[matrix.rows * matrix.columns + 1];
			matrix.copy(matrix.tab, tab2);
			delete[] matrix.tab;
			matrix.tab = tab2;
			inStrm >> matrix.tab[matrix.rows * matrix.columns];
			matrix.columns++;
			if(!inStrm.fail())
			{
				inStrm >> temp;
				if(temp != '|' && !inStrm.eof())
					inStrm.unget();
			}
		} while (temp != '|' && !inStrm.fail() && !inStrm.eof());
		bool toRead = true;
		while (toRead && !inStrm.fail() && !inStrm.eof())
		{
			char temp2;
			temp = inStrm.get();
			if(!inStrm.eof())
			{
				temp2 = inStrm.get();
				if((temp == '\n' && temp2 == '\n'))
					toRead = false;
				else
				{
					if(!inStrm.eof())
					{

						inStrm.putback(temp2);
						inStrm.putback(temp);
						inStrm >> temp;
						if(temp == '|')
						{
							T* tab2 = new T[(matrix.rows + 1) * matrix.columns];
							matrix.copy(matrix.tab, tab2);
							delete[] matrix.tab;
							matrix.tab = tab2;
							matrix.rows++;
							for (unsigned int i = 0;
									i < matrix.columns && inStrm.good() && !inStrm.eof(); i++)
							{
								inStrm >> matrix.tab[(matrix.rows - 1) * matrix.columns + i];
							}
							inStrm >> temp;
							if(temp != '|')
								inStrm.setstate(std::ios::failbit);
						}
						else
							inStrm.setstate(std::ios::failbit);
					}
				}
			}
		}
	}
	else
		inStrm.setstate(std::ios::failbit);
	return inStrm;
}

template<typename T>
void Matrix<T>::copy(const T* tab1, T* tab2)
{
	for (unsigned int i = 0; i < rows * columns; i++)
		tab2[i] = tab1[i];
}

template<typename T>
T Matrix<T>::operator()(unsigned int rowIndex, unsigned int columnIndex) const
		throw (const char*)
{
	if(rowIndex <= rows && columnIndex <= columns)
		return tab[rowIndex * columns + columnIndex];
	else
		throw "Element na podanym indeksie nie istnieje!";
}

template<typename T>
T& Matrix<T>::operator()(unsigned int rowIndex, unsigned int columnIndex)
		throw (const char*)
{
	if(rowIndex <= rows && columnIndex <= columns)
		return tab[rowIndex * columns + columnIndex];
	else
		throw "Element na podanym indeksie nie istnieje!";
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix)
{
	if(this != &matrix)
	{
		delete[] tab;
		columns = matrix.columns;
		rows = matrix.rows;
		tab = new T[rows * columns];
		copy(matrix.tab, tab);
	}
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matrix) const
		throw (const char*)
{
	if(columns == matrix.rows)
	{
		Matrix<T> m(rows, matrix.columns);
		for (unsigned int i = 0; i < m.rows; i++)
			for (unsigned int j = 0; j < m.columns; j++)
			{
				T sum;
				zero(sum);
				for (unsigned int k = 0; k < columns; k++)
					sum = sum + tab[i * columns + k] * matrix.tab[k * matrix.columns + j];
				m.tab[i * m.columns + j] = sum;
			}
		return m;
	}
	else
		throw "Nie mozna pomnozyc macierzy, ktorych ilosc kolumn pierwszej jest rozna od liczby wierszy drugiej";
}

template<typename T>
Vector<T> Matrix<T>::operator*(const Vector<T>& vector) const
		throw (const char*)
{
	if(columns == vector.getSize())
	{
		Vector<T> v(rows);
		for (unsigned int i = 0; i < rows; i++)
		{
			T sum;
			zero(sum);
			for (unsigned int k = 0; k < columns; k++)
				sum = sum + tab[i * rows + k] * vector[k];
			v.setElement(sum, i);
		}
		return v;
	}
	else
		throw "Nie mozna pomnozyc macierzy z wektorem ktory ma rozmiar rozny od ilosci kolumn";
}

template<typename T>
unsigned int Matrix<T>::getRowsNumber() const
{
	return rows;
}

template<typename T>
unsigned int Matrix<T>::getColumnsNumber() const
{
	return columns;
}

template<typename T>
void Matrix<T>::setElement(T element, unsigned int row, unsigned int column)
{
	if(row < rows && column < columns)
		tab[row * columns + column] = element;
}

template<typename T>
Matrix<T> Matrix<T>::inverseMatrix() const throw (const char*)
{
	if(rows == columns)
	{
		Matrix<T> AI(rows, 2 * columns);
		for (unsigned int i = 1; i <= AI.getRowsNumber(); i++)
		{
			for (unsigned int j = 1; j <= columns; j++)
				AI.setElement((*this)(i, j), i, j);
			for (unsigned int j = columns + 1; j <= AI.getColumnsNumber(); j++)
			{
				if(i == (j - columns))
					AI.setElement(T(1), i, j);
				else
					AI.setElement(T(), i, j);
			}
		}
		for (unsigned int i = 1; i <= AI.rows; i++)
		{
			if(!isZero(AI(i, i)))
				AI.multiplyRow(T(1) / AI(i, i), i);
			else
			{
				for (unsigned int j = i + 1; j <= AI.rows && isZero(AI(i, i)); j++)
					if(!isZero(AI(j, i)))
						AI.changeRows(j, i);
				if(isZero(AI(i, i)))
					throw "Nie da sie obliczyc macierzy odwrotnej!";
				else
					AI.multiplyRow(T(1) / AI(i, i), i);
			}
			for (unsigned int n = i + 1; n <= AI.rows; n++)
				AI.addRow(-AI(n, i), i, n);
		}
		for (unsigned int i = AI.rows; i > 1; i--)
			for (unsigned int j = i - 1; j >= 1; j--)
				AI.addRow(-AI(j, i), i, j);
		Matrix<T> inv(rows, columns);
		for (unsigned int i = 1; i <= rows; i++)
			for (unsigned int j = 1; j <= columns; j++)
				inv.setElement(AI(i, j + columns), i, j);
		return inv;
	}
	else
		throw "Macierz odwrotna maja tylko macierze kwadratowe";
}

template<typename T>
void Matrix<T>::addRow(T mult, unsigned int w1Index, unsigned int w2Index)
{
	for (unsigned int j = 0; j < columns; j++)
		setElement((*this)(w2Index, j) + mult * (*this)(w1Index, j), w2Index, j);
}

template<typename T>
void Matrix<T>::changeRows(unsigned int w1Index, unsigned int w2Index)
{
	for (unsigned int j = 0; j < columns; j++)
	{
		T temp = (*this)(w1Index, j);
		setElement((*this)(w2Index, j), w1Index, j);
		setElement(temp, w2Index, j);
	}
}

template<typename T>
void Matrix<T>::multiplyRow(T mult, unsigned int rowIndex)
{
	for (unsigned int j = 0; j < columns; j++)
		setElement(mult * (*this)(rowIndex, j), rowIndex, j);
}

template<typename T>
template<typename F>
unsigned long Matrix<T>::countIfInRange(unsigned long x1, unsigned long y1,
		unsigned long x2, unsigned long y2, F function) const
{
	if(x1 > x2 || y1 > y2)
		throw "Not specified rect area";
	if(x1 >= getRowsNumber() || y1 >= getColumnsNumber() || x2 >= getRowsNumber()
			|| y2 >= getColumnsNumber())
		throw "Index out of bound";
	unsigned long counted = 0;
	for (unsigned long i = x1; i <= x2; i++)
		for (unsigned long j = y1; j <= y2; j++)
			if(function((*this)(i, j)))
				counted++;
	return counted;
}

template<typename T>
void Matrix<T>::findMinimumInRange(unsigned long x1, unsigned long y1,
		unsigned long x2, unsigned long y2, unsigned long& row,
		unsigned long& column) const
{
	if(x1 > x2 || y1 > y2)
			throw "Not specified rect area";
		if(x1 >= getRowsNumber() || y1 >= getColumnsNumber() || x2 >= getRowsNumber()
				|| y2 >= getColumnsNumber())
			throw "Index out of bound";
		row=x1;column=x2;
		for (unsigned long i = x1; i <= x2; i++)
				for (unsigned long j = y1; j <= y2; j++)
					if((*this)(row,column)>(*this)(i,j))
					{
						row=i;
						column=j;
					}
}

#endif
