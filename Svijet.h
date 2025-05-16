#pragma once

#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include "Prozor.h"
#include "Spaceship.h"

//ustvari je namijenjeno rubu ekrana i kretanju igracevog broda :)

class Svijet {
public:
	//konstruktor i destruktor
	Svijet(sf::Vector2u);
	~Svijet();

	//gledamo je li brod došao do ruba
	void UpdateBrod(SpaceShip&, float);

	//za obrub
	void Renderiraj(Prozor*);

private:
	sf::Vector2u velicinaProzora;

	sf::RectangleShape obrub;
};

Svijet::Svijet(sf::Vector2u vProzora) :
	velicinaProzora(vProzora) {
	obrub.setFillColor(sf::Color::Transparent);
	obrub.setSize(sf::Vector2f(vProzora.x, vProzora.y));
	std::cout << vProzora.x << "," << vProzora.y;
	obrub.setOutlineColor(sf::Color::Blue);
	obrub.setOutlineThickness(-10.f);
}

Svijet::~Svijet() {}

void Svijet::UpdateBrod(SpaceShip& igrac, float b) {
	igrac.Korak(velicinaProzora, b);
}

void Svijet::Renderiraj(Prozor* p) {
	p->crtaj(obrub);
}