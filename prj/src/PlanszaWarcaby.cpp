#include "PlanszaWarcaby.hpp"
#include <cmath>

void PlanszaWarcaby::inicjuj(unsigned int rozmiarPlanszy, unsigned int iloscPionkow)
{
	const int MAKS_ROZMIAR=26;
	if(rozmiarPlanszy>MAKS_ROZMIAR)
		rozmiarPlanszy=MAKS_ROZMIAR;
	m_plansza=Macierz<Pole>(rozmiarPlanszy,rozmiarPlanszy);
	m_plansza.zmienRozmiar(rozmiarPlanszy,rozmiarPlanszy); //ustawia całą planszę pustą
	m_rozmiarPlanszy=rozmiarPlanszy;
	m_iloscBialychMatek=0;
	m_iloscCzarnychMatek=0;
	if(iloscPionkow/(rozmiar()/2)>rozmiar()/2-1)// czy ilosc pionkow nie za duża
	{
		if(rozmiar()%2==0)
			iloscPionkow=rozmiar()/2*(rozmiar()/2-1);
		else
		{
			unsigned int iloscZajetychWierszy=(rozmiar()-3)/2, // po jednej ze stron
					pionkowWNieparzystym=rozmiar()/2+1, pionkowWParzystym=rozmiar()/2,
					iloscWierszyParzystych,
					iloscWierszyNieparzystych;
			if(iloscZajetychWierszy%2==0)
				iloscWierszyParzystych=iloscWierszyNieparzystych=
						iloscZajetychWierszy/2;
			else
			{
				iloscWierszyParzystych=iloscZajetychWierszy/2;
				iloscWierszyNieparzystych=iloscZajetychWierszy/2+1;
			}
			iloscPionkow=pionkowWNieparzystym*iloscWierszyNieparzystych+pionkowWParzystym*iloscWierszyParzystych;
		}
	}
	m_iloscBialych=iloscPionkow;
	m_iloscCzarnych=iloscPionkow;
	rozstawCzarne();
	rozstawBiale();
}

const Pole& PlanszaWarcaby::pole(const Wspolrzedna& wspolrzedna) const
{
	unsigned int wiersz=wspolrzedna.wierszLiczba()-1,
			kolumna=wspolrzedna.kolumna()-1;
	if(wiersz<rozmiar() && kolumna<rozmiar())
		return m_plansza(wiersz,kolumna);
	throw "Nie ma takiego pola";
}

void PlanszaWarcaby::pole(const Wspolrzedna& wspolrzedna, Pole::STAN_POLA stanPola)
{
	unsigned int wiersz=wspolrzedna.wierszLiczba()-1,
				kolumna=wspolrzedna.kolumna()-1;
		if(wiersz<rozmiar() && kolumna<rozmiar())
			m_plansza(wiersz,kolumna).stan(stanPola);
		else
			throw "Nie ma takiego pola";
}



// Optymalne dla c++11!
std::list<Sciezka> PlanszaWarcaby::generujMozliweRuchyCzarnych() const
{
	std::list<Sciezka> mozliweSciezki;
	for(unsigned int i=0;i<rozmiar();i++)
		for(unsigned int j=0;j<rozmiar();j++)
			if(m_plansza(i,j).czyCzarne())
			{
				Wspolrzedna wspTemp;
				wspTemp.wierszLiczba(i+1);
				wspTemp.kolumna(j+1);
				std::list<Sciezka> mozliweSciezkiDanegoPola=generujMozliweRuchy(wspTemp);
				mozliweSciezki.splice(mozliweSciezki.end(),mozliweSciezkiDanegoPola);
			}
	return mozliweSciezki;
}

// Optymalne dla c++11!
std::list<Sciezka> PlanszaWarcaby::generujMozliweRuchyBialych() const
{
	std::list<Sciezka> mozliweSciezki;
	for(unsigned int i=0;i<rozmiar();i++)
		for(unsigned int j=0;j<rozmiar();j++)
			if(m_plansza(i,j).czyBiale())
			{
				Wspolrzedna wspTemp;
				wspTemp.wierszLiczba(i+1);
				wspTemp.kolumna(j+1);
				std::list<Sciezka> mozliweSciezkiDanegoPola=generujMozliweRuchy(wspTemp);
				mozliweSciezki.splice(mozliweSciezki.end(),mozliweSciezkiDanegoPola);
			}
	return mozliweSciezki;
}

