/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TEXTE_H__
#define __TEXTE_H__

#include <string>

class Jeu;

class Texte {
    typedef std::string ( Texte::*LANGFUNC ) ( int, std::string );

    public :
        Texte(Jeu* jeu);
        ~Texte();
        void draw(SDL_Surface* gpScreen);
        void setTexte(int idTxt, int vx, int vy, int vw, int vh, bool cadr, bool defil, int vit=30);
        bool suite();
        void affiche(SDL_Surface* gpScreen, std::string s, int a, int b);
        void afficheTexteAvecId(SDL_Surface* gpScreen, int id, std::string s, int a, int b);
        bool isFinished();
        void changeId(int i);
        void setTextLanguage(int id);
        int getId();
    private :
        bool hasNext();
        void drawCadre(SDL_Surface* gpScreen);
        void chercheText();
        void decoupeText();
        std::string getTexteEN(int id, std::string s);
        std::string getTexteFR(int id, std::string s);
        std::string getTexteDE(int id, std::string s);
        std::string getTexteES(int id, std::string s);
        int tailleMot(int deb);
        int afficheCaractere(SDL_Surface* gpScreen, char c, int &i, std::string s, int vx, int vy);
        void afficheLettre(SDL_Surface* gpScreen, char c, int vx, int vy);
        void affichePSBouton(SDL_Surface* gpScreen, int index, int vx, int vy);

        Jeu* gpJeu;
        int vitesse; // millisecondes entre 2 lettres
        int av; //avancement du défilement
        int x;
        int y;
        int w;
        int h;
        int id;
        int idsuiv;
        bool def; //si le texte doit défiler
        bool cadre; //si on doit dessiner un cadre
        std::string texte;
        std::string buffer;
        Uint32 lastAnimTime;
        SDL_Surface* imageFont;
        SDL_Surface* imageButtons;
        SDL_Surface* imageCoeur;
        LANGFUNC getTextByLangFunc;
};

#endif  // Texte.h
