#ifndef WARCABY_H
#define WARCABY_H

#include "PlanszaWarcaby.hpp"
#include <limits>

/*!
 * \brief Klasa reprezentująca grę w warcaby
 */
class Warcaby
{
  public:
    /*!
     * \brief Typ wyliczniowy definiujący kolor figur
     */
    enum class KOLOR { BIALY, CZARNY };

    /*!
     * \brief Typ wyliczeniowy definiujący poziom trudności
     */
    enum class POZIOM_KOMPUTERA { LATWY, SREDNI, TRUDNY };

    /*!
     * \brief Typ wyliczeniowy definiujący rodzaj gracza
     */
    enum class TYP_GRACZA { CZLOWIEK, KOMPUTER };

    /*!
     * \brief Domyślny konstruktor klasy Warcaby
     *
     * Ustawia poziom trudności na trudny, ruch będą zaczynać białe, gracz1 to człowiek,
     * gracz2 to komputer
     */
    Warcaby():m_maksGlebokoscMinMax(4),m_czyjRuch(KOLOR::BIALY), m_gracz1(TYP_GRACZA::CZLOWIEK),
        m_gracz2(TYP_GRACZA::KOMPUTER) {}

    /*!
     * \brief Pozwala na wybranie odpowiedniego ruchu dla gracza, którego jest kolej
     *
     * Funkcja zwraca true, jeśli zostanie znaleziony jakikolwiek ruch
     *
     * \param sciezka [out] - znaleziona ścieżka
     */
    bool podpowiedzRuch(Sciezka& sciezka) const;

    /*!
     * \brief Wykonuje ruch z danego pola na określone pole
     *
     * Jesli ruch sie powiedzie, ruch ma następny gracz, w.p.p
     * ruch ma nadal gracz aktywny
     */
    bool wykonajRuch(const Wspolrzedna& skad, const Wspolrzedna& dokad);

    /*!
     * \brief Wykonuje ruchy określone przez listę ruchów
     *
     * Jesli ruchy sie powiodą, kolej na następnego gracza, w.p.p
     * ruch ma nadal gracz aktywny
     */
    bool wykonajRuch(const std::list<Wspolrzedna>& ruchy);

    /*!
     * \brief Pozwala określić, jaki kolor ma ruch
     */
    KOLOR czyjRuch() const { return m_czyjRuch; }

    /*!
     * \brief Określa rodzaj gracza numer 1
     */
    TYP_GRACZA typGracza1() const {return m_gracz1; }

    /*!
     * \brief Pozwala ustawić typ gracza numer 1
     */
    void typGracza1(TYP_GRACZA nowyTypGracza1) { m_gracz1=nowyTypGracza1; }

    /*!
     * \brief Określa rodzaj gracza numer 2
     */
    TYP_GRACZA typGracza2() const {return m_gracz2; }

    /*!
     * \brief Pozwala ustawić typ gracza numer 1
     *
     * \param nowyTypGracza2 - nowy rodzaj gracza 2
     */
    void typGracza2(TYP_GRACZA nowyTypGracza2) { m_gracz2=nowyTypGracza2; }

    /*!
     * \brief Pozwala pobrać poziom AI
     */
    POZIOM_KOMPUTERA poziomKomputera() const;

    /*!
     * \brief Pozwala ustawić poziom AI
     *
     * \param nowyPoziom - nowy poziom AI
     */
    void poziomKomputera(POZIOM_KOMPUTERA nowyPoziom);

    /*!
     * \brief Pozwala pobrać referencję do planszy do gry w warcaby
     */
    const PlanszaWarcaby& plansza() const { return m_plansza; }

    /*!
     * \brief Sprawdza czy rozgrywka się nie zakończyła
     */
    bool czyKoniec() const { return m_plansza.iloscBialych()==0 || m_plansza.iloscCzarnych()==0; }

    /*!
     * \brief Odpuszcza ruch, oddaje kolej przeciwnikowi
     */
    void odpuscRuch();

    /*!
     * \brief Sprawdza czy ruch powinien wykonać komputer
     */
    bool czyRuchKomputera() const;

    /*!
     * \brief Pozwala zrestartować grę
     */
    void restartuj() { m_plansza.inicjuj(); }
  private:
    /*!
     * \brief Metoda przeprowadzająca algorytm min-max w celu znalezienia odpowiedniej ścieżki
     */
    template <typename F>
    int minMax(unsigned int poziom, const PlanszaWarcaby& plansza,
        F funkcja, KOLOR czyjRuch) const;

    /*!
     * \brief Pole przechowujące planszę do gry w warcaby
     */
    PlanszaWarcaby m_plansza;

    /*!
     * \brief Określa rodzaj gracza numer 1
     */
    TYP_GRACZA m_gracz1;

    /*!
     * \brief Określa rodzaj gracza numer 2
     */
    TYP_GRACZA m_gracz2;

    /*!
     * \brief Pole określające maksymalną głębokość algorytmu min-max
     */
    unsigned int m_maksGlebokoscMinMax;

    /*!
     * \brief Pole określające czyja jest kolej wykonania ruchu
     */
    KOLOR m_czyjRuch;
};


template <typename F>
int Warcaby::minMax(unsigned int poziom, const PlanszaWarcaby& plansza,
    F funkcja, Warcaby::KOLOR czyjRuch) const
{
  KOLOR czyjaKolejNastepna=czyjRuch==KOLOR::BIALY?KOLOR::CZARNY:KOLOR::BIALY;
  if(poziom>m_maksGlebokoscMinMax)
    return funkcja(plansza);
  bool ruchPrzeciwnika=this->czyjRuch()!=czyjRuch?true:false;
  int minMaxWartosc=ruchPrzeciwnika?std::numeric_limits<int>::max():std::numeric_limits<int>::min();
  std::list<Sciezka> mozliweRuchy=(czyjRuch==KOLOR::BIALY)?plansza.generujMozliweRuchyBialych():
      plansza.generujMozliweRuchyCzarnych();
  for(auto it=mozliweRuchy.begin();it!=mozliweRuchy.end();it++)
    {
      PlanszaWarcaby kopiaPlanszy=plansza;
      kopiaPlanszy.wykonajRuch(it->listaPol());
      int wartoscFunkcji=minMax(poziom+1,kopiaPlanszy,funkcja,czyjaKolejNastepna);
      if(ruchPrzeciwnika)
        {
          if(wartoscFunkcji<minMaxWartosc)
            minMaxWartosc=wartoscFunkcji;
        }
      else
        {
          if(wartoscFunkcji>minMaxWartosc)
            minMaxWartosc=wartoscFunkcji;
        }
    }
  return minMaxWartosc;
}
#endif // WARCABY_H
