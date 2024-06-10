#include "../include/ApplicationStateManager.h"
#include "../include/GameState.h"
#include "../include/CheckersBoard.h"
#include "../include/Player.h"
#include "../include/RealPlayer.h"
#include "../include/Button.h"
#include "../include/Texture.h"

int TOTAL_BUTTONS = 32; // Definiowanie całkowitej liczby przycisków na planszy

// Konstruktor klasy GameState
GameState::GameState(){
    BUTTON_WIDTH = 80;  // Szerokość przycisku
    BUTTON_HEIGHT = 80; // Wysokość przycisku

    currentStateEnum = GAME_STATE; // Ustawienie bieżącego stanu na GAME_STATE
    nextStateEnum = GAME_STATE;    // Ustawienie następnego stanu na GAME_STATE

    Board = new CheckersBoard;               // Utworzenie nowego obiektu CheckersBoard
    boardButtons = new Button[TOTAL_BUTTONS]; // Utworzenie tablicy przycisków

    userQuit = false; // Inicjalizacja zmiennej userQuit na false
    switch (GAMEMODE) {
        case 0: // Tryb gry dla dwóch prawdziwych graczy
            Player1 = new RealPlayer(true, Board, boardButtons);
            Player2 = new RealPlayer(false, Board, boardButtons);
            break;
        default: // Nieznany tryb gry, ustawienie userQuit na true
            userQuit = true;
            break;
    }
}

// Destruktor klasy GameState
GameState::~GameState(){
    delete Board;         // Usunięcie obiektu CheckersBoard
    Board = NULL;
    delete [] boardButtons; // Usunięcie tablicy przycisków
    boardButtons = NULL;
    delete Player1;        // Usunięcie gracza 1
    Player1 = NULL;
    delete Player2;        // Usunięcie gracza 2
    Player2 = NULL;
    spriteClips.clear();   // Wyczyść wektor spriteClips
}

// Metoda wywoływana przy wejściu do stanu
void GameState::stateEnter(){
    if (!loadMedia()) {
        cout<<"Could not load media"<<endl; // Jeśli nie uda się załadować mediów, wypisz komunikat o błędzie
    }
}

// Metoda obsługująca zdarzenia
void GameState::stateEvent(){
    SDL_Event event;

    // Pętla obsługi zdarzeń
    while(SDL_PollEvent(&event) != 0){
        // Jeśli użytkownik zamknie aplikację
        if(event.type == SDL_QUIT){
            userQuit = true;
        }

        if (!gameOver()) {
            // Ruch gracza 1
            if (Player1->turn) {
                if(Player1->makeMove(&event)){
                    Player1->updateKings();
                    Player1->turn = false;
                    Player2->turn = true;
                    Player2->updateTeam();
                    cout << *Board << endl;
                    break; // Zakończ pętlę po wykonaniu ruchu
                }
            }
            // Ruch gracza 2
            else {
                if(Player2->makeMove(&event)){
                    Player2->updateKings();
                    Player2->turn = false;
                    Player1->turn = true;
                    Player1->updateTeam();
                    cout << *Board << endl;
                    break; // Zakończ pętlę po wykonaniu ruchu
                }
            }
        }
        else {
            nextStateEnum = GAME_OVER_STATE; // Jeśli gra jest zakończona, ustaw stan na GAME_OVER_STATE
        }
    }
}

// Metoda ładująca media
bool GameState::loadMedia(){
    bool initSuccessful = true;

    // Ładowanie tekstury sprite'a
    if (!spriteSheetTexture.loadFromFile("data/CheckerSprites.png")) {
        printf("Could not load sprite");
        initSuccessful = false;
    }
    // Inicjalizacja klipów sprite'ów
    // Czerwony pionek
    SDL_Rect redPiece = {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    spriteClips.push_back(redPiece);
    // Czarny pionek
    SDL_Rect blackPiece = {BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    spriteClips.push_back(blackPiece);
    // Czerwony król
    SDL_Rect redKing = {BUTTON_WIDTH * 2, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    spriteClips.push_back(redKing);
    // Czarny król
    SDL_Rect blackKing = {BUTTON_WIDTH * 3, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    spriteClips.push_back(blackKing);

    int index = 0;
    bool indent = true;
    int xStart;

    // Ustawianie punktów dla przycisków (górny lewy punkt przycisku)
    for(int y = 0; y < SCREEN_HEIGHT; y += BUTTON_HEIGHT){
        if (indent) {
            xStart = BUTTON_WIDTH;
            indent = false;
        } else {
            xStart = 0;
            indent = true;
        }
        for(int x = xStart; x < SCREEN_WIDTH; x += 2 * BUTTON_WIDTH){
            boardButtons[index].setPoint(x, y);
            index++;
        }
    }
    return initSuccessful;
}

// Metoda sprawdzająca, czy gra się skończyła
bool GameState::gameOver(){
    if (Player1->team.size() == 0 || Player2->team.size() == 0) {
        return true; // Gra kończy się, gdy drużyna jednego z graczy ma 0 pionków
    }
    return false;
}

// Metoda aktualizująca stan
StateEnum GameState::stateUpdate(){
    if (currentStateEnum != nextStateEnum) {
        return nextStateEnum; // Zwraca następny stan, jeśli jest różny od bieżącego
    }
    return currentStateEnum;
}

// Metoda renderująca stan gry
void GameState::stateRender(){
    // Ustawienie koloru tła na jasny kolor drewna
    SDL_SetRenderDrawColor(gRenderer, 0xD4, 0x9A, 0x6A, 0xFF);
    // Wyczyść ekran
    SDL_RenderClear(gRenderer);

    Board->drawBoard(); // Narysuj planszę

    // Renderowanie wszystkich pionków
    int index = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if ((y + x) % 2 == 1) {
                Board->drawBoardPeices(x, y, &boardButtons[index]);
                index++;
            }
        }
    }
}

// Metoda sprawdzająca, czy użytkownik chce zakończyć grę
bool GameState::stateExit(){
    return userQuit; // Zwraca wartość flagi userQuit
}



