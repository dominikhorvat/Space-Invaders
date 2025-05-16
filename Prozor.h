#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Prozor {
public:
	Prozor();
	Prozor(const std::string&, const sf::Vector2u&);
	void prebaciNaCijeli();
	void ocisti();
	void crtaj(sf::Drawable&);
	void prikazi();
	void update();
	~Prozor();
	bool jelGotov() {
		return gotov;
	}
	bool jelCijeli() {
		return cijeliZaslon;
	}
	sf::Vector2u dohvatiVelicinu() {
		return velicina;
	}


	//za postavljanje backgrounda
	void postaviBackground(const std::string&);
	void crtajPozadinu();

private:
	void Stvori();
	void Unisti();
	void Postavi(const std::string&, const sf::Vector2u&);
	sf::RenderWindow prozor;
	sf::Vector2u velicina;
	std::string naslov;
	bool gotov;
	bool cijeliZaslon;

	sf::Texture backgroundTexture; //tekstura pozadine
	sf::Sprite backgroundSprite;    //sprite pozadine
};



void Prozor::update() {
	sf::Event event;
	while (prozor.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			gotov = true;
		else if (event.type == sf::Event::KeyPressed
			&& event.key.code == sf::Keyboard::F5)
			prebaciNaCijeli();
	}
}

void Prozor::prebaciNaCijeli() {
	cijeliZaslon = !cijeliZaslon;
	Unisti();
	Stvori();
}

Prozor::Prozor(const std::string& n,
	const sf::Vector2u& v) {
	Postavi(n, v);
}

Prozor::Prozor() {
	Postavi("Prozor", sf::Vector2u(640, 480));
}

Prozor::~Prozor() {
	Unisti();
}

void Prozor::Postavi(const std::string& n,
	const sf::Vector2u& v) {
	naslov = n;
	velicina = v;
	cijeliZaslon = false;
	gotov = false;
	//otvaranje prozora nakon popunjavanja postavki
	Stvori();
}

void Prozor::Stvori() {
	auto stil = (cijeliZaslon ? sf::Style::Fullscreen
		: sf::Style::Default);
	prozor.create(sf::VideoMode(velicina.x,
		velicina.y, 32), naslov, stil);

	//ovdje je postavljen background - tako da se slika ne ucitava iznova svaki put i da ne "laga" igrica
	postaviBackground("slike/backgroundfree.png");
	
	prozor.setFramerateLimit(200);
}

void Prozor::Unisti() {
	prozor.close();
}

void Prozor::ocisti() {
	//prozor.clear(sf::Color(0, 0, 0, 255));
	
	crtajPozadinu(); 
}

void Prozor::crtaj(sf::Drawable& d) {
	prozor.draw(d);
}

void Prozor::prikazi() {
	prozor.display();
}

void Prozor::postaviBackground(const std::string& putanja) {
	if (backgroundTexture.loadFromFile("slike/backgroundfree.png")) {
		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setScale(
			float(velicina.x) / backgroundTexture.getSize().x,
			float(velicina.y) / backgroundTexture.getSize().y);
	}
	else {
		std::cerr << "Ne mogu ucitati pozadinsku sliku: " << putanja << std::endl;
	}
}

void Prozor::crtajPozadinu() {
	if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) {
		prozor.draw(backgroundSprite);
	}
}

