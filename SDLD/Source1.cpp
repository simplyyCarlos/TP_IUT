#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include <fstream>
#include<iostream>
#include "config_sdl.h"
using namespace std;

const int CARRE = 30;
const int LARGEUR = 12;
const int HAUTEUR = 16;
const int TAILLEX = CARRE * LARGEUR + 120 ;
const int TAILLEY = CARRE * HAUTEUR;


void tabcolor(char couleur ,SDL_Color tabcouleur[HAUTEUR][LARGEUR],int i,int j) {
    switch (couleur)
    {
    case'B':
        tabcouleur[i][j].r = 255;
        tabcouleur[i][j].g = 255;
        tabcouleur[i][j].b = 255;
        break;
    case'V':
        tabcouleur[i][j].r = 106;
        tabcouleur[i][j].g = 164;
        tabcouleur[i][j].b = 30;
        break;
    case'J':
        tabcouleur[i][j].r = 255;
        tabcouleur[i][j].g = 255;
        tabcouleur[i][j].b = 0;
        break;
    case'N':
        tabcouleur[i][j].r = 0;
        tabcouleur[i][j].g = 0;
        tabcouleur[i][j].b = 0;
        break;
    case'R':
        tabcouleur[i][j].r = 255;
        tabcouleur[i][j].g = 0;
        tabcouleur[i][j].b = 0;
        break;
    }
}



void carre(SDL_Color tabcouleur[HAUTEUR][LARGEUR],int i, int j, SDL_Renderer* rendu) {
    SDL_Rect rect;

    rect.x = j * CARRE;  
    rect.y = i * CARRE;
    rect.w = CARRE;
    rect.h = CARRE;
    SDL_SetRenderDrawColor(rendu, tabcouleur[i][j].r, tabcouleur[i][j].g, tabcouleur[i][j].b, 255);
    SDL_RenderFillRect(rendu, &rect);
}

void negatif(SDL_Color tabcouleur[HAUTEUR][LARGEUR], SDL_Renderer* rendu) {
    for (int i=0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            tabcouleur[i][j].r = 255 - tabcouleur[i][j].r;
            tabcouleur[i][j].g = 255 - tabcouleur[i][j].g;
            tabcouleur[i][j].b = 255 - tabcouleur[i][j].b;
            carre(tabcouleur, i, j, rendu);
        }
    }
    SDL_RenderPresent(rendu);

}
void charger(const char* nom_fichier, SDL_Color tabcouleur[HAUTEUR][LARGEUR], SDL_Renderer* rendu) {
    int j;
    ifstream file(nom_fichier, ios::in);//declaration du flot 
    if (!file) //si le flot vaut false
        cout << "Probleme d'ouverture " << endl;
    else {
        char ligne[50];
        for (int i = 0; i < HAUTEUR; i++) {
            for (j = 0; j < LARGEUR-1; j++) {
                file.getline(ligne, 50, ' ');
                tabcolor(*ligne,tabcouleur,  i, j);
                carre(tabcouleur, i, j, rendu);
            }
            file.getline(ligne, 50);
            tabcolor(*ligne,tabcouleur, i, j);
            carre(tabcouleur, i, j, rendu);
        }
        SDL_RenderPresent(rendu);
        file.close();
    }
          
}

void charger_palette(SDL_Renderer* rendu) {
    SDL_Rect rect;
    rect.w = CARRE;
    rect.h = CARRE;

    rect.x = CARRE * LARGEUR + 20 ;
    rect.y = 20;
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
    SDL_RenderDrawRect(rendu, &rect);

    rect.x = CARRE * LARGEUR + 60;
    rect.y = 20;
    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
    SDL_RenderFillRect(rendu, &rect);

    rect.x = CARRE * LARGEUR + 20;
    rect.y = 60;
    SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
    SDL_RenderFillRect(rendu, &rect);

    rect.x = CARRE * LARGEUR + 60;
    rect.y = 60;
    SDL_SetRenderDrawColor(rendu, 138, 164, 30, 255);
    SDL_RenderFillRect(rendu, &rect);

    rect.x = CARRE * LARGEUR + 20;
    rect.y = 100;
    SDL_SetRenderDrawColor(rendu, 255, 255, 0, 255);
    SDL_RenderFillRect(rendu, &rect);

    rect.x = CARRE * LARGEUR + 60;
    rect.y = 100;
    SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255);
    SDL_RenderFillRect(rendu, &rect);

}

