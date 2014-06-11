/*
 * WarcabyGUI.hpp
 *
 *  Created on: May 26, 2014
 *      Author: mochman
 */

#ifndef WARCABYGUI_HPP_
#define WARCABYGUI_HPP_

#include <string>
#include "Warcaby.hpp"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"


class WarcabyGUI:public Warcaby
{
  public:
    /*!
     * \brief Konstruktor klasy WarcabyGUI
     *
     * Konstruuje obiekt
     *
     * \param wysokosc - wysokosc okna, jakie ma utworzyć obiekt
     */
    WarcabyGUI(unsigned int wysokosc=600);
    void uruchom();
    /*!
     * \brief Pozwala na pobranie szerokości utworzonego okna
     */
    unsigned int szerokoscOkna() const { return 1.25*m_wysokoscOkna; }

    /*!
     * \brief Pozwala na pobranie wysokości utworzonego okna
     */
    unsigned int wysokoscOkna() const { return m_wysokoscOkna; }

    /*!
     * \brief Pobiera ścieżkę do tekstury drewna
     */
    const std::string& sciezkaTeksturaDrewna() { return m_sciezkaTeksturaDrewna; }

    /*!
     * \brief Pozwala ustawić nową ścieżkę do tekstury drewna
     *
     * \param nowaSciezka - nowa ścieżka, która ma zostać ustawiona
     */
    void sciezkaTeksturaDrewna(const std::string& nowaSciezka) { m_sciezkaTeksturaDrewna=nowaSciezka; m_zainicjowano=false; }

    /*!
     * \brief Pobiera ścieżkę do obrazka pionka białego
     */
    const std::string& sciezkaPionekBialy() { return m_sciezkaPionekBialy; m_zainicjowano=false; }

    /*!
     * \brief Pozwala ustawić nową ścieżkę do obrazka białego pionka
     *
     * \param nowaSciezka - nowa ścieżka, która ma zostać ustawiona
     */
    void sciezkaPionekBialy(const std::string& nowaSciezka) { m_sciezkaPionekBialy=nowaSciezka; m_zainicjowano=false; }

    /*!
     * \brief Pobiera ścieżkę do obrazka białej matki
     */
    const std::string& sciezkaDamkaBiala() { return m_sciezkaDamkaBiala; }

    /*!
     * \brief Pozwala ustawić nową ścieżkę do obrazka białej matki
     *
     * \param nowaSciezka - nowa ścieżka, która ma zostać ustawiona
     */
    void sciezkaDamkaBiala(const std::string& nowaSciezka) { m_sciezkaDamkaBiala=nowaSciezka; m_zainicjowano=false; }

    /*!
     * \brief Pobiera ścieżkę do obrazka pionka czarnego
     */
    const std::string& sciezkaPionekCzarny() { return m_sciezkaPionekCzarny; }

    /*!
     * \brief Pozwala ustawić nową ścieżkę do obrazka czarnego pionka
     *
     * \param nowaSciezka - nowa ścieżka, która ma zostać ustawiona
     */
    void sciezkaPionekCzarny(const std::string& nowaSciezka) {m_sciezkaPionekCzarny=nowaSciezka; m_zainicjowano=false; }

    /*!
     * \brief Pobiera ścieżkę do obrazka matki czarnej
     */
    const std::string& sciezkaDamkaCzarna() { return m_sciezkaDamkaCzarna; }

    /*!
     * \brief Pozwala ustawić nową ścieżkę do obrazka czarnej damki
     *
     * \param nowaSciezka - nowa ścieżka, która ma zostać ustawiona
     */
    void sciezkaDamkaCzarna(const std::string& nowaSciezka) { m_sciezkaDamkaCzarna=nowaSciezka; m_zainicjowano=false; }

    /*!
     * \brief Pobiera ścieżkę do obrazka zaznaczenia aktywnego pola
     */
    const std::string& sciezkaZaznaczenie() { return m_sciezkaZaznaczenie; }

    /*!
     * \brief Pozwala ustawić nową ścieżkę do obrazka zaznaczenia
     *
     * \param nowaSciezka - nowa ścieżka, która ma zostać ustawiona
     */
    void sciezkaZaznaczenie(const std::string& nowaSciezka) { m_sciezkaZaznaczenie=nowaSciezka; m_zainicjowano=false; }

    /*!
     * \brief Pobiera ścieżkę do obrazka przełącznika opcji
     */
    const std::string& sciezkaPrzelacznik() { return m_sciezkaPrzelacznik; }

    /*!
     * \brief Pozwala ustawić nową ścieżkę do obrazka przełącznika
     *
     * \param nowaSciezka - nowa ścieżka, która ma zostać ustawiona
     */
    void sciezkaPrzelacznik(const std::string& nowaSciezka) { m_sciezkaPrzelacznik=nowaSciezka; m_zainicjowano=false; }

    /*!
     * \brief Pobiera ścieżkę do czcionki używanej w grze
     */
    const std::string& sciezkaCzcionka() { return m_sciezkaCzcionka; }

