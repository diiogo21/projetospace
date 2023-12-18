#pragma once

#include "bullet.h"
#include "action.h"
#include <iostream>
#include <curses.h>
#include <vector>

using namespace std;

class Nave : public Object {
    vector<Bullet*> balas;
    WINDOW* nave;
    WINDOW* GAME;
    Bullet* b;
    int y_origem, x_origem, y1, y2, x1, x2, altura, largura;
    int YMax, XMax;
public:
    int Max_bullets = 1;
    Nave(int y_origem, int x_origem, WINDOW* GAME) :b(b), GAME(GAME) {
        this->x_origem = x_origem;
        this->y_origem = y_origem;
        altura = 4;
        largura = 8;
        getmaxyx(GAME, YMax, XMax);
        nave = newwin(altura, largura, y_origem, x_origem);
        y1 = y_origem + altura / 2;
        y2 = y_origem - altura / 2 + 2;
        x1 = x_origem - largura / 2 + 3;
        x2 = x_origem + largura / 2 + 3;
        keypad(nave, true);
    }
    ~Nave() { wclear(nave); }
    bool jogar_nave(int move) {
        bool key = false;
        switch (move) {
        case KEY_LEFT:
            if (x_origem < 2)
                x_origem = 2;
            else
                x_origem--;
            break;
        case KEY_RIGHT:
            if (x_origem > XMax - 4)
            {
                x_origem = XMax - 4;
            }
            else
                x_origem++;
            break;
        case KEY_UP:
            if (balas.size() < Max_bullets) {
                b = new Bullet(y_origem - 1, x_origem + 4, GAME);
                balas.push_back(b);
            }
            break;
        case KEY_BACKSPACE:
            key = true;
            break;
        default:
            break;
        }
        return key;
    }

    void clear() {
        wclear(nave);
        refresh();
        wrefresh(nave);
    }

    void move() {
        mvwin(nave, y_origem, x_origem);
        y1 = y_origem + altura / 2;
        y2 = y_origem - altura / 2 + 1;
        x1 = x_origem - largura / 2 + 3;
        x2 = x_origem + largura / 2 + 3;
    }

    bool colisao(int bala_x, int bala_y) {
        if (bala_y > y2 && bala_y < y1 && bala_x > x1 && bala_x < x2)
            return true;
        return false;
    }

    vector<Bullet*> get_balas() {
        return balas;
    }

    void Obter_alteracao_balas(vector<Bullet*> get_balas) {
        balas = get_balas;
    }

    void draw() {
        for (int i = 0; i < balas.size(); i++)
            balas[i]->draw();

        if (has_colors())
            start_color();

        init_pair(1, COLOR_GREEN, COLOR_GREEN);

        wattron(nave, COLOR_PAIR(1));
        mvwaddch(nave, 2, 4, 219);
        mvwaddch(nave, 2, 3, 219);
        mvwaddch(nave, 3, 1, 0);
        mvwaddch(nave, 3, 2, 0);
        mvwaddch(nave, 3, 3, 0);
        mvwaddch(nave, 3, 4, 0);
        mvwaddch(nave, 3, 5, 0);
        wattroff(nave, COLOR_PAIR(1));

        refresh();
        wrefresh(nave);
    }
};