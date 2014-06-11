/*
 * Sciezka.hpp
 *
 *  Created on: 24 May 2014
 *      Author: mochman
 */

#ifndef SCIEZKA_HPP_
#define SCIEZKA_HPP_

#include "Wspolrzedna.hpp"
#include <list>
#include <initializer_list>
#include <iostream>


/*!
 * \brief Klasa reprezentująca kilka ruchów figury w grze warcaby
 */
class Sciezka
{
  public:
    /*!
     * \brief Domyślny konstruktor klasy Scieżka
     *
     * Tworzy pustą ścieżkę
     */
    Sciezka()=default;

    /*!
     * \brief Konstruktor pozwalający na utworzenie obiektu na postawie listy inicjalizacyjnej
     *
     * \param listaInicjujaca - lista inicjalizacyjna obiekt
     */
    Sciezka(const std::initializer_list<Wspolrzedna>& listaInicjujaca):m_listaPol(listaInicjujaca) {}

    /*!
     * \brief Pozwala pobrac ile ruchów musi wykonać figura w danej ścieżce
     */
    unsigned int iloscRuchow() const { return m_listaPol.size()-1; }

    /*!
     * \brief Pozwala pobrać ile pól odiwedz figura pokonując daną ścieżkę
     */
    unsigned int iloscPol() const {return m_listaPol.size(); }

    /*!
     * \brief Pozwala pobrać listę pól ścieżki
     */
    const std::list<Wspolrzedna>& listaPol() const {return m_listaPol; }

    /*!
     * \brief Pozwala dodać na koniec ścieżki dodatkowe pole do odwiedzenia
     *
     * \param wspolrzedna - dodatkowe pole do odwiedzenia
     */
    void dodaj(const Wspolrzedna& wspolrzedna) { m_listaPol.push_back(wspolrzedna); }

    /*!
     * \brief Pozwala usunąć ostatnie pole ze ścieżki
     */
    void usun() { m_listaPol.pop_back(); }

    /*!
     * \brief Pozwala dołączyć do jednej ścieżki drugą
     *
     * \param sciezka - dołączana ścieżka
     */
    bool dolaczSciezke(const Sciezka& sciezka);

    /*!
     * \brief Pozwala pobrać ostatnie pole ścieżki
     *
     * Jeśli ścieżka jest pusta zgłaszany jest wyjątek const char*
     */
    const Wspolrzedna& ostatniePole() const { if(m_listaPol.size()>0) return m_listaPol.back(); throw "Sciezka pusta"; }

    /*!
     * \brief Pozwala pobrać pierwsze pole ścieżki
     *
     * Jeśli ścieżka jest pusta zgłaszany jest wyjątek const char*
     */
    const Wspolrzedna& pierwszePole() const { if(m_listaPol.size()>0) return m_listaPol.front(); throw "Sciezka pusta"; }
  private:

    /*!
     * \brief Pole przechowujące pola ścieżki
     */
    std::list<Wspolrzedna> m_listaPol;
};

/*!
 * \brief Operator wyjścia
 *
 * Pozwala na wypisanie ścieżki
 *
 * \param os - strumień wyjściowy
 * \param sciezka - ścieżka, która ma zostać wypisana
 */
std::ostream& operator<<(std::ostream& os, const Sciezka& sciezka);
#endif /* SCIEZKA_HPP_ */
