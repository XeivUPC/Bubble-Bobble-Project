#include "SystemCalls.hpp"

SystemCalls::SystemCalls(){
    
}
void SystemCalls::Destroy(){
    
    for (auto& obj : destroyCall) {
        obj->Destroy();
    }

    earlyUpdateCall.clear();
    updateCall.clear();
    lateUpdateCall.clear();

    startCall.clear();
    awakeCall.clear();
    destroyCall.clear();

    renderCall.clear();
}
