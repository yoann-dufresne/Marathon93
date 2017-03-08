#include <iostream>
#include <vector>
using namespace std;

// abstract base class
class Animal
{
public:
    // pure virtual method
    virtual void speak() = 0;
};

// derived class
class Dog : public Animal
{
public:
    // polymorphic implementation of speak
    void speak() { cout << "Ruff!" << endl; }
};

int main( int argc, char* args[] ) {

    // container of base class pointers
    vector<Animal*> barn;

    // dynamically allocate an Animal instance and add it to the container
    barn.push_back( new Dog() );
    new Animal ();

    // invoke the speak method of the first Animal in the container
    barn.front()->speak();


    return 0;
}