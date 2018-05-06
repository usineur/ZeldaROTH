/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Generique.h"
#include "Jeu.h"
#include "Keyboard.h"
#include "Lang.h"

Generique::Generique(Jeu* jeu) : gpJeu(jeu), anim(0) {
    imageFin = NULL;
    imageArbre = NULL;
    image = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    imageTitre = gpJeu->loadImg("data/images/logos/titre.png");
    SDL_SetColorKey(imageTitre,SDL_SRCCOLORKEY,SDL_MapRGB(imageTitre->format,0,0,255));
    imageCurseur = gpJeu->loadImg("data/images/logos/curseur.png");
    SDL_SetColorKey(imageCurseur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCurseur->format,0,0,255));
    imageNiveau = gpJeu->loadImg("data/images/logos/niveau.png");
    SDL_SetColorKey(imageNiveau,SDL_SRCCOLORKEY,SDL_MapRGB(imageNiveau->format,0,0,255));
    imageFee = gpJeu->loadImg("data/images/logos/fee.png");
    imageCadre = gpJeu->loadImg("data/images/logos/cadres.png");
    imageFond1 = NULL;
    imageFond2 = NULL;
    imageNuit = NULL;
    for (int i = 0; i < 5; i++) imageIntro[i]=NULL;
    imageFlags = gpJeu->loadImg("data/images/logos/flags.png");
}

Generique::~Generique() {
    SDL_FreeSurface(imageFin);
    SDL_FreeSurface(imageArbre);
    SDL_FreeSurface(image);
    SDL_FreeSurface(imageTitre);
    SDL_FreeSurface(imageCurseur);
    SDL_FreeSurface(imageNiveau);
    SDL_FreeSurface(imageFee);
    SDL_FreeSurface(imageCadre);
    SDL_FreeSurface(imageFond1);
    SDL_FreeSurface(imageFond2);
    SDL_FreeSurface(imageNuit);
    for (int i = 0; i < 5; i++) SDL_FreeSurface(imageIntro[i]);
    SDL_FreeSurface(imageFlags);
}

void Generique::drawFin(SDL_Surface* gpScreen) {
    if (!imageFin) imageFin = gpJeu->loadImg("data/images/logos/fin.png");
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(imageFin, NULL, gpScreen, &dst);
    gpJeu->getTexte()->draw(gpScreen);
}

