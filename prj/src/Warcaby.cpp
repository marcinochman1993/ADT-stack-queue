#include "Warcaby.hpp"
#include <cstdlib>

bool Warcaby::wykonajRuch(const Wspolrzedna& skad, const Wspolrzedna& dokad)
{
	const Pole& poleSkad=m_plansza.pole(skad);
	if (czyjRuch() == KOLOR::BIALY && !poleSkad.czyBiale())
		return false;
	if (czyjRuch() == KOLOR::CZARNY && !poleSkad.czyCzarne())
		return false;
        if(m_plansza.wykonajRuch(skad,dokad))
          {
            if(czyjRuch()==KOLOR::CZARNY)
              m_czyjRuch=KOLOR::BIALY;
            else
              m_czyjRuch=KOLOR::CZARNY;
            return true;
          }
        return false;
}

bool Warcaby::wykonajRuch(const std::list<Wspolrzedna>& ruchy)
{
	if(ruchy.size()<2)
		return false;
	auto it=ruchy.begin();
	const Pole& poleSkad=m_plansza.pole(*it);
	if (czyjRuch() == KOLOR::BIALY && !poleSkad.czyBiale())
		return false;
	if (czyjRuch() == KOLOR::CZARNY && !poleSkad.czyCzarne())
		return false;
	if(m_plansza.wykonajRuch(ruchy))
	  {
	    if(czyjRuch()==KOLOR::CZARNY)
	      m_czyjRuch=KOLOR::BIALY;
	    else
	      m_czyjRuch=KOLOR::CZARNY;
	    return true;
	  }
	return false;
}


Warcaby::POZIOM_KOMPUTERA Warcaby::poziomKomputera() const
{
	switch(m_maksGlebokoscMinMax)
	{
	case 1:
		return POZIOM_KOMPUTERA::LATWY;
	case 3:
		return POZIOM_KOMPUTERA::SREDNI;
	default:
		return POZIOM_KOMPUTERA::TRUDNY;
	}
}

void Warcaby::poziomKomputera(Warcaby::POZIOM_KOMPUTERA nowyPoziom)
{
	int tablicaPoziomow[]={1,3,4};
	m_maksGlebokoscMinMax=tablicaPoziomow[static_cast<int>(nowyPoziom)];
}


bool Warcaby::podpowiedzRuch(Sciezka& sciezka) const
{
	std::list<Sciezka> mozliweRuchy=(czyjRuch()==KOLOR::BIALY)?m_plansza.generujMozliweRuchyBialych():
			m_plansza.generujMozliweRuchyCzarnych();
	if(mozliweRuchy.size()==0)
		return false;
	int najlepszaWartoscFunkcji=std::numeric_limits<int>::min();
	auto itNajlepszaSciezka=mozliweRuchy.begin();
	KOLOR nastepnyRuch=czyjRuch()==KOLOR::BIALY?KOLOR::CZARNY:KOLOR::BIALY;
	for(auto it=mozliweRuchy.begin();it!=mozliweRuchy.end();it++)
	{
		PlanszaWarcaby kopiaPlanszy=m_plansza;
		kopiaPlanszy.wykonajRuch(it->listaPol());
		int wartoscFunkcji=minMax(1,kopiaPlanszy,
				[this](const PlanszaWarcaby& plansza)
				{
			int wartoscFunkcji;
			if(czyjRuch()==KOLOR::BIALY)
			{
				wartoscFunkcji=
						static_cast<int>(plansza.iloscPionkowBialych())+static_cast<int>(3*plansza.iloscMatekBialych())+
						static_cast<int>(plansza.iloscPionkowBialych())-static_cast<int>(plansza.iloscPionkowCzarnych())+
						static_cast<int>(3*plansza.iloscMatekBialych())-static_cast<int>(3*plansza.iloscMatekCzarnych());
			}
			else
			{
				wartoscFunkcji=
						static_cast<int>(plansza.iloscPionkowCzarnych())+static_cast<int>(3*plansza.iloscMatekCzarnych())+
						static_cast<int>(plansza.iloscPionkowCzarnych())-static_cast<int>(plansza.iloscPionkowBialych())+
						static_cast<int>(3*plansza.iloscMatekCzarnych())-static_cast<int>(3*plansza.iloscMatekBialych());
			}
			return wartoscFunkcji;
				}, nastepnyRuch);
		if(wartoscFunkcji>najlepszaWartoscFunkcji)
		{
			najlepszaWartoscFunkcji=wartoscFunkcji;
			itNajlepszaSciezka=it;
		}
		else
			if(wartoscFunkcji==najlepszaWartoscFunkcji && rand()%2==1)
				itNajlepszaSciezka=it;
			std::cout<<*it<<": "<<wartoscFunkcji<<std::endl;
	}
	sciezka=*itNajlepszaSciezka;
	std::cout<<"*********Koniec decyzji ruchu*********\n\n";
	return true;
}

void Warcaby::odpuscRuch()
{
	if(czyjRuch()==KOLOR::CZARNY)
		m_czyjRuch=KOLOR::BIALY;
	else
		m_czyjRuch=KOLOR::CZARNY;
}

bool Warcaby::czyRuchKomputera() const
{
	return (czyjRuch()==KOLOR::BIALY && m_gracz1==TYP_GRACZA::KOMPUTER) ||
			(czyjRuch()==KOLOR::CZARNY && m_gracz2==TYP_GRACZA::KOMPUTER);
}

