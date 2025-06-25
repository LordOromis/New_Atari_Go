#pragma once

#include<iostream>
#include<string>
#include<vector>
#include <windows.h>
#include <cstdlib>  
#include <ctime>    

using namespace std;


#//Hilfsklasse um damit das Gamfield Vektorfield zu Befüllen
class Point {
public:
	//Zeigt womit das Feld gefüllt ist 'X' , 'O' oder für leere Felder '.'
	char type;
	//Wichtig für das Rekursive Aufrufen bei der CheckIfNeighbourAlive Funktion um sicherzustellen dass es nicht zu einer Endlosschleife kommt
	bool checked;
	//Speichert ob diese Zelle Lebendig oder Tot ist
	bool alive;
	/*setzt per default: type	  '.'
						 checked  false
						 alive	  false  */
	Point();

};


//Hauptklasse in der alle Punkte gespeichert werden und das gesammte Spiel abläuft
class GameField {

private:
	//Speichert alle Punkte in einem 2D Vektor
	vector<vector<Point>> listOfPoints;
	//Größe des Spielfeldes, immer quadratisch
	int size;

	//Füllt das Spieltfeld und initalisert die Punkte. In der Mitte werden vier Startsteine gesetzt
	void fillListOfPoints();

	//Zeigt die Punkte an (aber ohne Deko)
	void drawListOfAllPoint();

	//Checkt das Player Input im erlaubten Bereich ist
	bool inputCheck(int x, int y);										//hier die parameter geändert von string input, kürzer weiter hinte

	//Checkt ob der Zug gültig ist (Feld nicht belegt)
	bool checkIfValidMove(int x, int y);

	//*berprüft für einen Punkt ob er freien Nachbarn hat
	bool checkIfAlive(int x, int y);

	//makes a random Move
	void makeRandomMove(char type);

public:

	//Ruft FillListOfPoints auf und erstellt das Spielfeld
	GameField(int size);

	//Zeichnet das Spielfeld mit den Punkten und Deko
	void drawGame();

	//Playermove
	void inputMove(char type);

	//Checkt ob ein Punkt lebendig ist indem es Überprüft ob es einen lebendigen Nachbar gibt
	bool checkIfNeighbourAlive(int x, int y);

	//Checkt ob ein Stein geschlagen wurde
	void update();

	//gibt true zurück wenn ein Punkt nicht mehr alive ist. Ist Char spezeifsch um Situationen abzudecken in denen ein Suizidaler Stein zum Sieg führt
	bool gameOver(char type);

	//Computer macht Zug
	void computerMove(char type, int depth);

};