void Generique::initDisclamer() {
    SDL_Rect dst;
    SDL_Surface* attention = gpJeu->loadImg("data/images/logos/attention.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(attention, NULL, image, &dst);
    SDL_FreeSurface(attention);
}

void Generique::initLogo() {
    SDL_Rect dst;
    SDL_Surface* logo = gpJeu->loadImg(getLanguage() == LANG_FR ? "data/images/logos/logo_FR.png" : "data/images/logos/logo.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(logo, NULL, image, &dst);
    SDL_FreeSurface(logo);
}

void Generique::initTitre() {
    SDL_Rect dst;
    SDL_Surface* fond = gpJeu->loadImg("data/images/logos/fond.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(fond, NULL, image, &dst);
    SDL_FreeSurface(fond);
    SDL_Surface* logo = gpJeu->loadImg("data/images/logos/titre.png");
    SDL_SetColorKey(logo,SDL_SRCCOLORKEY,SDL_MapRGB(logo->format,0,0,255));
    logo = SDL_DisplayFormat(logo);
    dst.x = 60; dst.y = 56-32; SDL_BlitSurface(logo, NULL, image, &dst);
    SDL_FreeSurface(logo);
}

void Generique::initSelection() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
            
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 8; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 160; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 160; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 160; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,48,288,32);
    cadre(16,96,288,32);
    cadre(16,144,288,32);
    cadre(16,192,136,32);
    cadre(168,192,136,32);
    
    gpJeu->afficheTexteAvecId(image, 200, 40, 16);
    gpJeu->afficheTexteAvecId(image, 201, 44, 56);
    gpJeu->afficheTexteAvecId(image, 202, 44, 104);
    gpJeu->afficheTexteAvecId(image, 203, 44, 152);
    gpJeu->afficheTexteAvecId(image, 204, 63, 200);
    gpJeu->afficheTexteAvecId(image, 205, 215, 200);
    
    //stats :
    SDL_Surface* imageStat = gpJeu->loadImg("data/images/statut/statut.png");
    SDL_SetColorKey(imageStat,SDL_SRCCOLORKEY,SDL_MapRGB(imageStat->format,0,0,255));
    SDL_Surface* inventaire = gpJeu->loadImg("data/images/statut/inventaire.png");
    SDL_Surface* objets = gpJeu->loadImg("data/images/statut/objets.png");
    
    for (int i = 0; i < 3; i++) {
        Joueur* gpJoueur = new Joueur(gpJeu,i+1);
        if (gpJoueur->getLoader()) {
            //vie
            if(gpJoueur->getVie()>gpJoueur->getVieMax()) gpJoueur->setVie(gpJoueur->getVieMax());
            for(int j=0;j<gpJoueur->getVieMax()/2;j++) {
                src.h = 7; src.w = 7; src.y=9;
                dst.x = 64+((j%10)*8)+8;dst.y = 57+8*((int)(j/10))+i*48;
                if (gpJoueur->getVie()-(j*2)>1)src.x=141;
                if (gpJoueur->getVie()-(j*2)==1)src.x=149;
                if (gpJoueur->getVie()-(j*2)<1)src.x=157;
                SDL_BlitSurface(imageStat, &src, image, &dst);
            }
        
            //cristaux
            dst.x=176+8-16; dst.y=56+i*48;
            src.x=16; src.y=17*4; src.w=16; src.h=17;
            for (int j=0; j<7; j++) {
                if (gpJoueur->hasCristal(j)) src.x=16; else src.x=32;
                SDL_BlitSurface(inventaire, &src, image, &dst);
                dst.x+=16-3;
            }
            
            //triforce
            dst.x=272; dst.y=56+i*48;
            src.x=128; src.y=0; src.w=17; src.h=16;
            if (gpJoueur->getEnnemi(50)) SDL_BlitSurface(objets, &src, image, &dst);
            
            gpJeu->getKeyboard()->setSave(i,1);
        }else gpJeu->getKeyboard()->setSave(i,0);
        delete gpJoueur;
    }
    
    SDL_FreeSurface(objets);
    SDL_FreeSurface(imageStat);
    SDL_FreeSurface(inventaire);
}

void Generique::initOption() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64,288,32);
    cadre(16,107,288,32);
    cadre(16,150,288,32);
    cadre(16,192,136,32);
    
    // gpJeu->afficheTexteAvecId(image, 206, 40, 16);
    // gpJeu->afficheTexteAvecId(image, 207, 60, 72);
    // gpJeu->afficheTexteAvecId(image, 208, 60, 115);
    // gpJeu->afficheTexteAvecId(image, 208, 60, 158);
    // gpJeu->afficheTexteAvecId(image, 209, 63, 200);
    
    src.x = 0; src.y = 96; dst.x = 128; dst.y = 72; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    for (int i = 144; i < 264; i+=16) {
        src.x = 16; src.y = 96; dst.x = i; dst.y = 72; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    src.x = 32; src.y = 96; dst.x = 264; dst.y = 72; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    src.x = 0; src.y = 96; dst.x = 128; dst.y = 115; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    for (int i = 144; i < 264; i+=16) {
        src.x = 16; src.y = 96; dst.x = i; dst.y = 115; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    src.x = 32; src.y = 96; dst.x = 264; dst.y = 115; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
}

void Generique::initRecord() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(128,8,176,32);
    cadre(16,48,240,32); cadre(272,48,32,32);
    cadre(16,96,240,32); cadre(272,96,32,32);
    cadre(16,144,240,32); cadre(272,144,32,32);
    cadre(16,192,136,32);
    cadre(168,192,136,32);
    
    ostringstream oss;
    int temps = gpJeu->getKeyboard()->getTemps();
    if (temps > 359999) temps = 359999;
    int h = temps/3600;
    int m = (temps - ((int)(temps/3600))*3600)/60;
    int s = temps%60;
    if (h < 10) oss<<"0"; oss << h << ":";
    if (m < 10) oss<<"0"; oss << m << ":";
    if (s < 10) oss<<"0"; oss << s;
    
    
    gpJeu->afficheTexteAvecId(image, 210, 40, 16);
    gpJeu->afficheTexteAvecId(image, 211, oss.str(), 140, 16);
    gpJeu->afficheTexteAvecId(image, 212, 44, 56);
    gpJeu->afficheTexteAvecId(image, 213, 44, 104);
    gpJeu->afficheTexteAvecId(image, 214, 44, 152);
    gpJeu->afficheTexteAvecId(image, 215, 63, 200);
    gpJeu->afficheTexteAvecId(image, 216, 215, 200);
    
    SDL_Surface* objets = gpJeu->loadImg("data/images/statut/objets.png");
    
    //triforce
    src.y=0; src.w=17; src.h=16;
    
    for (int i = 0; i < 3; i++) {
        dst.x=279; dst.y=56+i*48;
        gpJeu->getKeyboard()->getRang(i) ? src.x=128 : src.x=145; 
        SDL_BlitSurface(objets, &src, image, &dst);}
    
    SDL_FreeSurface(objets);
}