std::list<Sciezka> PlanszaWarcaby::generujMozliweRuchy(const Wspolrzedna& wspolrzedna) const
{
	unsigned int wiersz=wspolrzedna.wierszLiczba()-1,
			kolumna=wspolrzedna.kolumna()-1;
	if(m_plansza(wiersz,kolumna).czyPionek())
		return generujMozliweRuchyPionek(wspolrzedna);
	if(m_plansza(wiersz,kolumna).czyMatka())
		return generujMozliweRuchyMatka(wspolrzedna);
	return std::list<Sciezka>();
}

void PlanszaWarcaby::rozstawCzarne()
{
	unsigned int i=0, czarneDoRozstawienia=m_iloscCzarnych;
	while(czarneDoRozstawienia>0)
	{
		bool bialePolePierwsze=(i%2==0)?true:false;
		for(unsigned int j=0;j<rozmiar() && czarneDoRozstawienia>0;j++)
		{
			if(bialePolePierwsze)
			{
				if(j%2==1)
				{
					m_plansza(i,j).stan(Pole::STAN_POLA::CZARNY_PIONEK);
					czarneDoRozstawienia--;
				}
			}
			else
			{
				if(j%2==0)
				{
					m_plansza(i,j).stan(Pole::STAN_POLA::CZARNY_PIONEK);
					czarneDoRozstawienia--;
				}

			}
		}
		i++;
	}
}


void PlanszaWarcaby::rozstawBiale()
{
	unsigned int i=rozmiar()-1;
	unsigned int bialeDoRozstawienia=m_iloscBialych;
	while(bialeDoRozstawienia>0)
	{
		bool bialePolePierwsze=(i%2==0)?true:false;
		for(unsigned int j=0;j<rozmiar() && bialeDoRozstawienia>0;j++)
		{
			if(bialePolePierwsze)
			{
				if(j%2==1)
				{
					m_plansza(i,j).stan(Pole::STAN_POLA::BIALY_PIONEK);
					bialeDoRozstawienia--;
				}
			}
			else
			{
				if(j%2==0)
				{
					m_plansza(i,j).stan(Pole::STAN_POLA::BIALY_PIONEK);
					bialeDoRozstawienia--;
				}
			}
		}
		i--;
	}
}

bool PlanszaWarcaby::czyPoprawnyRuchBicia(const Wspolrzedna& skad,
				const Wspolrzedna& dokad) const
{
	if(m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).czyPionek())
		return czyPoprawnyRuchBiciaPionek(skad,dokad);
	if(m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).czyMatka())
		return czyPoprawnyRuchBiciaMatka(skad,dokad);
	return false;
}

bool PlanszaWarcaby::czyRuchMozliwy(const Wspolrzedna& skad,
		const Wspolrzedna& dokad) const
{
	unsigned int wierszPoczatkowy = skad.wierszLiczba() - 1,
			kolumnaPoczatkowa = skad.kolumna() - 1,
			wierszDocelowy = dokad.wierszLiczba() - 1,
			kolumnaDocelowa = dokad.kolumna() - 1;
	if(m_plansza(wierszPoczatkowy,kolumnaPoczatkowa).czyPuste())
		return false;
	if(m_plansza(wierszDocelowy,kolumnaDocelowa).czyZajete())
		return false;

	if(m_plansza(wierszPoczatkowy,kolumnaPoczatkowa).czyPionek())
		return czyRuchMozliwyPionek(skad,dokad);
	return czyRuchMozliwyMatka(skad,dokad);
}


bool PlanszaWarcaby::czyRuchMozliwy(const std::list<Wspolrzedna>& ruchy) const
{
	if(ruchy.size()<0)
		return false;
	auto itSkad=ruchy.begin(), itDokad=itSkad;
	itDokad++;
	Wspolrzedna skad,dokad;
	PlanszaWarcaby kopiaPlanszy=*this;
	do
	{
		skad=*itSkad;
		dokad=*itDokad;
		if(!kopiaPlanszy.wykonajRuch(skad,dokad))
			return false;
		itDokad++;
		itSkad++;
	}while(itDokad!=ruchy.end());
	return true;
}

