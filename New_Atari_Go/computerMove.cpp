#pragma once
#include"Header.h"

//Hilfsklasse um mit einem 1D Vektor alle Z�ge und ihren Scores abzuspeichern
class simulation {
public:
	int x, y;
	int score;
	simulation(int x, int y) {
		this->x = x;
		this->y = y;
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

	//makeRandomMove(type);

	//Speichert alle m�glichen Z�ge und deren Scores
	vector<simulation> possibleMoves;
	int index = 0;


	//Jetzt wird f�r jeden m�glichen Zug depth-Anzahl Simulationen durchgef�hrt

	for (int i = 0; i < size; i++) {						//F�r alle m�glichen Z�ge, Ausf�hren der Simulationen
		for (int j = 0; j < size; j++) {
			if (checkIfValidMove(i, j)) {
				possibleMoves.push_back(simulation(i, j));
				index++;

				int iteration = 0;

				listOfPoints[i][j].type = type;

				while (iteration < depth) {					//Ausf�hren der Simulationen, solange noch nicht die gew�nschte Tiefe erreicht ist

					while (true) {							//Hauptschleife f�r Weiterspielen ohne Spielereingabe

						update();

						if (type == 'O') {					//�berpr�fen, ob jemand gewonnen hat
							if (gameOver('O')) {			
								possibleMoves[index].score++;					//Wenn der Computer gewinnt, Score erh�hen
								break;
							}

							makeRandomMove('X');			//Anschlie�end Zug f�r andere Farbe machen
						}
						else if (type == 'X') {
							if (gameOver('O')) {			
								break;
							}

							makeRandomMove('O');
						}

						update();

						if (type == 'O') {					
							if (gameOver('O')) {			
								possibleMoves[index].score++;					
								break;
							}

							makeRandomMove('O');			//Hier Zug f�r Computer machen
						}
						else if (type == 'X') {
							if (gameOver('O')) {			
								break;
							}

							makeRandomMove('X');
						}

					}

					iteration++;
				}
			}
		}
	}


	//finde in possibleMoves den Zug mit dem h�chsten Score

	for (int i = 0; i < possibleMoves.size(); i++) {
		if (possibleMoves[i].score > possibleMoves[0].score) {			//Wenn der Score der Simulation h�her ist, als der der ersten, tauschen
		swap(possibleMoves[0], possibleMoves[i]);
		}
	}

	listOfPoints[possibleMoves[0].x][possibleMoves[0].y].type = type;		//Setze den Zug mit dem h�chsten Score auf das Spielfeld

}

