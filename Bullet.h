#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include "Prozor.h"

//sf::Texture whiskasTexture;

class Bullet {
public:
	//Konstruktor i destruktor
	Bullet(sf::Vector2f);
	~Bullet();

	void Update(float); //od broda
	void UpdateAlien(float); //od aliena
	void Redneriraj(Prozor*);
	
	bool JelAktivan() {
		return active;
	}

	void PromijeniAktivan() {
		active = false;
	}

	sf::IntRect DohvatiPolozaj();

private:
	sf::RectangleShape bullet;
	sf::Vector2f pozicija;
	float bullet_speed = 0.8f; //za micanje bulleta

	//za micanje(kilanje) bullet objekta
	bool active;

	float speed = 500; //za satove
};

Bullet::Bullet(sf::Vector2f poz) {
	this->pozicija = poz;
	bullet.setSize(sf::Vector2f(6.f, 20.f));
	//bullet.setFillColor(sf::Color::Color(0,0,0,0));
	//whiskasTexture.loadFromFile("slike/whiskasbullet.png");
	active = true;
}

void Bullet::Redneriraj(Prozor* p) {
	if(active){
		bullet.setPosition(pozicija.x, pozicija.y);
		p->crtaj(bullet);
	}
}

//update odgovarajucih bulleta od igracevog broda
void Bullet::Update(float b) {
	bullet.setFillColor(sf::Color::Green);
	pozicija.y -= bullet_speed * speed * b;
	if (active) {
		if (pozicija.y > sf::VideoMode::getDesktopMode().height || pozicija.y < 0) {
			active = false;
		}
	}
}

//update odgovarajucih bulleta od aliena
void Bullet::UpdateAlien(float b) {
	//bullet.setTexture(&whiskasTexture);
	bullet.setFillColor(sf::Color::Red);
	pozicija.y += bullet_speed * speed * b;
	if (active) {
		if (pozicija.y > sf::VideoMode::getDesktopMode().height || pozicija.y > 790) {
			active = false;
		}
	}
}

sf::IntRect Bullet::DohvatiPolozaj() {
	sf::IntRect hitpoint;
	hitpoint.left = bullet.getPosition().x;
	hitpoint.top = bullet.getPosition().y;
	hitpoint.width = bullet.getSize().x;
	hitpoint.height = bullet.getSize().y;
	return hitpoint;
}

Bullet::~Bullet(){}
