/*
 * Pole.hpp
 *
 *  Created on: May 19, 2014
 *      Author: mochman
 */

#ifndef POLE_HPP_
#define POLE_HPP_

#include <iostream>

/*!
 * \brief Klasa reprezentuje pole planszy do gry w warcaby
 */
class Pole
{
  public:
    /*!
     * \brief Typ wyliczeniowy określający stan pola
     */
    enum class STAN_POLA
    {
      BIALY_PIONEK, CZARNY_PIONEK, PUSTE, BIALA_MATKA, CZARNA_MATKA
    };

    /*!
     * \brief Konstruktor klasy Pole
     *
     * \param stan - stan pola, który ma zostać ustawiony
     */
    Pole(STAN_POLA stan=STAN_POLA::PUSTE):m_stan(stan) {}

    /*!
     * \brief Sprawdza czy pole jest puste
     */
    bool czyPuste() const { return m_stan == STAN_POLA::PUSTE; }

    /*!
     * \brief Sprawdza czy pole jest zajęte
     */
    bool czyZajete() const { return !czyPuste(); }

    /*!
     * \brief Sprawdza czy pole jest zajęte przez białe figury
     */
    bool czyBiale() const { return m_stan == STAN_POLA::BIALY_PIONEK
        || m_stan == STAN_POLA::BIALA_MATKA; }

    /*!
     * \brief Sprawdza czy pole jest zajęte przez czarne figury
     */
    bool czyCzarne() const { return m_stan == STAN_POLA::CZARNY_PIONEK
        || m_stan == STAN_POLA::CZARNA_MATKA; }

    /*!
     * \brief Sprawdza czy pole jest zajęte przez matkę
     */
    bool czyMatka() const { return m_stan == STAN_POLA::BIALA_MATKA
        || m_stan == STAN_POLA::CZARNA_MATKA; }

    /*!
     * \brief Sprawdza czy pole jest zajęte przez pionek
     */
    bool czyPionek() const { return m_stan == STAN_POLA::BIALY_PIONEK
        || m_stan == STAN_POLA::CZARNY_PIONEK; }

    /*!
     * \brief Pozwala pobrać stan pola
     */
    void stan(STAN_POLA nowyStan) { m_stan=nowyStan; }

    /*!
     * \brief Pozwala ustawić stan pola
     */
    const STAN_POLA& stan() const { return m_stan; }

    /*!
     * \brief Pozwala na zamianę pionka na matkę
     */
    void awansPionka();
  private:
    /*!
     * \brief Pole przechowujące stan pola
     */
    STAN_POLA m_stan;
};

/*!
 * \brief Operator wyjścia dla klasy Pole
 *
 * Pozwala wypisać do strumienia zawartość pola
 *
 * \param os - strumień, do którego zostaną przekazane dane
 * \param pole - pole, które ma zostać wypisane
 */
std::ostream& operator<<(std::ostream& os, const Pole& pole);

#endif /* POLE_HPP_ */
