// build: g++ -fdump-class-hierarchy main.cpp
#include <iostream>

class Base {
public:
    Base(){}
    ~Base(){}
public:
    virtual  void Func() {}
};

class Derive :public Base {
public:
    virtual void Func() {}
private:
    int a;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    Base* b = new Derive;
    return 0;
}