void Generique::initEffacer() {
    cadre(104,84,112,72);
    gpJeu->afficheTexteAvecId(image, 217, 133, 93);
    gpJeu->afficheTexteAvecId(image, 218, 151, 113);
    gpJeu->afficheTexteAvecId(image, 219, 151, 133);
}

void Generique::initCharger() {
    cadre(104,84,112,72);
    gpJeu->afficheTexteAvecId(image, 220, 139, 93);
    gpJeu->afficheTexteAvecId(image, 221, 139, 113);
    gpJeu->afficheTexteAvecId(image, 222, 139, 133);
}

void Generique::initIntro() {
    if (imageFond1==NULL) {
        imageFond1 = gpJeu->loadImg("data/images/logos/fond1.png");
        SDL_SetColorKey(imageFond1,SDL_SRCCOLORKEY,SDL_MapRGB(imageFond1->format,0,0,255));}
    if (imageFond2==NULL) imageFond2 = gpJeu->loadImg("data/images/logos/fond2.png");
    
    ostringstream oss;
    for (int i = 0; i < 5; i++) {
        if (imageIntro[i]==NULL) {
            oss.str(""); oss << (i+1);
            imageIntro[i] = gpJeu->loadImg(("data/images/logos/intro" + oss.str() + ".png").c_str());
        }
    }
    
    lastAnimTime = SDL_GetTicks(); anim=0;
    gpJeu->ecrit(228, false, true, 32, 158, 256, 64);
}

void Generique::initNuit() {
    gpJeu->ecrit(233);
}

