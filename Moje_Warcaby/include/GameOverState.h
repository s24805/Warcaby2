#ifndef GameOverState_h
#define GameOverState_h

#include "ApplicationState.h"

class GameOverState: public ApplicationState{
public:
    GameOverState();
    ~GameOverState();
    void stateEnter();
    void stateEvent();
    StateEnum stateUpdate();
    void stateRender();
    bool stateExit();
private:
    bool loadMedia();
    bool userQuit;
};

#endif /* GameOverState_h */
