#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<SFML/Graphics.hpp>
#include "Prozor.h"

sf::Texture shieldTexture[7];

class Shield {
public:
	Shield(sf::Vector2f);
	~Shield();

	
	void PrikazStete();
	void UpdateOstecenje();
	void Renderiraj(Prozor*);

	void Update();

	sf::IntRect DohvatiHitPoint();

	std::vector<Shield> PostaviShieldove();

	/*sf::Sprite DohvatiSprite() {
		return shieldSprite;
	}*/

	int DohvatiPogodjenBrPuta() {
		return pogodjenBrPuta; //laksi pristup za UpdateOstecenje()
	}
	
	void PovecajPogodjen() {
		++pogodjenBrPuta;
	}
	sf::Sprite shieldSprite;
	

private:
	//sf::Vector2f shieldpoz;
	int pogodjenBrPuta;
	
	std::vector<Shield> shields; //4 stita su u tom polju
};

Shield::Shield(sf::Vector2f poz){
	//moram postaviti na poziciju, ukupno je 5 razmaka 176 * 5 = 880 + 400 = 1280 -> velicina ekrana (u vektoru ipak)
	// Uèitaj sve teksture
	for (int i = 0; i < 8; ++i) {
		if (!shieldTexture[i].loadFromFile("slike/savepoint_" + std::to_string(i + 1) + ".png")) {
			std::cerr << "Neuspjesno ucitavanje texture slike/savepoint_" << std::to_string(i + 1) << ".png" << std::endl;
		}
	}
	shieldSprite.setTexture(shieldTexture[0]);
	shieldSprite.setPosition(poz);
	pogodjenBrPuta = 0;

}

void Shield::PrikazStete(){}//unutar cu mijenjati prikaz

void Shield::Update(){}

std::vector<Shield> Shield::PostaviShieldove() {
	for (int i = 0; i < 4; i++) {
		float x = i * (176.f + 100.f) + 176.f;
		float y = 600.f;
		shields.push_back(Shield(sf::Vector2f(x, y)));
	}
	return shields;
}


void Shield::Renderiraj(Prozor* p) {
	p->crtaj(shieldSprite);
}

sf::IntRect Shield::DohvatiHitPoint() {
	sf::IntRect hitpoint;
	hitpoint.left = shieldSprite.getPosition().x;
	hitpoint.top = shieldSprite.getPosition().y;
	hitpoint.width = shieldSprite.getGlobalBounds().width;
	hitpoint.height = shieldSprite.getGlobalBounds().height;
	return hitpoint;
}

//svakim pogotkom se ostecenje updatea
void Shield::UpdateOstecenje() {
	if (DohvatiPogodjenBrPuta() < 8) {
		shieldSprite.setTexture(shieldTexture[DohvatiPogodjenBrPuta()]);
	}
}

Shield::~Shield(){}