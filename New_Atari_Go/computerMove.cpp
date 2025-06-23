#pragma once
#include"Header.h"

//Hilfsklasse um mit einem 1D Vektor alle Z�ge und ihren Scores abzuspeichern
class simulation {
public:
	int y, x;
	int score;
	simulation(int y, int x) {
		this->y = y;
		this->x = x;
		this->score = 0;
	};
};

//Hilfsfunktion welche einen random Zug macht
void GameField::makeRandomMove(char type) {
	while (true) {
		int x = rand() % size;
		int y = rand() % size;

		if (listOfPoints[x][y].type == '.') {
			listOfPoints[x][y].type = type;
			break;
		}
	}
}

void GameField::computerMove(char type, int depth) {

	makeRandomMove(type);

	//Speichert alle m�glichen Z�ge und deren Scores
	vector<simulation> possibleMoves;


	//Jetzt wird f�r jeden m�glichen Zug depth-Anzahl Simulationen durchgef�hrt

	//finde in possibleMoves den Zug mit dem h�chsten Score

}