void Generique::initAide1() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64-8,288,128);
    
    cadre(16,192+8,288,32);
    
    gpJeu->afficheTexteAvecId(image, 223, 40, 16);
    gpJeu->afficheTexteAvecId(image, 224, 24, 208);
    
    int ligne = 64;
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    gpJeu->afficheTexteAvecId(image, 225, 24, ligne); ligne+=16;
    gpJeu->afficheTexteAvecId(image, 226, 24, ligne); ligne+=16;
	gpJeu->afficheTexteAvecId(image, 227, 24, ligne); ligne+=16;

    if (gpJoueur->hasObjet(O_BOTTES)) {
        gpJeu->afficheTexteAvecId(image, 228, 24, ligne);
        ligne+=16;
    }
    if (gpJoueur->getEpee()) {
        gpJeu->afficheTexteAvecId(image, 229, 24, ligne); ligne+=16;
        gpJeu->afficheTexteAvecId(image, 230, 24, ligne); 
        ligne+=16;
    }

    gpJeu->afficheTexteAvecId(image, 231, 24, ligne); ligne+=16;
    if (ligne >= 176) return;
    gpJeu->afficheTexteAvecId(image, 232, 24, ligne); ligne+=16;
    if (ligne >= 176) return;
    if (gpJoueur->hasObjet(O_GANTS)) {
        gpJeu->afficheTexteAvecId(image, 233, 24, ligne); 
        ligne+=16;
    }
    if (ligne >= 176) return;
    if (gpJoueur->hasObjet(O_CARTE))
        gpJeu->afficheTexteAvecId(image, 234, 24, ligne);
    else gpJeu->afficheTexteAvecId(image, 235, 24, ligne);
    ligne+=16;
    if (ligne >= 176) return;
    if (gpJoueur->hasObjet(O_ENCYCL)) {
        gpJeu->afficheTexteAvecId(image, 236, 24, ligne);
        ligne+=16;
    }
    if (ligne >= 176) return;
    gpJeu->afficheTexteAvecId(image, 237, 24, ligne); ligne+=16;
    if (ligne >= 176) return;
    gpJeu->afficheTexteAvecId(image, 238, 24, ligne); ligne+=16;
#ifndef __vita__
    if (ligne >= 176) return;
    gpJeu->afficheTexteAvecId(image, 239, 24, ligne); ligne+=16;
#endif
}

void Generique::initAide2() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64-8,288,128);
    
    cadre(16,192+8,288,32);
    
    gpJeu->afficheTexteAvecId(image, 240, 40, 16);
    gpJeu->afficheTexteAvecId(image, 241, 24, 208);
    
    int ligne = 64-112;
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    ligne+=64;
    if (gpJoueur->hasObjet(O_BOTTES)) ligne+=16;
    if (gpJoueur->getEpee()) ligne+=32;
    if (ligne >= 64)
        gpJeu->afficheTexteAvecId(image, 242, 24, ligne); ligne+=16;
    if (ligne >= 64) 
    if (gpJoueur->hasObjet(O_GANTS)) {
        gpJeu->afficheTexteAvecId(image, 243, 24, ligne); 
        ligne+=16;
    }
    if (ligne >= 64) {
    if (gpJoueur->hasObjet(O_CARTE))
        gpJeu->afficheTexteAvecId(image, 244, 24, ligne);
    else gpJeu->afficheTexteAvecId(image, 245, 24, ligne);}
    ligne+=16;
    if (ligne >= 64) 
    if (gpJoueur->hasObjet(O_ENCYCL)) {
        gpJeu->afficheTexteAvecId(image, 246, 24, ligne); 
        ligne+=16;
    }
    if (ligne >= 64) 
        gpJeu->afficheTexteAvecId(image, 247, 24, ligne); ligne+=16;
    if (ligne >= 64) 
        gpJeu->afficheTexteAvecId(image, 248, 24, ligne); ligne+=16;
#ifndef __vita__
    if (ligne >= 64) 
        gpJeu->afficheTexteAvecId(image, 249, 24, ligne); ligne+=16;
#endif
}

