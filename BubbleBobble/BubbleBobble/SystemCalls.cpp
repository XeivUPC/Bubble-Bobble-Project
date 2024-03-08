#include "SystemCalls.hpp"

SystemCalls::SystemCalls(){
    
}
void SystemCalls::Destroy() {

    for (auto& obj : destroyCall) {
        obj->Destroy();
    }
    updateCall.clear();
    lateUpdateCall.clear();
    destroyCall.clear();
    renderCall.clear();
}

