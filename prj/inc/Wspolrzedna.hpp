#ifndef WSPOLRZEDNA_HPP
#define WSPOLRZEDNA_HPP

#include <map>
#include <iostream>

/*!
 * \brief Klasa reprezentująca współrzędna na planszy do gry w warcaby
 */
class Wspolrzedna
{
  public:
    /*!
     * \brief Konstruktor klasy wspołrzędna
     *
     * Pozwala ustawić wiersz oraz kolumnę współrzędnej
     *
     * \param wier - wiersz współrzędnej, który ma zostac ustawiony
     * \param kol - kolumna współrzędnej, która ma zostać ustawiona
     *
     */
    Wspolrzedna(char wier='a', unsigned int kol=1):
      m_kolumna(kol)
  { wiersz(wier); }

    /*!
     * \brief Pozwala ustawić wiersz współrzędnej
     *
     * \param nowyWiersz - wiersz, który ma zostać ustawiony
     */
    void wiersz(char nowyWiersz);

    /*!
     * \brief Pozwala ustawić kolumnę współrzędnej
     *
     * \param nowaKolumna - kolumna, ktora ma zostać ustawiona
     */
    void kolumna(unsigned int nowaKolumna) { m_kolumna=nowaKolumna; }

    /*!
     * \brief Pozwala pobrać wiersz współrzędnej w postaci litery
     */
    char wiersz () const { return m_wiersz; }

    /*!
     * \brief Pozwala pobrać kolumnę współrzędnej
     */
    unsigned int kolumna () const { return m_kolumna; }

    /*!
     * \brief Pozwala pobrac wiersz współrzędnej w postaci liczby
     *
     * Kolejne litery alfabetu są reprezentowane przez kolejne liczby 1,2,3...
     */
    unsigned int wierszLiczba () const;

    /*!
     * \brief Pozwala ustawić wiersz wspołrzędnej na podstawie liczby
     */
    void wierszLiczba(unsigned int wier);

    /*!
     * \brief Operator równości
     *
     * Sprawdza czy wiersz oraz kolumna są takie same
     */
    bool operator==(const Wspolrzedna& wsp) const { return m_wiersz==wsp.wiersz() && m_kolumna==wsp.kolumna(); }

    /*!
     * \brief Operator różności
     *
     * Sprawdza czy wiersz lub kolumna są różne od siebie
     */
    bool operator!=(const Wspolrzedna& wsp) const { return !(*this==wsp); }

    /*!
     * \brief Operator mniejszości
     *
     * Sprawdza czy wiersz jest mniejszy, jeśli jest równy to porównuje kolumnę
     */
    bool operator<(const Wspolrzedna& wsp) const { return wierszLiczba()<wsp.wierszLiczba() ||
        (!(wierszLiczba()<wsp.wierszLiczba()) && wsp.kolumna()<wsp.kolumna()); }

    /*!
     * \brief Operator większości
     *
     * Sprawdza czy wiersz jest większy, jeśli jest równy to porównuje kolumnę
     */
    bool operator>(const Wspolrzedna& wsp) const { return wierszLiczba()>wsp.wierszLiczba() ||
        (!(wierszLiczba()>wsp.wierszLiczba()) && wsp.kolumna()>wsp.kolumna()); }
  private:

    /*!
     * \brief Pole przechowujące wiersz
     */
    char m_wiersz;

    /*!
     * \brief Pole przechowujące kolumnę
     */
    unsigned int m_kolumna;

    /*!
     * \brief Zmienna statyczna służąca do konwersji wiersza z litery na liczbę
     */
    static std::map<char,unsigned int> s_zamianaCharUint;

    /*!
     * \brief Zmienna statyczna, tablica asocjacyjna, służaca do konwersji wiersza z liczby na literę
     */
    static std::map<unsigned int,char> s_zamianaUintChar;
};

std::ostream& operator<<(std::ostream& os,const Wspolrzedna& wsp);
#endif // WSPOLRZEDNA_HPP
