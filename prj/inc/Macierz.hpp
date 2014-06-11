#ifndef MACIERZ_H
#define MACIERZ_H

#include <vector>
#include <iostream>


/*!
 * \brief Klasa definiująca macierz
 *
 * Może przechowywać dane różnego rodzaju.
 */
template<typename T>
class Macierz
{
  public:

    /*!
     * \brief Operator indeksowania dla macierzy
     *
     * Pozwala dostać się do elementu o podanych indeksach. Indeksy zaczynają się od zera.
     * Zwracana jest stała referencja do elementu
     *
     * \param x - wiersz, w którym znajduje się element
     * \param y - kolumna, w której znajduje się element
     *
     */
    const T& operator()(unsigned int x, unsigned int y) const;

    /*!
     * \brief Operator indeksowania dla macierzy
     *
     * Pozwala dostać się do elementu o podanych indeksach. Indeksy zaczynają się od zera.
     * Zwracana jest referencja do elementu, przez co można edytować element
     *
     * \param x - wiersz, w którym znajduje się element
     * \param y - kolumna, w której znajduje się element
     *
     */
    T& operator()(unsigned int x, unsigned int y);


    /*!
     * \brief Konstruktor klasy Macierz
     *
     * Tworzy macierz o podanej liczbie wierszy oraz kolumn
     *
     * \param wierszy - ilość wierszy
     * \param kolumn - ilość kolumn
     */
    Macierz(unsigned int wierszy = 1, unsigned int kolumn = 1)
    {
      zmienRozmiar(wierszy, kolumn);
    }

    /*!
     * \brief Pozwala zmienić rozmiary macierzy
     *
     * Zmienia rozmiar macierzy na podaną przez użytkownika wielkość
     *
     * \param wierszy - nowa ilość wierszy
     * \param kolumn - nowa ilość kolumn
     *
     */
    void zmienRozmiar(unsigned int wierszy, unsigned int kolumn);

    /*!
     * \brief Pozwala pobrać ilość wierszy macierzy
     *
     */
    unsigned int wierszy() const
    {
      return m_wierszy;
    }

    /*!
     * \brief Pozwala pobrać ilość kolumn macierzy
     *
     */
    unsigned int kolumn() const
    {
      return m_kolumn;
    }

  private:
    /*!
     * \brief Tablica przechowująca dane macierzy
     */
    std::vector<T> m_tab;

    /*!
     * \brief Zmienna przechowująca ilość wierszy macierzy
     */
    unsigned int m_wierszy;

    /*!
     * \brief Zmienna przechowująca ilość kolumn macierzy
     */
    unsigned int m_kolumn;
};

template<typename T>
void Macierz<T>::zmienRozmiar(unsigned int wierszy, unsigned int kolumn)
{
  m_wierszy = wierszy;
  m_kolumn = kolumn;
  m_tab.resize(wierszy * kolumn);
}

template<typename T>
const T& Macierz<T>::operator()(unsigned int x, unsigned int y) const
{
  if (x < wierszy() && y < kolumn())
    return m_tab[x * wierszy() + y];
  throw "Niepoprawne indeksy";
}

template<typename T>
T& Macierz<T>::operator()(unsigned int x, unsigned int y)
{
  if (x < wierszy() && y < kolumn())
    return m_tab[x * wierszy() + y];
  throw "Niepoprawne indeksy";
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Macierz<T>& macierz)
{
  for(unsigned int i=0;i<macierz.wierszy();i++)
    {
      os<<"| ";
      for(unsigned int j=0;j<macierz.kolumn();j++)
        os<<macierz(i,j)<<' ';
      if(i==macierz.wierszy()-1)
        os<<"|";
      else
        os<<"|\n";
    }
  return os;
}
#endif // MACIERZ_H
