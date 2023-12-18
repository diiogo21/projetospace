#pragma once

#include <iostream>
#include "bullet.h"
#include <list>
#include <curses.h>

using namespace std;

class Object
{
public:
    virtual void draw() = 0;
    virtual void move() = 0;
    virtual void clear() = 0;
private:
};

class Action {
    list<Object*> shapes;
public:
    void refresh() {
        for (Object* s : shapes) {
            s->clear();
            s->move();
            s->draw();
        }
    }
    void add(Object* s) {
        shapes.push_back(s);
    }
};
