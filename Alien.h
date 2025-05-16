#pragma once

#include<iostream>
#include<vector>
#include<random> // za nasumicne bullete vjv
#include<SFML/Graphics.hpp>
#include "Prozor.h"
#include "Bullet.h"

sf::Texture alienTexture[3]; //obavezno da se spritovi razlikuju!
static float pomak; //pomak mora biti globalna varijabla tako da bi se macke (alieni) kretale paralelno
bool dolje = false; //za pomak dolje

class Alien {
public:

	
	//konstruktor i destruktor
	Alien(sf::Vector2f, int); //argument za poziciju aliena, i koja je vrsta
	~Alien();
	

	std::vector<Alien> PoljeAliena();
	void Renderiraj(Prozor*);
	void PomakAliena(float); //za micanje aliena 
	void UpdateAlien(float); //biti ce za brisanje i ostale stvari
	void DotaknuoZid(); //u slucaju da se udare sa zidom idu u drugu stranu
	void PomakDolje(); //pomice aliene prema dolje kada dotaknu zid
	

	int DohvatiVrstu(){
		return vrsta;
	}

	//za pucanje kod Aliena
	void FireAlien();
	void IzbrisiPotroseneAlien();
	std::vector<Bullet> bulletsAlien;

	sf::IntRect DohvatiHitPoint();

private:
	int vrsta; //postoje 3 vrste (u nas ce biti to cat1, cat2, cat3 - 1, 2, 3)
	sf::Vector2f pozicija;
	std::vector<Alien> aliens;
	sf::Sprite alienSprite;

	float speed = 500; //za satove
};

//KONSTRUKTOR ZA ALIENA
Alien::Alien(sf::Vector2f poz, int v) {
	//this->pozicija = poz;
	this->vrsta = v;
	switch (vrsta) {
	case 1:
		alienTexture[0].loadFromFile("slike/cat1.png");
		alienSprite.setTexture(alienTexture[0]);
		alienSprite.setPosition(poz);
		pomak = -0.10f;
		break;
	case 2:
		alienTexture[1].loadFromFile("slike/cat2.png");
		alienSprite.setTexture(alienTexture[1]);
		alienSprite.setPosition(poz);
		pomak = -0.10f;
		break;
	case 3:
		alienTexture[2].loadFromFile("slike/cat3.png");
		alienSprite.setTexture(alienTexture[2]);
		alienSprite.setPosition(poz);
		pomak = -0.10f;
		break;
	default:	
		break;
	}
	
}

//DESTRUKTOR
Alien::~Alien() {}

//STVARAMO ALIENE U 5 REDAKA I 11 STUPACA
std::vector<Alien> Alien::PoljeAliena() {
	int vrsta_aliena;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 11; j++) {
			if (i == 0) {
				vrsta_aliena = 1;
			}
			else if (i == 1 || i == 2) {
				vrsta_aliena = 2;
			}
			else {
				vrsta_aliena = 3;
			}
			//izracunajmo pozicije
			float x = j * 66.f + 300.f;
			float y = i * 66.f + 120.f;
			aliens.push_back(Alien(sf::Vector2f(x, y), vrsta_aliena));
		}
	}
	return aliens;
}


//PRIKAZ ALIENA NA EKRANU
void Alien::Renderiraj(Prozor* p){
	p->crtaj(alienSprite);
}

void Alien::PomakAliena(float b) {
	alienSprite.move(pomak * b * speed, 0);
}

void Alien::PomakDolje() {
	alienSprite.move(0, 30.f);
}

void Alien::DotaknuoZid() {
		if (alienSprite.getPosition().x + 60.f > 1270.f) {
			pomak = -0.10f;
			dolje = true;
		}
		if (alienSprite.getPosition().x < 10.f) {
			pomak = 0.10f;
			dolje = true;
		}
}

void Alien::UpdateAlien(float b) {
	PomakAliena(b);
	DotaknuoZid();
}

void Alien::FireAlien() {
		bulletsAlien.push_back(Bullet(sf::Vector2f(alienSprite.getPosition().x + alienSprite.getGlobalBounds().width/2 - 3, alienSprite.getPosition().y + alienSprite.getGlobalBounds().height)));
}

void Alien::IzbrisiPotroseneAlien() {
	for (auto it = bulletsAlien.begin(); it != bulletsAlien.end();) {
		if (!it->JelAktivan()) {
			it = bulletsAlien.erase(it);
		}
		else
			++it;
	}
}

sf::IntRect Alien::DohvatiHitPoint() {
	sf::IntRect hitpoint;
	hitpoint.left = alienSprite.getPosition().x;
	hitpoint.top = alienSprite.getPosition().y;
	hitpoint.width = alienSprite.getGlobalBounds().width;
	hitpoint.height = alienSprite.getGlobalBounds().height;
	return hitpoint;
}