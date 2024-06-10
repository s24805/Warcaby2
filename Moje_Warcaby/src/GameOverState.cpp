#include <stdio.h>
#include "../include/GameOverState.h"
#include "../include/Texture.h"
// Konstruktor klasy GameOverState
GameOverState::GameOverState(){
    currentStateEnum = GAME_OVER_STATE;    // Ustawienie bieżącego stanu na GAME_OVER_STATE
    nextStateEnum = GAME_OVER_STATE;       // Ustawienie następnego stanu na GAME_OVER_STATE
    userQuit = false;                      // Inicjalizacja zmiennej userQuit na false
}

// Destruktor klasy GameOverState
GameOverState::~GameOverState(){
    // Pusty destruktor, brak dodatkowych zasobów do zwolnienia
}

// Metoda wykonywana przy wejściu w stan
void GameOverState::stateEnter(){
    printf("GAME OVER");                   // Wyświetlenie komunikatu "GAME OVER" w konsoli
}

// Metoda obsługująca zdarzenia
void GameOverState::stateEvent(){
    SDL_Event event;
    // Pętla zdarzeń
    while(SDL_PollEvent(&event) != 0){
        // Sprawdzenie, czy użytkownik zamknął aplikację
        if(event.type == SDL_QUIT){
            userQuit = true;               // Ustawienie flagi userQuit na true
        }
    }
}

// Metoda aktualizująca stan
StateEnum GameOverState::stateUpdate(){
    // Jeśli bieżący stan różni się od następnego stanu, zwróć następny stan
    if (currentStateEnum != nextStateEnum) {
        return nextStateEnum;
    }
    // W przeciwnym razie zwróć bieżący stan
    return currentStateEnum;
}

// Metoda renderująca ekran
void GameOverState::stateRender(){
    // Ustawienie koloru tła na jasny kolor drewna
    SDL_SetRenderDrawColor(gRenderer, 0xD4, 0x9A, 0x6A, 0xFF);
    // Wyczyść ekran
    SDL_RenderClear(gRenderer);
}

// Metoda sprawdzająca, czy użytkownik chce wyjść z gry
bool GameOverState::stateExit(){
    return userQuit;                       // Zwraca wartość flagi userQuit
}

// Metoda ładująca zasoby (zwraca false, ponieważ brak zasobów do załadowania)
bool GameOverState::loadMedia(){
    return false;
}