void Generique::initRang(int i) {
    int languageId = getLanguage();
    int paddingX = 0;
    int paddingY = 0;
    switch (i) {
        case 0 :
            paddingX = 2+16;
            paddingY = 4+32;
            if (languageId == LANG_FR){
                paddingX = 0;
                paddingY = 0;
            }
            cadre(88-paddingX,96,144+paddingY,48);
            if (gpJeu->getKeyboard()->getRang(i)) 
                gpJeu->afficheTexteAvecId(image, 250, 96-paddingX, 104);
            else gpJeu->afficheTexteAvecId(image, 251, 96-paddingX, 104);
            gpJeu->afficheTexteAvecId(image, 252, 96-paddingX, 120);
            break;
        case 1 :
            paddingX = 8+16;
            paddingY = 16+32;
            if (languageId == LANG_FR){
                paddingX = 0;
                paddingY = 0;
            }
            cadre(64-paddingX,64,192+paddingY,112);
            int l; l=72;
            if (gpJeu->getKeyboard()->getRang(i)) 
                gpJeu->afficheTexteAvecId(image, 253, 72-paddingX, l);
            else gpJeu->afficheTexteAvecId(image, 254, 72-paddingX, l);
            l+=16;
            gpJeu->afficheTexteAvecId(image, 255, 72-paddingX, l);l+=16;
            gpJeu->afficheTexteAvecId(image, 256, 72-paddingX, l);l+=16;
            gpJeu->afficheTexteAvecId(image, 257, 72-paddingX, l);l+=16;
            gpJeu->afficheTexteAvecId(image, 258, 72-paddingX, l);l+=16;
            gpJeu->afficheTexteAvecId(image, 259, 72-paddingX, l);l+=16;
            break;
        case 2 :
            paddingX = 10;
            paddingY = 20;
            if (languageId == LANG_FR){
                paddingX = 0;
                paddingY = 0;
            }
            cadre(71-paddingX,88,178+paddingY,64);
            if (gpJeu->getKeyboard()->getRang(i)) 
                gpJeu->afficheTexteAvecId(image, 260, 78-paddingX, 96);
            else gpJeu->afficheTexteAvecId(image, 261, 78-paddingX, 96);
            gpJeu->afficheTexteAvecId(image, 262, 78-paddingX, 112);
            gpJeu->afficheTexteAvecId(image, 263, 78-paddingX, 128);
            break;
    }
}

