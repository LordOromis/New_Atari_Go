#include"Header.h"

void GameField::fillListOfPoints() {				//zuerst alle Punkte mit '.' füllen, dann Startpositionen eintragen
	vector<Point> points;
	for (int i = 0; i < size; i++) {
		points.push_back(Point());
	}
	for (int i = 0; i < size; i++) {
		listOfPoints.push_back(points);		//alle Punkte mit '.' füllen
	}

	//Startposition RICHTIG eintragen, bei asymmetrichen am rechten und unteren Rand
	if (size % 2 == 0) {
		listOfPoints[size / 2][size / 2].type = 'O';
		listOfPoints[size / 2 - 1][size / 2 - 1].type = 'O';
		listOfPoints[size / 2 - 1][size / 2].type = 'X';
		listOfPoints[size / 2][size / 2 - 1].type = 'X';
	}
	else if (size % 2 == 1) {
		listOfPoints[size / 2 + 1][size / 2 + 1].type = 'O';
		listOfPoints[size / 2][size / 2].type = 'O';
		listOfPoints[size / 2][size / 2 + 1].type = 'X';
		listOfPoints[size / 2 + 1][size / 2].type = 'X';
	}
}

GameField::GameField(int size) {
	this->size = size;
	fillListOfPoints();
}

void GameField::drawListOfAllPoint() {
	cout << ' ' << ' ';
	for (int i = 0; i < size; i++) {
		cout << i;
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << i << ' ';
		for (int j = 0; j < size; j++) {
			cout << listOfPoints[i][j].type;
		}
		cout << endl;
	}
	cout << endl;
}

bool GameField::inputCheck(int x, int y) {
	if (0 <= x && x < size && 0 <= y && y < size) {
		return true;
	}
	else {
		return false;
	}
}

bool GameField::checkIfValidMove(int x, int y) {			//Zuerst prüfen ob die Koordinaten gültig sind, dann ob der Stein auf dem Feld '.' ist
	if (listOfPoints[x][y].type == '.') {
		return true;
	}
	else {
		return false;
	}
}


void GameField::drawGame() {
	//mit Koordinaten und Deko
	drawListOfAllPoint();								//beinhaltet koordinaten, aber keine deko, wird auch schwierig, wegen der zeilen

}



void GameField::inputMove(char type) {
	//Fehlerschutz für Input
	string input;
	while (true) {
		cout << "Bitte geben Sie Reihe und Spalte des Feldes HINTEREINANDER ein:   " << endl;
		cin >> input;
		if (input.length() != 2) {														//prüft ob die Eingabe 2 Zeichen lang ist
			cout << "Ung" << '\x81' << "ltige Eingabe!    ";
			continue;
		}
		int x = input[0] - '0';
		int y = input[1] - '0';

		if (inputCheck(x, y)) {										//prüft ob Input gültig ist
			if (checkIfValidMove(x, y)) {							//prüft ob das Feld '.' ist
				listOfPoints[x][y].type = type;						//setzt den Stein auf das Feld
				break;
			}
			else {
				cout << "Dieses Feld ist belegt!    ";
			}
		}
		else {
			cout << "Ung" << '\x81' << "ltige Eingabe!    ";
		}
	}
}

//////////////////////////////////// Ab hier alles für update//////////////////////////////////////

void GameField::update() {

	//Setzt am Anfang alle Steine auf alive true und checked false, Generell werden nur Steine überprüft welche einen Typ anderen als '.' haben
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (listOfPoints[i][j].type != '.') {

				listOfPoints[i][j].alive = true;					//setzt alle Steine auf alive true
			}
			listOfPoints[i][j].checked = false;						//setzt alle Felder auf checked false
		}
	}
	//Alle Steine die keine Freiheitsgrade mehr haben, sollen auf alive = false gesetzt werden
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (listOfPoints[i][j].alive == true) {					//Überprüft ob ein Stein alive ist und setzt ihn auf false, wenn er keine freiheitsgrade mehr hat
				if (!checkIfAlive(i, j)) {
					listOfPoints[i][j].alive = false;
				}
			}
		}
	}

	//Jetzt wird für alle Steine die nicht lebendig sind überprüft, ob sie einen lebendigen Nachbarn haben
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (listOfPoints[i][j].alive == false and listOfPoints[i][j].type != '.') {
				if (checkIfNeighbourAlive(i, j)) {
					for (int i = 0; i < size; i++) {				//nach jeder überprüfung der einzelnen Steine, alle zurücksetzen, damit beim erstem aufruf von checkifneighbouralive wieder alle betrachtet werden
						for (int j = 0; j < size; j++) {			//also: für jeden stein neu alle anderen Steine überprüfen
							listOfPoints[i][j].checked = false;
						}
					}
					listOfPoints[i][j].alive = true;
				}
			}
		}
	}

}

