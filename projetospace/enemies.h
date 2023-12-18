#pragma once

#include <iostream>
#include "action.h"
#include <curses.h>
#include <vector>
#include <Windows.h>

using namespace std;

class Enemie {
    WINDOW* Especie;
    WINDOW* GAME;
    int Max_bullets = 1;
    vector<Bullet*> balas_dos_inimigos;
    Bullet* bala_inimigo;
    int y_origem, x_origem;

    int altura = 5, largura = 10;
    int velocidade = 0;

public:
    int y1, x1, y2, x2;
    Enemie(int y_origem, int x_origem, WINDOW* GAME) :bala_inimigo(bala_inimigo), x_origem(x_origem), y_origem(y_origem), Especie(Especie), GAME(GAME) {
        Especie = newwin(altura, largura, y_origem, x_origem);
        y1 = y_origem + altura / 2;
        y2 = y_origem - altura / 2;
        x1 = x_origem - largura / 2;
        x2 = x_origem + largura / 2 + 3;
    }

    ~Enemie() {
        for (int i = 0; i < balas_dos_inimigos.size(); i++) {
            balas_dos_inimigos[i]->~Bullet();
            balas_dos_inimigos[i]->clear();
        }
    }

    void GO_RIGHT() {
        if (velocidade > 10) {
            x_origem += 2;
            x1 = x_origem - largura / 2;
            x2 = x_origem + largura / 2 + 3;
            velocidade = 0;
        }
        velocidade++;
        mvwin(Especie, y_origem, x_origem);
    }

    void GO_LEFT() {
        if (velocidade > 10) {
            x_origem -= 2;
            x1 = x_origem - largura / 2;
            x2 = x_origem + largura / 2 + 3;
            velocidade = 0;
        }
        velocidade++;
        mvwin(Especie, y_origem, x_origem);
    }

    void GO_DOWN() {
        y_origem++;
        y1 = y_origem + altura / 2;
        y2 = y_origem - altura / 2;
        mvwin(Especie, y_origem, x_origem);
    }

    int getx() {
        return x_origem;
    }

    int gety() {
        return y_origem;
    }
    vector<Bullet*> get_balas_inimigo() {
        return balas_dos_inimigos;
    }
    void shock() {
        for (int i = 0; i < balas_dos_inimigos.size(); i++)
            balas_dos_inimigos[i]->change_shock();
    }
    void shoot() {
        if (balas_dos_inimigos.size() < Max_bullets) {
            bala_inimigo = new Bullet(y_origem + 4, x_origem + 2, GAME);
            balas_dos_inimigos.push_back(bala_inimigo);
        }
    }

    bool colisao(int x_bala, int y_bala) {
        if (y_bala < y1 && y_bala > y2 && x_bala > x1 && x_bala < x2) {
            return true;
        }
        return false;
    }

    void move_balas() {
        if (!balas_dos_inimigos.empty()) {
            for (int i = 0; i < balas_dos_inimigos.size(); i++) {
                balas_dos_inimigos[i]->GO_DOWN();
                if (balas_dos_inimigos[i]->colisao() == true) { // Deteta a colisão da bala com o Chão
                    balas_dos_inimigos[i]->~Bullet(); // Destroi a bala que colidiu
                    balas_dos_inimigos.erase(balas_dos_inimigos.begin() + i);
                }
            }
        }
    }

    void clear() {
        wclear(Especie);
        refresh();
        wrefresh(Especie);
    }

    void draw() {
        for (int i = 0; i < balas_dos_inimigos.size(); i++)
            balas_dos_inimigos[i]->draw();
        if (has_colors())
            start_color();

        init_pair(1, COLOR_BLUE, COLOR_BLUE);
        wattron(Especie, COLOR_PAIR(1));
        mvwaddch(Especie, 3, 7, 219);
        mvwaddch(Especie, 2, 7, 0);
        mvwaddch(Especie, 2, 6, 0);
        mvwaddch(Especie, 2, 5, 0);
        mvwaddch(Especie, 2, 4, 0);
        mvwaddch(Especie, 2, 3, 0);
        mvwaddch(Especie, 2, 2, 0);
        mvwaddch(Especie, 2, 1, 0);
        mvwaddch(Especie, 1, 3, 0);
        mvwaddch(Especie, 1, 4, 0);
        mvwaddch(Especie, 1, 5, 0);
        mvwaddch(Especie, 3, 2, 219);
        wattroff(Especie, COLOR_PAIR(1));


        refresh();
        wrefresh(Especie);
    }
};

