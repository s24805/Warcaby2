#include "../include/RealPlayer.h"
#include "../include/GameState.h"

// Konstruktor klasy RealPlayer, dziedziczący po klasie Player
RealPlayer::RealPlayer(bool topSideOfBoard, CheckersBoard *board, Button *buttons) : Player(topSideOfBoard, board, buttons){
    selectingState = false; // Inicjalizacja stanu wyboru pionka
}

// Destruktor klasy RealPlayer
RealPlayer::~RealPlayer(){
    delete Board; // Usunięcie planszy z pamięci
    Board = NULL; // Ustawienie wskaźnika na planszę na NULL
    delete boardButtons; // Usunięcie przycisków z pamięci
    boardButtons = NULL; // Ustawienie wskaźnika na przyciski na NULL
}

// Metoda wykonująca ruch gracza
bool RealPlayer::makeMove(SDL_Event* event){

    if (event->type == SDL_MOUSEBUTTONDOWN) {
        
        // Sprawdzanie stanu wyboru pionka //
        if (!selectingState) {
            killWasMade = false; // Resetowanie flagi zabójstwa
            for (int index = 0; index < TOTAL_BUTTONS; index++) {
                if (boardButtons[index].insideButton(BUTTON_WIDTH, BUTTON_HEIGHT)) {
                    // Gracz wybiera pionek do ruchu //
                    selectPiece(boardButtons[index].getButtonPointX() / 80, boardButtons[index].getButtonPointY() / 80);
                    break;
                }
            }
        }
        // Wybór miejsca, do którego pionek ma się przemieścić //
        else {
            for (int index = 0; index < TOTAL_BUTTONS; index++) {
                if (boardButtons[index].insideButton(BUTTON_WIDTH, BUTTON_HEIGHT)) {
                    // Gracz wybiera miejsce, do którego pionek ma się przemieścić //
                    
                    if (selectedLocationIsValid(currentIndex, boardButtons[index].getButtonPointX() / 80, boardButtons[index].getButtonPointY() / 80, false)) {
                        movePiece(Board->virtualBoard, team, currentIndex, boardButtons[index].getButtonPointX() / 80, boardButtons[index].getButtonPointY() / 80);
                        Board->turnHighLightOff(); // Wyłączenie podświetlenia ruchu
                        
                        if (killWasMade) {
                            selectPiece(team[killerPeiceIndex].x, team[killerPeiceIndex].y);
                            if (Board->validLocations.size() == 0) {
                                selectingState = false;
                                Board->turnHighLightOff();
                                return true;
                            }
                        }
                        if (!killWasMade) {
                            return true;
                        }
                    }
                    else {
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

// Metoda wybierająca pionek do ruchu
void RealPlayer::selectPiece(int x, int y){
    // WYBÓR PIONKA //
    // Gdy pionek nie został jeszcze wybrany, a aktualnie wybrany przycisk nie zawiera pionka //
    if (sameTeam(Board->virtualBoard[x][y], TEAM_NUMBER)) {
        currentIndex = pieceTeamIndexByXY(x, y); // Ustawienie aktualnego indeksu pionka
        Board->turnHighLightOn(x, y); // Włączenie podświetlenia dla wybranego pionka
        highlightValidMoves(); // Podświetlenie możliwych ruchów
        selectingState = true; // Zmiana stanu wyboru pionka
        cout << "Selected piece is:\t(" << x << ", " << y << ")" << endl;
    }
    else {
        cout << "Piece isn't apart of your team" << endl;
    }
}

// Metoda sprawdzająca, czy wybrana lokalizacja jest prawidłowa
bool RealPlayer::selectedLocationIsValid(int currentIndex, int x, int y, bool forHighlight) {
    bool locationIsValid = false;
    if (Board->virtualBoard[x][y] == EMPTY_PIECE) {

        // przypadek 1: ruch w kwadracie 3x3 centrowanym na pochodzeniu //
        if (abs(x - team[currentIndex].x) == 1 && abs(y - team[currentIndex].y) == 1 && !killWasMade) {

            // przypadek 1.1: pionek jest królem //
            if (team[currentIndex].isKing()) {
                locationIsValid = true;
            }

            // przypadek 1.2: pionek nie jest królem //
            else if (y - team[currentIndex].y == ONE) {
                locationIsValid = true;
            }
        }

        // przypadek 2: ruch w kwadracie 5x5 centrowanym na pochodzeniu, aby zabić pionek //
        else if (abs(x - team[currentIndex].x) == 2 && abs(y - team[currentIndex].y) == 2 && sameTeam(Board->virtualBoard[(x + team[currentIndex].x) / 2][(y + team[currentIndex].y) / 2], ENEMY_TEAM_NUMBER)) {

            // przypadek 2.1: pionek jest królem //
            if (team[currentIndex].isKing()) {
                locationIsValid = true;
            }

            // przypadek 2.2: pionek nie jest królem //
            else if (y - team[currentIndex].y == 2 * ONE) {
                locationIsValid = true;
            }
        }
    }
    // przypadek 3: wybór własnego pionka w celu zmiany wyboru //
    else if (sameTeam(Board->virtualBoard[x][y], TEAM_NUMBER) && !forHighlight && !killWasMade) {
        Board->turnHighLightOff();
        selectPiece(x, y); // Zmiana wybranego pionka
        locationIsValid = false;
    }
    if (!locationIsValid && !forHighlight) {
        cout << "can't move here" << endl;
    }
    else if (!killWasMade) {
        selectingState = false;
    }
    return locationIsValid;
}

// Metoda podświetlająca możliwe ruchy
void RealPlayer::highlightValidMoves() {
    int x, y;
    for (int i = -2; i <= 2; i++) {
        x = team[currentIndex].x + i;
        for (int j = -2; j <= 2; j++) {
            y = team[currentIndex].y + j;
            
            if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                if (selectedLocationIsValid(currentIndex, x, y, true)) {
                    pointXY pointToHighlight = {x, y};
                    Board->validLocations.push_back(pointToHighlight); // Dodanie możliwego ruchu do listy
                }
            }
        }
    }
}
