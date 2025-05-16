#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include "Prozor.h"

sf::Texture bbTexture;

class BonusBrod {
public:

	BonusBrod(sf::Vector2f);
	~BonusBrod();

	void Renderiraj(Prozor*);

	void Update(float);

	bool JelAktivan() {
		return active;
	}

	void PromijeniAktivan() {
		active = false;
	}

	void Start();

	void UnistiBB();

	sf::IntRect DohvatiHitPoint();

	std::vector<BonusBrod> bonusbrod_vekt;


private:
	sf::Vector2f pozicija; //biti ce van ekrana i ici ce do lijevog ruba onda ga tamo unistimo
	float brzina = -0.30f;;

	sf::Sprite bbSprite;
	bool active;

	float speed = 500; //za satove
};

BonusBrod::BonusBrod(sf::Vector2f poz)
{
	this->pozicija = poz;
	bbTexture.loadFromFile("slike/bonusbrod.png");
	bbSprite.setTexture(bbTexture);
	bbSprite.setPosition(poz);
	active = true;
}

BonusBrod::~BonusBrod() {}

//crtanje broda
void BonusBrod::Renderiraj(Prozor* p) {
	if (active) {
		bbSprite.setPosition(pozicija.x, pozicija.y);
		p->crtaj(bbSprite);
	}
}

//kretanje bonus broda
void BonusBrod::Update(float b) {
	pozicija.x += brzina * speed * b;
	if (active) {
		if (pozicija.x < 0) {
			active = false;
		}
	}
}

//stvaramo brod - dodajemo ga u vektor
void BonusBrod::Start() {
	if (bonusbrod_vekt.size() == 0) {
		bonusbrod_vekt.push_back(BonusBrod(sf::Vector2f(1280.f, 70.f)));
	}
}

//micemo bonus brod u slucaju da vise nije aktivan
void BonusBrod::UnistiBB() {
	if (bonusbrod_vekt.size() == 1)
		if (!bonusbrod_vekt[0].JelAktivan()) {
			bonusbrod_vekt.pop_back();
		}
}

sf::IntRect BonusBrod::DohvatiHitPoint() {
	sf::IntRect hitpoint;
	hitpoint.left = bbSprite.getPosition().x;
	hitpoint.top = bbSprite.getPosition().y;
	hitpoint.width = bbSprite.getGlobalBounds().width;
	hitpoint.height = bbSprite.getGlobalBounds().height;
	return hitpoint;
}
