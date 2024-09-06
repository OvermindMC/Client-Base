#include "TestModule.h"

TestMod::TestMod(Category* c) : Module(c) {
    this->setIsEnabled(true);
};

std::string TestMod::getName() const {
    return "Test Module";
};