class Enemies : public Object {
    vector<Enemie*>::iterator it;
    vector<Enemie*>::iterator it_s;
    vector<Enemie*> enemies[4];
    WINDOW* GAME;
    int delay_bala = 0;
    int YMax, XMax, y, x, x2, y2, x3;
    bool first_y, first_x;
    bool sentido = true;
    bool descer = false;
    Enemie* e1;
    int numero_de_inimigos = 3;
public:
    Enemies(int y, int x, WINDOW* GAME) : e1(e1), GAME(GAME) {
        this->y = y;
        this->x = x;
        x2 = x;
        y2 = y;
        first_y = false;
        first_x = false;
        getmaxyx(GAME, YMax, XMax);
        for (int i = 0; i < numero_de_inimigos; i++) {
            x2 = x;
            if (first_y == true)
                y2 += 3;
            for (int j = 0; j < 10; j++) {
                if (first_x == true)
                    x2 += 8;
                e1 = new Enemie(y2 + i, x2 + j, GAME);
                enemies[i].push_back(e1);
                first_x = true;
            }
            first_x = false;
            first_y = true;
        }
        x2 = x;
        y2 = y;
    }

    bool Verifica_Integridade() {
        int conta = 0;
        for (int conta_enemies = 0; conta_enemies < numero_de_inimigos; conta_enemies++)
            if (enemies[conta_enemies].empty())
                conta++;
        if (conta == 3) {
            return true;
        }
        return false;
    }

    void reset() {
        x2 = x;
        y2 = y;
        first_y = false;
        first_x = false;
        getmaxyx(GAME, YMax, XMax);
        for (int i = 0; i < numero_de_inimigos; i++) {
            x2 = x;
            if (first_y == true)
                y2 += 3;
            for (int j = 0; j < 10; j++) {
                if (first_x == true)
                    x2 += 8;
                e1 = new Enemie(y2 + i, x2 + j, GAME);
                enemies[i].push_back(e1);
                first_x = true;
            }
            first_x = false;
            first_y = true;
        }
    }

    vector<Enemie*> get_Enemies(int conta_enemies) {
        return enemies[conta_enemies];
    }

    void Obter_Alteracoes_Enemies(vector<Enemie*> get_Enemies[3]) {
        for (int conta_enemies = 0; conta_enemies < numero_de_inimigos; conta_enemies++) {
            enemies[conta_enemies] = get_Enemies[conta_enemies];
        }
    }
    ~Enemies() {}
    void shoot() {
        vector<Enemie*> disparar;
        bool dispara = true;
        for (int i = 0; i < numero_de_inimigos; i++) {
            if (!enemies[i].empty()) {
                for (int j = 0; j < enemies[i].size(); j++) { // Alterar
                    for (int i_compara = 0; i_compara < numero_de_inimigos; i_compara++) {
                        for (int j_compara = 0; j_compara < enemies[i_compara].size(); j_compara++) {
                            if (i != i_compara && j != j_compara)
                                if (enemies[i][j]->gety() - enemies[i_compara][j_compara]->gety() < 0 && enemies[i_compara][j_compara]->x1 == enemies[i][j]->x1 && enemies[i_compara][j_compara]->x2 == enemies[i][j]->x2) { // Não pode disparar
                                    dispara = false;
                                }
                        }
                    }
                    if (dispara == true) {
                        disparar.push_back(enemies[i][j]);
                    }
                    dispara = true;
                }
            }
        }
        int t = disparar.size();
        int s = rand() % t;
        disparar[s]->shoot();
        disparar.clear();
    }

    void move() {
        delay_bala++;
        if (delay_bala > 20) {
            shoot();
            delay_bala = 0;
        }
        if (sentido == true) {
            if (descer == true) {
                for (int i = 0; i < numero_de_inimigos; i++) {
                    for (int j = 0; j < enemies[i].size(); j++) {
                        enemies[i][j]->GO_DOWN();
                    }
                    descer = false;
                }
            }
            for (int i = 0; i < numero_de_inimigos; i++) {
                for (int j = 0; j < enemies[i].size(); j++) {
                    enemies[i][j]->GO_RIGHT();

                    if (enemies[i][j]->getx() == XMax - 12) {
                        sentido = false;
                        descer = true;
                    }
                }
            }
        }
        else {
            if (descer == true) {
                for (int i = 0; i < numero_de_inimigos; i++) {
                    for (int j = 0; j < enemies[i].size(); j++) {
                        enemies[i][j]->GO_DOWN();
                    }
                    descer = false;
                }
            }
            for (int i = 0; i < numero_de_inimigos; i++) {
                for (int j = 0; j < enemies[i].size(); j++) {
                    enemies[i][j]->GO_LEFT();

                    if (enemies[i][j]->getx() == 8) {
                        sentido = true;
                        descer = true;
                    }
                }
            }
        }
    }

    void clear() {
        for (int i = 0; i < numero_de_inimigos; i++) {
            for (it = enemies[i].begin(); it != enemies[i].end(); it++)
                (*it)->clear();
        }
    }

    void draw() {
        for (int i = 0; i < numero_de_inimigos; i++) {
            for (it = enemies[i].begin(); it != enemies[i].end(); it++)
                (*it)->draw();
        }
    }
};