int main(int argn, char* argv[]) {
    
    // Init de la sdl
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Echec à l’ouverture";
        return 1;
    }

    // Création fenêtre
    SDL_Window* SDL_Window = SDL_CreateWindow("Palette ",
        SDL_WINDOWPOS_CENTERED,     //pos. X: autre option: SDL_WINDOWPOS_UNDEFINED
        SDL_WINDOWPOS_CENTERED,     //pos. Y: autre option: SDL_WINDOWPOS_UNDEFINED 
        TAILLEX,                         //largeur en pixels                        
        TAILLEY,                         //hauteur en pixels
        SDL_WINDOW_SHOWN //d’autres options (plein ecran, resizable, sans bordure...)
    );

    if (SDL_Window == NULL)
        cout << "erreur ouverture fenetre";

    //Création d’un dessin associé à la fenêtre (1 seul renderer par fenetre)
    SDL_Renderer* rendu = SDL_CreateRenderer(
        SDL_Window,  //nom de la fenêtre
        -1, //par défaut
        SDL_RENDERER_ACCELERATED); //utilisation du GPU, valeur recommandée
    SDL_Color tabcouleur[HAUTEUR][LARGEUR];
    charger("Mystere.txt", tabcouleur,rendu);
    charger_palette(rendu);
    SDL_RenderPresent(rendu);
    
    


    bool continuer = true;   //booléen fin de programme
    SDL_Event event;//gestion des évènements souris/clavier, 
                                    //SDL_Event est de type struct
    while (continuer)
    {
        SDL_WaitEvent(&event);//attente d’un évènement
        switch (event.type) //test du type d’évènement
        {
        case SDL_QUIT:
            continuer = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_n) {
                negatif(tabcouleur, rendu);
            }
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {//si on clique bouton gauche
                if (event.button.x > CARRE * LARGEUR+20 && event.button.x<CARRE * LARGEUR + 20 + CARRE && event.button.y>20 && event.button.y < 20 + CARRE) {
                    SDL_SetRenderDrawColor(rendu, 0,0 ,0,255 );
                }
                else if (event.button.x > CARRE * LARGEUR + 60 && event.button.x < CARRE * LARGEUR + 60 + CARRE && event.button.y>20 && event.button.y < 20 + CARRE){
                    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255);
                }
                else if (event.button.x > CARRE * LARGEUR + 20 && event.button.x < CARRE * LARGEUR + 20 + CARRE && event.button.y>60 && event.button.y < 60 + CARRE) {
                    SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
                }
                else if (event.button.x > CARRE * LARGEUR + 60 && event.button.x < CARRE * LARGEUR + 60 + CARRE && event.button.y>60 && event.button.y < 60 + CARRE) {
                    SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);
                }
                else if (event.button.x > CARRE * LARGEUR + 20 && event.button.x < CARRE * LARGEUR + 20 + CARRE && event.button.y>100 && event.button.y < 100 + CARRE) {
                    SDL_SetRenderDrawColor(rendu, 255, 255, 0, 255);
                }
                else if (event.button.x > CARRE * LARGEUR + 60 && event.button.x < CARRE * LARGEUR + 60 + CARRE && event.button.y>100 && event.button.y < 100 + CARRE) {
                    SDL_SetRenderDrawColor(rendu, 0, 0, 255, 255);
                }
            }
        }
   }
    
    return 0;
}