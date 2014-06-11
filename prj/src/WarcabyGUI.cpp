/*
 * WarcabyGui.cpp
 *
 *  Created on: May 26, 2014
 *      Author: mochman
 */

#include "WarcabyGUI.hpp"
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>


WarcabyGUI::WarcabyGUI(unsigned int wysokosc)
    : Warcaby()
{
  m_glowneOkno = nullptr;
  m_wysokoscOkna = wysokosc;
  m_zainicjowano = false;
  m_sciezkaTeksturaDrewna = "data/tekstura_drewno.bmp";
  m_sciezkaPionekBialy = "data/bialy.bmp";
  m_sciezkaPionekCzarny = "data/czarny.bmp";
  m_sciezkaCzcionka = "data/czcionka.ttf";
  m_sciezkaDamkaBiala = "data/bialaDamka.bmp";
  m_sciezkaDamkaCzarna = "data/czarnaDamka.bmp";
  m_sciezkaZaznaczenie = "data/zaznaczenie.bmp";
  m_sciezkaPrzelacznik = "data/przelacznik.bmp";
  m_teksturaDrewna = nullptr;
  m_pionekBialy = nullptr;
  m_pionekCzarny = nullptr;
  m_damkaBiala = nullptr;
  m_damkaCzarna = nullptr;
  m_zaznaczenie = nullptr;
  m_przelacznik = nullptr;
}

void
WarcabyGUI::uruchom()
{
  inicjuj();
  m_glowneOkno = SDL_SetVideoMode(szerokoscOkna(),wysokoscOkna(),32,
      SDL_SWSURFACE);
  SDL_WM_SetCaption("Warcaby ver. 0.1","data/ikona.bmp");
  SDL_Event zdarzenie;
  m_czyKontynuowac = true;
  Sciezka sciezka;
  while (m_czyKontynuowac)
    {
      while (SDL_PollEvent(&zdarzenie))
        {
          switch (zdarzenie.type)
            {
            case SDL_QUIT:
              m_czyKontynuowac = false;
              break;
            case SDL_KEYDOWN:
              wcisnietoPrzycisk(zdarzenie);
              break;
            case SDL_MOUSEBUTTONDOWN:
              kliknietoPrzyciskMyszy(zdarzenie);
              break;
            }
        }
      if (czyRuchKomputera()) if (podpowiedzRuch(sciezka))
        wykonajRuch(sciezka.listaPol());
      else
        odpuscRuch();
      if (czyKoniec())
        {
          restartuj();
        }
      rysuj();
    }
  SDL_Quit();
}

void
WarcabyGUI::rysuj()
{
  rysujPlansze();
  rysujStatystyki();
  rysujPrzyciski();
  SDL_Flip(m_glowneOkno);
}

void
WarcabyGUI::rysujStatystyki()
{
  const unsigned int szerokoscRamki = 0.7 * m_wysokoscOkna
      / plansza().rozmiar(), rozmiarPlanszy = plansza().rozmiar(), rozmiarPola =
      (m_wysokoscOkna - 1.4 * m_wysokoscOkna / rozmiarPlanszy) / rozmiarPlanszy;
  std::ostringstream oss;
  oss << "Pionkow: " << plansza().iloscPionkowCzarnych();
  SDL_Color kolorCzcionki =
    { 255, 255, 255 };
  SDL_Surface* napis = TTF_RenderText_Blended(m_czcionka,oss.str().c_str(),
      kolorCzcionki);
  SDL_Rect obszarNapis =
    { rozmiarPlanszy * rozmiarPola + 2 * szerokoscRamki, szerokoscRamki,
        napis->w, napis->h };
  SDL_BlitSurface(napis,nullptr,m_glowneOkno,&obszarNapis);
  SDL_FreeSurface(napis);
  obszarNapis.y += 1.5 * napis->h;
  oss.str("");
  oss << "Matek: " << plansza().iloscMatekCzarnych();
  napis = TTF_RenderText_Blended(m_czcionka,oss.str().c_str(),kolorCzcionki);
  SDL_BlitSurface(napis,nullptr,m_glowneOkno,&obszarNapis);
  SDL_FreeSurface(napis);
  oss.str("");
  oss << "Pionkow: " << plansza().iloscPionkowBialych();
  obszarNapis.y = wysokoscOkna() - szerokoscRamki - 2.5 * napis->h;
  napis = TTF_RenderText_Blended(m_czcionka,oss.str().c_str(),kolorCzcionki);
  SDL_BlitSurface(napis,nullptr,m_glowneOkno,&obszarNapis);
  SDL_FreeSurface(napis);
  obszarNapis.y += 1.5 * napis->h;
  oss.str("");
  oss << "Matek: " << plansza().iloscMatekBialych();
  napis = TTF_RenderText_Blended(m_czcionka,oss.str().c_str(),kolorCzcionki);
  SDL_BlitSurface(napis,nullptr,m_glowneOkno,&obszarNapis);
  SDL_FreeSurface(napis);
  obszarNapis.x -= 1.5 * m_przelacznik->w;

}

