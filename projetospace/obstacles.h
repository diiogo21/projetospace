#pragma once

#include <iostream>
#include <curses.h>
#include "bullet.h"
#include "action.h"
#include <vector>
#include <Windows.h>

using namespace std;

class obstacles
{
    WINDOW* obstacle;
    int y, x;
    int YMax, XMax;

public:
    obstacles(int y, int x)
    {
        this->x = x;
        this->y = y;
        getmaxyx(stdscr, YMax, XMax);
        obstacle = newwin(1, 1, y, x);
    }

    ~obstacles() {}

    void clear()
    {
        wclear(obstacle);
        wrefresh(obstacle);
    }
    int get_x() {
        return x;
    }
    int get_y() {
        return y;
    }
    void draw()
    {
        if (has_colors())
            start_color();

        init_pair(3, COLOR_CYAN, COLOR_CYAN);
        wattron(obstacle, COLOR_PAIR(3));
        mvwaddch(obstacle, 0, 0, 0);
        wattroff(obstacle, COLOR_PAIR(3));

        refresh();
        wrefresh(obstacle);
    }

    bool colisao()
    {
        return false;
    }

};

class matriz_obstacles : public Object
{
    vector<obstacles*> matriz_o[3];
    vector<obstacles*>::iterator it_o;
    int x = 0;
    int y = 0;
    obstacles* o;
public:

    matriz_obstacles(int y, int x) : o(o) {
        this->x = x;
        this->y = y;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 6; j++)
            {
                o = new obstacles(y + i, x + j);
                matriz_o[i].push_back(o);
            }

    }
    vector<obstacles*> get_obstaculos(int conta_o) {
        return matriz_o[conta_o];
    }
    void Obter_alteracao_obtaculos(vector<obstacles*> get_obstaculos[3]) {
        for (int conta_o = 0; conta_o < 3; conta_o++) {
            matriz_o[conta_o] = get_obstaculos[conta_o];
        }
    }
    void reset() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 6; j++)
            {
                o = new obstacles(y + i, x + j);
                matriz_o[i].push_back(o);
            }
    }
    void move() {}
    //void clear() -> class object
    void clear() {}

    //bool colisao() -> class object
    bool colisao() {
        return true;
    }
    //void draw() -> class object 
    void draw()
    {
        for (int i = 0; i < 3; i++) {
            for (it_o = matriz_o[i].begin(); it_o != matriz_o[i].end(); it_o++)
                (*it_o)->draw();
        }
    }

};