bool PlanszaWarcaby::czyRuchMozliwyMatka(const Wspolrzedna& skad,
		const Wspolrzedna& dokad) const
{
	const Pole& poleSkad=m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1);
	int wierszPoczatkowy=skad.wierszLiczba()-1, kolumnaPoczatkowa=skad.kolumna()-1,
			wierszKoncowy=dokad.wierszLiczba()-1, kolumnaKoncowa=dokad.kolumna()-1;
	int roznicaWierszy=wierszKoncowy-wierszPoczatkowy,
			roznicaKolumn=kolumnaKoncowa-kolumnaPoczatkowa;
	if(!poleSkad.czyMatka())
			return false;
	if(czyPoprawnyRuchBiciaMatka(skad,dokad))
		return true;

	if(std::abs(roznicaWierszy) != std::abs(roznicaKolumn))
		return false;
	if(m_plansza(wierszKoncowy,kolumnaKoncowa).czyZajete())
		return false;
	int naliczonychPoDrodze=0,
			inkrWiersz=roznicaWierszy/std::abs(roznicaWierszy),
			inkrKol=roznicaKolumn/std::abs(roznicaKolumn),
			wierszAktywny=wierszPoczatkowy+inkrWiersz,
			kolumnaAktywna=kolumnaPoczatkowa+inkrKol;
	while(naliczonychPoDrodze==0 && kolumnaAktywna!=kolumnaKoncowa &&
			wierszAktywny!=wierszKoncowy)
	{
		wierszAktywny+=inkrWiersz;
		kolumnaAktywna+=inkrKol;
		if(m_plansza(wierszAktywny,kolumnaAktywna).czyZajete())
			naliczonychPoDrodze++;
	}
	if(naliczonychPoDrodze==0)
		return true;
	return false;
}

bool PlanszaWarcaby::czyRuchMozliwyPionek(const Wspolrzedna& skad,
		const Wspolrzedna& dokad) const
{
	const Pole& poleSkad=m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1);
	if(!poleSkad.czyPionek())
		return false;
	if(czyPoprawnyRuchBiciaPionek(skad,dokad))
		return true;
	bool bialy=(poleSkad.czyBiale())?true:false;
	if(bialy)
	{
		if(static_cast<int>(dokad.wierszLiczba())-static_cast<int>(skad.wierszLiczba()) != -1)
			return false;
		if(std::abs(static_cast<int>(dokad.kolumna())-static_cast<int>(skad.kolumna()))!=1)
			return false;
	}
	else
	{
		if(dokad.wierszLiczba()-skad.wierszLiczba() != 1)
			return false;
		if(std::abs(static_cast<int>(dokad.kolumna())-static_cast<int>(skad.kolumna()))!=1)
			return false;
	}
	return true;
}

bool PlanszaWarcaby::wykonajRuch(const Wspolrzedna& skad, const Wspolrzedna& dokad)
{
	if(!czyRuchMozliwy(skad,dokad))
		return false;
	if(wykonajBicie(skad,dokad))
		return true;
	Pole::STAN_POLA stan=m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).stan();
	m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).stan(Pole::STAN_POLA::PUSTE);
	m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).stan(stan);
	if(m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).czyPionek() &&
			((m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).czyBiale() && dokad.wierszLiczba()==1) ||
					(m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).czyCzarne() && dokad.wierszLiczba()==rozmiar())))
	{
		m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).awansPionka();
		if(m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).czyBiale())
			m_iloscBialychMatek++;
		else
			m_iloscCzarnychMatek++;

	}
	return true;
}

bool PlanszaWarcaby::wykonajRuch(const std::list<Wspolrzedna>& ruchy)
{
	if(ruchy.size()<0)
		return false;
	auto itSkad=ruchy.begin(), itDokad=itSkad;
	itDokad++;
	Wspolrzedna skad,dokad;
	PlanszaWarcaby kopiaPlanszy=*this;
	do
	{
		skad=*itSkad;
		dokad=*itDokad;
		if(!kopiaPlanszy.wykonajRuch(skad,dokad))
			return false;
		itDokad++;
		itSkad++;
	}while(itDokad!=ruchy.end());
	*this=kopiaPlanszy;
	return true;
}