void
WarcabyGUI::rysujPrzyciski()
{
  const unsigned int szerokoscRamki = 0.7 * m_wysokoscOkna
      / plansza().rozmiar(), rozmiarPlanszy = plansza().rozmiar(), rozmiarPola =
      (m_wysokoscOkna - 1.4 * m_wysokoscOkna / rozmiarPlanszy) / rozmiarPlanszy;
  SDL_Color kolorCzcionki =
    { 255, 255, 255 };
  SDL_Surface* napis = TTF_RenderText_Blended(m_czcionka,"Latwy",kolorCzcionki);
  SDL_Rect obszarNapis =
    { rozmiarPlanszy * rozmiarPola + 2 * szerokoscRamki, 3.5 * szerokoscRamki,
        napis->w, napis->h };
  SDL_Rect obszarPrzelacznik =
    { rozmiarPlanszy * rozmiarPola + 2 * szerokoscRamki
        - 1.5 * m_przelacznik->w, 0, m_przelacznik->w, m_przelacznik->h };
  SDL_BlitSurface(napis,nullptr,m_glowneOkno,&obszarNapis);
  if (poziomKomputera() == POZIOM_KOMPUTERA::LATWY)
    {
      obszarPrzelacznik.y = obszarNapis.y;
      SDL_BlitSurface(m_przelacznik,nullptr,m_glowneOkno,&obszarPrzelacznik);
    }
  SDL_FreeSurface(napis);
  obszarNapis.y += 0.5 * szerokoscRamki;
  napis = TTF_RenderText_Blended(m_czcionka,"Sredni",kolorCzcionki);
  SDL_BlitSurface(napis,nullptr,m_glowneOkno,&obszarNapis);
  if (poziomKomputera() == POZIOM_KOMPUTERA::SREDNI)
    {
      obszarPrzelacznik.y = obszarNapis.y;
      SDL_BlitSurface(m_przelacznik,nullptr,m_glowneOkno,&obszarPrzelacznik);
    }
  SDL_FreeSurface(napis);
  obszarNapis.y += 0.5 * szerokoscRamki;
  napis = TTF_RenderText_Blended(m_czcionka,"Trudny",kolorCzcionki);
  SDL_BlitSurface(napis,nullptr,m_glowneOkno,&obszarNapis);
  if (poziomKomputera() == POZIOM_KOMPUTERA::TRUDNY)
    {
      obszarPrzelacznik.y = obszarNapis.y;
      SDL_BlitSurface(m_przelacznik,nullptr,m_glowneOkno,&obszarPrzelacznik);
    }
  SDL_FreeSurface(napis);
  napis = TTF_RenderText_Blended(m_czcionka,"CPU vs CZL",kolorCzcionki);
  obszarNapis.y = wysokoscOkna() - 4 * szerokoscRamki;
  SDL_BlitSurface(napis,nullptr,m_glowneOkno,&obszarNapis);
  if (typGracza1() == TYP_GRACZA::CZLOWIEK
      && typGracza2() == TYP_GRACZA::KOMPUTER)
    {
      obszarPrzelacznik.y = obszarNapis.y;
      SDL_BlitSurface(m_przelacznik,nullptr,m_glowneOkno,&obszarPrzelacznik);
    }
  SDL_FreeSurface(napis);
  napis = TTF_RenderText_Blended(m_czcionka,"CZL vs CZL",kolorCzcionki);
  obszarNapis.y = wysokoscOkna() - 3.5 * szerokoscRamki;
  SDL_BlitSurface(napis,nullptr,m_glowneOkno,&obszarNapis);
  if (typGracza1() == TYP_GRACZA::CZLOWIEK
      && typGracza2() == TYP_GRACZA::CZLOWIEK)
    {
      obszarPrzelacznik.y = obszarNapis.y;
      SDL_BlitSurface(m_przelacznik,nullptr,m_glowneOkno,&obszarPrzelacznik);
    }
  SDL_FreeSurface(napis);
}

