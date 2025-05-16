#pragma once

#include <iostream>
#include<vector>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "Prozor.h"
#include "Spaceship.h"
#include "Alien.h"
#include "Svijet.h"
#include "Bonus.h"
#include "Bullet.h"
#include "Shield.h"
#include "Textbox.h"

int brojac = 0;

class Igra {
public:
	Igra();
	~Igra();
	void obradiUlaz();
	void update();
	void renderiraj();

	//ako je broj zivota = 0
	void Reset();

	//vracamo aliene ako ih vise nema i igra se nastavlja s istim bodovima i zivotima
	void ZavrsenaRunda();

	void ProvjeraDogadjaja(); //ovo je kreirano s namjerom da u update bude samo ova funkcija pozvana kao ProvjeraDogadjaja()

	void ProvjeraPozicijeAliena(); //provjeravamo jesu li alieni dosli do stita i igraca

	void TryBonus(); //za generiranje bonus broda

	void TryAlienFire(); //za generiranje bulleta od aliena

	Prozor* dohvatiProzor() {
		return &p;
	}

	sf::Time protekloVrijeme(); //koristimo kako bi postigli "jednako igranje" na svim racunalima

	void restartSata();

	float DohvatiBrzinuIgre() { 
		return brzina;
	}
	

private:
	Prozor p;
	
	Svijet svijet;
	
	SpaceShip spaceship;
	
	std::vector<Alien> aliens;
	
	BonusBrod bb;
	
	std::vector<Shield> shields;

	TextBox textbox;

	sf::Clock sat;
	sf::Time vrijeme;

	float brzina = 200;
	
	sf::Music music;

};

void Igra::ZavrsenaRunda() {
	for (auto& bullet : spaceship.bullets) {
		bullet.PromijeniAktivan();
	}

	//micanje svih metaka od aliena
	for (auto& alien : aliens) {
		for (auto& bulletalien : alien.bulletsAlien) {
			bulletalien.PromijeniAktivan();
		}
	}

	Alien alien(sf::Vector2f(100.f, 100.f), 2);
	aliens = alien.PoljeAliena();

	bb.bonusbrod_vekt.clear();
}


//jednostavnija opcija restetiranja
void Igra::Reset() {
	
	for (auto& bullet : spaceship.bullets) {
		bullet.PromijeniAktivan();
	}
	
	//micanje svih metaka od aliena
	for (auto& alien : aliens) {
		for (auto& bulletalien : alien.bulletsAlien) {
			bulletalien.PromijeniAktivan();
		}
	}

	// Resetiranje broda
	spaceship.Reset();	

	// Resetiranje vanzemaljaca
	aliens.clear();
	Alien alien(sf::Vector2f(100.f, 100.f), 2);
	aliens = alien.PoljeAliena();

	// Resetiranje štitova
	shields.clear();
	Shield shield(sf::Vector2f(100.f, 100.f));
	shields = shield.PostaviShieldove();

	// Resetiranje bonusa
	bb.bonusbrod_vekt.clear();

	// Resetiranje tekstualnog okvira
	textbox.Azuriraj("SCORE 0", "LIVES 3");

}



