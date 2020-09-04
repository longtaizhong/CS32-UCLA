//
//  main.cpp
//  animal
//
//  Created by Ryan Zhong  on 5/3/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

class Animal{
 public:
    Animal(string name);
    virtual ~Animal();
    virtual void speak() const = 0;
    virtual string moveAction() const;
    string name() const;
private:
    string m_name;
};

Animal::Animal(string name):m_name(name){}  //constructor for ANIMAL

Animal::~Animal(){}

string Animal:: name() const{       //returns name
    return m_name;
}

string Animal:: moveAction() const{     //return walk because normally animals jus returns walk
    return "walk";
}



class Cat: public Animal{
public:
    Cat(string name);
    ~Cat();
    virtual void speak() const;
  //  virtual void moveAction() const;
};

Cat::Cat(string name):Animal(name){}    //constructor using animal because its the same

Cat::~Cat(){
    cout<<"Destroying " << name() << " the cat" <<endl;
}


void Cat:: speak() const{
    cout<<"Meow";
}

class Pig: public Animal{
public:
    Pig(string name, int weight);
    ~Pig();
    virtual void speak() const;
private:
    int m_weight;
};

Pig::Pig(string name, int weight):Animal(name){
    m_weight = weight;
}

Pig::~Pig(){
    cout<<"Destroying " <<name() << " the pig" <<endl;
}

void Pig:: speak() const{
    if(m_weight<160){
        cout<<"Oink";
    }else{
        cout<<"Grunt";
    }
}

class Duck: public Animal{
public:
    Duck(string name);
    ~Duck();
    virtual void speak() const;
    virtual string moveAction() const;
};

Duck::Duck(string name):Animal(name){}
Duck::~Duck(){
    cout<<"Destroying " << name() << " the duck" << endl;
}
void Duck::speak() const{
    cout<<"Quack";
}

string Duck::moveAction() const{
    return "swim";
}


void animate(const Animal* a)
{
    a->speak();
    cout << "!  My name is " << a->name()
    << ".  Watch me " << a->moveAction() << "!\n";
}

int main()
{
   
    
    Animal* animals[4];
    animals[0] = new Cat("Fluffy");
    // Pigs have a name and a weight in pounds.  Pigs under 160
    // pounds oink; pigs weighing at least 160 pounds grunt.
    animals[1] = new Pig("Napoleon", 190);
    animals[2] = new Pig("Wilbur", 50);
    animals[3] = new Duck("Daffy");
    
    cout << "Here are the animals." << endl;
    for (int k = 0; k < 4; k++)
        animate(animals[k]);
    
    // Clean up the animals before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete animals[k];
    
}
