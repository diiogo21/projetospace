#pragma once

#include <iostream>
#include <curses.h>
#include <Windows.h>
#include <list>
#include "action.h"
#include "obstacles.h"

using namespace std;

class Bullet {
    WINDOW* bala;
    const char* draw_b = "|";
    int y, x;
    int YMax, XMax;
    bool shock = false;

public:
    Bullet(int y, int x, WINDOW* GAME) {
        this->x = x;
        this->y = y;
        x = x + 2;
        y = y - 1;
        getmaxyx(GAME, YMax, XMax);
        bala = newwin(1, 1, y, x);
    }
    ~Bullet() {
        wclear(bala);
    }
    int Posicao_x() {
        return x;
    }
    int Posicao_y() {
        return y;
    }
    void GO_UP() {
        clear();
        if (y > 1) {
            y--;
            mvwin(bala, y, x);
        }
        else if (y == 1) {
            shock = true;
        }
        draw();
    }
    void GO_DOWN() {
        clear();
        if (y < YMax - 2) {
            y++;
            mvwin(bala, y, x);
        }
        else if (y == YMax - 2)
            shock = true;
        draw();
    }

    void change_shock() {
        shock = true;
    }

    void clear() {
        wclear(bala);
        refresh();
        wrefresh(bala);
    }

    bool colisao() {
        if (shock == false) {
            return false;
        }
        else
            return true;
    }

    void draw() {
        if (colisao() == false) {
            waddstr(bala, draw_b);
            refresh();
            wrefresh(bala);
        }

    }
};