void Igra::ProvjeraDogadjaja() {

	//provjera je li bullet od igraca pogodio aliena (cat)
	for (auto& bullet : spaceship.bullets) {
		for(auto it = aliens.begin(); it != aliens.end();){
		
			if (it->DohvatiHitPoint().intersects( bullet.DohvatiPolozaj())) {
				
				if (it->DohvatiVrstu() == 1) //Povecava bodove ! :)
					spaceship.PovecajBodove(40);
				if (it->DohvatiVrstu() == 2)
					spaceship.PovecajBodove(20);
				if (it->DohvatiVrstu() == 3) //najdoljniji su 3
					spaceship.PovecajBodove(10);

				it = aliens.erase(it);
				if (bullet.JelAktivan())
					bullet.PromijeniAktivan();

			}
			else {
				++it;
			}
		}
	}

	//provjera je li metak od aliena pogodio brod
	for (auto& alien : aliens) {
		for (auto& bulletalien : alien.bulletsAlien) {
			if (spaceship.DohvatiHitPoint().intersects(bulletalien.DohvatiPolozaj())) {
				//++brojac;
				spaceship.SmanjiBrZivota();
				bulletalien.PromijeniAktivan();
			}
		}
	}

	//dvije provjere je li alien pogodio stit i je li igrac pogodio stit
	if (shields.size() > 0) {
		for (auto& bullet : spaceship.bullets) {
			//iako je samo jedan spaceship.bullets u vektoru

			for (auto is = shields.begin(); is != shields.end();) {
				if (is->DohvatiHitPoint().intersects(bullet.DohvatiPolozaj())) {
					if (bullet.JelAktivan())
						bullet.PromijeniAktivan();
					//trebam maknut ako je brPogodjen = 8;
					is->PovecajPogodjen();
					if (is->DohvatiPogodjenBrPuta() == 8) //ako je stit na zadnjem hitu brisem ga!
					{
						is = shields.erase(is);
						break;
					}
					else
					{
						is->UpdateOstecenje();
						break; 
					}
				}
				else {
					++is;
				}
			}
		}
	}

	//trebam provjeru JE LI ALIEN POGODIO STIT
	if (shields.size() > 0) {
		for (auto& alien : aliens) {
			for (auto& bulletalien : alien.bulletsAlien) {
				for (auto il = shields.begin(); il != shields.end();) {
					if (il->DohvatiHitPoint().intersects(bulletalien.DohvatiPolozaj())) {
						bulletalien.PromijeniAktivan();

						il->PovecajPogodjen();
						if (il->DohvatiPogodjenBrPuta() == 8) {
							il = shields.erase(il);
							break;
						}
						else {
							il->UpdateOstecenje();
							break;
						}
					}
					else
					{
						++il;
					}

				}
			}
		}
	}

	//provjera izmedju dodatnog broda i igraca, je li pogodio bonus brod
	for (auto& bullet : spaceship.bullets) {
		for (auto& bonus : bb.bonusbrod_vekt) {
			if (bonus.DohvatiHitPoint().intersects(bullet.DohvatiPolozaj())) {
				bullet.PromijeniAktivan();
				bonus.PromijeniAktivan();
				spaceship.PovecajBodove(100);
				break;
			}
		}
	}
}


void Igra::ProvjeraPozicijeAliena() {
	//provjera jesu li alieni dosli do stita, ako da unisti stitove
	for (auto& alien : aliens) {
		for (auto& shield : shields) {
			if (alien.DohvatiHitPoint().top + alien.DohvatiHitPoint().height > shield.DohvatiHitPoint().top) {
				shields.clear();
				break;
			}
		}
	}
	//provjera jesu li alieni dosli do igracevog broda, ako da brZivota = 0 i igra zavrsava!
	for (auto& alien : aliens) {
		if (alien.DohvatiHitPoint().top + alien.DohvatiHitPoint().height > spaceship.DohvatiHitPoint().top) {
			spaceship.NemaViseZivota();
			break;
		}
	}
}

//funkcija koja isproba napraviti bonus brod, radi nasumican broj i ako pogodi stvara se bonus brod
//naravno to je slucaj ako bonus brod jos ne postoji
void Igra::TryBonus() {
	if (bb.bonusbrod_vekt.size() == 0) {
		std::random_device bb_nasumican;
		std::mt19937 gen(bb_nasumican());
		std::uniform_int_distribution<> distrib1(0, 1000);
		int nasumican_bb = distrib1(gen);
		if (nasumican_bb == 500)
		{
			bb.Start();
		}
	}	
}

//funkcija koja odredjuje pucanje aliena
void Igra::TryAlienFire() {
	//za alien bullete //smjestit u zasebnu funkciju radje zbog preglednosti!!!
	std::random_device nasum;
	std::mt19937 gen(nasum());
	std::uniform_int_distribution<> distrib1(0, 400);
	int nasumican = distrib1(gen);

	if (nasumican == 100 || nasumican == 200 || nasumican == 300) {
		std::random_device ab;
		std::mt19937 gen(ab());
		std::uniform_int_distribution<> distrib(0, aliens.size() - 1);
		int random_number = distrib(gen);
		aliens[random_number].FireAlien();
	}
}

