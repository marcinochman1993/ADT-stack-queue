#ifndef PLANSZAWARCABY_HPP
#define PLANSZAWARCABY_HPP


#include <list>
#include "Wspolrzedna.hpp"
#include "Macierz.hpp"
#include "Pole.hpp"
#include "Sciezka.hpp"

/*!
 * \brief Klasa reprezentuje planszę do gry w warcaby o dowolnej wielkości
 *
 */
class PlanszaWarcaby
{
  public:

    /*!
     * \brief Konstruktor klasy PlanszaWarcaby
     *
     * Ustawia rozmiar planszy na 8, ilość pionków jednej strony na 8 oraz rozstawia pionki
     */
    PlanszaWarcaby(unsigned int rozmiarPlanszy=8, unsigned int iloscPionkow=8) { inicjuj(rozmiarPlanszy,iloscPionkow); }

    /*!
     * \brief Sprawdza czy ruch jest możliwy
     *
     * \param skad - pole startowe
     * \param dokad - pole docelowe
     *
     * \return Zwraca true jeśli jest możliwy, w.p.p. false
     */
    bool czyRuchMozliwy(const Wspolrzedna& skad,
        const Wspolrzedna& dokad) const;

    /*!
     * \brief Sprawdza czy ruchy określone w liście wspołrzędnych są możliwe
     *
     * \param ruchy - lista ruchów
     *
     * \return Zwraca true jeśli jest możliwy, w.p.p. false
     */
    bool czyRuchMozliwy(const std::list<Wspolrzedna>& ruchy) const;

    /*!
     * \brief Wykonuje ruch na planszy
     *
     * \param skad - pole startowe
     * \param dokad - pole docelowe
     *
     * \return Zwraca true jeśli ruch wykonano, w.p.p. false
     */
    bool wykonajRuch(const Wspolrzedna& skad, const Wspolrzedna& dokad);

    /*!
     * \brief Wykonuje ruch na planszy
     *
     * \param ruchy - lista współrzędnych kolejnych pól
     *
     * \return Zwraca true jeśli ruch wykonano, w.p.p. false
     */
    bool wykonajRuch(const std::list<Wspolrzedna>& ruchy);

    /*!
     * \brief Pozwala pobrać rozmiar planszy
     */
    unsigned int rozmiar() const { return m_rozmiarPlanszy; }

    /*!
     * \brief Pozwala pobrać ilość białych figur na planszy
     */
    unsigned int iloscBialych() const { return m_iloscBialych; }

    /*!
     * \brief Pozwala pobrać ilość czarnych figur na planszy
     */
    unsigned int iloscCzarnych() const { return m_iloscCzarnych; }

    /*!
     * \brief Pozwala pobrać ilość czarnych matek na planszy
     */
    unsigned int iloscMatekCzarnych() const { return m_iloscCzarnychMatek; }

    /*!
     * \brief Pozwala pobrać ilość białych matek na planszy
     */
    unsigned int iloscMatekBialych() const { return m_iloscBialychMatek; }

    /*!
     * \brief Pozwala pobrac ilość białych pionków na planszy
     *
     */
    unsigned int iloscPionkowBialych() const { return m_iloscBialych-m_iloscBialychMatek; }

    /*!
     * \brief Pozwala pobrać ilość czarnych pionków na planszy
     */
    unsigned int iloscPionkowCzarnych() const { return m_iloscCzarnych-m_iloscCzarnychMatek; }

    /*!
     * \brief Pozwala pobrac referencję do pola o podanym indeksie
     *
     */
    Pole& operator()(unsigned int x, unsigned int y) { return m_plansza(x,y); }

    /*!
     * \brief Pozwala pobrać stałą referencję do pola o podanym indeksie
     *
     */
    const Pole& operator()(unsigned int x, unsigned int y) const { return m_plansza(x,y); }

