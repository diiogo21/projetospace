// Space_Ivaders.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "nave.h"
#include "bullet.h"
#include "enemies.h"
#include "action.h"
#include "obstacles.h"
#include <iostream>
#include <curses.h>
#include <Windows.h>
#include <vector>
#include <stdlib.h>

using namespace std;

void fullscreen() {                        //abrir o programa em Full screen
    keybd_event(VK_MENU, 0x36, 0, 0);
    keybd_event(VK_RETURN, 0x1C, 0, 0);
    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void game_loop() {
    
    WINDOW* GAME = newwin(30,120,0,0);
    box(GAME, 0, 0);
    refresh();
    wrefresh(GAME);
    keypad(stdscr, true);
    vector<matriz_obstacles> obstaculos;
    vector<Bullet*> balas_da_nave;
    vector<Bullet*> balas_dos_inimigos;
    vector<obstacles*> matriz_de_obtaculos1[3];
    vector<obstacles*> matriz_de_obtaculos2[3];
    vector<obstacles*> matriz_de_obtaculos3[3];
    vector<Enemie*> inimigos[5];
    matriz_obstacles o1(20, 20);
    matriz_obstacles o2(20, 60);
    matriz_obstacles o3(20, 100);
    Action d;
    Enemies e(1,1,GAME);
    Nave n(25, 55,GAME);
    int numero_de_inimigos = 3;
    d.add(&o1);
    d.add(&o2);
    d.add(&o3);
    d.add(&n);
    d.add(&e);
    bool key = false; // chave para sair do loop game
    int Score = 0;
    mvwprintw(GAME,28,1, "SCORE: %d",Score);
    while (1) {
        // Sair do Jogo
        if (key == true) {
            clear();
            wclear(GAME);
            break;
        }
        Sleep(30);
        // Inicializações 
        balas_da_nave = n.get_balas();
        for (int i = 0; i < numero_de_inimigos; i++)
            inimigos[i] = e.get_Enemies(i);
        for (int i = 0; i < 3; i++)
            matriz_de_obtaculos1[i] = o1.get_obstaculos(i);
        for (int i = 0; i < 3; i++)
            matriz_de_obtaculos2[i] = o2.get_obstaculos(i);
        for (int i = 0; i < 3; i++)
            matriz_de_obtaculos3[i] = o3.get_obstaculos(i);
        // colisão da bala da nave com o obstaculo 
        for (int i = 0; i < 3; i++)
            for (int conta_o = 0; conta_o < matriz_de_obtaculos1[i].size(); conta_o++)
                for (int conta_balas = 0; conta_balas < balas_da_nave.size(); conta_balas++)
                    if (matriz_de_obtaculos1[i][conta_o]->get_x() == balas_da_nave[conta_balas]->Posicao_x() &&
                        matriz_de_obtaculos1[i][conta_o]->get_y() == balas_da_nave[conta_balas]->Posicao_y()) {
                        balas_da_nave[conta_balas]->change_shock();
                        balas_da_nave[conta_balas]->clear();
                        balas_da_nave[conta_balas]->~Bullet();
                        balas_da_nave.erase(balas_da_nave.begin() + conta_balas);
                        matriz_de_obtaculos1[i][conta_o]->~obstacles();
                        matriz_de_obtaculos1[i].erase(matriz_de_obtaculos1[i].begin() + conta_o);
                    }
        for (int i = 0; i < 3; i++)
            for (int conta_o = 0; conta_o < matriz_de_obtaculos2[i].size(); conta_o++)
                for (int conta_balas = 0; conta_balas < balas_da_nave.size(); conta_balas++)
                    if (matriz_de_obtaculos2[i][conta_o]->get_x() == balas_da_nave[conta_balas]->Posicao_x() &&
                        matriz_de_obtaculos2[i][conta_o]->get_y() == balas_da_nave[conta_balas]->Posicao_y()) {
                        balas_da_nave[conta_balas]->change_shock();
                        balas_da_nave[conta_balas]->clear();
                        balas_da_nave[conta_balas]->~Bullet();
                        balas_da_nave.erase(balas_da_nave.begin() + conta_balas);
                        matriz_de_obtaculos2[i][conta_o]->~obstacles();
                        matriz_de_obtaculos2[i].erase(matriz_de_obtaculos2[i].begin() + conta_o);
                    }
        for (int i = 0; i < 3; i++)
            for (int conta_o = 0; conta_o < matriz_de_obtaculos3[i].size(); conta_o++)
                for (int conta_balas = 0; conta_balas < balas_da_nave.size(); conta_balas++)
                    if (matriz_de_obtaculos3[i][conta_o]->get_x() == balas_da_nave[conta_balas]->Posicao_x() &&
                        matriz_de_obtaculos3[i][conta_o]->get_y() == balas_da_nave[conta_balas]->Posicao_y()) {
                        balas_da_nave[conta_balas]->change_shock();
                        balas_da_nave[conta_balas]->clear();
                        balas_da_nave[conta_balas]->~Bullet();
                        balas_da_nave.erase(balas_da_nave.begin() + conta_balas);
                        matriz_de_obtaculos3[i][conta_o]->~obstacles();
                        matriz_de_obtaculos3[i].erase(matriz_de_obtaculos3[i].begin() + conta_o);
                    }
            // colisao da bala da nave com os inimigos
        int conta_linhas_do_inimigo_vazias = 0;
        for (int i = 0; i < numero_de_inimigos; i++)
            if (!inimigos[i].empty()) {
                for (int conta_enemies = 0; conta_enemies < inimigos[i].size(); conta_enemies++)
                    for (int conta_balas = 0; conta_balas < balas_da_nave.size(); conta_balas++)
                        if (inimigos[i][conta_enemies]->colisao(balas_da_nave[conta_balas]->Posicao_x(), balas_da_nave[conta_balas]->Posicao_y()) == true) {
                            balas_da_nave[conta_balas]->change_shock();
                            balas_da_nave[conta_balas]->clear();
                            balas_da_nave[conta_balas]->~Bullet();
                            balas_da_nave.erase(balas_da_nave.begin() + conta_balas);
                            inimigos[i][conta_enemies]->clear();
                            inimigos[i][conta_enemies]->~Enemie();
                            inimigos[i].erase(inimigos[i].begin() + conta_enemies);
                            Score += 150;
                        }
            }
            else
                conta_linhas_do_inimigo_vazias++;
        if (conta_linhas_do_inimigo_vazias == 4)
            Score += 400;

        //Mover Balas
        for (int conta_balas = 0; conta_balas < balas_da_nave.size(); conta_balas++) {
            balas_da_nave[conta_balas]->GO_UP();
            if (balas_da_nave[conta_balas]->colisao() == true) { // Deteta a colisão da bala com o Teto
                balas_da_nave[conta_balas]->~Bullet(); // Destroi a bala que colidiu
                balas_da_nave.erase(balas_da_nave.begin() + conta_balas);
            }
        }
        for (int i = 0; i < numero_de_inimigos; i++)
            for (int conta_inimigos = 0; conta_inimigos < inimigos[i].size(); conta_inimigos++)
                inimigos[i][conta_inimigos]->move_balas();
        //  colisão da bala dos inimigos com a bala da Nave
        for (int i = 0; i < numero_de_inimigos; i++)
            for (int conta_inimigos = 0; conta_inimigos < inimigos[i].size(); conta_inimigos++)
                if (!inimigos[i][conta_inimigos]->get_balas_inimigo().empty())
                    for (int conta_balas_dos_inimigos = 0; conta_balas_dos_inimigos < inimigos[i][conta_inimigos]->get_balas_inimigo().size(); conta_balas_dos_inimigos++)
                        for (int conta_balas_da_nave = 0; conta_balas_da_nave < n.get_balas().size(); conta_balas_da_nave++)
                            if (inimigos[i][conta_inimigos]->get_balas_inimigo()[conta_balas_dos_inimigos]->Posicao_x() == n.get_balas()[conta_balas_da_nave]->Posicao_x() && 
                                inimigos[i][conta_inimigos]->get_balas_inimigo()[conta_balas_dos_inimigos]->Posicao_y() == n.get_balas()[conta_balas_da_nave]->Posicao_y()) {
                                inimigos[i][conta_inimigos]->get_balas_inimigo()[conta_balas_dos_inimigos]->change_shock();
                                inimigos[i][conta_inimigos]->get_balas_inimigo()[conta_balas_dos_inimigos]->clear();
                                inimigos[i][conta_inimigos]->get_balas_inimigo()[conta_balas_dos_inimigos]->~Bullet();
                                inimigos[i][conta_inimigos]->shock();
                                balas_da_nave[conta_balas_da_nave]->clear();
                                balas_da_nave[conta_balas_da_nave]->~Bullet();
                                balas_da_nave.erase(balas_da_nave.begin() + conta_balas_da_nave);
                        }
    // colisao da bala dos inimigo com os obstaculos
    for (int i = 0; i < 3; i++)
        for (int conta_o = 0; conta_o < matriz_de_obtaculos1[i].size(); conta_o++)
            for (int j = 0; j < numero_de_inimigos; j++)
                for (int conta_inimigos = 0; conta_inimigos < inimigos[j].size(); conta_inimigos++) 
                    if (!inimigos[j][conta_inimigos]->get_balas_inimigo().empty()) 
                        for (int conta_balas = 0; conta_balas < inimigos[j][conta_inimigos]->get_balas_inimigo().size(); conta_balas++)
                            if (matriz_de_obtaculos1[i][conta_o]->get_x() == inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->Posicao_x() &&
                                matriz_de_obtaculos1[i][conta_o]->get_y() == inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->Posicao_y()) {
                                inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->change_shock();
                                inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->clear();
                                inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->~Bullet();
                                inimigos[j][conta_inimigos]->shock();
                                matriz_de_obtaculos1[i][conta_o]->~obstacles();
                                //matriz_de_obtaculos1[i].erase(matriz_de_obtaculos1[i].begin() + conta_o);
                            }
    for (int i = 0; i < 3; i++)
        for (int conta_o = 0; conta_o < matriz_de_obtaculos2[i].size(); conta_o++)
            for (int j = 0; j < numero_de_inimigos; j++)
                for (int conta_inimigos = 0; conta_inimigos < inimigos[j].size(); conta_inimigos++)
                    if (!inimigos[j][conta_inimigos]->get_balas_inimigo().empty())
                        for (int conta_balas = 0; conta_balas < inimigos[j][conta_inimigos]->get_balas_inimigo().size(); conta_balas++)
                            if (matriz_de_obtaculos2[i][conta_o]->get_x() == inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->Posicao_x() &&
                                matriz_de_obtaculos2[i][conta_o]->get_y() == inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->Posicao_y()) {
                                inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->change_shock();
                                inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->clear();
                                inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->~Bullet();
                                matriz_de_obtaculos2[i][conta_o]->~obstacles();
                                //matriz_de_obtaculos2[i].erase(matriz_de_obtaculos2[i].begin() + conta_o);
                            }
    for (int i = 0; i < 3; i++)
        for (int conta_o = 0; conta_o < matriz_de_obtaculos3[i].size(); conta_o++)
            for (int j = 0; j < numero_de_inimigos; j++)
                for (int conta_inimigos = 0; conta_inimigos < inimigos[j].size(); conta_inimigos++)
                    if (!inimigos[j][conta_inimigos]->get_balas_inimigo().empty())
                        for (int conta_balas = 0; conta_balas < inimigos[j][conta_inimigos]->get_balas_inimigo().size(); conta_balas++)
                            if (matriz_de_obtaculos3[i][conta_o]->get_x() == inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->Posicao_x() &&
                                matriz_de_obtaculos3[i][conta_o]->get_y() == inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->Posicao_y()) {
                                inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->change_shock();
                                inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->clear();
                                inimigos[j][conta_inimigos]->get_balas_inimigo()[conta_balas]->~Bullet();
                                inimigos[j][conta_inimigos]->shock();
                                matriz_de_obtaculos3[i][conta_o]->~obstacles();
                                //matriz_de_obtaculos3[i].erase(matriz_de_obtaculos2[i].begin() + conta_o);
                            }
    // colisao da bala dos inimigos com a nave 
    for (int i = 0; i < numero_de_inimigos; i++)
       if(!inimigos[i].empty()) 
            for (int conta_inimigos = 0; conta_inimigos < inimigos[i].size(); conta_inimigos++) 
                if (!inimigos[i][conta_inimigos]->get_balas_inimigo().empty()) 
                    for (int conta_balas = 0; conta_balas < inimigos[i][conta_inimigos]->get_balas_inimigo().size();conta_balas++) 
                        if (n.colisao(inimigos[i][conta_inimigos]->get_balas_inimigo()[conta_balas]->Posicao_x(), inimigos[i][conta_inimigos]->get_balas_inimigo()[conta_balas]->Posicao_y()) == true) {
                            inimigos[i][conta_inimigos]->get_balas_inimigo()[conta_balas]->change_shock();
                            inimigos[i][conta_inimigos]->get_balas_inimigo()[conta_balas]->clear();
                            inimigos[i][conta_inimigos]->get_balas_inimigo()[conta_balas]->~Bullet();         
                            inimigos[i][conta_inimigos]->shock();
                            n.clear();
                            n.~Nave();
                            // GameOver
                            while (true) {
                                WINDOW* GAME_OVER = newwin(13, 55, 10, 30);
                                has_colors();
                                start_color();
                                box(GAME_OVER, 0, 0);
                                init_pair(2, COLOR_GREEN, COLOR_GREEN);
                                wattron(GAME_OVER, COLOR_PAIR(2));

                                //  LETRA G
                                mvwprintw(GAME_OVER, 1, 1, "2222222");
                                mvwprintw(GAME_OVER, 2, 1, "2");
                                mvwprintw(GAME_OVER, 3, 1, "2");
                                mvwprintw(GAME_OVER, 4, 1, "2");
                                mvwprintw(GAME_OVER, 5, 1, "2222222");
                                mvwprintw(GAME_OVER, 3, 5, "222");
                                mvwprintw(GAME_OVER, 4, 7, "2");
                                //LETRA A
                                mvwprintw(GAME_OVER, 1, 9, "2222222");
                                mvwprintw(GAME_OVER, 2, 9, "2");
                                mvwprintw(GAME_OVER, 3, 9, "2222222");
                                mvwprintw(GAME_OVER, 4, 9, "2");
                                mvwprintw(GAME_OVER, 5, 9, "2");
                                mvwprintw(GAME_OVER, 2, 15, "2");
                                mvwprintw(GAME_OVER, 4, 15, "2");
                                mvwprintw(GAME_OVER, 5, 15, "2");

                                //letra M
                                mvwprintw(GAME_OVER, 1, 17, "2");
                                mvwprintw(GAME_OVER, 2, 17, "2");
                                mvwprintw(GAME_OVER, 3, 17, "2");
                                mvwprintw(GAME_OVER, 4, 17, "2");
                                mvwprintw(GAME_OVER, 5, 17, "2");
                                mvwprintw(GAME_OVER, 1, 24, "2");
                                mvwprintw(GAME_OVER, 2, 24, "2");
                                mvwprintw(GAME_OVER, 3, 24, "2");
                                mvwprintw(GAME_OVER, 4, 24, "2");
                                mvwprintw(GAME_OVER, 5, 24, "2");
                                mvwprintw(GAME_OVER, 1, 18, "2");
                                mvwprintw(GAME_OVER, 2, 19, "2");
                                mvwprintw(GAME_OVER, 3, 20, "2");
                                mvwprintw(GAME_OVER, 1, 23, "2");
                                mvwprintw(GAME_OVER, 2, 22, "2");
                                mvwprintw(GAME_OVER, 3, 21, "2");


                                //letra e
                                mvwprintw(GAME_OVER, 1, 26, "2222222");
                                mvwprintw(GAME_OVER, 2, 26, "2");
                                mvwprintw(GAME_OVER, 3, 26, "2222");
                                mvwprintw(GAME_OVER, 4, 26, "2");
                                mvwprintw(GAME_OVER, 5, 26, "2222222");

                                //letra o

                                mvwprintw(GAME_OVER, 7, 17, "22222222");
                                mvwprintw(GAME_OVER, 8, 17, "2");
                                mvwprintw(GAME_OVER, 9, 17, "2");
                                mvwprintw(GAME_OVER, 10, 17, "2");
                                mvwprintw(GAME_OVER, 11, 17, "22222222");
                                mvwprintw(GAME_OVER, 8, 24, "2");
                                mvwprintw(GAME_OVER, 9, 24, "2");
                                mvwprintw(GAME_OVER, 10, 24, "2");


                                //LETRA V

                                mvwprintw(GAME_OVER, 7, 26, "2");
                                mvwprintw(GAME_OVER, 8, 27, "2");
                                mvwprintw(GAME_OVER, 9, 27, "2");
                                mvwprintw(GAME_OVER, 10, 28, "2");
                                mvwprintw(GAME_OVER, 11, 29, "2");
                                mvwprintw(GAME_OVER, 10, 30, "2");
                                mvwprintw(GAME_OVER, 9, 31, "2");
                                mvwprintw(GAME_OVER, 8, 31, "2");
                                mvwprintw(GAME_OVER, 7, 32, "2");

                                //LETRA E
                                mvwprintw(GAME_OVER, 7, 34, "2222222");
                                mvwprintw(GAME_OVER, 8, 34, "2");
                                mvwprintw(GAME_OVER, 9, 34, "2222");
                                mvwprintw(GAME_OVER, 10, 34, "2");
                                mvwprintw(GAME_OVER, 11, 34, "2222222");

                                //LETRA R
                                mvwprintw(GAME_OVER, 7, 43, "2222222");
                                mvwprintw(GAME_OVER, 8, 43, "2");
                                mvwprintw(GAME_OVER, 9, 43, "2222222");
                                mvwprintw(GAME_OVER, 10, 43, "2");
                                mvwprintw(GAME_OVER, 11, 43, "2");
                                mvwprintw(GAME_OVER, 8, 43, "2");
                                mvwprintw(GAME_OVER, 10, 47, "2");
                                mvwprintw(GAME_OVER, 11, 48, "22");
                                mvwprintw(GAME_OVER, 8, 49, "2");

                                wattroff(GAME_OVER, COLOR_PAIR(2));
                                refresh();
                                wrefresh(GAME_OVER);
                                mvwprintw(GAME_OVER, 1, 36, "SCORE: %d", Score);
                                refresh();
                                wrefresh(GAME_OVER);
                                getchar();
                                key = true;
                                clear();
                                wclear(GAME_OVER);
                                break;
                            }
                        }
    
// Devolver as Alterações às classes 
        n.Obter_alteracao_balas(balas_da_nave);
        e.Obter_Alteracoes_Enemies(inimigos);
        for (int i = 0; i < 3; i++)
            o1.Obter_alteracao_obtaculos(matriz_de_obtaculos1);
        for (int i = 0; i < 3; i++) 
            o2.Obter_alteracao_obtaculos(matriz_de_obtaculos2);
        for (int i = 0; i < 3; i++) 
            o3.Obter_alteracao_obtaculos(matriz_de_obtaculos3);
        if (e.Verifica_Integridade() == true) {// Verifica se não existe mais inimigos
            e.reset(); // Faz reset ao jogo
            //reset aos obstáculos
            o1.reset();
            o2.reset();
            o3.reset();
        } 

        //Pontuação
        mvwprintw(GAME, 28, 1, "Score: %0.d", Score);
        //refresh com o movimento da nave
        int mov = getch();
            if (mov == ERR)
                d.refresh();
            else {
                d.refresh();
                key = n.jogar_nave(mov);
            } 
        refresh();
        wrefresh(GAME);
    }
}

void menu()
{   
    int cursor = 0;
    bool Selecionado = false;
    bool first = false;
    bool key_menu = false; 
    curs_set(0);
    int XMAX, xmax;
    int YMAX, ymax;
    WINDOW* MENU = newwin(30, 120, 0, 0);
    getmaxyx(MENU, YMAX, XMAX);
    WINDOW* JanelaPrincipal = newwin(YMAX / 2 - 4, XMAX / 2 - 4, YMAX / 4 + 11, XMAX / 4);
    keypad(JanelaPrincipal, true);
    WINDOW* DESENHO = newwin(17, 120, 0, 0);
    has_colors();
    start_color();
    //LETRA S
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    wattron(DESENHO, COLOR_PAIR(1));
    mvwprintw(DESENHO, 1, 1, "11111111111");
    mvwprintw(DESENHO, 2, 1, "11");
    mvwprintw(DESENHO, 3, 1, "11");
    mvwprintw(DESENHO, 4, 1, "11111111111");
    mvwprintw(DESENHO, 5, 10, "11");
    mvwprintw(DESENHO, 6, 10, "11");
    mvwprintw(DESENHO, 7, 1, "11111111111");


    //LETRA p
    mvwprintw(DESENHO, 1, 13, "11111111111");
    mvwprintw(DESENHO, 2, 13, "11");
    mvwprintw(DESENHO, 3, 13, "11");
    mvwprintw(DESENHO, 2, 22, "11");
    mvwprintw(DESENHO, 3, 22, "11");
    mvwprintw(DESENHO, 4, 13, "11111111111");
    mvwprintw(DESENHO, 5, 13, "11");
    mvwprintw(DESENHO, 6, 13, "11");
    mvwprintw(DESENHO, 7, 13, "11");


    //LETRA A
    mvwprintw(DESENHO, 1, 25, "11111111111");
    mvwprintw(DESENHO, 2, 25, "11");
    mvwprintw(DESENHO, 3, 25, "11");
    mvwprintw(DESENHO, 4, 25, "11111111111");
    mvwprintw(DESENHO, 5, 25, "11");
    mvwprintw(DESENHO, 6, 25, "11");
    mvwprintw(DESENHO, 7, 25, "11");
    mvwprintw(DESENHO, 2, 34, "11");
    mvwprintw(DESENHO, 3, 34, "11");
    mvwprintw(DESENHO, 5, 34, "11");
    mvwprintw(DESENHO, 6, 34, "11");
    mvwprintw(DESENHO, 7, 34, "11");



    //LETRA C
    mvwprintw(DESENHO, 1, 37, "11111111111");
    mvwprintw(DESENHO, 2, 37, "11");
    mvwprintw(DESENHO, 3, 37, "11");
    mvwprintw(DESENHO, 4, 37, "11");
    mvwprintw(DESENHO, 5, 37, "11");
    mvwprintw(DESENHO, 6, 37, "11");
    mvwprintw(DESENHO, 7, 37, "11111111111");


    //LETRA E
    mvwprintw(DESENHO, 1, 49, "11111111111");
    mvwprintw(DESENHO, 2, 49, "11");
    mvwprintw(DESENHO, 3, 49, "11");
    mvwprintw(DESENHO, 4, 49, "111111");
    mvwprintw(DESENHO, 5, 49, "11");
    mvwprintw(DESENHO, 6, 49, "11");
    mvwprintw(DESENHO, 7, 49, "11111111111");


    //LETRA I
    mvwprintw(DESENHO, 10, 13, "11111111111");
    mvwprintw(DESENHO, 11, 18, "11");
    mvwprintw(DESENHO, 12, 18, "11");
    mvwprintw(DESENHO, 13, 18, "11");
    mvwprintw(DESENHO, 14, 18, "11");
    mvwprintw(DESENHO, 15, 18, "11");
    mvwprintw(DESENHO, 16, 13, "11111111111");


    //LETRA N
    mvwprintw(DESENHO, 10, 25, "11");
    mvwprintw(DESENHO, 11, 25, "11");
    mvwprintw(DESENHO, 12, 25, "11");
    mvwprintw(DESENHO, 13, 25, "11");
    mvwprintw(DESENHO, 14, 25, "11");
    mvwprintw(DESENHO, 15, 25, "11");
    mvwprintw(DESENHO, 16, 25, "11");
    mvwprintw(DESENHO, 10, 27, "1");
    mvwprintw(DESENHO, 11, 28, "1");
    mvwprintw(DESENHO, 12, 29, "1");
    mvwprintw(DESENHO, 13, 30, "1");
    mvwprintw(DESENHO, 14, 31, "1");
    mvwprintw(DESENHO, 15, 32, "1");
    mvwprintw(DESENHO, 16, 33, "1");
    mvwprintw(DESENHO, 10, 34, "11");
    mvwprintw(DESENHO, 11, 34, "11");
    mvwprintw(DESENHO, 12, 34, "11");
    mvwprintw(DESENHO, 13, 34, "11");
    mvwprintw(DESENHO, 14, 34, "11");
    mvwprintw(DESENHO, 15, 34, "11");
    mvwprintw(DESENHO, 16, 34, "11");

    //LETRA V
    mvwprintw(DESENHO, 10, 37, "11");
    mvwprintw(DESENHO, 11, 38, "11");
    mvwprintw(DESENHO, 12, 38, "11");
    mvwprintw(DESENHO, 13, 39, "11");
    mvwprintw(DESENHO, 14, 40, "11");
    mvwprintw(DESENHO, 15, 40, "11");
    mvwprintw(DESENHO, 16, 41, "111");
    mvwprintw(DESENHO, 10, 46, "11");
    mvwprintw(DESENHO, 11, 45, "11");
    mvwprintw(DESENHO, 12, 45, "11");
    mvwprintw(DESENHO, 13, 44, "11");
    mvwprintw(DESENHO, 14, 43, "11");
    mvwprintw(DESENHO, 15, 43, "11");


    //LETRA A
    mvwprintw(DESENHO, 10, 49, "11111111111");
    mvwprintw(DESENHO, 11, 49, "11");
    mvwprintw(DESENHO, 12, 49, "11");
    mvwprintw(DESENHO, 14, 49, "11");
    mvwprintw(DESENHO, 13, 49, "11111111111");
    mvwprintw(DESENHO, 15, 49, "11");
    mvwprintw(DESENHO, 16, 49, "11");
    mvwprintw(DESENHO, 17, 49, "11");
    mvwprintw(DESENHO, 11, 58, "11");
    mvwprintw(DESENHO, 12, 58, "11");
    mvwprintw(DESENHO, 13, 58, "11");
    mvwprintw(DESENHO, 14, 58, "11");
    mvwprintw(DESENHO, 15, 58, "11");
    mvwprintw(DESENHO, 16, 58, "11");
    mvwprintw(DESENHO, 17, 58, "11");


    //LETRA D
    mvwprintw(DESENHO, 10, 61, "111111111");
    mvwprintw(DESENHO, 11, 61, "11");
    mvwprintw(DESENHO, 12, 61, "11");
    mvwprintw(DESENHO, 14, 61, "11");
    mvwprintw(DESENHO, 13, 61, "11");
    mvwprintw(DESENHO, 15, 61, "11");
    mvwprintw(DESENHO, 16, 61, "11");
    mvwprintw(DESENHO, 11, 69, "11");
    mvwprintw(DESENHO, 12, 70, "1");
    mvwprintw(DESENHO, 13, 70, "1");
    mvwprintw(DESENHO, 14, 70, "1");
    mvwprintw(DESENHO, 15, 69, "11");
    mvwprintw(DESENHO, 16, 61, "111111111");


    //LETRA E
    mvwprintw(DESENHO, 10, 72, "11111111111");
    mvwprintw(DESENHO, 11, 72, "11");
    mvwprintw(DESENHO, 12, 72, "11");
    mvwprintw(DESENHO, 13, 72, "111111");
    mvwprintw(DESENHO, 14, 72, "11");
    mvwprintw(DESENHO, 15, 72, "11");
    mvwprintw(DESENHO, 16, 72, "11111111111");

    //LETRA R
    mvwprintw(DESENHO, 10, 84, "11111111111");
    mvwprintw(DESENHO, 11, 84, "11");
    mvwprintw(DESENHO, 12, 84, "11");
    mvwprintw(DESENHO, 11, 93, "11");
    mvwprintw(DESENHO, 12, 93, "11");
    mvwprintw(DESENHO, 13, 84, "11111111111");
    mvwprintw(DESENHO, 14, 84, "11");
    mvwprintw(DESENHO, 15, 84, "11");
    mvwprintw(DESENHO, 16, 84, "11");
    mvwprintw(DESENHO, 14, 86, "111");
    mvwprintw(DESENHO, 15, 89, "111");
    mvwprintw(DESENHO, 16, 92, "111");

    //LETRA S
    mvwprintw(DESENHO, 10, 96, "11111111111");
    mvwprintw(DESENHO, 11, 96, "11");
    mvwprintw(DESENHO, 12, 96, "11");
    mvwprintw(DESENHO, 13, 96, "11111111111");
    mvwprintw(DESENHO, 14, 105, "11");
    mvwprintw(DESENHO, 15, 105, "11");
    mvwprintw(DESENHO, 16, 96, "11111111111");
    wattroff(DESENHO, COLOR_PAIR(1));

    refresh();
    wrefresh(MENU);
    wrefresh(DESENHO);
while (1) {
    if (key_menu == true)
        break;
    WINDOW* DESENHO = newwin(17, 120, 0, 0);
    start_color();
    //LETRA S
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    wattron(DESENHO, COLOR_PAIR(1));
    mvwprintw(DESENHO, 1, 1, "11111111111");
    mvwprintw(DESENHO, 2, 1, "11");
    mvwprintw(DESENHO, 3, 1, "11");
    mvwprintw(DESENHO, 4, 1, "11111111111");
    mvwprintw(DESENHO, 5, 10, "11");
    mvwprintw(DESENHO, 6, 10, "11");
    mvwprintw(DESENHO, 7, 1, "11111111111");


    //LETRA p
    mvwprintw(DESENHO, 1, 13, "11111111111");
    mvwprintw(DESENHO, 2, 13, "11");
    mvwprintw(DESENHO, 3, 13, "11");
    mvwprintw(DESENHO, 2, 22, "11");
    mvwprintw(DESENHO, 3, 22, "11");
    mvwprintw(DESENHO, 4, 13, "11111111111");
    mvwprintw(DESENHO, 5, 13, "11");
    mvwprintw(DESENHO, 6, 13, "11");
    mvwprintw(DESENHO, 7, 13, "11");


    //LETRA A
    mvwprintw(DESENHO, 1, 25, "11111111111");
    mvwprintw(DESENHO, 2, 25, "11");
    mvwprintw(DESENHO, 3, 25, "11");
    mvwprintw(DESENHO, 4, 25, "11111111111");
    mvwprintw(DESENHO, 5, 25, "11");
    mvwprintw(DESENHO, 6, 25, "11");
    mvwprintw(DESENHO, 7, 25, "11");
    mvwprintw(DESENHO, 2, 34, "11");
    mvwprintw(DESENHO, 3, 34, "11");
    mvwprintw(DESENHO, 5, 34, "11");
    mvwprintw(DESENHO, 6, 34, "11");
    mvwprintw(DESENHO, 7, 34, "11");



    //LETRA C
    mvwprintw(DESENHO, 1, 37, "11111111111");
    mvwprintw(DESENHO, 2, 37, "11");
    mvwprintw(DESENHO, 3, 37, "11");
    mvwprintw(DESENHO, 4, 37, "11");
    mvwprintw(DESENHO, 5, 37, "11");
    mvwprintw(DESENHO, 6, 37, "11");
    mvwprintw(DESENHO, 7, 37, "11111111111");


    //LETRA E
    mvwprintw(DESENHO, 1, 49, "11111111111");
    mvwprintw(DESENHO, 2, 49, "11");
    mvwprintw(DESENHO, 3, 49, "11");
    mvwprintw(DESENHO, 4, 49, "111111");
    mvwprintw(DESENHO, 5, 49, "11");
    mvwprintw(DESENHO, 6, 49, "11");
    mvwprintw(DESENHO, 7, 49, "11111111111");


    //LETRA I
    mvwprintw(DESENHO, 10, 13, "11111111111");
    mvwprintw(DESENHO, 11, 18, "11");
    mvwprintw(DESENHO, 12, 18, "11");
    mvwprintw(DESENHO, 13, 18, "11");
    mvwprintw(DESENHO, 14, 18, "11");
    mvwprintw(DESENHO, 15, 18, "11");
    mvwprintw(DESENHO, 16, 13, "11111111111");


    //LETRA N
    mvwprintw(DESENHO, 10, 25, "11");
    mvwprintw(DESENHO, 11, 25, "11");
    mvwprintw(DESENHO, 12, 25, "11");
    mvwprintw(DESENHO, 13, 25, "11");
    mvwprintw(DESENHO, 14, 25, "11");
    mvwprintw(DESENHO, 15, 25, "11");
    mvwprintw(DESENHO, 16, 25, "11");
    mvwprintw(DESENHO, 10, 27, "1");
    mvwprintw(DESENHO, 11, 28, "1");
    mvwprintw(DESENHO, 12, 29, "1");
    mvwprintw(DESENHO, 13, 30, "1");
    mvwprintw(DESENHO, 14, 31, "1");
    mvwprintw(DESENHO, 15, 32, "1");
    mvwprintw(DESENHO, 16, 33, "1");
    mvwprintw(DESENHO, 10, 34, "11");
    mvwprintw(DESENHO, 11, 34, "11");
    mvwprintw(DESENHO, 12, 34, "11");
    mvwprintw(DESENHO, 13, 34, "11");
    mvwprintw(DESENHO, 14, 34, "11");
    mvwprintw(DESENHO, 15, 34, "11");
    mvwprintw(DESENHO, 16, 34, "11");

    //LETRA V
    mvwprintw(DESENHO, 10, 37, "11");
    mvwprintw(DESENHO, 11, 38, "11");
    mvwprintw(DESENHO, 12, 38, "11");
    mvwprintw(DESENHO, 13, 39, "11");
    mvwprintw(DESENHO, 14, 40, "11");
    mvwprintw(DESENHO, 15, 40, "11");
    mvwprintw(DESENHO, 16, 41, "111");
    mvwprintw(DESENHO, 10, 46, "11");
    mvwprintw(DESENHO, 11, 45, "11");
    mvwprintw(DESENHO, 12, 45, "11");
    mvwprintw(DESENHO, 13, 44, "11");
    mvwprintw(DESENHO, 14, 43, "11");
    mvwprintw(DESENHO, 15, 43, "11");


    //LETRA A
    mvwprintw(DESENHO, 10, 49, "11111111111");
    mvwprintw(DESENHO, 11, 49, "11");
    mvwprintw(DESENHO, 12, 49, "11");
    mvwprintw(DESENHO, 14, 49, "11");
    mvwprintw(DESENHO, 13, 49, "11111111111");
    mvwprintw(DESENHO, 15, 49, "11");
    mvwprintw(DESENHO, 16, 49, "11");
    mvwprintw(DESENHO, 17, 49, "11");
    mvwprintw(DESENHO, 11, 58, "11");
    mvwprintw(DESENHO, 12, 58, "11");
    mvwprintw(DESENHO, 13, 58, "11");
    mvwprintw(DESENHO, 14, 58, "11");
    mvwprintw(DESENHO, 15, 58, "11");
    mvwprintw(DESENHO, 16, 58, "11");
    mvwprintw(DESENHO, 17, 58, "11");


    //LETRA D
    mvwprintw(DESENHO, 10, 61, "111111111");
    mvwprintw(DESENHO, 11, 61, "11");
    mvwprintw(DESENHO, 12, 61, "11");
    mvwprintw(DESENHO, 14, 61, "11");
    mvwprintw(DESENHO, 13, 61, "11");
    mvwprintw(DESENHO, 15, 61, "11");
    mvwprintw(DESENHO, 16, 61, "11");
    mvwprintw(DESENHO, 11, 69, "11");
    mvwprintw(DESENHO, 12, 70, "1");
    mvwprintw(DESENHO, 13, 70, "1");
    mvwprintw(DESENHO, 14, 70, "1");
    mvwprintw(DESENHO, 15, 69, "11");
    mvwprintw(DESENHO, 16, 61, "111111111");


    //LETRA E
    mvwprintw(DESENHO, 10, 72, "11111111111");
    mvwprintw(DESENHO, 11, 72, "11");
    mvwprintw(DESENHO, 12, 72, "11");
    mvwprintw(DESENHO, 13, 72, "111111");
    mvwprintw(DESENHO, 14, 72, "11");
    mvwprintw(DESENHO, 15, 72, "11");
    mvwprintw(DESENHO, 16, 72, "11111111111");

    //LETRA R
    mvwprintw(DESENHO, 10, 84, "11111111111");
    mvwprintw(DESENHO, 11, 84, "11");
    mvwprintw(DESENHO, 12, 84, "11");
    mvwprintw(DESENHO, 11, 93, "11");
    mvwprintw(DESENHO, 12, 93, "11");
    mvwprintw(DESENHO, 13, 84, "11111111111");
    mvwprintw(DESENHO, 14, 84, "11");
    mvwprintw(DESENHO, 15, 84, "11");
    mvwprintw(DESENHO, 16, 84, "11");
    mvwprintw(DESENHO, 14, 86, "111");
    mvwprintw(DESENHO, 15, 89, "111");
    mvwprintw(DESENHO, 16, 92, "111");

    //LETRA S
    mvwprintw(DESENHO, 10, 96, "11111111111");
    mvwprintw(DESENHO, 11, 96, "11");
    mvwprintw(DESENHO, 12, 96, "11");
    mvwprintw(DESENHO, 13, 96, "11111111111");
    mvwprintw(DESENHO, 14, 105, "11");
    mvwprintw(DESENHO, 15, 105, "11");
    mvwprintw(DESENHO, 16, 96, "11111111111");
    wattroff(DESENHO, COLOR_PAIR(1));

    refresh();
    wrefresh(MENU);
    wrefresh(DESENHO);

    if(first == false){
    mvwaddch(JanelaPrincipal, 3, 21, ACS_DIAMOND);
    first = true;
    }
    //inicializacoes do menu
    mvwprintw(JanelaPrincipal, 1, 23, "Menu:");
    mvwprintw(JanelaPrincipal, 3, 23, "New game:");
    mvwprintw(JanelaPrincipal, 5, 23, "Leave the game:");
    wborder(JanelaPrincipal, 0, 0, 0, 0, 0, 0, 0, 0);
    int op = wgetch(JanelaPrincipal);
        
    switch (op) {
        case KEY_UP:
            if (cursor > 0)
                cursor--;
            else
                cursor = 0;
            break;
        case KEY_DOWN:
            if (cursor < 2)
                cursor++;
            else
                cursor = 2;
            break;
        case 'a':
            Selecionado = true;
            break;
        default:
            break;
    }
        
    if (cursor == 0 && Selecionado == false) {
        mvwaddch(JanelaPrincipal, 3,21, ACS_DIAMOND);
        mvwaddch(JanelaPrincipal, 5, 21, 32);
    }
    if(cursor == 0 && Selecionado == true) {
        clear();
        wclear(JanelaPrincipal);
        wclear(MENU);
        game_loop();
        Selecionado = false;
        first = false;
    }

    if (cursor == 1 && Selecionado == false) {
        mvwaddch(JanelaPrincipal, 3, 21, 32);
        mvwaddch(JanelaPrincipal, 5, 21, ACS_DIAMOND);   
    }
    if (cursor == 1 && Selecionado == true) {
        key_menu = true;
        Selecionado = false;
    }
    refresh();
    wrefresh(JanelaPrincipal);
    }
    
}
int main()
{
    //fullscreen();
    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    menu();
    getch();
    endwin();
}