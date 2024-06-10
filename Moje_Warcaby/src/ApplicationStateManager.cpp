#include "../include/ApplicationStateManager.h"
#include "../include/GameState.h"
#include "../include/GameOverState.h"

// Konstruktor klasy ApplicationStateManager
ApplicationStateManager::ApplicationStateManager(){
    // Inicjalizacja bieżącego stanu jako MenuState
    currentState = new GameState();
    // Wywołanie metody stateEnter na bieżącym stanie
    currentState->stateEnter();
}

// Destruktor klasy ApplicationStateManager
ApplicationStateManager::~ApplicationStateManager(){
    // Usunięcie bieżącego stanu z pamięci
    delete currentState;
    // Ustawienie wskaźnika currentState na NULL
    currentState = NULL;
}

// Metoda przekazująca obsługę zdarzeń do bieżącego stanu
void ApplicationStateManager::stateEvent(){
    currentState->stateEvent(); // Wywołanie metody stateEvent bieżącego stanu
}

// Metoda aktualizująca bieżący stan i zwracająca nowy stan
StateEnum ApplicationStateManager::stateUpdate(){
    return currentState->stateUpdate(); // Wywołanie metody stateUpdate bieżącego stanu i zwrócenie wyniku
}

// Metoda renderująca bieżący stan
void ApplicationStateManager::stateRender(){
    currentState->stateRender(); // Wywołanie metody stateRender bieżącego stanu
}

// Metoda sprawdzająca, czy bieżący stan powinien się zakończyć
bool ApplicationStateManager::stateExit(){
    return currentState->stateExit(); // Wywołanie metody stateExit bieżącego stanu i zwrócenie wyniku
}

// Metoda ustawiająca nową wartość bieżącego stanu
void ApplicationStateManager::setCurrentStateEnum(StateEnum current){
    currentStateEnum = current; // Ustawienie wartości currentStateEnum na wartość przekazaną jako argument
}

// Metoda zwracająca bieżącą wartość stanu
StateEnum ApplicationStateManager::getCurrentStateEnum(){
    return currentStateEnum; // Zwrócenie wartości currentStateEnum
}

// Metoda zmieniająca stan aplikacji na nowy zgodnie z wartością currentStateEnum
void ApplicationStateManager::changeStates(){
    
    delete currentState; // Usunięcie bieżącego stanu z pamięci
    currentState = NULL; // Ustawienie wskaźnika currentState na NULL
    
    // Przełączanie stanów na podstawie wartości currentStateEnum
    switch (currentStateEnum) {
        case GAME_STATE:
            currentState = new GameState; // Ustawienie nowego stanu jako GameState
            break;
        case GAME_OVER_STATE:
            currentState = new GameOverState; // Ustawienie nowego stanu jako GameOverState
            break;
        default:
            break; // Domyślny przypadek (nic nie robi)
    }
    // Wywołanie metody stateEnter na nowym stanie
    currentState->stateEnter();
}
