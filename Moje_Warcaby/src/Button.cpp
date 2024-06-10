#include "../include/Button.h"
#include "../include/GameState.h"
#include "../include/Texture.h"
#include "../include/Application.h"

// Konstruktor klasy Button
Button::Button(){
    // Inicjalizacja punktu startowego przycisku na (0, 0)
    buttonPoint.x = 0;
    buttonPoint.y = 0;
}

// Destruktor klasy Button
Button::~Button(){
    // Ustawienie współrzędnych punktu startowego przycisku na NULL
    buttonPoint.x = NULL;
    buttonPoint.y = NULL;
}

// Metoda ustawiająca punkt startowy przycisku
void Button::setPoint(int x, int y){
    // Ustawienie współrzędnych punktu startowego przycisku
    buttonPoint.x = x;
    buttonPoint.y = y;
}

// Metoda renderująca przycisk z użyciem określonego sprite'a
void Button::render(int sprite){
    // Renderowanie przycisku z użyciem tekstury spriteSheetTexture
    spriteSheetTexture.render(buttonPoint.x, buttonPoint.y, &spriteClips[sprite]);
}

// Metoda sprawdzająca, czy myszka znajduje się wewnątrz przycisku
bool Button::insideButton(int buttonWidth, int buttonHeight){
    int x, y;
    bool insideButton = true;
    
    // Pobranie aktualnej pozycji kursora myszy
    SDL_GetMouseState(&x, &y);
    
    // Sprawdzenie, czy kursor myszy jest powyżej przycisku
    if (y < buttonPoint.y) {
        insideButton = false;
    }
    // Sprawdzenie, czy kursor myszy jest poniżej przycisku
    else if (y > buttonPoint.y + buttonHeight) {
        insideButton = false;
    }
    // Sprawdzenie, czy kursor myszy jest po lewej stronie przycisku
    else if (x < buttonPoint.x) {
        insideButton = false;
    }
    // Sprawdzenie, czy kursor myszy jest po prawej stronie przycisku
    else if (x > buttonPoint.x + buttonWidth) {
        insideButton = false;
    }

    // Zwrócenie wartości true, jeśli kursor myszy znajduje się wewnątrz przycisku, w przeciwnym razie false
    return insideButton;
}

// Metoda zwracająca współrzędną x punktu startowego przycisku
int Button::getButtonPointX(){
    return buttonPoint.x; // Zwrócenie współrzędnej x punktu startowego przycisku
}

// Metoda zwracająca współrzędną y punktu startowego przycisku
int Button::getButtonPointY(){
    return buttonPoint.y; // Zwrócenie współrzędnej y punktu startowego przycisku
}


