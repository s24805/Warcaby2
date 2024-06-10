#include "../include/Piece.h"

// Definicja ruchów dla króla (może poruszać się w 4 kierunkach)
Directions kingMoves[4] = {LEFT, RIGHT, BACK_LEFT, BACK_RIGHT};

// Definicja ruchów dla zwykłego pionka (może poruszać się w 2 kierunkach)
Directions pieceMoves[2] = {LEFT, RIGHT};

// Konstruktor klasy Piece
Piece::Piece() {
    x = 0; // Inicjalizacja współrzędnej x na 0
    y = 0; // Inicjalizacja współrzędnej y na 0
    king = false; // Inicjalizacja pionka jako nie-króla
}

// Metoda ustawiająca współrzędne pionka
void Piece::setPoint(int xLocation, int yLocation) {
    x = xLocation; // Ustawienie współrzędnej x
    y = yLocation; // Ustawienie współrzędnej y
}

// Metoda sprawdzająca, czy pionek jest królem
bool Piece::isKing() {
    return king; // Zwraca wartość flagi king
}

// Metoda, która zamienia pionek w króla
void Piece::makeKing() {
    king = true; // Ustawienie flagi king na true
}


