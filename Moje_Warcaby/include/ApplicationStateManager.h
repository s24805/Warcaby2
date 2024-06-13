#ifndef ApplicationStateManager_h
#define ApplicationStateManager_h

#include "ApplicationState.h"
//class ApplicationState;

class ApplicationStateManager{
public:
    ApplicationStateManager();
    ~ApplicationStateManager();
    void stateEvent();
    StateEnum stateUpdate();
    void stateRender();
    bool stateExit();
    StateEnum getCurrentStateEnum();
    void setCurrentStateEnum(StateEnum);
    void changeStates();
private:
    ApplicationState *currentState;
    StateEnum currentStateEnum;
};
#endif /* ApplicationStateManager_h */
