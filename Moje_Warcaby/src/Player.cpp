#include "../include/Player.h"
#include "../include/CheckersBoard.h"
#include "../include/Button.h"
#include "../include/GameState.h"

// Konstruktor klasy Player
Player::Player(bool topSideOfBoard, CheckersBoard *board, Button buttons[]){
    Board = board; // Inicjalizacja wskaźnika na planszę
    boardButtons = buttons; // Inicjalizacja wskaźnika na przyciski
    topSide = topSideOfBoard; // Określenie, czy gracz gra na górnej stronie planszy
    currentIndex = 0; // Inicjalizacja aktualnego indeksu
    initTeam(); // Inicjalizacja zespołu gracza
    if (topSideOfBoard) {
        ONE = 1; // Ustawienie kierunku ruchu dla górnej strony
        turn = false; // Inicjalizacja tury gracza
    }
    else{
        ONE = -1; // Ustawienie kierunku ruchu dla dolnej strony
        turn = true; // Inicjalizacja tury gracza
    }
}

// Destruktor klasy Player
Player::~Player(){
    team.clear(); // Czyszczenie wektora zespołu
    Board = NULL; // Ustawienie wskaźnika na planszę na NULL
    boardButtons = NULL; // Ustawienie wskaźnika na przyciski na NULL
}

// Metoda inicjalizująca zespół gracza
void Player::initTeam() {
    if (topSide) {
        //----------------------------CZARNY ZESPÓŁ----------------------------\\
        // Dodawanie nowych pionków do zespołu
        team.push_back(Piece());
        team[0].x = 1;
        team[0].y = 0;

        team.push_back(Piece());
        team[1].x = 3;
        team[1].y = 0;

        team.push_back(Piece());
        team[2].x = 5;
        team[2].y = 0;

        team.push_back(Piece());
        team[3].x = 7;
        team[3].y = 0;

        team.push_back(Piece());
        team[4].x = 0;
        team[4].y = 1;

        team.push_back(Piece());
        team[5].x = 2;
        team[5].y = 1;

        team.push_back(Piece());
        team[6].x = 4;
        team[6].y = 1;

        team.push_back(Piece());
        team[7].x = 6;
        team[7].y = 1;

        team.push_back(Piece());
        team[8].x = 1;
        team[8].y = 2;

        team.push_back(Piece());
        team[9].x = 3;
        team[9].y = 2;

        team.push_back(Piece());
        team[10].x = 5;
        team[10].y = 2;

        team.push_back(Piece());
        team[11].x = 7;
        team[11].y = 2;

        // Ustawienie numeru zespołu
        TEAM_NUMBER = BLACK_PIECE;
        ENEMY_TEAM_NUMBER = RED_PIECE;
    }
    else {
        //-----------------------------CZERWONY ZESPÓŁ----------------------------\\
        // Dodawanie nowych pionków do zespołu
        team.push_back(Piece());
        team[0].x = 0;
        team[0].y = 7;

        team.push_back(Piece());
        team[1].x = 2;
        team[1].y = 7;

        team.push_back(Piece());
        team[2].x = 4;
        team[2].y = 7;

        team.push_back(Piece());
        team[3].x = 6;
        team[3].y = 7;

        team.push_back(Piece());
        team[4].x = 1;
        team[4].y = 6;

        team.push_back(Piece());
        team[5].x = 3;
        team[5].y = 6;

        team.push_back(Piece());
        team[6].x = 5;
        team[6].y = 6;

        team.push_back(Piece());
        team[7].x = 7;
        team[7].y = 6;

        team.push_back(Piece());
        team[8].x = 0;
        team[8].y = 5;

        team.push_back(Piece());
        team[9].x = 2;
        team[9].y = 5;

        team.push_back(Piece());
        team[10].x = 4;
        team[10].y = 5;

        team.push_back(Piece());
        team[11].x = 6;
        team[11].y = 5;

        // Ustawienie numeru zespołu
        TEAM_NUMBER = RED_PIECE;
        ENEMY_TEAM_NUMBER = BLACK_PIECE;
    }

    // Aktualizacja wirtualnej planszy po inicjalizacji zespołu
    for (int teamIndex = 0; teamIndex < team.size(); teamIndex++) {
        Board->virtualBoard[team[teamIndex].x][team[teamIndex].y] = topSide + 1;
    }
}