//za satove
sf::Time Igra::protekloVrijeme() {
	return vrijeme;
}
void Igra::restartSata() {
	vrijeme = sat.restart();
}

void Igra::renderiraj() {
	p.ocisti();
	svijet.Renderiraj(&p);
	spaceship.Renderiraj(&p);

	for (auto& bonbrod : bb.bonusbrod_vekt) {
		bonbrod.Renderiraj(&p); // crtanje bonus broda
	}
	
	
	//za bullete
	for (auto& bullet : spaceship.bullets) {
		bullet.Redneriraj(&p);
	}

	for(auto& alien: aliens)
		alien.Renderiraj(&p);

	for (auto& shield : shields)
		shield.Renderiraj(&p);

	for (auto& alien : aliens)
		for (auto& bullet : alien.bulletsAlien)
			bullet.Redneriraj(&p);

	textbox.Renderiraj(&p);

	p.prikazi();
}

void Igra::update() {

	TryBonus();

	TryAlienFire();

	p.update();

	float vri = protekloVrijeme().asSeconds();

	//float vrijemeIteracije = 1.0f / spaceship.DohvatiBrzinu();

	svijet.UpdateBrod(spaceship, vri); //pazi ovo je samo je li dosao do ruba brod!

	//za updateanje bulleta
	for (auto& bullet : spaceship.bullets) {
		bullet.Update(vri);
	}

	//za updateanje bulleta aliena
	for (auto& alien : aliens)
		for (auto& bullet : alien.bulletsAlien) {
			bullet.UpdateAlien(vri);
		}


	for (auto& alien : aliens)
		alien.UpdateAlien(vri);

	//rješenje za micanje aliena prema dolje kada udare u zid :) 
	if (dolje == true) {
		for (auto& alien : aliens)
			alien.PomakDolje();
	}
	dolje = false; //globalno definirana varijabla "dolje" u Alien.h

	for (auto& bonbrod : bb.bonusbrod_vekt) {
		bonbrod.Update(vri); //micanje bonus broda
	}

	//brisanje bonus broda koji je izaso van ekrana
	bb.UnistiBB();

	//brisanje onih koji su izasli van ekrana od strane broda
	spaceship.IzbrisiPotrosene();

	//brise metke od aliena koji su izasli van ekrana!
	for (auto& alien : aliens)
		alien.IzbrisiPotroseneAlien();

	ProvjeraPozicijeAliena(); //alieni dosli do zida ili kraja

	ProvjeraDogadjaja(); //obradjuje pogotke izmedju aliena i broda, tj. svega na ekranu

	if (spaceship.DohvatiZivote() == 0) {
		//azuriramo highscore ako je postignut
		if (spaceship.DohvatiBodove() > textbox.loadHighSC("highscore.txt")) {
			int highscore = spaceship.DohvatiBodove();
			textbox.saveHighSC("highscore.txt", highscore);

			//prikazemo highscore
			textbox.AzurirajHighSC("HIGH SCORE " + std::to_string(textbox.loadHighSC("highscore.txt")));
		}

		Reset();
	}

	if (aliens.size() == 0) {
		ZavrsenaRunda();
	}
}

void Igra::obradiUlaz() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		spaceship.PostaviSmjer(Smjer::Lijevo);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		spaceship.PostaviSmjer(Smjer::Desno);
	}
	else {
		spaceship.PostaviSmjer(Smjer::Nema);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		spaceship.Fire();
	}
}


Igra::Igra() : p("Cat invaders", sf::Vector2u(1280, 800)), svijet(p.dohvatiVelicinu()), spaceship(&textbox), bb(sf::Vector2f(1280.f, 70.f))
{
	Alien alien(sf::Vector2f(100.f, 100.f),2);
	aliens = alien.PoljeAliena();

	Shield shield(sf::Vector2f(100.f, 100.f));
	shields = shield.PostaviShieldove();

	textbox.Postavi(30, 1100, sf::Vector2f(100, 10));

	music.openFromFile("music/free2use_retromusic.mp3");
	music.setLoop(true);
	music.play();

}

Igra::~Igra() {}