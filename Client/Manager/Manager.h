#pragma once

#include "../Client.h"

#include "Event/Dispatcher.h"
#include "Sigs/Sig.h"

class BaseHook;
class Category;
class Module;

class Manager {
public:
    Manager(Client*);
    ~Manager();
    
    Client* getClient();
    
    bool isTicking() const;
    void stop();

    template<class C>
    void registerHook();

    template<typename C, typename T>
    T getSig();

    template<class C>
    C* getCategory();

    std::vector<Category*> getCategories() const;

    template<class C, class M>
    void registerMod();
private:
    Client* ciPtr = nullptr;
    bool isTickingState = false;
    std::vector<std::unique_ptr<BaseHook>> hooks;
    std::map<std::string, std::unique_ptr<BaseSig>> sigMap;
    std::map<std::string, std::unique_ptr<Category>> categories;
};