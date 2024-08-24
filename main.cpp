#include "Client/Client.h"

void init(HINSTANCE hInstance) {
    Client* client = new Client("Client");

    delete client;
    FreeLibraryAndExitThread(Mem::getDll(), 0);
};

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpRes) {

    if(fdwReason == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, 0);
    };

    return TRUE;
};