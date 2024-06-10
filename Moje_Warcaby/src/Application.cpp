#include "../include/Application.h"
#include "../include/ApplicationState.h"
#include "../include/ApplicationStateManager.h"
#include "../include/Texture.h"

// Zmienna przechowująca indeks aktualnego sprite'a
int currentSprite = 0;

// Wskaźnik na okno SDL
SDL_Window *gWindow;

// Wskaźnik na renderer SDL
SDL_Renderer *gRenderer;

// Stałe określające szerokość i wysokość okna
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

// Stałe określające szerokość i wysokość przycisku
int BUTTON_WIDTH = 0;
int BUTTON_HEIGHT = 0;

// Zmienna przechowująca tryb gry
int GAMEMODE = 0;

// Wektor przechowujący klipy sprite'ów
vector<SDL_Rect> spriteClips;

// Tekstura przechowująca sprite'y
Texture spriteSheetTexture;

// Konstruktor klasy Application
Application::Application(){
    gWindow=NULL; // Inicjalizacja wskaźnika na okno jako NULL
    gRenderer=NULL; // Inicjalizacja wskaźnika na renderer jako NULL

    // Sprawdzenie, czy inicjalizacja powiodła się
    if(!init()){
        cout<<"Could not load application!"<<endl; // Wyświetlenie komunikatu o niepowodzeniu inicjalizacji
    }

    // Utworzenie menedżera stanu aplikacji
    applicationStateManager = new ApplicationStateManager;
}

// Destruktor klasy Application
Application::~Application(){
    delete applicationStateManager; // Zwolnienie pamięci zaalokowanej dla menedżera stanu aplikacji
    applicationStateManager = NULL; // Ustawienie wskaźnika na menedżer stanu aplikacji jako NULL

    SDL_DestroyWindow(gWindow); // Zniszczenie okna SDL
    gWindow=NULL; // Ustawienie wskaźnika na okno jako NULL

    SDL_DestroyRenderer(gRenderer); // Zniszczenie renderera SDL
    gRenderer=NULL; // Ustawienie wskaźnika na renderer jako NULL
}

// Metoda inicjalizująca aplikację
bool Application::init(){
    bool initSuccessful = true; // Inicjalizacja flagi informującej o sukcesie inicjalizacji

    // Inicjalizacja SDL
    if(SDL_Init(SDL_INIT_VIDEO)>0)
    {
        cout<<"Failed init. SDL_ERROR: %s\n"<<SDL_GetError(); // Wyświetlenie komunikatu o błędzie inicjalizacji SDL
        initSuccessful = false; // Ustawienie flagi na wartość false
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            cout<<"Warning: Linear texture filtering not enabled!"<<endl; // Wyświetlenie ostrzeżenia o braku włączonej filtracji liniowej tekstur
        }

        // Utworzenie okna SDL
        gWindow=SDL_CreateWindow("Checkers",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

        if(gWindow==NULL)
        {
            cout<<"Couldnt make window. SDL_Error: %s\n"<<SDL_GetError()<<endl; // Wyświetlenie komunikatu o błędzie tworzenia okna
            initSuccessful = false; // Ustawienie flagi na wartość false
        }
        else
        {
            // Utworzenie renderera SDL
            gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer==NULL)
            {
                cout<<"Renderer failed. SDL_Error: %s\n"<<SDL_GetError()<<endl; // Wyświetlenie komunikatu o błędzie tworzenia renderera
                initSuccessful = false; // Ustawienie flagi na wartość false
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF); // Ustawienie koloru renderowania na biały

                // Inicjalizacja wczytywania obrazków
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    cout<<"Image failed. SDl_image Error: %s\n"<<IMG_GetError()<<endl; // Wyświetlenie komunikatu o błędzie inicjalizacji wczytywania obrazków
                    initSuccessful = false; // Ustawienie flagi na wartość false
                }
            }
        }
    }
    return initSuccessful; // Zwrócenie informacji o sukcesie inicjalizacji
}

// Metoda rozpoczynająca działanie aplikacji
int Application::startApplication(){

    // Pętla główna aplikacji
    while (!applicationStateManager->stateExit()) {
        applicationStateManager->stateEvent(); // Obsługa zdarzeń dla bieżącego stanu
        applicationStateManager->stateRender(); // Renderowanie bieżącego stanu
        if (applicationStateManager->stateUpdate() != applicationStateManager->getCurrentStateEnum()) {
            applicationStateManager->setCurrentStateEnum(applicationStateManager->stateUpdate()); // Aktualizacja stanu aplikacji
            applicationStateManager->changeStates(); // Zmiana stanów aplikacji
        }
        SDL_RenderPresent(gRenderer); // Odświeżenie renderera
        if (applicationStateManager->getCurrentStateEnum() == MENU_STATE) {
            SDL_Delay(30); // Opóźnienie dla stanu menu
        }
        else {
            SDL_Delay(100); // Opóźnienie dla innych stanów
        }
    }

    closeApplication(); // Zamknięcie aplikacji

    return (EXIT_SUCCESS); // Zakończenie aplikacji
}

// Metoda zamykająca aplikację
void Application::closeApplication(){
    IMG_Quit(); // Wyłączenie wczytywania obrazków
    SDL_Quit(); // Wyłączenie SDL
}