    /*!
     * \brief Pozwala zainicjować planszę
     *
     * Rozstawia określoną ilość pionków na podanym rozmiarze planszy
     *
     * \param rozmiarPlanszy - rozmiar planszy do gry
     * \param iloscPionkow - ilość pionków po jeden stronie
     */
    void inicjuj(unsigned int rozmiarPlanszy=8, unsigned int iloscPionkow=8);

    /*!
     * \brief Pozwala pobrać stan pola o podanej współrzędnej
     *
     * \param wspolrzedna - wspołrzędna określająca dane pole
     */
    const Pole& pole(const Wspolrzedna& wspolrzedna) const;

    /*!
     * \brief Pozwala ustawić stan pola o podanej współrzędnej
     *
     * \param wspolrzedna - wspołrzędna określająca dane pole
     * \param stanPola - nowy stan pola
     */
    void pole(const Wspolrzedna& wspolrzedna, Pole::STAN_POLA stanPola);

    /*!
     * \brief Operator wyjścia
     *
     * Pozwala wypisać planszę na strumień wyjściowy
     *
     * \param os - strumień wyjściowy
     * \param plansza - plansza, która ma zostac wypisana
     */
    friend std::ostream& operator<<(std::ostream& os, const PlanszaWarcaby& plansza);

    /*!
     * \brief Pozwala wygenerować wszystkie możliwe ruchy figury na odpowiednim polu
     *
     * \param wspolrzedna - wspołrzędna pola figury, na podstawie której zostaną wygenerowane możliwe ruchy
     */
    std::list<Sciezka> generujMozliweRuchy(const Wspolrzedna& wspolrzedna) const;

    /*!
     * \brief Generuje wszystkie możliwe ruchy czarnych figur i zwraca w postaci listy
     *
     */
    std::list<Sciezka> generujMozliweRuchyCzarnych() const;

    /*!
     * \brief Generuje wszystkie możliwe ruchy białych figur i zwraca w postaci listy
     *
     */
    std::list<Sciezka> generujMozliweRuchyBialych() const;

    /*!
     * \brief Sprawdza czy bicie z danego pola do docelowego jest możliwe
     *
     * \param skad - współrzędna pola startowego
     * \param dokad - współrzędna pola docelowego
     */
    bool czyPoprawnyRuchBicia(const Wspolrzedna& skad,
        const Wspolrzedna& dokad) const;
  private:

    /*!
     * \brief Macierz reprezentująca stan planszy
     */
    Macierz<Pole> m_plansza;

    /*!
     * \brief Pole przechowujące rozmiar planszy
     */
    unsigned int m_rozmiarPlanszy;

    /*!
     * \brief Pole przechowujące ilośc figur czarnych na planszy
     */
    unsigned int m_iloscCzarnych;

    /*!
     * \brief Pole przechowujące ilośc figur białych na planszy
     */
    unsigned int m_iloscBialych;

    /*!
     * \brief Pole przechowujące ilość białych matek na planszy
     */
    unsigned int m_iloscBialychMatek;

    /*!
     * \brief Pole przechowujące ilość czarnych matek na planszy
     */
    unsigned int m_iloscCzarnychMatek;

    /*!
     * \brief Sprawdza czy ruch matką z danego pola do docelowego jest możliwy
     *
     * \param skad - współrzędna pola startowego
     * \param dokad - współrzędna pola docelowego
     */
    bool czyRuchMozliwyMatka(const Wspolrzedna& skad,
        const Wspolrzedna& dokad) const;

    /*!
     * \brief Sprawdza czy ruch pionka z danego pola do docelowego jest możliwy
     *
     * \param skad - współrzędna pola startowego
     * \param dokad - współrzędna pola docelowego
     */
    bool czyRuchMozliwyPionek(const Wspolrzedna& skad,
        const Wspolrzedna& dokad) const;

    /*!
     * \brief Sprawdza czy bicie matką z danego pola do docelowego jest możliwe
     *
     * \param skad - współrzędna pola startowego
     * \param dokad - współrzędna pola docelowego
     */
    bool czyPoprawnyRuchBiciaMatka(const Wspolrzedna& skad,
        const Wspolrzedna& dokad) const;