bool
WarcabyGUI::pobierzWspolrzedna(Wspolrzedna& wsp, unsigned int x, unsigned int y)
{
  const unsigned int rozmiarPlanszy = plansza().rozmiar(), rozmiarPola =
      (m_wysokoscOkna - 1.4 * m_wysokoscOkna / rozmiarPlanszy) / rozmiarPlanszy,
      szerokoscRamki = 0.7 * m_wysokoscOkna / rozmiarPlanszy;
  if (x < szerokoscRamki || y < szerokoscRamki) return false;
  x -= szerokoscRamki;
  y -= szerokoscRamki;
  x /= rozmiarPola;
  y /= rozmiarPola;
  if (x > rozmiarPlanszy - 1 || y > rozmiarPlanszy - 1) return false;
  wsp.wierszLiczba(y + 1);
  wsp.kolumna(x + 1);
  return true;
}

bool
WarcabyGUI::poprawnieWybranaWspolrzedna(const Wspolrzedna& wsp) const
{
  PlanszaWarcaby kopiaPlanszy = plansza();
  if (m_zaznaczonePola.size() > 0)
    {
      if (m_zaznaczonePola.size() > 1)
        {
          kopiaPlanszy.wykonajRuch(m_zaznaczonePola);
          return kopiaPlanszy.czyPoprawnyRuchBicia(m_zaznaczonePola.back(),wsp);
        }
      else
        return kopiaPlanszy.czyRuchMozliwy(m_zaznaczonePola.back(),wsp);
    }
  else
    {
      return (plansza()(wsp.wierszLiczba() - 1,wsp.kolumna() - 1).czyBiale()
          && czyjRuch() == Warcaby::KOLOR::BIALY)
          || (plansza()(wsp.wierszLiczba() - 1,wsp.kolumna() - 1).czyCzarne()
              && czyjRuch() == Warcaby::KOLOR::CZARNY);
    }
}

