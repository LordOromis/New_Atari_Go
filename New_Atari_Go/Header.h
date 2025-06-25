#pragma once

#include<iostream>
#include<string>
#include<vector>
#include <windows.h>
#include <cstdlib>  
#include <ctime>    

using namespace std;


#//Hilfsklasse um damit das Gamfield Vektorfield zu Bef�llen
class Point {
public:
	//Zeigt womit das Feld gef�llt ist 'X' , 'O' oder f�r leere Felder '.'
	char type;
	//Wichtig f�r das Rekursive Aufrufen bei der CheckIfNeighbourAlive Funktion um sicherzustellen dass es nicht zu einer Endlosschleife kommt
	bool checked;
	//Speichert ob diese Zelle Lebendig oder Tot ist
	bool alive;
	/*setzt per default: type	  '.'
						 checked  false
						 alive	  false  */
	Point();

};


//Hauptklasse in der alle Punkte gespeichert werden und das gesammte Spiel abl�uft
class GameField {

private:
	//Speichert alle Punkte in einem 2D Vektor
	vector<vector<Point>> listOfPoints;
	//Gr��e des Spielfeldes, immer quadratisch
	int size;

	//F�llt das Spieltfeld und initalisert die Punkte. In der Mitte werden vier Startsteine gesetzt
	void fillListOfPoints();

	//Zeigt die Punkte an (aber ohne Deko)
	void drawListOfAllPoint();

	//Checkt das Player Input im erlaubten Bereich ist
	bool inputCheck(int x, int y);										//hier die parameter ge�ndert von string input, k�rzer weiter hinte

	//Checkt ob der Zug g�ltig ist (Feld nicht belegt)
	bool checkIfValidMove(int x, int y);

	//*berpr�ft f�r einen Punkt ob er freien Nachbarn hat
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

	//Checkt ob ein Punkt lebendig ist indem es �berpr�ft ob es einen lebendigen Nachbar gibt
	bool checkIfNeighbourAlive(int x, int y);

	//Checkt ob ein Stein geschlagen wurde
	void update();

	//gibt true zur�ck wenn ein Punkt nicht mehr alive ist. Ist Char spezeifsch um Situationen abzudecken in denen ein Suizidaler Stein zum Sieg f�hrt
	bool gameOver(char type);

	//Computer macht Zug
	void computerMove(char type, int depth);

};

