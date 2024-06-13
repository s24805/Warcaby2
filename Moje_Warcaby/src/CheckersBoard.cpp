#include "../include/CheckersBoard.h"
#include "../include/GameState.h"
#include "../include/Texture.h"

// Konstruktor klasy CheckersBoard
CheckersBoard::CheckersBoard(){
    // Inicjalizacja wirtualnej planszy do gry w warcaby
    for (int y = 0; y < 8; y++) {
        vector<int> rowVector;
        for (int x = 0; x < 8; x++) {
            rowVector.push_back(0); // Dodanie pola z wartością 0 do każdego wiersza
        }
        virtualBoard.push_back(rowVector); // Dodanie wiersza do wirtualnej planszy
    }
    highLight = false;                     // Inicjalizacja zmiennej highLight na false
    highLightSelected.x = NULL;            // Inicjalizacja współrzędnej x wybranego pola na NULL
    highLightSelected.y = NULL;            // Inicjalizacja współrzędnej y wybranego pola na NULL
}

// Destruktor klasy CheckersBoard
CheckersBoard::~CheckersBoard(){
    virtualBoard.clear(); // Czyszczenie wirtualnej planszy
}

// Operator przesunięcia bitowego do wyświetlania planszy w konsoli
ostream & operator << (ostream & output, CheckersBoard & boardPassed) {
    output << "========" << endl;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if ((y + x) % 2 == 1) { // Sprawdza, czy pole jest ciemne
                output << boardPassed.virtualBoard[x][y]; // Wyświetla wartość pola
            } else {
                output << " "; // Wyświetla pustą przestrzeń dla jasnych pól
            }
        }
        output << endl; // Przechodzi do nowej linii po każdym wierszu
    }
    return output; // Zwraca strumień wyjściowy
}

// Metoda włączająca podświetlenie na określonym polu
void CheckersBoard::turnHighLightOn(int x, int y){
    highLight = true;                        // Ustawia zmienną highLight na true
    highLightSelected.x = x * 80;            // Ustawia współrzędną x podświetlonego pola
    highLightSelected.y = y * 80;            // Ustawia współrzędną y podświetlonego pola
}

// Metoda wyłączająca podświetlenie
void CheckersBoard::turnHighLightOff(){
    highLight = false;                       // Ustawia zmienną highLight na false
    validLocations.clear();                  // Czyści listę prawidłowych lokalizacji
}

// Metoda rysująca planszę do gry w warcaby
void CheckersBoard::drawBoard(){
    bool indent = false;                     // Flaga określająca, czy wiersz powinien być wcięty
    int xStart;
    SDL_SetRenderDrawColor(gRenderer, 0x86, 0x75, 0xB4, 0xFF); // Ustawienie koloru jasnego 
	//jasny kolor jest ustawiany w game state
    for (int y = 0; y < SCREEN_HEIGHT; y += BUTTON_HEIGHT) {
        if (indent) {
            xStart = BUTTON_WIDTH;           // Jeśli wiersz jest wcięty, zaczyna się od szerokości przycisku
            indent = false;                  // Zresetowanie flagi wcięcia
        } else {
            xStart = 0;                      // Jeśli wiersz nie jest wcięty, zaczyna się od 0
            indent = true;                   // Ustawienie flagi wcięcia
        }
        for (int x = xStart; x < SCREEN_WIDTH; x += 2 * BUTTON_WIDTH) {
            SDL_Rect redRect = {x, y, BUTTON_WIDTH, BUTTON_HEIGHT}; // Definicja prostokąta
            SDL_RenderFillRect(gRenderer, &redRect); // Wypełnienie prostokąta kolorem
        }
    }
    drawHighlights(); // Rysowanie podświetleń na planszy
}

// Metoda rysująca podświetlenia na planszy
void CheckersBoard::drawHighlights() {
    if (highLight) {
        SDL_SetRenderDrawColor(gRenderer, 0x32, 0x0D, 0xFA, 0xFF); // Ustawienie koloru na ciemny
        SDL_Rect outLine = {highLightSelected.x, highLightSelected.y, BUTTON_WIDTH, BUTTON_HEIGHT}; // Definicja obrysu podświetlenia
        SDL_RenderFillRect(gRenderer, &outLine); // Rysowanie obrysu

        SDL_SetRenderDrawColor(gRenderer, 0xF3, 0x07, 0xF0, 0xFF); // Ustawienie koloru na rozowy
        for (int indexOfValidMoves = 0; indexOfValidMoves < validLocations.size(); indexOfValidMoves++) {
            SDL_Rect outLineValid = {validLocations[indexOfValidMoves].x * 80, validLocations[indexOfValidMoves].y * 80, BUTTON_WIDTH, BUTTON_HEIGHT}; // Definicja obrysu prawidłowego ruchu
            SDL_RenderFillRect(gRenderer, &outLineValid); // Rysowanie obrysu prawidłowego ruchu
        }
    }
}

// Metoda rysująca pionki na planszy
void CheckersBoard::drawBoardPeices(int x, int y, Button *boardButton){
    switch (virtualBoard[x][y]) {
        case RED_PIECE:                    // Jeśli pole zawiera czerwony pionek
            currentSprite = RED_PIECE;
            boardButton->render(0);
            break;

        case BLACK_PIECE:                  // Jeśli pole zawiera czarny pionek
            currentSprite = BLACK_PIECE;
            boardButton->render(1);
            break;

        case RED_KING:                     // Jeśli pole zawiera czerwonego króla
            currentSprite = RED_KING;
            boardButton->render(2);
            break;

        case BLACK_KING:                   // Jeśli pole zawiera czarnego króla
            currentSprite = BLACK_KING;
            boardButton->render(3);
            break;

        default:                           // W przypadku domyślnym (puste pole)
            break;
    }
}