bool PlanszaWarcaby::czyPoprawnyRuchBiciaMatka(const Wspolrzedna& skad,
		const Wspolrzedna& dokad) const
{
	long roznicaWierszy=static_cast<long>(dokad.wierszLiczba())-static_cast<long>(skad.wierszLiczba()),
			roznicaKolumn=static_cast<long>(dokad.kolumna())-static_cast<long>(skad.kolumna());
	if(!m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).czyMatka())
		return false;
	if(std::abs(roznicaWierszy)!=std::abs(roznicaKolumn))
		return false;
	if(std::abs(roznicaWierszy)<2)
		return false;
	if(m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).czyZajete())
		return false;
	int wiersz=skad.wierszLiczba()-1,kolumna=skad.kolumna()-1;
	bool jestBiala=m_plansza(wiersz,kolumna).czyBiale();
	const long inkrWiersz=roznicaWierszy/std::abs(roznicaWierszy),
			inkrKol=roznicaKolumn/std::abs(roznicaKolumn);
	unsigned int napotkanych=0;
	if((m_plansza(wiersz+inkrWiersz,kolumna+inkrKol).czyBiale() && jestBiala) ||
			(m_plansza(wiersz+inkrWiersz,kolumna+inkrKol).czyCzarne() && !jestBiala))
		return false;
	for(unsigned int i=1;i<std::abs(roznicaWierszy);i++)
	{
		if((m_plansza(wiersz+i*inkrWiersz,kolumna+i*inkrKol).czyBiale() && jestBiala) ||
				(m_plansza(wiersz+i*inkrWiersz,kolumna+i*inkrKol).czyCzarne() && !jestBiala))
			return false;

		if(m_plansza(wiersz+i*inkrWiersz,kolumna+i*inkrKol).czyZajete() &&
				m_plansza(wiersz+i*inkrWiersz-inkrWiersz,kolumna+i*inkrKol-inkrKol).czyZajete() && i!=1)
			return false;
		if(m_plansza(wiersz+i*inkrWiersz,kolumna+i*inkrKol).czyZajete())
			napotkanych++;
	}
	if(napotkanych!=1)
		return false;
	return true;
}

bool PlanszaWarcaby::czyPoprawnyRuchBiciaPionek(const Wspolrzedna& skad,
		const Wspolrzedna& dokad) const
{
	long roznicaWierszy=
			static_cast<long>(dokad.wierszLiczba())-static_cast<long>(skad.wierszLiczba()),
		 roznicaKolumn=
			static_cast<long>(dokad.kolumna())-static_cast<long>(skad.kolumna());
	if(m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).czyPionek())
		return false;

	if(m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).czyPuste())
		return false;
	if(std::abs(roznicaWierszy)!=std::abs(roznicaKolumn) || std::abs(roznicaWierszy)!=2 || std::abs(roznicaKolumn)!=2)
		return false;
	if(m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).czyBiale())
	{

		if(!m_plansza(skad.wierszLiczba()-1+0.5*roznicaWierszy,skad.kolumna()-1+0.5*roznicaKolumn).czyCzarne())
			return false;
	}
	else
	{
		if(!m_plansza(skad.wierszLiczba()-1+0.5*roznicaWierszy,skad.kolumna()-1+0.5*roznicaKolumn).czyBiale())
			return false;
	}
	return true;
}

bool PlanszaWarcaby::wykonajBicie(const Wspolrzedna& skad,
		const Wspolrzedna& dokad)
{
	if(m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).czyPionek())
		return wykonajBiciePionkiem(skad,dokad);
	if(m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).czyMatka())
		return wykonajBicieMatka(skad,dokad);
	return false;
}