//Endbedingung
bool  GameField::gameOver(char type) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {

			if (listOfPoints[i][j].type == type and listOfPoints[i][j].alive == false) {		//nimmt die überprüften alive werte und schaut ob steine des Typs nicht alive sind
				listOfPoints[i][j].type = '!';
				return true;
			}
		}

	}
	return false;													//wenn alle Steine des Typs alive sind, geht das Spiel weiter
}

//Überprüfen ob ein Stein alive ist bezüglich seiner Freiheitsgrade, alle Steine ohne Freiheitsgrad sind "tot"
bool GameField::checkIfAlive(int x, int y) {
	//Wenn der Stein keinen freien Nachbarn hat, wird er auf alive false gesetzt
	if (x - 1 >= 0 and listOfPoints[x - 1][y].type == '.') {
		listOfPoints[x - 1][y].alive = true;
		return true;
	}
	else if (x + 1 < size and listOfPoints[x + 1][y].type == '.') {
		listOfPoints[x + 1][y].alive = true;
		return true;
	}
	else if (y - 1 >= 0 and listOfPoints[x][y - 1].type == '.') {
		listOfPoints[x][y - 1].alive = true;
		return true;
	}
	else if (y + 1 < size and listOfPoints[x][y + 1].type == '.') {
		listOfPoints[x][y + 1].alive = true;
		return true;
	}
	return false;
}

//aufrufen der checkalive funktion für jeden nachbarn in bounds
bool GameField::checkIfNeighbourAlive(int x, int y) {

	if (x < 0 || x >= size || y < 0 || y >= size) {			//dafür zuerst hier schauen ob nachbar existiert
		return false;
	}
	if (listOfPoints[x][y].checked) {						//wurde der Stein schon überprüft -> false
		return false;
	}
	listOfPoints[x][y].checked = true;						//setzt den Stein auf checked true, damit er nicht nochmal überprüft wird			

	if (x + 1 < size and listOfPoints[x + 1][y].type == listOfPoints[x][y].type) {			//da der jeweils andere wert von x und y nicht verändert wird, muss auch nicht nach in bounds geprüft werden
		if (checkIfAlive(x + 1, y) || checkIfNeighbourAlive(x + 1, y)) {					//zuerst checkIfAlive aufrufen, weil zuerst die Freieheitsgrade betrachtet werden sollen
			listOfPoints[x + 1][y].alive = true;
			return true;
		}
	}
	if (x - 1 >= 0 and listOfPoints[x - 1][y].type == listOfPoints[x][y].type) {
		if (checkIfAlive(x - 1, y) || checkIfNeighbourAlive(x - 1, y)) {
			listOfPoints[x - 1][y].alive = true;
			return true;
		}
	}
	if (y + 1 < size and listOfPoints[x][y + 1].type == listOfPoints[x][y].type) {
		if (checkIfAlive(x, y + 1) || checkIfNeighbourAlive(x, y + 1)) {
			listOfPoints[x][y + 1].alive = true;
			return true;
		}
	}
	if (y - 1 >= 0 and listOfPoints[x][y - 1].type == listOfPoints[x][y].type) {
		if (checkIfAlive(x, y - 1) || checkIfNeighbourAlive(x, y - 1)) {
			listOfPoints[x][y - 1].alive = true;
			return true;
		}
	}
	return false;
}
