#include<SDL.h> //ne pas oublier
#include<SDL_ttf.h> //ne pas oublier
#include<iostream>
#include "config_sdl.h"
using namespace std;
const int LARGEUR = 640; //largeur fenetre
const int HAUTEUR = 480;  //hauteur fenetre

int main(int argn, char* argv[]) {//ent�te impos�e
   //ouverture de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Echec � l�ouverture";
        return 1;
    }

    //on cr�e la fen�tre
    SDL_Window* win = SDL_CreateWindow("Titre de la fenetre",
        SDL_WINDOWPOS_CENTERED,     //pos. X: autre option: SDL_WINDOWPOS_UNDEFINED
        SDL_WINDOWPOS_CENTERED,     //pos. Y: autre option: SDL_WINDOWPOS_UNDEFINED 
        LARGEUR,                         //largeur en pixels                        
        HAUTEUR,                         //hauteur en pixels
        SDL_WINDOW_SHOWN //d�autres options (plein ecran, resizable, sans bordure...)
    );
    if (win == NULL)
        cout << "erreur ouverture fenetre";

    //Cr�ation d�un dessin associ� � la fen�tre (1 seul renderer par fenetre)
    SDL_Renderer* rendu = SDL_CreateRenderer(
        win,  //nom de la fen�tre
        -1, //par d�faut
        SDL_RENDERER_ACCELERATED); //utilisation du GPU, valeur recommand�e

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\calibri.ttf", 25);

    //changer la couleur du pinceau
    SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255); //on d�finit la couleur rouge (r,g,b,a)

    //tracer une ligne
    SDL_RenderDrawLine(rendu, 10, 0, 10, HAUTEUR); //x1,y1,x2,y2 

    SDL_Rect rect; //on d�finit le rectangle � tracer
            //SDL_Rect est un type struct        
    rect.x = LARGEUR / 2 - 100;  //coin en haut � gauche
    rect.y = HAUTEUR / 2 - 50;  //coin en haut � gauche
    rect.w = 200;                //largeur
    rect.h = 100;                //hauteur
    SDL_SetRenderDrawColor(rendu, 0, 255, 0, 255);        //pinceau vert
    SDL_RenderFillRect(rendu, &rect); //on trace un rectangle plein

    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255); //pinceau blanc
    SDL_RenderDrawRect(rendu, &rect); //on trace un rectangle vide

    SDL_Color violet = { 255,0,255 }; //on d�finit une couleur de texte
    SDL_Rect positionTexte; //rectangle d�finissant le positionnement du texte, et sa taille

    //on place le texte au point (100,100)
    positionTexte.x = 100;
    positionTexte.y = 100;
    //on cr�e une texture � partir du texte, de sa couleur, et de la fonte
    SDL_Texture* texture = loadText(rendu, "coucou", violet, font);
    //on maj le rectangle couvrant cette texture
    SDL_QueryTexture(texture, NULL, NULL, &positionTexte.w, &positionTexte.h);
    //si on veut modifier le cadre du texte
    positionTexte.w *= 3;
    positionTexte.h *= 3;
    //on copie la texture dans le rendu
    SDL_RenderCopy(rendu, texture, NULL, &positionTexte);
        //on met � jour le rendu
        SDL_RenderPresent(rendu);
    //on d�truit la texture
    SDL_DestroyTexture(texture);

    //on met � jour le rendu
    SDL_RenderPresent(rendu); //sinon on ne voit rien

    bool continuer = true;   //bool�en fin de programme
    SDL_Event event;//gestion des �v�nements souris/clavier, 
                                    //SDL_Event est de type struct
    while (continuer)
    {
        SDL_WaitEvent(&event);//attente d�un �v�nement
        switch (event.type) //test du type d��v�nement
        {
        case SDL_QUIT: //clic sur la croix de fermeture
                                        //on peut enlever SDL_Delay
            continuer = false;
            break;
        case SDL_MOUSEBUTTONUP://appui souris
            if (event.button.button == SDL_BUTTON_LEFT) {//si on clique bouton gauche
                if (event.button.x > rect.x && event.button.x<rect.x + rect.w && event.button.y>rect.y && event.button.y < rect.y + rect.h) { //dans         le rectangle
                //on retrace le rectangle avec une couleur al�atoire
                    SDL_SetRenderDrawColor(rendu, rand() % 256, rand() % 256, rand() % 256, 255); //on d�finit une clouleur aleatoire
                    SDL_RenderFillRect(rendu, &rect); //on trace un rectangle plein
                    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255); //on d�finit la couleur blanche
                    SDL_RenderDrawRect(rendu, &rect); //on trace un rectangle vide
                }
                SDL_RenderPresent(rendu);//on rafraichit
            }
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_j) { //touche j
                SDL_SetRenderDrawColor(rendu, rand() % 255, rand() % 255, rand() % 255, 255);
                SDL_RenderDrawLine(rendu, 600, 0, 600, 480);
                SDL_RenderPresent(rendu);
            }
            break;
        }
    }

    //SDL_Delay(3000); //pause de 3 secondes

    TTF_CloseFont(font); //on ferme la font
    TTF_Quit(); //on quitte la TTF

    //destruction du renderer � la fin
    SDL_DestroyRenderer(rendu);

    //destruction � la fin
    SDL_DestroyWindow(win);   //equivalent du delete


    //fermeture
    SDL_Quit();
    return 0;
}