bool PlanszaWarcaby::wykonajBiciePionkiem(const Wspolrzedna& skad,
		const Wspolrzedna& dokad)
{
	if(!czyPoprawnyRuchBiciaPionek(skad,dokad))
		return false;
	int inkrWiersz=static_cast<int>(dokad.wierszLiczba())-static_cast<int>(skad.wierszLiczba()),
			inkrKolumna=static_cast<int>(dokad.kolumna())-static_cast<int>(skad.kolumna());
	Pole::STAN_POLA stan=m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).stan();
	m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).stan(Pole::STAN_POLA::PUSTE);
	m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).stan(stan);

	if(m_plansza(skad.wierszLiczba()-1+0.5*inkrWiersz,skad.kolumna()-1+0.5*inkrKolumna).czyBiale())
	{
		m_iloscBialych--;
		if(m_plansza(skad.wierszLiczba()-1+0.5*inkrWiersz,skad.kolumna()-1+0.5*inkrKolumna).czyMatka())
			m_iloscBialychMatek--;
	}
	else
	{
		m_iloscCzarnych--;
		if(m_plansza(skad.wierszLiczba()-1+0.5*inkrWiersz,skad.kolumna()-1+0.5*inkrKolumna).czyMatka())
			m_iloscCzarnychMatek--;
	}
	m_plansza(skad.wierszLiczba()-1+0.5*inkrWiersz,skad.kolumna()-1+0.5*inkrKolumna).stan(Pole::STAN_POLA::PUSTE);
	if((m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).czyBiale() && dokad.wierszLiczba()==1) ||
			(m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).czyCzarne() && dokad.wierszLiczba()==rozmiar()))
	{
		m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).awansPionka();
		if(m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).czyBiale())
			m_iloscBialychMatek++;
		else
			m_iloscCzarnychMatek++;
	}
	return true;
}

bool PlanszaWarcaby::wykonajBicieMatka(const Wspolrzedna& skad,
		const Wspolrzedna& dokad)
{
	if(!czyPoprawnyRuchBiciaMatka(skad,dokad))
		return false;
	int inkrWiersz=dokad.wierszLiczba()-skad.wierszLiczba(),
			inkrKol=dokad.kolumna()-skad.kolumna();
	inkrWiersz/=std::abs(inkrWiersz),inkrKol/=std::abs(inkrKol);
	for(int i=1;i<std::abs(static_cast<int>(dokad.kolumna())-static_cast<int>(skad.kolumna()));i++)
	{
		if(m_plansza(skad.wierszLiczba()-1+i*inkrWiersz,skad.kolumna()-1+i*inkrKol).czyBiale())
		{
			m_iloscBialych--;
			if(m_plansza(skad.wierszLiczba()-1+i*inkrWiersz,skad.kolumna()-1+i*inkrKol).czyMatka())
				m_iloscBialychMatek--;
		}
		if(m_plansza(skad.wierszLiczba()-1+i*inkrWiersz,skad.kolumna()-1+i*inkrKol).czyCzarne())
		{
			m_iloscCzarnych--;
			if(m_plansza(skad.wierszLiczba()-1+i*inkrWiersz,skad.kolumna()-1+i*inkrKol).czyMatka())
				m_iloscCzarnychMatek--;
		}
		m_plansza(skad.wierszLiczba()-1+i*inkrWiersz,skad.kolumna()-1+i*inkrKol).stan(Pole::STAN_POLA::PUSTE);
	}
	Pole::STAN_POLA stan=m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).stan();
	m_plansza(skad.wierszLiczba()-1,skad.kolumna()-1).stan(Pole::STAN_POLA::PUSTE);
	m_plansza(dokad.wierszLiczba()-1,dokad.kolumna()-1).stan(stan);
	return true;
}

std::ostream& operator<<(std::ostream& os, const PlanszaWarcaby& plansza)
{
	os<<plansza.m_plansza;
	return os;
}


std::list<Sciezka> PlanszaWarcaby::gdzieMozeBicPionek(const Wspolrzedna& skad) const
{
	int wiersz=static_cast<int>(skad.wierszLiczba())-1,
			kolumna=static_cast<int>(skad.kolumna())-1;
	std::list<Sciezka> sciezkiPojedyncze;
	if(!m_plansza(wiersz,kolumna).czyPionek())
		return sciezkiPojedyncze;
	bool czyBialy=m_plansza(wiersz,kolumna).czyBiale()?true:false;
	int wierszeBicia[]={wiersz-2,wiersz+2};
	int kolumnyBicia[]={kolumna-2,kolumna+2};
	if(czyBialy)
	{
		for(int i:wierszeBicia)
			for(int j:kolumnyBicia)
				if(i>=0 && i<rozmiar() && j>=0 && j<rozmiar())
				{
					Wspolrzedna dokad;
					dokad.wierszLiczba(i+1);
					dokad.kolumna(j+1);
					if(czyPoprawnyRuchBiciaPionek(skad,dokad))
					{
						Sciezka sciezka={skad,dokad};
						sciezkiPojedyncze.push_back(sciezka);
					}
				}
	}
	else
		for(int i:wierszeBicia)
			for(int j:kolumnyBicia)
				if(i>=0 && i<rozmiar() && j>=0 && j<rozmiar())
				{
					Wspolrzedna dokad;
					dokad.wierszLiczba(i+1);
					dokad.kolumna(j+1);
					if(czyPoprawnyRuchBiciaPionek(skad,dokad))
					{
						Sciezka sciezka={skad,dokad};
						sciezkiPojedyncze.push_back(sciezka);
					}
				}
	return sciezkiPojedyncze;
}

