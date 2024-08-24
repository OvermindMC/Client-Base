#pragma once

#include "../Mem/Mem.h"
#include "../Utils/Utils.h"

class Manager;

class Client {
public:
    Client(const char*);
    ~Client();

    Manager* getMgr() const;
private:
    const char* name = nullptr;
    std::unique_ptr<Manager> mgrPtr;
};