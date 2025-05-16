#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include "Prozor.h"
#include "Bullet.h"
#include "Textbox.h"

enum class Smjer { Nema, Lijevo, Desno };

class SpaceShip {
public:
	Smjer DohvatiSmjer() {
		return smjer;
	}
	int DohvatiZivote() {
		return brZivota;
	}
	
	int DohvatiBodove() {
		return bodovi;
	}
	bool JelIzgubio() {
		return izgubio;
	}
	float DohvatiBrzinu() {
		return pomak;
	}

	void Izgubio() {
		izgubio = true;
	}

	void PovecajBodove(int bod) {
		bodovi += bod;
		textbox->Azuriraj("SCORE " + std::to_string(DohvatiBodove()), "LIVES " + std::to_string(DohvatiZivote()));
	}

	void PostaviSmjer(Smjer s) {
		smjer = s;
	}

	void NemaViseZivota() {
		brZivota = 0;
		textbox->Azuriraj("SCORE " + std::to_string(DohvatiBodove()), "LIVES " + std::to_string(0));
	}

	//za svaki pogodak od aliena
	void SmanjiBrZivota() {
		--brZivota;
		textbox->Azuriraj("SCORE " + std::to_string(DohvatiBodove()), "LIVES " + std::to_string(DohvatiZivote()));
	} //ovo radi

	//konstruktor i destruktor
	//SpaceShip(int);
	SpaceShip(TextBox*);
	~SpaceShip();

	void Reset();
	void Korak(sf::Vector2u, float);
	void Pomakni(float);
	void ProvjeraSudara(sf::Vector2u); //za provjeru je li dotaknut zid
	void Renderiraj(Prozor*);

	//za pucanje
	void Fire();
	void IzbrisiPotrosene();
	std::vector<Bullet> bullets;

	sf::IntRect DohvatiHitPoint();

private:
	Smjer smjer; //za kretanje lijevo-desno ili stajanje na mjestu - nema
	int brZivota;
	int bodovi;
	bool izgubio;
	float pomak;

	sf::RectangleShape blok;
	sf::Texture brodTexture;
	sf::Sprite brodSprite;
	
	TextBox* textbox;

	float speed = 500; //za satove
};

SpaceShip::SpaceShip(TextBox* t) : textbox(t){
	blok.setSize(sf::Vector2f(80.f, 40.f));
	brodTexture.loadFromFile("slike/brod.png");
	blok.setTexture(&brodTexture);
	//brodSprite.setTexture(brodTexture);
	Reset();
}

void SpaceShip::Reset() {
	PostaviSmjer(Smjer::Nema);
	pomak = 0.5f;
	brZivota = 3;
	textbox->AzurirajLS("LAST SCORE " + std::to_string(DohvatiBodove()));
	bodovi = 0;
	izgubio = false;
	blok.setPosition(sf::Vector2f(600.f, 720.f));
}

void SpaceShip::Korak(sf::Vector2u velicinaProzora, float b) {
	if (smjer != Smjer::Nema) {
		Pomakni(b); //lijevo-desno
		ProvjeraSudara(velicinaProzora); // je li doso do zida
	}
}

void SpaceShip::Pomakni(float b) {
	if (smjer == Smjer::Lijevo) {
		blok.move(-pomak * b  * speed, 0);
	}
	else if (smjer == Smjer::Desno) {
		blok.move(pomak * b * speed, 0);
	}
}

void SpaceShip::ProvjeraSudara(sf::Vector2u velicinaProzora) {
	sf::Vector2f pozicija = blok.getPosition();
	sf::Vector2f velicina = blok.getSize();

	if (pozicija.x < 10) {
		blok.setPosition(10.f, pozicija.y);
	}
	else if (pozicija.x + velicina.x > velicinaProzora.x - 10) {
		blok.setPosition(velicinaProzora.x - velicina.x - 10, pozicija.y);
	}
}


//za crtanje broda na stranici
void SpaceShip::Renderiraj(Prozor* p) {
	p->crtaj(blok); //trebo bi se nacrtat spaceship kao pravokutnik
}

void SpaceShip::Fire() {
	if (bullets.size() == 0) {
		bullets.push_back(Bullet(sf::Vector2f(blok.getPosition().x + blok.getSize().x / 2 - 4, blok.getPosition().y)));
	}
}

//dakle pozicija gornjeg kuta broda + za sredinu - 4 jer je metak 8 sirok

void SpaceShip::IzbrisiPotrosene() {
	if (bullets.size() == 1)
		if (!bullets[0].JelAktivan()) {
			bullets.pop_back();
		}
}	

//za pogodak broda od strane aliena
sf::IntRect SpaceShip::DohvatiHitPoint() {
	sf::IntRect hitpoint;
	hitpoint.left = blok.getPosition().x;
	hitpoint.top = blok.getPosition().y;
	hitpoint.width = blok.getSize().x;
	hitpoint.height = blok.getSize().y;
	return hitpoint;
}

SpaceShip::~SpaceShip() {}