std::list<Sciezka> PlanszaWarcaby::gdzieMozeBicMatka(const Wspolrzedna& skad) const
{
	int wiersz=static_cast<int>(skad.wierszLiczba())-1,
			kolumna=static_cast<int>(skad.kolumna())-1;
	std::list<Sciezka> sciezkiPojedyncze;
	if(!m_plansza(wiersz,kolumna).czyMatka())
		return sciezkiPojedyncze;
	int inkrWierszTab[]={-1,1};
	int inkrKolumnaTab[]={-1,1};
	for(int inkrWiersz:inkrWierszTab)
		for(int inkrKolumna:inkrKolumnaTab)
		{
			int wierszAktywny=wiersz+2*inkrWiersz,
					kolumnaAktywna=kolumna+2*inkrKolumna;
			bool kontynuowac=true;
			while(wierszAktywny<rozmiar() && wierszAktywny>=0 &&
					kolumnaAktywna<rozmiar() && kolumnaAktywna>=0 && kontynuowac)
			{
				Wspolrzedna dokad;
				dokad.wierszLiczba(wierszAktywny+1);
				dokad.kolumna(kolumnaAktywna+1);
				if(czyPoprawnyRuchBiciaMatka(skad,dokad))
				{
					Sciezka sciezka={skad,dokad};
					sciezkiPojedyncze.push_back(sciezka);
				}
				else
					kontynuowac=false;
				wierszAktywny+=inkrWiersz;
				kolumnaAktywna+=inkrKolumna;
			}
		}
	return sciezkiPojedyncze;
}

std::list<Sciezka> PlanszaWarcaby::generujMozliweRuchyPionek(const Wspolrzedna& skad) const
{
	std::list<Sciezka> mozliweSciezki;
	unsigned int wiersz=skad.wierszLiczba()-1,
			kolumna=skad.kolumna()-1;
	if(!m_plansza(wiersz,kolumna).czyPionek())
		return mozliweSciezki;
	if(m_plansza(wiersz,kolumna).czyBiale())
	{
		Wspolrzedna dokad;
		if(kolumna+1<rozmiar() && kolumna+1>=0 && m_plansza(wiersz-1,kolumna+1).czyPuste())
		{
			dokad.wierszLiczba(wiersz);
			dokad.kolumna(kolumna+2);
			Sciezka sciezka={skad,dokad};
			mozliweSciezki.push_back(sciezka);
		}
		if(kolumna-1<rozmiar() && kolumna-1>=0 && m_plansza(wiersz-1,kolumna-1).czyPuste())
		{
			dokad.wierszLiczba(wiersz);
			dokad.kolumna(kolumna);
			Sciezka sciezka={skad,dokad};
			mozliweSciezki.push_back(sciezka);
		}
	}
	else
	{
		Wspolrzedna dokad;
		if(kolumna+1<rozmiar() && kolumna+1>=0 && m_plansza(wiersz+1,kolumna+1).czyPuste())
		{
			dokad.wierszLiczba(wiersz+2);
			dokad.kolumna(kolumna+2);
			Sciezka sciezka={skad,dokad};
			mozliweSciezki.push_back(sciezka);
		}
		if(kolumna-1<rozmiar() && kolumna-1>=0 && m_plansza(wiersz+1,kolumna-1).czyPuste())
		{
			dokad.wierszLiczba(wiersz+2);
			dokad.kolumna(kolumna);
			Sciezka sciezka={skad,dokad};
			mozliweSciezki.push_back(sciezka);
		}
	}
	std::list<Sciezka> listaSciezekBicia=generujMozliweRuchyBiciaPionek(skad);
	mozliweSciezki.splice(mozliweSciezki.end(),listaSciezekBicia);
	return mozliweSciezki;
}