    /*!
     * \brief Sprawdza czy ruch bicia pionkiem z danego pola do docelowego jest możliwy
     *
     * \param skad - współrzędna pola startowego
     * \param dokad - współrzędna pola docelowego
     */
    bool czyPoprawnyRuchBiciaPionek(const Wspolrzedna& skad,
        const Wspolrzedna& dokad) const;

    /*!
     * \brief Wykonuje bicie figurą
     *
     * \param skad - współrzędna pola startowego
     * \param dokad - współrzędna pola docelowego
     */
    bool wykonajBicie(const Wspolrzedna& skad,
        const Wspolrzedna& dokad);

    /*!
     * \brief Wykonuje bicie pionkiem
     *
     * \param skad - współrzędna pola startowego
     * \param dokad - współrzędna pola docelowego
     */
    bool wykonajBiciePionkiem(const Wspolrzedna& skad,
        const Wspolrzedna& dokad);

    /*!
     * \brief Wykonuje bicie matką
     *
     * \param skad - współrzędna pola startowego
     * \param dokad - współrzędna pola docelowego
     */
    bool wykonajBicieMatka(const Wspolrzedna& skad,
        const Wspolrzedna& dokad);

    /*!
     * \brief Rozstawia pionki czarne na planszy przy inicjowaniu
     */
    void rozstawCzarne();

    /*!
     * \brief Rozstawia pionki białe na planszy przy inicjowaniu
     */
    void rozstawBiale();

    /*!
     * \brief Generuje listę możliwych ruchów, w jaki sposób może bić pionek (pojedynczo)
     * \param wspolrzedna - pole, na którym stoi pionek, którego możliwe ruchy mają być wygenerowane
     *
     * \return Zwracana jest lista możliwych ruchów
     */
    std::list<Sciezka> gdzieMozeBicPionek(const Wspolrzedna& wspolrzedna) const;

    /*!
     * \brief Generuje listę możliwych ruchów, w jaki sposób może bić pionek (pojedynczo)
     * \param wspolrzedna - pole, na którym stoi matka, którego możliwe ruchy mają być wygenerowane
     *
     * \return Zwracana jest lista możliwych ruchów
     */
    std::list<Sciezka> gdzieMozeBicMatka(const Wspolrzedna& wspolrzedna) const;

    /*!
     * \brief Generuje możliwe ruchy pionka na określonym polu
     *
     * \param wspolrzedna - pole, na którym stoi pionek, którego możliwe ruchy mają być wygenerowane
     *
     * \return Zwracana jest lista możliwych ruchów
     */
    std::list<Sciezka> generujMozliweRuchyPionek(const Wspolrzedna& wspolrzedna) const;

    /*!
     * \brief Generuje możliwe ruchy pionka na określonym polu
     *
     * \param wspolrzedna - pole, na którym stoi pionek, którego możliwe ruchy mają być wygenerowane
     *
     * \return Zwracana jest lista możliwych ruchów
     */
    std::list<Sciezka> generujMozliweRuchyBiciaPionek(const Wspolrzedna& wspolrzedna) const;

    /*!
     * \brief Generuje możliwe ruchy matki na określonym polu
     *
     * \param wspolrzedna - pole, na którym stoi matka, której możliwe ruchy mają być wygenerowane
     *
     * \return Zwracana jest lista możliwych ruchów
     */
    std::list<Sciezka> generujMozliweRuchyMatka(const Wspolrzedna& wspolrzedna) const;

    /*!
     * \brief Generuje możliwe ruchy matki na określonym polu
     *
     * \param wspolrzedna - pole, na którym stoi matka, której możliwe ruchy mają być wygenerowane
     *
     * \return Zwracana jest lista możliwych ruchów
     */
    std::list<Sciezka> generujMozliweRuchyBiciaMatka(const Wspolrzedna& wspolrzedna) const;
};

#endif // PLANSZAWARCABY_HPP