void
WarcabyGUI::rysujPlansze()
{
  SDL_Rect obszarTekstury =
    { 0, 0, szerokoscOkna(), wysokoscOkna() };
  SDL_BlitSurface(m_teksturaDrewna,&obszarTekstury,m_glowneOkno,nullptr);
  Uint32 kolorBialy = SDL_MapRGB(m_glowneOkno->format,255,255,255),
      kolorCzarny = SDL_MapRGB(m_glowneOkno->format,0,0,0);
  const unsigned int rozmiarPlanszy = plansza().rozmiar(), rozmiarPola =
      (m_wysokoscOkna - 1.4 * m_wysokoscOkna / rozmiarPlanszy) / rozmiarPlanszy,
      szerokoscRamki = 0.7 * m_wysokoscOkna / rozmiarPlanszy;
  SDL_Rect obszarRamki =
    { 0.6 * szerokoscRamki, 0.6 * szerokoscRamki, rozmiarPola * rozmiarPlanszy
        + 0.8 * szerokoscRamki, rozmiarPola * rozmiarPlanszy
        + 0.8 * szerokoscRamki };
  SDL_FillRect(m_glowneOkno,&obszarRamki,
      SDL_MapRGB(m_glowneOkno->format,140,140,140));
  bool pierwszyBialy = true;
  const SDL_Color kolorCzcionki =
    { 255, 255, 255 };
  for (unsigned int i = 0; i < rozmiarPlanszy; i++)
    {
      bool bialy;
      if (pierwszyBialy)
        bialy = true;
      else
        bialy = false;
      for (unsigned int j = 0; j < rozmiarPlanszy; j++)
        {
          SDL_Rect pole =
            { szerokoscRamki + j * rozmiarPola, szerokoscRamki
                + i * rozmiarPola, rozmiarPola, rozmiarPola };
          if (bialy)
            {
              SDL_FillRect(m_glowneOkno,&pole,kolorBialy);
            }
          else
            {
              SDL_FillRect(m_glowneOkno,&pole,kolorCzarny);
              if (plansza()(i,j).czyPionek())
                {
                  if (plansza()(i,j).czyBiale())
                    SDL_BlitSurface(m_pionekBialy,nullptr,m_glowneOkno,&pole);
                  else if (plansza()(i,j).czyCzarne())
                  SDL_BlitSurface(m_pionekCzarny,nullptr,m_glowneOkno,&pole);
                }
              else
                {
                  if (plansza()(i,j).czyBiale())
                    SDL_BlitSurface(m_damkaBiala,nullptr,m_glowneOkno,&pole);
                  else if (plansza()(i,j).czyCzarne())
                  SDL_BlitSurface(m_damkaCzarna,nullptr,m_glowneOkno,&pole);
                }
            }
          bialy = !bialy;
        }
      Wspolrzedna wspTemp;
      wspTemp.wierszLiczba(i + 1);
      char wiersz[] =
        { wspTemp.wiersz(), '\0' };
      SDL_Surface* napis = TTF_RenderText_Blended(m_czcionka,wiersz,
          kolorCzcionki);
      SDL_Rect obszarNapis =
        { 0.5 * szerokoscRamki + 0.5 * (0.5 * szerokoscRamki - napis->w),
            szerokoscRamki + i * rozmiarPola + 0.5 * (rozmiarPola - napis->h),
            napis->w, napis->h };
      SDL_BlitSurface(napis,nullptr,m_glowneOkno,&obszarNapis);
      SDL_FreeSurface(napis);
      pierwszyBialy = !pierwszyBialy;
    }
  for (unsigned int j = 0; j < rozmiarPlanszy; j++)
    {
      Wspolrzedna wspTemp;
      wspTemp.kolumna(j + 1);
      std::ostringstream str;
      str << wspTemp.kolumna();
      SDL_Surface* napis = TTF_RenderText_Blended(m_czcionka,str.str().c_str(),
          kolorCzcionki);
      SDL_Rect obszarNapis =
        { szerokoscRamki + j * rozmiarPola + 0.5 * (rozmiarPola - napis->w), 0.5
            * szerokoscRamki + 0.5 * (0.5 * szerokoscRamki - napis->h),
            napis->w, napis->h };
      SDL_BlitSurface(napis,nullptr,m_glowneOkno,&obszarNapis);
      SDL_FreeSurface(napis);
    }
  for (auto it : m_zaznaczonePola)
    {
      unsigned int y = szerokoscRamki + (it.wierszLiczba() - 1) * rozmiarPola,
          x = szerokoscRamki + (it.kolumna() - 1) * rozmiarPola;
      SDL_Rect obszarZaznaczenie
        { x, y, m_zaznaczenie->w, m_zaznaczenie->h };
      SDL_BlitSurface(m_zaznaczenie,nullptr,m_glowneOkno,&obszarZaznaczenie);
    }
}

void
WarcabyGUI::wcisnietoPrzycisk(SDL_Event& zdarzenie)
{
  if (zdarzenie.type == SDL_KEYDOWN) switch (zdarzenie.key.keysym.sym)
    {
    case SDLK_ESCAPE:
      m_czyKontynuowac = false;
      break;
    case SDLK_RETURN:
      wykonajRuch(m_zaznaczonePola);
      m_zaznaczonePola.clear();
    case SDLK_BACKSPACE:
      if (m_zaznaczonePola.size() > 0) m_zaznaczonePola.pop_back();
      break;
    case SDLK_r:
      restartuj();
      break;
    }
}

void
WarcabyGUI::kliknietoPrzyciskMyszy(SDL_Event& zdarzenie)
{
  if (zdarzenie.type == SDL_MOUSEBUTTONDOWN)
    {
      Wspolrzedna wspTemp;
      switch (zdarzenie.button.button)
        {
        case SDL_BUTTON_LEFT:
          if (pobierzWspolrzedna(wspTemp,zdarzenie.button.x,zdarzenie.button.y)
              && poprawnieWybranaWspolrzedna(wspTemp))
            m_zaznaczonePola.push_back(wspTemp);
          else
            przetworzKlikniecieOpcji(zdarzenie);
          break;
        case SDL_BUTTON_RIGHT:
          m_zaznaczonePola.clear();
          break;
        }
    }
}