void Generique::cadre(int x, int y, int w, int h) {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    for (int j = y+16; j < y+h-16; j+=16)
        for (int i = x+16; i < x+w-16; i+=16) {
            src.x = 16; src.y = 64; dst.x = i; dst.y = j; 
            SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
    
    //haut et bas
    for (int i = x+16; i < x+w-16; i+=16) {
        src.x = 16; src.y = 48; dst.x = i; dst.y = y; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 80; dst.x = i; dst.y = y+h-16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    //gauche et droite
    for (int j = y+16; j < y+h-16; j+=16) {
        src.x = 0; src.y = 64; dst.x = x; dst.y = j; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 32; src.y = 64; dst.x = x+w-16; dst.y = j;
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    //haut gauche
    src.x = 0; src.y = 48; dst.x = x; dst.y = y; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //haut droite
    src.x = 32; src.y = 48; dst.x = x+w-16; dst.y = y; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //bas gauche
    src.x = 0; src.y = 80; dst.x = x; dst.y = y+h-16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //bas droite
    src.x = 32; src.y = 80; dst.x = x+w-16; dst.y = y+h-16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
}

void Generique::initScore() {
    SDL_FreeSurface(imageArbre);
    imageArbre = gpJeu->loadImg("data/images/logos/arbre.png");
    image = SDL_CreateRGBSurface(SDL_HWSURFACE, 320, 240, 32, 0, 0, 0, 0);
    
    SDL_Rect dst; 
    
    for (int i = 0; i < 320; i+=48) {
        dst.x = i;
        for (int j = 0; j < 240; j+=96) {
            dst.y = j;
            SDL_BlitSurface(imageArbre, NULL, image, &dst);
        }
    }
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    ostringstream oss;
    int pctg = 0;
    gpJeu->afficheTexteAvecId(image, 264, 136, 10);
    
    int temps = gpJoueur->getTemps(0)+gpJoueur->getTemps(1)*60+gpJoueur->getTemps(2)*3600;
    if (temps < gpJeu->getKeyboard()->getTemps() || gpJeu->getKeyboard()->getTemps()==0) {
        gpJeu->getKeyboard()->setTemps(temps); gpJeu->getKeyboard()->saveP();}
        
    oss.str(""); 
    if (gpJoueur->getTemps(2)<10)oss<<"0";oss << gpJoueur->getTemps(2) << ":";
    if (gpJoueur->getTemps(1)<10)oss<<"0";oss << gpJoueur->getTemps(1) << ":";
    if (gpJoueur->getTemps(0)<10)oss<<"0";oss << gpJoueur->getTemps(0);
    gpJeu->afficheTexteAvecId(image, 265, oss.str(), 10, 30);
    
    int tmp=gpJoueur->getMort();
    oss.str(""); oss << tmp;
    if (tmp==1) gpJeu->afficheTexteAvecId(image, 266, oss.str(), 10, 50);
    else gpJeu->afficheTexteAvecId(image, 267, oss.str(), 10, 50);
    
    tmp=gpJoueur->nbQuarts();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->afficheTexteAvecId(image, 268, oss.str(), 10, 70);

    tmp=0;
    for (int i = 0; i < 10; i++) if (i != O_SAC_BOMBES) if (gpJoueur->hasObjet(i)) tmp++;
    if (gpJoueur->hasObjet(O_ARC) == 5) tmp++;
    if (gpJoueur->hasObjet(O_GANTS) == 2) tmp++;
    if (gpJoueur->getBouclier()) tmp++;
    for (int i = 0; i < 3; i++) if (gpJoueur->hasBouteille(i)) tmp++;
    if (gpJoueur->getEpee()) tmp++;
    if (gpJoueur->getEpee()>1) tmp++;
    if (gpJoueur->getEpee()>3) tmp++;
    if (gpJoueur->getMagieMax() > 32) tmp++;
    for (int i = 0; i < 3; i++) if (gpJoueur->hasMedaillon(i)) tmp++;
    for (int i = 0; i < 7; i++) if (gpJoueur->hasCristal(i)) tmp++;
    for (int j = 0; j < 9; j++) for (int i = 0; i < 3; i++) if (gpJoueur->getCle(j,i)) tmp++;
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->afficheTexteAvecId(image, 269, oss.str(), 10, 90);
    
    tmp=gpJoueur->nbEnnemis();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->afficheTexteAvecId(image, 270, oss.str(), 10, 110);
    
    pctg=(int)((pctg*100)/138);
    oss.str(""); oss << pctg;
    gpJeu->afficheTexteAvecId(image, 271, oss.str(), 
        10, 130);
    
    int result;
    int ligne = 170;
    gpJeu->afficheTexteAvecId(image, 272, 10, ligne);
    
    if (gpJoueur->getMort()==0 && gpJoueur->hasBouteille(0)==0
        && gpJoueur->hasBouteille(1)==0 && gpJoueur->hasBouteille(2)==0
        && gpJoueur->hasMedaillon(0)==0 && gpJoueur->hasMedaillon(1)==0
        && gpJoueur->hasMedaillon(2)==0 && gpJoueur->getVieMax()==20
        && gpJoueur->getMagieMax()==32 && gpJoueur->getBouclier()==0) {
        gpJeu->afficheTexteAvecId(image, 273, 52, ligne); ligne+=20;
        gpJeu->getKeyboard()->setRang(1); gpJeu->getKeyboard()->saveP();}
    else {
        if (pctg==100) {result=274; 
            gpJeu->getKeyboard()->setRang(0); gpJeu->getKeyboard()->saveP();}
        if (pctg<100) result=275;
        if (pctg<95) result=276;
        if (pctg<90) result=277;
        if (pctg<85) result=278;
        if (pctg<80) result=279;
        gpJeu->afficheTexteAvecId(image, result, 52, ligne);
        ligne+=20;
    }
    
    if (gpJoueur->getMort()>=50) {
        result=280; gpJeu->afficheTexteAvecId(image, result, 52, ligne); ligne+=20;}
    else if (gpJoueur->getMort()>=20) {
        result=281; gpJeu->afficheTexteAvecId(image, result, 52, ligne); ligne+=20;}
        
    if (temps<=7200) {
        result=282; 
        gpJeu->getKeyboard()->setRang(2); gpJeu->getKeyboard()->saveP();
        gpJeu->afficheTexteAvecId(image, result, 52, ligne); ligne+=20;}
}

void Generique::draw(SDL_Surface* gpScreen) {
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(image, NULL, gpScreen, &dst);
}

void Generique::drawSelection(SDL_Surface* gpScreen, int ligne, int colonne) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26+152*colonne; dst.y = 53+48*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
}

void Generique::drawOption(SDL_Surface* gpScreen, int ligne, int opt1, int opt2) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    int languageID = getLanguage();
    gpJeu->afficheTexteAvecId(gpScreen, 206, 40, 16);
    gpJeu->afficheTexteAvecId(gpScreen, 207, 60, 72);
    gpJeu->afficheTexteAvecId(gpScreen, 208, 60, 115);
    gpJeu->afficheTexteAvecId(gpScreen, 283, 60, 158);
    gpJeu->afficheTexteAvecId(gpScreen, 284, 170, 158);
    gpJeu->afficheTexteAvecId(gpScreen, 209, 63, 200);

    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26; dst.y = 69+43*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
    
    src.h = 16; src.w = 8;src.x = 0;src.y=0;
    dst.x = 136+16*opt1; dst.y = 56+16;
    SDL_BlitSurface(imageNiveau, &src, gpScreen, &dst);
                
    src.h = 16; src.w = 8;src.x = 0;src.y=0;
    dst.x = 136+16*opt2; dst.y = 56+16+43;
    SDL_BlitSurface(imageNiveau, &src, gpScreen, &dst);
    drawFlag(gpScreen, languageID);
}

void Generique::drawRecord(SDL_Surface* gpScreen, int ligne, int colonne) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26+152*colonne; dst.y = 53+48*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
}

