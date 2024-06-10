#include "../include/Texture.h"

// Konstruktor klasy Texture
Texture::Texture(){
    currentTexture = NULL; // Inicjalizacja wskaźnika na bieżącą teksturę jako NULL
    width = 0; // Inicjalizacja szerokości jako 0
    height = 0; // Inicjalizacja wysokości jako 0
}

// Destruktor klasy Texture
Texture::~Texture(){
    free(); // Zwolnienie zasobów tekstury
}

// Metoda wczytująca teksturę z pliku
bool Texture::loadFromFile(std::string path){

    // Zwolnienie obecnej tekstury //
    free();

    SDL_Texture *newTexture;
    // Wczytanie obrazu z podanej ścieżki //
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == NULL){
        printf("Unable to load img from %s! SDL Error: %s\n",path.c_str(),IMG_GetError()); // Wyświetlenie komunikatu błędu w przypadku niepowodzenia ładowania obrazu
    }
    else{
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); // Utworzenie tekstury na podstawie wczytanego obrazu
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n",path.c_str(), SDL_GetError()); // Wyświetlenie komunikatu błędu w przypadku niepowodzenia tworzenia tekstury
        }
        else{
            // Pobranie wymiarów obrazu //
            width = loadedSurface->w;
            height = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface); // Zwolnienie załadowanej powierzchni
    }
        currentTexture = newTexture; // Ustawienie bieżącej tekstury
        return currentTexture != NULL; // Zwrócenie informacji, czy tekstura została załadowana pomyślnie
}

// Metoda renderująca teksturę na ekranie
void Texture::render(int x, int y, SDL_Rect *clip){

    // Ustawienie miejsca renderowania na ekranie //
    SDL_Rect renderSpace = {x, y, width, height};

    // Ustawienie wymiarów przestrzeni renderowania na podstawie wymiarów klipu //
    if(clip != NULL){
        renderSpace.w = clip->w;
        renderSpace.h = clip->h;
    }

    // Renderowanie na ekranie //
    SDL_RenderCopy(gRenderer, currentTexture, clip, &renderSpace);
}

// Metoda zwalniająca zasoby zajmowane przez teksturę
void Texture::free(){
    if(currentTexture!=NULL){
        SDL_DestroyTexture(currentTexture); // Zwolnienie tekstury
        currentTexture = NULL; // Ustawienie wskaźnika na teksturę jako NULL
        width = 0; // Zresetowanie szerokości
        height = 0; // Zresetowanie wysokości
    }
}

// Metoda zwracająca szerokość tekstury
int Texture::getWidth(){
    return width;
}

// Metoda zwracająca wysokość tekstury
int Texture::getHeight(){
    return height;
}



