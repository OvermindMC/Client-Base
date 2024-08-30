#include "Manager/Manager.h"

Client::Client(const char* client_name) : name(client_name) {
    Debugger::init(client_name);
    this->mgrPtr = std::make_unique<Manager>(this);
};

Client::~Client() {
    this->mgrPtr.reset();
    Debugger::free();
};

Manager* Client::getMgr() const {
    return this->mgrPtr.get();
};

std::string Client::getName() const {
    return this->name;
};