// Metoda wykonująca ruch gracza (na razie zwraca false)
bool Player::makeMove(SDL_Event *){
    return false;
}

// Metoda sprawdzająca, czy dwa pionki są z tego samego zespołu
bool Player::sameTeam(int value1, int value2){
    // Sprawdza, czy dwa pionki są na tej samej drużynie
    if (value1 % 2 == value2 % 2 && value1 != EMPTY_PIECE) {
        return true;
    }
    return false;
}

// Metoda przemieszczająca pionek w nowe miejsce
void Player::movePiece(vector<vector<int>> &pBoard, vector<Piece>& teamMove, int teamIndex, int newX, int newY){
    // Przemieszcza pionek na nową pozycję (newX, newY)
    if (abs(newX - teamMove[teamIndex].x) == 2 && abs(newY - teamMove[teamIndex].y) == 2) {
        // Zabija pionek na średniej lokalizacji
        killPiece(pBoard, abs(newX + teamMove[teamIndex].x) / 2, abs(newY + teamMove[teamIndex].y) / 2);
        // Informuje gracza, który pionek dokonał zabójstwa
        killerPeiceIndex = teamIndex;
    }
    pBoard[newX][newY] = pBoard[teamMove[teamIndex].x][teamMove[teamIndex].y];
    pBoard[teamMove[teamIndex].x][teamMove[teamIndex].y] = EMPTY_PIECE;
    teamMove[teamIndex].x = newX;
    teamMove[teamIndex].y = newY;

    // Wyświetla wirtualną planszę po wykonaniu ruchu
    // cout << pBoard << endl;
}

// Metoda zabijająca pionek na planszy
void Player::killPiece(vector<vector<int>> &pBoard, int x, int y) {
    pBoard[x][y] = EMPTY_PIECE; // Ustawia pole na planszy jako puste
    killWasMade = true; // Ustawia flagę informującą, że zabójstwo miało miejsce
}

// Metoda aktualizująca zespół gracza
void Player::updateTeam() {
    // Aktualizuje zespół, gdy rozmiar zespołu został zmieniony
    bool updateMade = false;
    for (int index = 0; index < team.size(); index++) {
        if (!sameTeam(Board->virtualBoard[team[index].x][team[index].y], TEAM_NUMBER)) {
            team.erase(team.begin() + index); // Usuwa pionek z zespołu
            index--;
            updateMade = true;
            cout << "Team:\t" << TEAM_NUMBER << "\thas a team.size():\t" << team.size() << endl;
        }
    }
    if (updateMade) {
        cout << "*Team updated" << endl;
    }
}

// Metoda aktualizująca pionki króla w zespole gracza
void Player::updateKings() {
    int yToMakeKing = 7 * topSide; // Określenie, która strona planszy jest bazą króla
    bool updateMade = false;
    for (int index = 0; index < team.size(); index++) {
        if (team[index].y == yToMakeKing && !team[index].isKing()) {
            team[index].makeKing(); // Ustawienie pionka jako króla
            Board->virtualBoard[team[index].x][team[index].y] += 2; // Aktualizacja wirtualnej planszy
            updateMade = true;
        }
    }
    if (updateMade) {
        cout << "*Kings updated" << endl;
    }
}

// Metoda zwracająca indeks pionka na podstawie jego pozycji (x, y)
int Player::pieceTeamIndexByXY(int x, int y) {
    int index = 0;
    for (; index < team.size(); index++) {
        if ((team[index].x == x) && (team[index].y == y)) {
            break;
        }
    }
    return index;
}


