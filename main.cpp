#include "src/Client.h"

void init(HINSTANCE hInst) {
    auto client = std::make_unique<Client>();
    client.reset();

    FreeLibraryAndExitThread(Mem::GetDll(), 1);
};

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD fdwReason, LPVOID lpRes) {
    if(fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hInst);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInst, 0, 0);
    };
    
    return TRUE;
};