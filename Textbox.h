#pragma once

#include<iostream>
#include<string>
#include <fstream>
#include<SFML/Graphics.hpp>
#include "Prozor.h"

//sve za textboxove, u ovoj .h datoteci je sadrzano i za last sc i high sc, te bodovi i zivoti

class TextBox {
public:
	TextBox();
	TextBox(int, float, sf::Vector2f);
	~TextBox();

	void Postavi(int, float, sf::Vector2f);

	void Azuriraj(std::string, std::string);

	void AzurirajLS(std::string);

	void Renderiraj(Prozor*);

	int loadHighSC(const std::string&);

	void saveHighSC(const std::string&, int);

	void AzurirajHighSC(std::string);

private:

	

	std::string bodovi;
	std::string zivoti;
	std::string lastsc;
	std::string highsc;
	sf::RectangleShape pozadina;
	sf::Font font;
	sf::Text zaBodove;
	sf::Text zaZivote;
	sf::Text zaLastScore;
	sf::Text zaHighScore;
	int highscore;
};


// Funkcija za uèitavanje highscore-a iz datoteke
int TextBox::loadHighSC(const std::string& filename) {
	std::ifstream file(filename);
	int highscore = 0;
	if (file.is_open()) {
		file >> highscore;
		file.close();
	}
	return highscore;
}

// Funkcija za spremanje highscore-a u datoteku
void TextBox::saveHighSC(const std::string& filename, int highscore) {
	std::ofstream file(filename);
	if (file.is_open()) {
		file << highscore;
		file.close();
	}
}


TextBox::TextBox(){
	Postavi(9, 200, sf::Vector2f(0, 0));
}

TextBox::TextBox(int velZn, float sirinaProz, sf::Vector2f pozProz) {
	Postavi(velZn, sirinaProz, pozProz);
}

TextBox::~TextBox() {}

void TextBox::Postavi(int velZn,
	float sirinaProz, sf::Vector2f pozPro) {	
	font.loadFromFile("slkscr.ttf");

	zaBodove.setFont(font);
	bodovi = "SCORE " + std::to_string(0);
	zaBodove.setString(bodovi);
	zaBodove.setCharacterSize(velZn);
	zaBodove.setFillColor(sf::Color::Green);
	zaBodove.setPosition(pozPro + sf::Vector2f(90.0f, 2.0f));

	zaZivote.setFont(font);
	zivoti = "LIVES " + std::to_string(3);
	zaZivote.setString(zivoti);
	zaZivote.setCharacterSize(velZn);
	zaZivote.setFillColor(sf::Color::Green);
	zaZivote.setPosition(pozPro + sf::Vector2f(900.0f, 2.0f));

	zaLastScore.setFont(font);
	lastsc = "LAST SCORE " + std::to_string(0);
	zaLastScore.setString(lastsc);
	zaLastScore.setCharacterSize(velZn);
	zaLastScore.setFillColor(sf::Color::White);
	zaLastScore.setPosition(pozPro + sf::Vector2f(40.0f, 750.0f));

	highscore = loadHighSC("highscore.txt");

	zaHighScore.setFont(font);
	highsc = "HIGH SCORE " + std::to_string(highscore);
	zaHighScore.setString(highsc);
	zaHighScore.setCharacterSize(velZn);
	zaHighScore.setFillColor(sf::Color::White);
	zaHighScore.setPosition(pozPro + sf::Vector2f(840.0f, 750.0f));


	pozadina.setSize(sf::Vector2f(
		sirinaProz, ((velZn * 1.2f))));
	pozadina.setFillColor(sf::Color(90, 90, 90, 90));
	pozadina.setPosition(pozPro);
}


void TextBox::Azuriraj(std::string string1, std::string string2) {
	zaBodove.setString(string1);
	zaZivote.setString(string2);
}

void TextBox::AzurirajLS(std::string string3) {
	zaLastScore.setString(string3);
}

void TextBox::AzurirajHighSC(std::string string4) {
	zaHighScore.setString(string4);
}

void TextBox::Renderiraj(Prozor* p) {
	p->crtaj(pozadina);
	p->crtaj(zaBodove);
	p->crtaj(zaZivote);
	p->crtaj(zaLastScore);
	p->crtaj(zaHighScore);
}