std::list<Sciezka> PlanszaWarcaby::generujMozliweRuchyBiciaPionek(const Wspolrzedna& skad) const
{
	std::list<Sciezka> listaSciezekBicia=gdzieMozeBicPionek(skad); //pojedyncze bicie
	std::list<Sciezka> wynik;
	for(auto itSciezkaBicia=listaSciezekBicia.begin();itSciezkaBicia!=listaSciezekBicia.end(); // kombinacje kolejnych bić
			itSciezkaBicia++)
	{
		PlanszaWarcaby kopiaPlansza=*this;
		kopiaPlansza.wykonajBicie(skad,itSciezkaBicia->ostatniePole());
		std::list<Sciezka> listaSciezekBiciaRek=
				kopiaPlansza.generujMozliweRuchyBiciaPionek(itSciezkaBicia->ostatniePole());
		wynik.push_back(*itSciezkaBicia);
		for(auto itSciezkaBiciaRek=listaSciezekBiciaRek.begin();itSciezkaBiciaRek!=listaSciezekBiciaRek.end();
				itSciezkaBiciaRek++)
		{
			Sciezka sciezka=*itSciezkaBicia;
			sciezka.dolaczSciezke(*itSciezkaBiciaRek);
			wynik.push_back(sciezka);
		}
	}
	return wynik;
}

std::list<Sciezka> PlanszaWarcaby::generujMozliweRuchyMatka(const Wspolrzedna& skad) const
{
	int wiersz=skad.wierszLiczba()-1,
			kolumna=skad.kolumna()-1;
	std::list<Sciezka> mozliweSciezki;
	int inkrWierszTab[]={-1,1}, inkrKolumnaTab[]={-1,1};
	for(int inkrWiersz:inkrWierszTab)
		for(int inkrKolumna:inkrKolumnaTab)
		{
			int wierszAktywny=wiersz+inkrWiersz,
					kolumnaAktywna=kolumna+inkrKolumna;
			bool kontynuacja=true;
			while(wierszAktywny<rozmiar() && wierszAktywny>=0 &&
					kolumnaAktywna<rozmiar() && kolumnaAktywna>=0 && kontynuacja)
			{
				Wspolrzedna dokad;
				dokad.wierszLiczba(wierszAktywny+1);
				dokad.kolumna(kolumnaAktywna+1);
				if(czyRuchMozliwyMatka(skad,dokad))
				{
					Sciezka sciezka={skad,dokad};
					mozliweSciezki.push_back(sciezka);
				}
				else
					kontynuacja=false;
				wierszAktywny+=inkrWiersz;
				kolumnaAktywna+=inkrKolumna;
			}
		}
	std::list<Sciezka> listaSciezekBicia=generujMozliweRuchyBiciaMatka(skad);
	mozliweSciezki.splice(mozliweSciezki.end(),listaSciezekBicia);
	return mozliweSciezki;
}

std::list<Sciezka> PlanszaWarcaby::generujMozliweRuchyBiciaMatka(const Wspolrzedna& wspolrzedna) const
{
	std::list<Sciezka> listaSciezekBicia=gdzieMozeBicMatka(wspolrzedna); //pojedyncze bicie
	std::list<Sciezka> wynik;
	for(auto itSciezkaBicia=listaSciezekBicia.begin();itSciezkaBicia!=listaSciezekBicia.end(); // kombinacje kolejnych bić
			itSciezkaBicia++)
	{
		PlanszaWarcaby kopiaPlansza=*this;
		kopiaPlansza.wykonajBicie(wspolrzedna,itSciezkaBicia->ostatniePole());
		std::list<Sciezka> listaSciezekBiciaRek=
				kopiaPlansza.generujMozliweRuchyBiciaMatka(itSciezkaBicia->ostatniePole());
		wynik.push_back(*itSciezkaBicia);
		for(auto itSciezkaBiciaRek=listaSciezekBiciaRek.begin();itSciezkaBiciaRek!=listaSciezekBiciaRek.end();
				itSciezkaBiciaRek++)
		{
			Sciezka sciezka=*itSciezkaBicia;
			sciezka.dolaczSciezke(*itSciezkaBiciaRek);
			wynik.push_back(sciezka);
		}
	}
	return wynik;
}
