#pragma once

#include "../SDK/Minecraft.h"

class Manager;

class Client {
public:
    Client(const char*);
    ~Client();

    Manager* getMgr() const;
    std::string getName() const;
private:
    const char* name = nullptr;
    std::unique_ptr<Manager> mgrPtr;
};