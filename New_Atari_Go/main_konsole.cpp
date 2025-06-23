#include"Header.h"

//Hilfsfunktion um Spielfeld anzuzeugen
void showGame(GameField& gf) {
	system("cls");
	gf.drawGame();
}


int main() {
	//Seed f�r zufallszahlen
	srand(static_cast<unsigned int>(time(NULL)));



	//Game wird erstellt, Parameter size = Gr��e des Spielfeldes, start = 1 f�r Computer beginnt, 2 f�r Mensch beginnt, depth = wie viele Z�ge der Computer im Voraus berechnen soll
	int size = 6, start = 1, depth = 1000;

	GameField gf(size);


	//Game Loop
	while (true) {
		showGame(gf);


		if (start == 1) {
			gf.computerMove('X', depth);
		}
		else if (start == 2) {
			gf.inputMove('X');
		}

		showGame(gf);

		gf.update();

		//Damit suizidale Z�ge welche zum Sieg f�hren UND welche die verlieren abgedeckt sind diese doppel �berpr�fung
		if (gf.gameOver('O')) {
			showGame(gf);
			cout << "Player X wins!";
			system("pause");
			gf = GameField(size);
			showGame(gf);
		}
		else if (gf.gameOver('X')) {
			showGame(gf);
			cout << "Player O wins!";
			system("pause");
			gf = GameField(size);
			showGame(gf);
		}


		if (start == 1) {

			gf.inputMove('O');
		}
		else if (start == 2) {
			gf.computerMove('O', depth);
		}
		showGame(gf);
		gf.update();
		if (gf.gameOver('X')) {
			showGame(gf);
			cout << "Player O wins!";
			system("pause");
			gf = GameField(size);
			showGame(gf);
		}
		else if (gf.gameOver('O')) {
			showGame(gf);
			cout << "Player X wins!";
			system("pause");
			gf = GameField(size);
			showGame(gf);
		}

	}


	return 0;
}