    /*!
     * \brief Pozwala ustawić nową ścieżkę do czcionki
     *
     * \param nowaSciezka - nowa ścieżka, która ma zostać ustawiona
     */
    void sciezkaCzcionka(const std::string& nowaSciezka) { m_sciezkaCzcionka=nowaSciezka; m_zainicjowano=false; }

    /*!
     * \brief Destruktor klasy
     *
     * Zwalnia zajęte zasoby
     */
    ~WarcabyGUI();
  private:

    /*!
     * \brief Powierzchnia głównego okna
     */
    SDL_Surface* m_glowneOkno;

    /*!
     * \brief Pole określające wysokość okna
     */
    unsigned int m_wysokoscOkna;

    /*!
     * \brief Pole przechowujące współrzędne zaznaczone przez użytkownika do poruszenia figury
     */
    std::list<Wspolrzedna> m_zaznaczonePola;

    /*!
     * \brief Rysuje całą grę
     */
    void rysuj();

    /*!
     * \brief Inicjuje grę
     */
    void inicjuj();

    /*!
     * \brief Odpowiada za obsługę klawiszy klawiatury
     */
    void wcisnietoPrzycisk(SDL_Event& zdarzenie);

    /*!
     * \brief Odpowiada za obsługę przecisków myszy
     */
    void kliknietoPrzyciskMyszy(SDL_Event& zdarzenie);

    /*!
     * \brief Przetwarza kliknięcie opcji rozgrywki
     */
    void przetworzKlikniecieOpcji(SDL_Event& zdarzenie);

    /*!
     * \brief Rysuje samą planszę do gry
     */
    void rysujPlansze();

    /*!
     * \brief Rysuje statystyki rozgrywki
     */
    void rysujStatystyki();

    /*!
     * \brief Rysuje przyciski do wybrania opcji rozgrywki
     */
    void rysujPrzyciski();

    /*!
     * \brief Zamienia kliknięcie myszy na współrzędną
     *
     * Jeśli zamiana się powiedzie zwraca true
     *
     * \param x - współrzędna pozioma miejsca kliknięcia
     * \param y - wsþółrzędna pionowa miejsca kliknięcia
     * \param wsp - zmienna do której zostanie zapisana zamieniona współrzędna
     */
    bool pobierzWspolrzedna(Wspolrzedna& wsp, unsigned int x, unsigned int y);

    /*!
     * \brief Sprawdza czy wsþółrzędna jest wybrana poprawnie
     *
     * Na podstawie poprzednich wciśnięć sprawdza czy podana współrzędna
     * może zostać wybrana
     *
     * \param wsp - testowana wsþółrzędna
     */
    bool poprawnieWybranaWspolrzedna(const Wspolrzedna& wsp) const;

    /*!
     * \brief Sprawdza czy ruch powinien być wykoanany przez komputer
     *
     */
    bool czyWykonacRuchKomputera() const;

    /*!
     * \brief Zwalnia zajęta zasoby przez grę
     */
    void zwolnijZasoby();

    /*!
     * \brief Pole określające czy gra nie ma być wyłączona
     */
    bool m_czyKontynuowac;

    /*!
     * \brief Pole przechowujące ścieżkę do
     */
    std::string m_sciezkaTeksturaDrewna;

    /*!
     * \brief Pole przechowujące ścieżkę do
     */
    std::string m_sciezkaPionekBialy;

    /*!
     * \brief Pole przechowujące ścieżkę do
     */
    std::string m_sciezkaDamkaBiala;

    /*!
     * \brief Pole przechowujące ścieżkę do
     */
    std::string m_sciezkaPionekCzarny;

    /*!
     * \brief Pole przechowujące ścieżkę do
     */
    std::string m_sciezkaDamkaCzarna;

    /*!
     * \brief Pole przechowujące ścieżkę do
     */
    std::string m_sciezkaZaznaczenie;

    /*!
     * \brief Pole przechowujące ścieżkę do
     */
    std::string m_sciezkaPrzelacznik;

    /*!
     * \brief Pole przechowujące ścieżkę do
     */
    std::string m_sciezkaCzcionka;

    /*!
     * \brief Powierzchnia tektury drewna
     */
    SDL_Surface* m_teksturaDrewna;

    /*!
     * \brief Obraz białego pionka
     */
    SDL_Surface* m_pionekBialy;

    /*!
     * \brief Obraz białej matki
     */
    SDL_Surface* m_damkaBiala;

    /*!
     * \brief Obraz czarnego pionka
     */
    SDL_Surface* m_pionekCzarny;

    /*!
     * \brief Obraz czarnej matki
     */
    SDL_Surface* m_damkaCzarna;

    /*!
     * \brief Obraz zaznaczenia aktywnego pola
     */
    SDL_Surface* m_zaznaczenie;

    /*!
     * \brief Obraz czarnego pionka
     */
    SDL_Surface* m_przelacznik;

    /*!
     * \brief Czcionka używana do wyświetlania tekstu
     */
    TTF_Font* m_czcionka;

    /*!
     * \brief Zmienna określająca czy wszystkie rzeczy są zainicjowane
     */
    bool m_zainicjowano;
};
#endif /* WARCABYGUI_HPP_ */
