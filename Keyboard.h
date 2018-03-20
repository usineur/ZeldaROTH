/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "Carte.h"
#include "Encyclopedie.h"

class Keyboard {
    public :
        Keyboard(Jeu* jeu, Carte* carte, Encyclopedie* encycl, SDL_Surface* screen, int m);
        int gererClavier();
        int getMode();
        void setMode(int i);
        int getLigne();
        int getColonne();
        int getSave(int i);
        void setSave(int i, int val);
        int getLigneOption();
        int getVolume();
        int getVolson();
        int getLigneRecord();
        int getColonneRecord();
        int getTemps();
        void setTemps(int t);
        int getRang(int i);
        void setRang(int i);
        int getLigneVal();
        int getIntro();
        void saveP();
    private :
        void loadP();
        int pollKey(SDL_Event event);
        void pollKeys(Uint8* keys);
        void toggleFullScreen();
        int buttonPressed(int i);
        int stickPosition(int stick, int direction);
        
        Jeu* gpJeu;
        Carte* gpCarte;
        Encyclopedie* gpEncyclopedie;
        int mode;
        int gFullScreen;
        SDL_Surface* gpScreen;
        int tmp;
        int tmpx;
        int tmpc;
        int tmpw;
        int tmpt;
        int tmpp;
        int tmpm;
        int ligne;
        int colonne;
        int save[3];
        int ligneOption;
        int volume;
        int volson;
        int ligneRecord;
        int colonneRecord;
        int temps;
        int rang[3];
        int ligneVal;
        int intro;
        int verrRun;
        SDL_Event event;
        Uint8* keys;
        
#ifdef __vita__
        SDL_Joystick* joystick;
#endif
};

#endif  // Keyboard.h