void
WarcabyGUI::przetworzKlikniecieOpcji(SDL_Event& zdarzenie)
{
  const unsigned int rozmiarPlanszy = plansza().rozmiar(), rozmiarPola =
      (m_wysokoscOkna - 1.4 * m_wysokoscOkna / rozmiarPlanszy) / rozmiarPlanszy,
      szerokoscRamki = 0.7 * m_wysokoscOkna / rozmiarPlanszy;
  unsigned int x = zdarzenie.button.x, y = zdarzenie.button.y, xPrawegoBoku =
      rozmiarPola * rozmiarPlanszy + szerokoscRamki, rozmiarCzcionki = 0.3
      * (m_wysokoscOkna - 1.4 * m_wysokoscOkna / plansza().rozmiar())
      / plansza().rozmiar();
  if (x > xPrawegoBoku)
    {
      if (y > 3.5 * szerokoscRamki
          && y < 3.5 * szerokoscRamki + rozmiarCzcionki)
        poziomKomputera(POZIOM_KOMPUTERA::LATWY);
      else if (y > 4 * szerokoscRamki
          && y < 4 * szerokoscRamki + rozmiarCzcionki)
        poziomKomputera(POZIOM_KOMPUTERA::SREDNI);
      else if (y > 4.5 * szerokoscRamki
          && y < 4.5 * szerokoscRamki + rozmiarCzcionki)
        poziomKomputera(POZIOM_KOMPUTERA::TRUDNY);
      else if (y > wysokoscOkna() - 4 * szerokoscRamki
          && y < wysokoscOkna() - 4 * szerokoscRamki + rozmiarCzcionki)
        typGracza2(TYP_GRACZA::KOMPUTER);
      else if (y > wysokoscOkna() - 3.5 * szerokoscRamki
          && y < wysokoscOkna() - 3.5 * szerokoscRamki + rozmiarCzcionki)
        typGracza2(TYP_GRACZA::CZLOWIEK);
    }
}

void
WarcabyGUI::inicjuj()
{
  if (!m_zainicjowano)
    {
      zwolnijZasoby();
      SDL_Init(SDL_INIT_EVERYTHING);
      TTF_Init();
      srand(time(NULL));
      typGracza2(Warcaby::TYP_GRACZA::KOMPUTER);
      poziomKomputera(POZIOM_KOMPUTERA::SREDNI);
      m_zainicjowano = true;
      m_teksturaDrewna = SDL_LoadBMP(m_sciezkaTeksturaDrewna.c_str());
      m_pionekBialy = SDL_LoadBMP(m_sciezkaPionekBialy.c_str());
      m_pionekCzarny = SDL_LoadBMP(m_sciezkaPionekCzarny.c_str());
      m_czcionka = TTF_OpenFont(m_sciezkaCzcionka.c_str(),
          0.3 * (m_wysokoscOkna - 1.4 * m_wysokoscOkna / plansza().rozmiar())
              / plansza().rozmiar());
      m_damkaBiala = SDL_LoadBMP(m_sciezkaDamkaBiala.c_str());
      m_damkaCzarna = SDL_LoadBMP(m_sciezkaDamkaCzarna.c_str());
      m_zaznaczenie = SDL_LoadBMP(m_sciezkaZaznaczenie.c_str());
      Uint32 kolor = SDL_MapRGB(m_zaznaczenie->format,0,0,0);
      SDL_SetColorKey(m_zaznaczenie,SDL_SRCCOLORKEY,kolor);
      m_przelacznik = SDL_LoadBMP(m_sciezkaPrzelacznik.c_str());
      SDL_SetColorKey(m_przelacznik,SDL_SRCCOLORKEY,kolor);
    }
}

void WarcabyGUI::zwolnijZasoby()
{
  SDL_FreeSurface(m_teksturaDrewna);
  SDL_FreeSurface(m_pionekBialy);
  SDL_FreeSurface(m_pionekCzarny);
  SDL_FreeSurface(m_damkaBiala);
  SDL_FreeSurface(m_damkaCzarna);
  SDL_FreeSurface(m_zaznaczenie);
  SDL_FreeSurface(m_przelacznik);
  TTF_Quit();
  SDL_Quit();
}

WarcabyGUI::~WarcabyGUI()
{
  zwolnijZasoby();
}