void Generique::drawEffacer(SDL_Surface* gpScreen, int ligne) {
    drawRecord(gpScreen, 3, 1);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = 113+20*ligne;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawCharger(SDL_Surface* gpScreen, int ligne, int ligne2) {
    drawSelection(gpScreen, ligne, 0);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = 93+20*ligne2;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawEffacerSave(SDL_Surface* gpScreen, int ligne, int ligne2) {
    drawSelection(gpScreen, ligne, 0);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = 113+20*ligne2;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawIntro(SDL_Surface* gpScreen, int etape) {
    SDL_Rect src;
    SDL_Rect dst;
    
    if(SDL_GetTicks() > lastAnimTime + 40) {
        lastAnimTime = SDL_GetTicks();
        anim++;            
        if (anim > 31) anim = 0;
    }
                
    src.h = 16; src.w = 16;
    for (int j=0; j<240; j+=16) 
        for (int i=0; i<320; i+=16) {
            src.x = 16-anim%16;src.y=anim%16; dst.x = i; dst.y = j;
            if (i>16 && i<288 && j>144 && j<224) src.x+=32;
            SDL_BlitSurface(imageFond2, &src, gpScreen, &dst);
        }
                
    src.h = 32; src.w = 32;
    for (int j=0; j<240; j+=32) 
        for (int i=0; i<320; i+=32) {
            src.x = anim;src.y=anim; dst.x = i; dst.y = j;
            if (i>16 && i<288 && j>144 && j<224) src.x+=64;
            SDL_BlitSurface(imageFond1, &src, gpScreen, &dst);
        }
                
    src.h = 111; src.w = 320;
    src.x = 0; src.y=0; dst.x = 0; dst.y = 17;
    SDL_BlitSurface(imageIntro[etape], &src, gpScreen, &dst);
                
    gpJeu->getTexte()->draw(gpScreen);
}

void Generique::drawDebut(SDL_Surface* gpScreen) {
    if (!imageNuit) imageNuit = gpJeu->loadImg("data/images/logos/nuit.png");
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(imageNuit, NULL, gpScreen, &dst);
    gpJeu->getTexte()->draw(gpScreen);
}

void Generique::drawFlag(SDL_Surface* gpScreen, int flagID){
    SDL_Rect src; src.x = (flagID-1)*26; src.y = 0;src.h = 16; src.w = 26;
    SDL_Rect dst; dst.x = 136; dst.y = 158;
    SDL_BlitSurface(imageFlags, &src, gpScreen, &dst);
}
