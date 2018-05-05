/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Texte.h"
#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"

Texte::Texte(Jeu* jeu) : gpJeu(jeu), vitesse(40), av(0), x(0), y(0), w(0), h(0),
id(0), idsuiv(0), def(false), cadre(false), texte(""), buffer("") {
    lastAnimTime = SDL_GetTicks();
    imageFont = gpJeu->loadImg("data/images/texte/font.png");
    SDL_SetColorKey(imageFont,SDL_SRCCOLORKEY,SDL_MapRGB(imageFont->format,0,0,255));
    imageCoeur = gpJeu->loadImg("data/images/menu/coeur.png");
    SDL_SetColorKey(imageCoeur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCoeur->format,0,0,255));
    getTextByLangFunc = &Texte::getTexteEN;
}

Texte::~Texte() {
    SDL_FreeSurface(imageFont);
    SDL_FreeSurface(imageCoeur);
}

void Texte::setTextLanguage(int id){
    switch(id){
        case 2:
            getTextByLangFunc = &Texte::getTexteFR;
            break;
        default:
            getTextByLangFunc = &Texte::getTexteEN;
    }
}

std::string Texte::getTexteEN(int id, std::string s){
    std::string texte = "";
    switch(id) {
        // 0 -> 99 : Carte
        case 0 : 
            texte = "Temple de la forêt"; 
            break;
        case 1 : 
            texte = "Temple de l'eau"; 
            break;
        case 2 : 
            texte = "Temple de la montagne";
            break;
        case 3 : 
            texte = "Temple du désert"; 
            break;
        case 4 : 
            texte = "Temple de l'ombre"; 
            break;
        case 5 : 
            texte = "Temple du feu"; 
            break;
        case 6 : 
            texte = "Temple de la glace"; 
            break;
        case 7 : 
            texte = "Temple secret"; 
            break;
        case 8 : 
            texte = "Château d'Hyrule"; 
            break;

        // 100 -> 199 : Encyclopedie
        case 100 : 
            texte = "MONSTRES " + s;
            break;
            
        // 200 -> 299 : Generique
        case 200 :
            texte = "ECRAN DE SELECTION";
            break;
        case 201 : 
            texte = "1.";
            break;
        case 202 :
            texte = "2.";
            break;
        case 203 : 
            texte = "3.";
            break;
        case 204 :
            texte = "OPTIONS";
            break;
        case 205 :
            texte = "RECORDS";
            break;
        case 206 :
            texte = "OPTIONS";
            break;
        case 207 :
            texte = "MUSIC";
            break;
        case 208 :
            texte = "SOUND";
            break;
        case 209 :
            texte = "RETURN";
            break;
        case 210 :
            texte = "RECORDS";
            break;
        case 211 :
            texte = "MEILLEUR TEMPS : " + s;
            break;
        case 212 :
            texte = "RANG DES 100%";
            break;
        case 213 :
            texte = "RANG ULTIME";
            break;
        case 214 :
            texte = "RANG DE RAPIDITE";
            break;
        case 215 :
            texte = "RETOUR";
            break;
        case 216 :
            texte = "EFFACER";
            break;
        case 217 :
            texte = "EFFACER ?";
            break;
        case 218 :
            texte = "OUI";
            break;
        case 219 :
            texte = "NON";
            break;
        case 220 :
            texte = "CHARGER";
            break;
        case 221 :
            texte = "EFFACER";
            break;
        case 222 :
            texte = "ANNULER";
            break;
        case 223 :
            texte = "AIDE 1/2";
            break;
        case 224 :
#ifdef __vita__
            texte = "Retour au jeu : Croix - Suite : Droite";
#else
            texte = "Retour au jeu : Entrée - Suite : Droite";
#endif
            break;
        case 225 :
#ifdef __vita__
            texte = "Lire / Ouvrir / Parler : Rond";
#else
            texte = "Lire / Ouvrir / Parler : Espace";
#endif
            break;
        case 226 :
#ifdef __vita__
            texte = "Valider / Passer texte : Croix";
#else
            texte = "Valider / Passer texte : Entrée";
#endif
            break;
        case 227 :
#ifdef __vita__
            texte = "Déplacer Link : Stick Gauche";
#else
            texte = "Déplacer Link : Flèches de direction";
#endif
            break;
        case 228 :
#ifdef __vita__
            texte = "Courir : L (maintenu) / R";
#else
            texte = "Courir : Shift maintenu ou Caps lock";
#endif
            break;
        case 229 :
#ifdef __vita__
            texte = "Coup d'épée : Carré";
#else
            texte = "Coup d'épée : W ou Z";
#endif
            break;
        case 230 :
#ifdef __vita__
            texte = "Attaque Tornade : Carré maintenu puis lâché";
#else
            texte = "Attaque Tornade : W ou Z maintenu puis lâché";
#endif
            break;
        case 231 :
#ifdef __vita__
            texte = "Menu de sélection d'objet : D-Pad Droite";
#else
            texte = "Menu de sélection d'objet : Entrée";
#endif
            break;
        case 232 :
#ifdef __vita__
            texte = "Utiliser l'objet sélectionné : Triangle";
#else
            texte = "Utiliser l'objet sélectionné : X";
#endif
            break;
        case 233 :
#ifdef __vita__
            texte = "Porter sans équiper les gants : Croix";
#else
            texte = "Porter sans équiper les gants : C";
#endif
            break;
        case 234 :
#ifdef __vita__
            texte = "Afficher la carte : D-Pad Gauche (ext/donjons)";
#else
            texte = "Afficher la carte : D-Pad Gauche (dans les donjons)";
#endif
            break;
        case 235 :
#ifdef __vita__
            texte = "Afficher la carte : L (extérieur ou donjons)";
#else
            texte = "Afficher la carte : P (dans les donjons)";
#endif
            break;
        case 236 :
#ifdef __vita__
            texte = "Afficher les monstres vaincus : D-Pad Haut";
#else
            texte = "Afficher les monstres vaincus : M";
#endif
            break;
        case 237 :
#ifdef __vita__
            texte = "Regarder autour : Stick Droite";
#else
            texte = "Regarder autour : Ctrl et direction";
#endif
            break;
        case 238 :
#ifdef __vita__
            texte = "Sauvegarder / Quitter : Start";
#else
            texte = "Sauvegarder / Quitter : Echap";
#endif
            break;
        case 239 :
#ifdef __vita__
            texte = "";
#else
            texte = "Agrandir / Rétrécir : Ctrl et Entrée";
#endif
            break;
        case 240 :
            texte = "AIDE 2/2";
            break;
        case 241 :    
#ifdef __vita__
            texte = "Retour au jeu : Croix - Précédent : Gauche";
#else
            texte = "Retour au jeu : Entrée - Précédent : Gauche";
#endif
            break;
        case 242 :
#ifdef __vita__
            texte = "Utilise objet sélectionné: Triangle";
#else
            texte = "Utilise objet sélectionné: X";
#endif
            break;
        case 243 :
#ifdef __vita__
            texte = "Porter sans équiper les gants : Croix"; 
#else
            texte = "Porter sans équiper les gants : C"; 
#endif
            break;
        case 244 :
#ifdef __vita__
            texte = "Afficher la carte : D-Pad Gauche (ext/donjon)";
#else
            texte = "Afficher la carte : P (extérieur ou donjons)";
#endif
            break;
        case 245 :
#ifdef __vita__
            texte = "Afficher la carte : D-Pad Gauche (dans les donjons)";
#else
            texte = "Afficher la carte : P (dans les donjons)";
#endif
            break;
        case 246 :
            texte = "Afficher les monstres vaincus : M";
            break;
        case 247 :
#ifdef __vita__
            texte = "Regarder autour : Stick Droite";
#else
            texte = "Regarder autour : Ctrl et direction";
#endif
            break;
        case 248 :
#ifdef __vita__
            texte = "Sauvegarder / Quitter : Start";
#else
            texte = "Sauvegarder / Quitter : Echap";
#endif
            break;
        case 249 :
#ifdef __vita__
            texte = "";
#else
            texte = "Agrandir / Rétrécir : Ctrl et Entrée";
#endif
            break;

        case 250 :
            texte = "RANG : Héros d'Hyrule";
            break;
        case 251 :
            texte = "RANG : INCONNU";
            break;
        case 252 :
            texte = "Finir le jeu à 100%";
            break;
        case 253 :
            texte = "RANG : Frimeur";
            break;
        case 254 :
            texte = "RANG : INCONNU";
            break;
        case 255 :
            texte = "Finir le jeu sans mourir,";
            break;
        case 256 :
            texte = "avec 10 coeurs au maximum,";
            break;
        case 257 :
            texte = "sans parler aux Grandes Fées,";
            break;
        case 258 :
            texte = "sans acheter de flacons";
            break;
        case 259 :
            texte = "et sans prendre le bouclier.";
            break;
        case 260 :
            texte = "RANG : Marathonien d'Hyrule";
            break;
        case 261 :
            texte = "RANG : INCONNU";
            break;
        case 262 :
            texte = "Finir le jeu en moins de";
            break;
        case 263 :
            texte = "deux heures";
            break;
        case 264 : 
            texte = "SCORES :";
            break;
        case 265 :
            texte = "Temps de jeu : " + s;
            break;
        case 266 :
            texte = "Mort " + s + " time";
            break;
        case 267 :
            texte = "Mort " + s + " times";
            break;
        case 268 :
            texte = "Quarts de coeurs : " + s + " / 36";
            break;
        case 269 :
            texte = "Objets : " + s + " / 56";
            break;
        case 270 :
            texte = "Types d'ennemis vaincus : " + s + " / 46";
            break;
        case 271 :
            texte = "Tu as fini ce jeu à " + s + "%, félicitation !";
            break;
        case 272 :
            texte = "RANG : ";
            break;
        case 273 :
            texte = " - Frimeur";
            break;
        case 274 :
            texte = " - Héros d'Hyrule";
            break;
        case 275 :
            texte = " - Perfectionniste";
            break;
        case 276 :
            texte = " - Fan de Zelda";
            break;
        case 277 :
#ifdef __vita__
            texte = " - Pro du pad";
#else
            texte = " - Pro du clavier";
#endif
            break;
        case 278 :
            texte = " - Confirmé";
            break;
        case 279 :
            texte = " - Débutant";
            break;
        case 280 :
            texte = " - Mort-vivant";
            break;
        case 281 : 
            texte = " - Kamikaze";
            break;
        case 282 :
            texte = " - Marathonien d'Hyrule";
            break;
        case 283 :
            texte = "LANGUAGE";
            break;
        case 284 :
            texte = "English";
            break;

        // 300 -> 399 : Menu
        case 300 :
            texte = "X";
            break;
        case 301 :
            texte = "STATUT :";
            break;
        case 302 :
            texte = "VIE       : " + s;
            break;
        case 303 :
            texte = "MAGIE     : " + s;
            break;
        case 304 :
            texte = "FORCE     : " + s;
            break;
        case 305 :
            texte = "DEFENSE   : " + s;
            break;
        case 306 :
            texte = "TEMPS     : " + s;
            break;
        case 307 :
            texte = "CRISTAUX :";
            break;
        default : 
            texte = "ERREUR TEXTE";
    }

    return texte;
}

std::string Texte::getTexteFR(int id, std::string s){
    std::string texte = "";
    switch(id) {
        // 0 -> 99 : Carte
        case 0 : 
            texte = "Temple de la forêt"; 
            break;
        case 1 : 
            texte = "Temple de l'eau"; 
            break;
        case 2 : 
            texte = "Temple de la montagne";
            break;
        case 3 : 
            texte = "Temple du désert"; 
            break;
        case 4 : 
            texte = "Temple de l'ombre"; 
            break;
        case 5 : 
            texte = "Temple du feu"; 
            break;
        case 6 : 
            texte = "Temple de la glace"; 
            break;
        case 7 : 
            texte = "Temple secret"; 
            break;
        case 8 : 
            texte = "Château d'Hyrule"; 
            break;

        // 100 -> 199 : Encyclopedie
        case 100 : 
            texte = "MONSTRES " + s;
            break;
            
        // 200 -> 299 : Generique
        case 200 :
            texte = "ECRAN DE SELECTION";
            break;
        case 201 : 
            texte = "1.";
            break;
        case 202 :
            texte = "2.";
            break;
        case 203 : 
            texte = "3.";
            break;
        case 204 :
            texte = "OPTIONS";
            break;
        case 205 :
            texte = "RECORDS";
            break;
        case 206 :
            texte = "OPTIONS";
            break;
        case 207 :
            texte = "MUSIQUE";
            break;
        case 208 :
            texte = "SON";
            break;
        case 209 :
            texte = "RETOUR";
            break;
        case 210 :
            texte = "RECORDS";
            break;
        case 211 :
            texte = "MEILLEUR TEMPS : " + s;
            break;
        case 212 :
            texte = "RANG DES 100%";
            break;
        case 213 :
            texte = "RANG ULTIME";
            break;
        case 214 :
            texte = "RANG DE RAPIDITE";
            break;
        case 215 :
            texte = "RETOUR";
            break;
        case 216 :
            texte = "EFFACER";
            break;
        case 217 :
            texte = "EFFACER ?";
            break;
        case 218 :
            texte = "OUI";
            break;
        case 219 :
            texte = "NON";
            break;
        case 220 :
            texte = "CHARGER";
            break;
        case 221 :
            texte = "EFFACER";
            break;
        case 222 :
            texte = "ANNULER";
            break;
        case 223 :
            texte = "AIDE 1/2";
            break;
        case 224 :
#ifdef __vita__
            texte = "Retour au jeu : Croix - Suite : Droite";
#else
            texte = "Retour au jeu : Entrée - Suite : Droite";
#endif
            break;
        case 225 :
#ifdef __vita__
            texte = "Lire / Ouvrir / Parler : Rond";
#else
            texte = "Lire / Ouvrir / Parler : Espace";
#endif
            break;
        case 226 :
#ifdef __vita__
            texte = "Valider / Passer texte : Croix";
#else
            texte = "Valider / Passer texte : Entrée";
#endif
            break;
        case 227 :
#ifdef __vita__
            texte = "Déplacer Link : Stick Gauche";
#else
            texte = "Déplacer Link : Flèches de direction";
#endif
            break;
        case 228 :
#ifdef __vita__
            texte = "Courir : L (maintenu) / R";
#else
            texte = "Courir : Shift maintenu ou Caps lock";
#endif
            break;
        case 229 :
#ifdef __vita__
            texte = "Coup d'épée : Carré";
#else
            texte = "Coup d'épée : W ou Z";
#endif
            break;
        case 230 :
#ifdef __vita__
            texte = "Attaque Tornade : Carré maintenu puis lâché";
#else
            texte = "Attaque Tornade : W ou Z maintenu puis lâché";
#endif
            break;
        case 231 :
#ifdef __vita__
            texte = "Menu de sélection d'objet : D-Pad Droite";
#else
            texte = "Menu de sélection d'objet : Entrée";
#endif
            break;
        case 232 :
#ifdef __vita__
            texte = "Utiliser l'objet sélectionné : Triangle";
#else
            texte = "Utiliser l'objet sélectionné : X";
#endif
            break;
        case 233 :
#ifdef __vita__
            texte = "Porter sans équiper les gants : Croix";
#else
            texte = "Porter sans équiper les gants : C";
#endif
            break;
        case 234 :
#ifdef __vita__
            texte = "Afficher la carte : D-Pad Gauche (ext/donjons)";
#else
            texte = "Afficher la carte : D-Pad Gauche (dans les donjons)";
#endif
            break;
        case 235 :
#ifdef __vita__
            texte = "Afficher la carte : L (extérieur ou donjons)";
#else
            texte = "Afficher la carte : P (dans les donjons)";
#endif
            break;
        case 236 :
#ifdef __vita__
            texte = "Afficher les monstres vaincus : D-Pad Haut";
#else
            texte = "Afficher les monstres vaincus : M";
#endif
            break;
        case 237 :
#ifdef __vita__
            texte = "Regarder autour : Stick Droite";
#else
            texte = "Regarder autour : Ctrl et direction";
#endif
            break;
        case 238 :
#ifdef __vita__
            texte = "Sauvegarder / Quitter : Start";
#else
            texte = "Sauvegarder / Quitter : Echap";
#endif
            break;
        case 239 :
#ifdef __vita__
            texte = "";
#else
            texte = "Agrandir / Rétrécir : Ctrl et Entrée";
#endif
            break;
        case 240 :
            texte = "AIDE 2/2";
            break;
        case 241 :    
#ifdef __vita__
            texte = "Retour au jeu : Croix - Précédent : Gauche";
#else
            texte = "Retour au jeu : Entrée - Précédent : Gauche";
#endif
            break;
        case 242 :
#ifdef __vita__
            texte = "Utilise objet sélectionné: Triangle";
#else
            texte = "Utilise objet sélectionné: X";
#endif
            break;
        case 243 :
#ifdef __vita__
            texte = "Porter sans équiper les gants : Croix"; 
#else
            texte = "Porter sans équiper les gants : C"; 
#endif
            break;
        case 244 :
#ifdef __vita__
            texte = "Afficher la carte : D-Pad Gauche (ext/donjon)";
#else
            texte = "Afficher la carte : P (extérieur ou donjons)";
#endif
            break;
        case 245 :
#ifdef __vita__
            texte = "Afficher la carte : D-Pad Gauche (dans les donjons)";
#else
            texte = "Afficher la carte : P (dans les donjons)";
#endif
            break;
        case 246 :
            texte = "Afficher les monstres vaincus : M";
            break;
        case 247 :
#ifdef __vita__
            texte = "Regarder autour : Stick Droite";
#else
            texte = "Regarder autour : Ctrl et direction";
#endif
            break;
        case 248 :
#ifdef __vita__
            texte = "Sauvegarder / Quitter : Start";
#else
            texte = "Sauvegarder / Quitter : Echap";
#endif
            break;
        case 249 :
#ifdef __vita__
            texte = "";
#else
            texte = "Agrandir / Rétrécir : Ctrl et Entrée";
#endif
            break;

        case 250 :
            texte = "RANG : Héros d'Hyrule";
            break;
        case 251 :
            texte = "RANG : INCONNU";
            break;
        case 252 :
            texte = "Finir le jeu à 100%";
            break;
        case 253 :
            texte = "RANG : Frimeur";
            break;
        case 254 :
            texte = "RANG : INCONNU";
            break;
        case 255 :
            texte = "Finir le jeu sans mourir,";
            break;
        case 256 :
            texte = "avec 10 coeurs au maximum,";
            break;
        case 257 :
            texte = "sans parler aux Grandes Fées,";
            break;
        case 258 :
            texte = "sans acheter de flacons";
            break;
        case 259 :
            texte = "et sans prendre le bouclier.";
            break;
        case 260 :
            texte = "RANG : Marathonien d'Hyrule";
            break;
        case 261 :
            texte = "RANG : INCONNU";
            break;
        case 262 :
            texte = "Finir le jeu en moins de";
            break;
        case 263 :
            texte = "deux heures";
            break;
        case 264 : 
            texte = "SCORES :";
            break;
        case 265 :
            texte = "Temps de jeu : " + s;
            break;
        case 266 :
            texte = "Mort " + s + " time";
            break;
        case 267 :
            texte = "Mort " + s + " times";
            break;
        case 268 :
            texte = "Quarts de coeurs : " + s + " / 36";
            break;
        case 269 :
            texte = "Objets : " + s + " / 56";
            break;
        case 270 :
            texte = "Types d'ennemis vaincus : " + s + " / 46";
            break;
        case 271 :
            texte = "Tu as fini ce jeu à " + s + "%, félicitation !";
            break;
        case 272 :
            texte = "RANG : ";
            break;
        case 273 :
            texte = " - Frimeur";
            break;
        case 274 :
            texte = " - Héros d'Hyrule";
            break;
        case 275 :
            texte = " - Perfectionniste";
            break;
        case 276 :
            texte = " - Fan de Zelda";
            break;
        case 277 :
#ifdef __vita__
            texte = " - Pro du pad";
#else
            texte = " - Pro du clavier";
#endif
            break;
        case 278 :
            texte = " - Confirmé";
            break;
        case 279 :
            texte = " - Débutant";
            break;
        case 280 :
            texte = " - Mort-vivant";
            break;
        case 281 : 
            texte = " - Kamikaze";
            break;
        case 282 :
            texte = " - Marathonien d'Hyrule";
            break;
        case 283 :
            texte = "LANGUE";
            break;
        case 284 :
            texte = "Française";
            break;

        // 300 -> 399 : Menu
        case 300 :
            texte = "X";
            break;
        case 301 :
            texte = "STATUT :";
            break;
        case 302 :
            texte = "VIE       : " + s;
            break;
        case 303 :
            texte = "MAGIE     : " + s;
            break;
        case 304 :
            texte = "FORCE     : " + s;
            break;
        case 305 :
            texte = "DEFENSE   : " + s;
            break;
        case 306 :
            texte = "TEMPS     : " + s;
            break;
        case 307 :
            texte = "CRISTAUX :";
            break;

        // 500 -> ?? : Texte
        case 501 : texte = "Tu as trouvé un bouclier !!!**Ta défense augmente d'un point !"; break;
#ifdef __vita__
        case 502 : texte = "Tu as trouvé une épée !!!**Tu vas pouvoir te défendre face aux monstres avec la touche Carré !!!*Maintiens Carré enfoncé pour charger une attaque cyclone !!!"; break;
#else
        case 502 : texte = "Tu as trouvé une épée !!!**Tu vas pouvoir te défendre face aux monstres avec la touche W (ou Z) !!!*Maintiens W enfoncé pour charger une attaque cyclone !!!"; break;
#endif
        case 503 : texte = "Tu as trouvé un quart de coeur !!!"; break;
        case 504 : texte = "Encore "+s+" et tu gagneras un coeur supplémentaire !!!"; break;
        case 505 : texte = "Ton nombre de coeurs vient d'augmenter !!!"; break;
        case 511 : texte = "N : Maison de Link*O : Plaine d'Hyrule*E : Temple de la Forêt"; break;
        case 512 : texte = "Temple de la Montagne**Déconseillé aux cardiaques, peureux, et aux âmes sensibles en général."; break;
        case 513 : texte = "O : Entrée du Désert*N : Temple de la Montagne"; break;
        case 514 : texte = "N : Temple de la Montagne*S : Plaine d'Hyrule"; break;
        case 515 : texte = "N : Mont du Péril"; break;
        case 516 : texte = "E : Entrée de la Forêt"; break;
        case 517 : texte = "S : Lac Hylia*E : Cimetière Hanté"; break;
        case 518 : texte = "S : Vers le Village Cocorico"; break;
        case 519 : texte = "N : Village Cocorico"; break;
        case 520 : texte = "N : Plaine d'Hyrule"; break;
        case 521 : texte = "O : Terres de Feu"; break;
        case 522 : texte = "E : Village de l'Ombre*- Déconseillé aux vivants -"; break;
        case 523 : texte = "Temple des Ténèbres**Si vous êtes un fantôme et que vous cherchez un job, venez plutôt chômer ici."; break;
        case 524 : texte = "N : Village de l'Ombre*O : Lac Hylia"; break;
        case 525 : texte = "N : Cimetière Hanté**Entrée interdite"; break;
        case 526 : texte = "Village de l'Ombre"; break;
        case 527 : texte = "Je vends un flacon pour 100 rubis, ça t'intéresse ?*              OUI ?            non  "; break;
        case 528 : texte = "Je vends un flacon pour 100 rubis, ça t'intéresse ?*              oui              NON ?"; break;
        case 529 : texte = "Désolé, mais tu n'as pas assez de rubis."; break;
        case 530 : texte = "Merci beaucoup, voilà ton flacon."; break;
        case 531 : texte = "Reviens me voir si tu changes d'avis."; break;
        case 532 : texte = "Désolé, c'était mon seul flacon."; break;
        case 533 : texte = "Tu as trouvé un flacon vide !!!**Tu vas pouvoir t'en servir pour stocker des potions !!!"; break;
        case 535 : texte = "Les habitants de ce village ont un dialecte très particulier, je n'y comprends rien..."; break;
        case 536 : texte = "@+@+@+@+@+@+@@@+*@=++=@=+@=+@=+=@*+@+@+@+=+="; break;
        case 537 : texte = "Obtiens une autorisation du chef si tu veux vraiment passer!!!"; break;
        case 538 : texte = "Le chef t'as autorisé à passer ??? Grrrr... Alors écarte toi!!!"; break;
        case 539 : texte = "Ne traîne pas dans mes pattes !!!"; break;
        case 540 : texte = "On n'a pas l'habitude de voir des visiteurs par ici..."; break;
        case 541 : texte = "Les monstres du coin ne craignent pas grand chose, heureusement qu'ils n'attaquent que les humains."; break;
        case 542 : texte = "C'est vrai ?*Tu comprends ce que je dis ?"; break;
        case 543 : texte = "N : Désert et Village Gerudo"; break;
        case 544 : texte = "S : Lac Hylia*O : Château d'Hyrule"; break;
        case 545 : texte = "Village Cocorico"; break;
        case 546 : texte = "O : Château d'Hyrule"; break;
        case 547 : texte = "Quelle belle journée !!!"; break;
        case 548 : texte = "Pourquoi ai-je accepté de m'occuper de ces saletés ???*J'ai horreur des poules !!!"; break;
        case 549 : texte = "On trouve des tas de choses dans les boutiques du village."; break;
        case 550 : texte = "S : Village Cocorico*O : Désert*E : Mont du Péril"; break;
        case 551 : texte = "Village Gerudo"; break;
        case 552 : texte = "Perdu dans le désert ?*Vous êtes ici :*                        X"; break;
        case 554 : texte = "S : Vers le Château d'Hyrule"; break;
        case 555 : texte = "Temple du Désert**Venez essayer nos bains.*(eau non-potable)"; break;
        case 556 : texte = "Temple de la Forêt**Sauvez les arbres, mangez du castor!!!"; break;
        case 557 : texte = "Temple du Lac**Bonnet de bain obligatoire."; break;
        case 558 : texte = "Temple de Glace**Le personnel tient à rappeler qu'un donjon n'est pas une patinoire."; break;
        case 559 : texte = "As-tu été voir le forgeron de ce village ?*On dit qu'il est très doué pour améliorer l'équipement des aventuriers, beaucoup de monde lui rend visite."; break;
        case 560 : texte = "Le temple se trouve au fin fond du désert, à la place d'une ancienne oasis."; break;
        case 561 : texte = "S : Terres de Feu*E : Village Cocorico"; break;
        case 562 : texte = "Château d'Hyrule"; break;
        case 563 : texte = "E : Village Cocorico"; break;
        case 564 : texte = "O : Roc de la Tortue*E : Lac Hylia"; break;
        case 565 : texte = "Temple Caché**Ici repose la lame purificatrice, Excalibur."; break;
        case 566 : texte = "N : Vers le cimetière hanté"; break;
#ifdef __vita__
        case 567 : texte = "Tu as trouvé la carte du donjon !!!*Appuie sur D-Pad Gauche pour voir le plan."; break;
#else
        case 567 : texte = "Tu as trouvé la carte du donjon !!!*Appuie sur P pour voir le plan."; break;
#endif
        case 568 : texte = "Tu as trouvé la boussole !!!*Tu peux localiser le boss et les coffres sur le plan."; break;
        case 569 : texte = "Tu as trouvé la clé du boss !!!"; break;
        case 570 : texte = "Tu as trouvé une petite clé !!!*Approche une porte pour l'ouvrir."; break;
        case 571 : texte = "Tu as trouvé les gants !!!*Utilise-les pour soulever des objets en les équipant ou en appuyant sur C."; break;
        case 572 : texte = "Tu as trouvé un cristal magique !!!"; break;
        case 573 : texte = "A quoi pourra-t-il bien servir ?"; break;
        case 574 : texte = "Il en reste encore "+s+" à trouver !!!"; break;
        case 575 : texte = "Plus que 2 à trouver !!!"; break;
        case 576 : texte = "Il ne t'en manque plus qu'un seul !!!"; break;
        case 577 : texte = "Tu as tous les cristaux, cours au château sauver Zelda !!!"; break;
        case 580 : texte = "Tu as trouvé le grappin !!!*Utilise-le pour franchir des obstacles."; break;
        case 581 : texte = "Tu as trouvé la lanterne !!!*Utilise-la pour faire jaillir des flammes."; break;
        case 582 : texte = "Tu as trouvé les palmes !!!*Equipe-les pour aller dans l'eau."; break;
        case 583 : texte = "Tu as trouvé le marteau magique !!!*Utilise-le pour écraser les obstacles."; break;
        case 584 : texte = "Tu as trouvé le baton de feu !!!*Tu peux désormais lancer de puissantes flammes à distance."; break;
        case 585 : texte = "Tu as trouvé le baton de glace !!!*Utilise-le pour tout congeler à distance."; break;
        case 586 : texte = "Tu as trouvé Excalibur !!!*Même Ganon ne devrait pas pouvoir résister à sa puissance !!! (en théorie)"; break;
        case 587 : texte = "Félicitation Link, tu as réussi à venir me délivrer!!!***Allons vite trouver Ganon, il faut impérativement lui reprendre la Triforce !"; break;
        case 589 : texte = "Le passage secret derrière la salle du trône mène à Ganon. Dépêchons-nous !"; break;
        case 590 : texte = "Nous y sommes presque, suis-moi !"; break;
        case 591 : texte = "J'ai bien peur que tu ne puisses jamais vaincre Ganon avec tes armes actuelles...*Va parler au chef du village Cocorico, je suis sûre qu'il trouvera une solution."; break;
        case 592 : texte = "Ganon est juste derrière cette porte, je vais soigner tes blessures."; break;
        case 593 : texte = "Ganon est toujours quelque part dans le château."; break;
        case 594 : texte = "Tu devrais attendre la princesse Zelda !!!"; break;
        case 595 : texte = "Tu n'aurais pas l'étrange sentiment d'oublier quelqu'un par hasard ???"; break;
        case 596 : texte = "Zelda t'attend!!!"; break;
        case 597 : texte = "Tu as trouvé la Triforce!!!"; break;
        case 598 : texte = "Tu as trouvé le livre de Mudora!!!**Tu comprends désormais le Hylien ancien!!!"; break;
        case 599 : texte = "Félicitation Link, tu as réussi à me trouver. En récompense, je t'offre le médaillon de Din, il augmente ta défense d'un point."; break;
        case 600 : texte = "Félicitation Link, tu as réussi à me trouver. En récompense, je t'offre le médaillon de Nayru, il augmente ta défense de deux points!!!"; break;
        case 601 : texte = "..."; break;
        case 602 : texte = "Tu as obtenu un médaillon magique !!!**Ta défense vient d'augmenter!!!"; break;
        case 603 : texte = "Félicitation Link, tu as réussi à me trouver. Pour te récompenser, je vais doubler la capacité de ta réserve de magie!!!"; break;
        case 604 : texte = "Ta réserve de magie a doublé!!!"; break;
        case 605 : texte = "Reviens me voir quand tu auras un flacon vide  et je te vendrai une potion rouge qui restaure l'énergie."; break;
        case 606 : texte = "Une potion rouge pour 60 rubis, ça t'intéresse?*              OUI ?            non  "; break;
        case 607 : texte = "Une potion rouge pour 60 rubis, ça t'intéresse?*              oui              NON ?"; break;
        case 608 : texte = "Merci, voilà ta potion.";break;
        case 609 : texte = "Tu as obtenu une potion rouge !!!*Bois-la pour restaurer ton énergie!!!"; break;
        case 610 : texte = "Tu as obtenu une potion verte !!!*Bois-la pour restaurer ta magie!!!"; break;
        case 611 : texte = "Tu as obtenu une potion bleue !!!*Bois-la pour restaurer ton énergie et ta magie!!!"; break;
        case 612 : texte = "Bonjour, je vous sers quelque chose ?"; break;
        case 613 : texte = "Hic! On raconte qu'une fée donnerait des objets enchantés... Hic! ...aux aventuriers qui la  trouveraient... Hic!!!"; break;
        case 614 : texte = "Un coeur pour 10 rubis, ok ?**              OUI ?            non  "; break;
        case 615 : texte = "Un coeur pour 10 rubis, ok ?**              oui              NON ?"; break;
        case 616 : texte = "Un peu de magie pour 20 rubis, ok ?**              OUI ?            non  "; break;
        case 617 : texte = "Un peu de magie pour 20 rubis, ok ?**              oui              NON ?"; break;
        case 618 : texte = "Beaucoup de magie pour 30 rubis, ok ?**              OUI ?            non  "; break;
        case 619 : texte = "Beaucoup de magie pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 620 : texte = "5 flèches pour 30 rubis, ok ?**              OUI ?            non  "; break;
        case 621 : texte = "5 flèches pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 622 : texte = "Une bombe pour 30 rubis, ok ?**              OUI ?            non  "; break;
        case 623 : texte = "Une bombe pour 30 rubis, ok ?**              oui              NON ?"; break;
        case 624 : texte = "Un arc pour 1000 rubis, ok ?**              OUI ?            non  "; break;
        case 625 : texte = "Un arc pour 1000 rubis, ok ?**              oui              NON ?"; break;
        case 626 : texte = "Un arc pour 50 rubis, ok ?**              OUI ?            non  "; break;
        case 627 : texte = "Un arc pour 50 rubis, ok ?**              oui              NON ?"; break;
        case 628 : texte = "Tu n'as pas besoin de ça maintenant."; break;
        case 629 : texte = "Merci."; break;
        case 630 : texte = "Tu as obtenu l'arc !!!*Utilise-le pour atteindre des cibles éloignées."; break;
        case 631 : texte = "Choisis ce que tu veux."; break;
        case 632 : texte = "Hein ???*Tu es en mission pour le chef ???*Bon alors je vais te faire une réduction sur l'arc..."; break;
        case 633 : texte = "Bonjour Link, je suis le chef de ce village, je me doutais que tu passerais."; break;
        case 634 : texte = "Depuis ce matin des monstres sont apparus un peu partout à Hyrule, j'ai voulu aller en parler à la princesse Zelda, mais comme tu l'as peut-être déjà vu, un puissant sortilège bloque l'accès au château..."; break;
        case 636 : texte = "Tu dis que Ganon est responsable de tout ça ? Qu'il a volé la Triforce et qu'il détient la princesse Zelda prisonnière ?"; break;
        case 637 : texte = "Mmmm... la situation est plus grave que je le croyais..."; break;
        case 638 : texte = "Il faut agir au plus vite, tu dois affronter Ganon à nouveau!"; break;
        case 639 : texte = "Comment entrer dans le château ? J'ai peut-être une idée..."; break;
        case 640 : texte = "Comme tu le sais, le pouvoir des 7 sages a été enfermé dans 7 cristaux par le sorcier Aghanim alors qu'il tentait de lever le sceau qui confinait Ganon au monde des ténèbres."; break;
        case 641 : texte = "Or, bien que tu aies ressuscité les descendants des sages après avoir vaincu Ganon et trouvé la Triforce, ces cristaux ont conservé leur puissance."; break;
        case 642 : texte = "Ils ont été cachés au fin fond des 7 temples, réunis-les tous et tu pourras passer outre le sortilège de Ganon."; break;
        case 643 : texte = "Ce ne sera toutefois pas chose aisé, Ganon a certainement dû envoyer ses meilleurs éléments protéger ces cristaux..."; break;
        case 644 : texte = "Une dernière chose, tu n'iras pas loin avec ton équipement actuel. Va voir le marchand d'armes et dis-lui que tu viens de ma part. Il fera sûrement un geste pour toi."; break;
        case 645 : texte = "Va voir le marchand d'armes et dis-lui que tu viens de ma part, il fera certainement un geste pour toi."; break;
        case 646 : texte = "Il te faut rassembler les 7 cristaux pour avoir une chance de sauver Zelda et Hyrule..."; break;
        case 647 : texte = "Tu as trouvé les 7 cristaux ? Alors rends-toi au château, tu dois avant tout délivrer la princesse, elle saura mieux que moi comment sauver Hyrule."; break;
        case 648 : texte = "Tes armes sont sans effet sur Ganon ? Dans ce cas tu dois trouver Excalibur. On raconte qu'elle a été dissimulée dans un temple caché.*On dit aussi que le chemin menant à la lame purificatrice passe par un village peuplé de monstres...*Je me demande si un tel village existe..."; break;
        case 650 : texte = "Toutefois j'ai bien peur que ton équipement actuel soit insuffisant pour accéder à ce temple, tu devrais peut-être passer voir le forgeron du village Gerudo..."; break;
        case 651 : texte = "Il est temps d'affronter Ganon et de lui reprendre la Triforce!"; break;
        case 652 : texte = "Hey! Il faut payer pour ouvrir un de mes coffres!!!"; break;
        case 653 : texte = "Un de ces coffres contient un quart de coeur, tu veux tenter ta chance pour 10 rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?*              OUI ?            non  "; break;
        case 654 : texte = "Un de ces coffres contient un quart de coeur, tu veux tenter ta chance pour 10 rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?*              oui              NON ?"; break;
        case 655 : texte = "Choisis un coffre."; break;
        case 656 : texte = "Je n'ai plus de prix à mettre en jeu, désolé."; break;
        case 657 : texte = "Perdu! Ce coffre est vide."; break;
        case 658 : texte = "Bonjour! Si vous êtes venu voir le forgeron, il habite un peu plus loin."; break;
        case 659 : texte = "Bonjour Link, je suis le chef de ce village.*Tu devrais aller voir le forgeron et lui présenter ce que tu veux qu'il reforge dans ton équipement."; break;
        case 660 : texte = "J'ai été informé de ta quête, alors je me suis arrangé avec lui.*Tout sera gratuit pour toi."; break;
        case 661 : texte = "Tu n'as pas besoin de boire cette potion maintenant."; break;
        case 662 : texte = "Une potion verte pour 40 rubis, ça t'intéresse?*              OUI ?            non  "; break;
        case 663 : texte = "Une potion verte pour 40 rubis, ça t'intéresse?*              oui              NON ?"; break;
        case 664 : texte = "Reviens me voir quand tu auras un flacon vide et je te vendrai une potion verte qui restaure la magie."; break;
        case 665 : texte = "Reviens plus tard, je suis débordé!"; break;
        case 666 : texte = "Puis-je faire quelque chose pour toi ?"; break;
        case 667 : texte = "Veux-tu que je reforge ton épée ?**              OUI ?            non  "; break;
        case 668 : texte = "Veux-tu que je reforge ton épée ?**              oui              NON ?"; break;
        case 669 : texte = "Ton épée a triplé de puissance et peut désormais renvoyer certaines attaques magiques, trop bien !!!*"; break;
        case 670 : texte = "Veux-tu que j'améliore tes gants ?**              OUI ?            non  "; break;
        case 671 : texte = "Veux-tu que j'améliore tes gants ?**              oui              NON ?"; break;
        case 672 : texte = "La puissance de tes gants va te permettre de soulever de lourds rochers."; break;
        case 673 : texte = "Veux-tu que j'améliore ton arc ?**              OUI ?            non  "; break;
        case 674 : texte = "Veux-tu que j'améliore ton arc ?**              oui              NON ?"; break;
        case 675 : texte = "Ton arc tire désormais des flèches d'argent d'une puissance dévastatrice!!!"; break;
        case 676 : texte = "Reviens me voir quand tu auras un flacon vide et je te vendrai une potion bleue qui restaure l'énergie et la magie."; break;
        case 677 : texte = "Une potion bleue pour 160 rubis, ça t'intéresse?*              OUI ?            non  "; break;
        case 678 : texte = "Une potion bleue pour 160 rubis, ça t'intéresse?*              oui              NON ?"; break;
        case 679 : texte = "Notre village a été fondé pour empêcher les aventuriers imprudents d'accéder au temple, je ne donne pas l'autorisation de passer à n'importe qui."; break;
        case 680 : texte = "Mmmm... Tu as déjà trouvé 4 cristaux ?*Je dois avouer que tu m'impressionnes..."; break;
        case 681 : texte = "Bon c'est entendu, tu as l'autorisation de passer par le cimetière, à tes risques et périls."; break;
        case 682 : texte = "Va parler au garde au nord du village, il te laissera passer."; break;
        case 683 : texte = "Je vois que tu es toujours vivant...*Etonnant."; break;
        case 684 : texte = "Le temple de l'ombre constitue le point de départ du chemin menant à un objet de légende. Ce village ne sert qu'à dissuader les aventuriers de trop s'en approcher."; break;
        case 685 : texte = "Ainsi tu as trouvé l'Epée ?*Mais ne crois pas qu'elle soit à toi pour autant."; break;
        case 686 : texte = "Excalibur fait partie du patrimoine le plus précieux d'Hyrule avec la Triforce, tu devras la ramener dans son sanctuaire une fois ta mission achevée."; break;
        case 687 : texte = "Les habitants de ce village sont tous des esprits ayant répondu à l'appel de la princesse Zelda."; break;
        case 688 : texte = "Lorsque tu as ramené la paix sur Hyrule et réunifié le monde de la lumière avec la Terre d'Or, Zelda a secrètement demandé aux esprits volontaires de créer ce village pour bloquer"; break;
        case 689 : texte = "l'accès à un objet de très grande valeur."; break;        
        case 690 : texte = "Bienvenue Link!*Laisse-moi t'expliquer ce que je fais ici."; break;
        case 691 : texte = "Comme tu l'as certainement remarqué, des monstres sont apparus partout dans Hyrule. C'est la première fois que je vois des monstres depuis que tu as vaincu Ganon."; break;
        case 692 : texte = "Et bien j'ai décidé de tous les répertorier."; break;
        case 693 : texte = "L'ennui c'est que je suis bien trop peureux pour aller à leur rencontre, alors j'ai besoin de ton aide."; break;
        case 694 : texte = "Il faut que tu battes chaque type de monstre et que tu viennes me faire ton rapport."; break;
        case 695 : texte = "Je te récompenserai tous les 7 nouveaux types d'ennemis vaincus."; break;
        case 696 : texte = "Si tu veux savoir quels ennemis tu as déjà vaincu, appuye sur M."; break;
        case 697 : texte = "Encore "+s+" ennemis différents avant la prochaine récompense."; break;
        case 698 : texte = "Plus qu'un nouvel ennemi avant la prochaine récompense!!!"; break;
        case 699 : texte = "Accepte ce cadeau pour ta contribution à mon projet :"; break;
        case 700 : texte = "Je suis désolé mais je n'ai plus rien à t'offrir..."; break;
        case 701 : texte = "Je n'en crois pas mes yeux, tu as réussi à vaincre chaque type d'ennemis !!!*Félicitation Link!!!"; break;        
        case 702 : texte = "                   Niveau 1 :**               Temple de la forêt"; break;
        case 703 : texte = "                   Niveau 2 :**                 Temple de l'eau"; break;
        case 704 : texte = "                   Niveau 3 :**              Temple de la montagne"; break;
        case 705 : texte = "                   Niveau 4 :**                Temple du désert"; break;
        case 706 : texte = "                   Niveau 5 :**                Temple de l'ombre"; break;
        case 707 : texte = "                   Niveau 6 :**                  Temple du feu"; break;
        case 708 : texte = "                   Niveau 7 :**                Temple de la glace"; break;
        case 709 : texte = "                   Niveau ? :**                   Temple secret"; break;
        case 710 : texte = "                 Niveau Final :**                Château d'Hyrule"; break;        
        case 711 :texte = "                Déjà fatigué ?                  ?                CONTINUER                  ?             Sauvegarder et quitter                        Quitter sans sauvegarder           "; break;
        case 712 :texte = "                Déjà fatigué ?                                   Continuer                     ?          SAUVEGARDER ET QUITTER           ?            Quitter sans sauvegarder           "; break;
        case 713 :texte = "                Déjà fatigué ?                                   Continuer                                Sauvegarder et quitter              ?         QUITTER SANS SAUVEGARDER          ?"; break;
        case 714 : texte = "A l'instant où Link toucha la Triforce, les monstres disparurent et la paix revint.**La princesse Zelda prit alors une grande décision: elle toucha à son tour la Triforce pour exaucer son voeu...**La Triforce fut depuis toujours à l'origine des problèmes survenus au Royaume, tôt ou tard un autre être malfaisant aurait fini par la trouver.**A la seconde où la princesse toucha la relique, elle disparue à jamais d'Hyrule.";
        case 715 : texte = "Depuis ce jour, le peuple d'Hyrule vécut en paix, sans craindre de nouveaux désastres.**Ainsi s'achève la légende de Zelda, celle de la  Triforce et de la Terre d'Or.**On dit que l'épée Excalibur repose en sûreté quelque part, et qu'elle constitue le dernier souvenir de la quête de Link..."; break;
        case 716 : texte = "Félicitation Link, tu as réussi à me trouver. En récompense, je t'offre le médaillon de Farore, il augmente ta défense d'un point."; break;
        case 717 : texte = "Souhaites-tu sauvegarder ta partie ?**                    ? OUI ?*                      non  "; break;
        case 718 : texte = "Souhaites-tu sauvegarder ta partie ?**                      oui  *                    ? NON ?"; break;
        case 719 : texte = "Partie sauvegardée."; break;
        case 720 : texte = "Le Royaume d'Hyrule était en paix depuis que Link, dernier chevalier hylien, avait vaincu le maléfique Ganon et lui avait repris la précieuse Triforce."; break;
        case 721 : texte = "Nul ne sait quel voeu fit Link en touchant la Triforce, mais il eut comme effet de réunifier le monde de la lumière et celui des ténèbres, et ramena à la vie les descendants des 7 sages."; break;
        case 722 : texte = "Link remit ensuite à la princesse Zelda la Triforce et l'épée Excalibur, et le peuple se mit à croire que la paix durerait.*Mais le peuple se trompait..."; break;
        case 723 : texte = "Le souhait de Link à la Triforce eu hélas de fâcheux effets. Ganon et ses sbires furent ainsi ressuscités et s'apprêtèrent à attaquer."; break;
        case 724 : texte = "Quelque part dans la forêt d'Hyrule, Link dort sans se douter que Ganon est passé à l'attaque, jusqu'à ce qu'"; break;
        case 725 : texte ="une voix familière lui parle dans son sommeil..."; break;
        case 726 : texte = "A l'aide!*A l'aide!*C'est moi! C'est Zelda!*Je te parle par télépathie."; break;
        case 727 : texte = "Je suis retenue prisonnière dans le donjon du château! J'ai besoin de ton aide!*Ganon est de retour, et il a certainement dû trouver la Triforce à l'heure qu'il est..."; break;
        case 728 : texte = "Viens vite au château Link, tu es mon seul espoir..."; break;
#ifdef __vita__
        case 729 : texte = "AIDE : Appuie sur Select pour consulter l'aide."; break;
#else
        case 729 : texte = "AIDE : Appuie sur F1 pour consulter l'aide."; break;
#endif
        default : 
            texte = "[ERREUR TEXTE]";
    }

    return texte;
}

void Texte::chercheText() {
    ostringstream os;
    int tmp;
    switch (id) {
        case 1  : texte = (this->*getTextByLangFunc)(501, os.str()); break;
        case 2  : texte = (this->*getTextByLangFunc)(502, os.str()); break;
        case 3  : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = (this->*getTextByLangFunc)(503, os.str());
            if (tmp<4) buffer = (this->*getTextByLangFunc)(504, os.str());
            else buffer = (this->*getTextByLangFunc)(505, os.str());
            break;
        case 11 : texte = (this->*getTextByLangFunc)(511, os.str()); break;
        case 12 : texte = (this->*getTextByLangFunc)(512, os.str()); break;
        case 13 : texte = (this->*getTextByLangFunc)(513, os.str()); break;
        case 14 : texte = (this->*getTextByLangFunc)(514, os.str()); break;
        case 15 : texte = (this->*getTextByLangFunc)(515, os.str()); break;
        case 16 : texte = (this->*getTextByLangFunc)(516, os.str()); break;
        case 17 : texte = (this->*getTextByLangFunc)(517, os.str()); break;
        case 18 : texte = (this->*getTextByLangFunc)(518, os.str()); break;
        case 19 : texte = (this->*getTextByLangFunc)(519, os.str()); break;
        case 20 : texte = (this->*getTextByLangFunc)(520, os.str()); break;
        case 21 : texte = (this->*getTextByLangFunc)(521, os.str()); break;
        case 22 : texte = (this->*getTextByLangFunc)(522, os.str()); break;
        case 23 : texte = (this->*getTextByLangFunc)(523, os.str()); break;
        case 24 : texte = (this->*getTextByLangFunc)(524, os.str()); break;
        case 25 : texte = (this->*getTextByLangFunc)(525, os.str()); break;
        case 26 : texte = (this->*getTextByLangFunc)(526, os.str()); break;
        case 27 : texte = (this->*getTextByLangFunc)(527, os.str()); 
            if ((gpJeu->getJoueur()->hasBouteille(0) && gpJeu->getZone()==8)
            || (gpJeu->getJoueur()->hasBouteille(1) && gpJeu->getZone()==5)
            || (gpJeu->getJoueur()->hasBouteille(2) && gpJeu->getZone()==6)) {id=32; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) idsuiv=29;
            else idsuiv=30;
            break;
        case 28 : texte = (this->*getTextByLangFunc)(528, os.str()); idsuiv=31; break;
        case 29 : texte = (this->*getTextByLangFunc)(529, os.str()); break;
        case 30 : texte = (this->*getTextByLangFunc)(530, os.str()); break;
        case 31 : texte = (this->*getTextByLangFunc)(531, os.str()); break;
        case 32 : texte = (this->*getTextByLangFunc)(532, os.str()); break;
        case 33 : texte = (this->*getTextByLangFunc)(533, os.str()); break;
        case 35 : texte = (this->*getTextByLangFunc)(535, os.str()); break;
        case 36 : texte = (this->*getTextByLangFunc)(536, os.str()); break;
        case 37 : texte = (this->*getTextByLangFunc)(537, os.str()); break;
        case 38 : texte = (this->*getTextByLangFunc)(538, os.str()); break;
        case 39 : texte = (this->*getTextByLangFunc)(539, os.str()); break;
        case 40 : texte = (this->*getTextByLangFunc)(540, os.str()); break;
        case 41 : texte = (this->*getTextByLangFunc)(541, os.str()); break;
        case 42 : texte = (this->*getTextByLangFunc)(542, os.str()); break;
        case 43 : texte = (this->*getTextByLangFunc)(543, os.str()); break;
        case 44 : texte = (this->*getTextByLangFunc)(544, os.str()); break;
        case 45 : texte = (this->*getTextByLangFunc)(545, os.str()); break;
        case 46 : texte = (this->*getTextByLangFunc)(546, os.str()); break;
        case 47 : texte = (this->*getTextByLangFunc)(547, os.str()); break;
        case 48 : texte = (this->*getTextByLangFunc)(548, os.str()); break;
        case 49 : texte = (this->*getTextByLangFunc)(549, os.str()); break;
        case 50 : texte = (this->*getTextByLangFunc)(550, os.str()); break;
        case 51 : texte = (this->*getTextByLangFunc)(551, os.str()); break;
        case 52 : texte = (this->*getTextByLangFunc)(552, os.str()); break;
        case 54 : texte = (this->*getTextByLangFunc)(554, os.str()); break;
        case 55 : texte = (this->*getTextByLangFunc)(555, os.str()); break;
        case 56 : texte = (this->*getTextByLangFunc)(556, os.str()); break;
        case 57 : texte = (this->*getTextByLangFunc)(557, os.str()); break;
        case 58 : texte = (this->*getTextByLangFunc)(558, os.str()); break;
        case 59 : texte = (this->*getTextByLangFunc)(559, os.str()); break;
        case 60 : texte = (this->*getTextByLangFunc)(560, os.str()); break;
        case 61 : texte = (this->*getTextByLangFunc)(561, os.str()); break;
        case 62 : texte = (this->*getTextByLangFunc)(562, os.str()); break;
        case 63 : texte = (this->*getTextByLangFunc)(563, os.str()); break;
        case 64 : texte = (this->*getTextByLangFunc)(564, os.str()); break;
        case 65 : texte = (this->*getTextByLangFunc)(565, os.str()); break;
        case 66 : texte = (this->*getTextByLangFunc)(566, os.str()); break;
        case 67 : texte = (this->*getTextByLangFunc)(567, os.str()); break;
        case 68 : texte = (this->*getTextByLangFunc)(568, os.str()); break;
        case 69 : texte = (this->*getTextByLangFunc)(569, os.str()); break;
        case 70 : texte = (this->*getTextByLangFunc)(570, os.str()); break;
        case 71 : texte = (this->*getTextByLangFunc)(571, os.str()); break;
        case 72 : 
            texte = (this->*getTextByLangFunc)(572, os.str());; 
            tmp = 7-gpJeu->getJoueur()->nbCristaux();
            os << tmp;
            if (tmp==6 && !gpJeu->getJoueur()->getAvancement()) buffer = (this->*getTextByLangFunc)(573, os.str());
            else if (tmp>2) buffer = (this->*getTextByLangFunc)(574, os.str());
            else if (tmp==2) buffer = (this->*getTextByLangFunc)(575, os.str());
            else if (tmp==1) buffer = (this->*getTextByLangFunc)(576, os.str());
            else if (tmp==0) buffer = (this->*getTextByLangFunc)(577, os.str());
            break;
        case 80 : texte = (this->*getTextByLangFunc)(580, os.str());; break;
        case 81 : texte = (this->*getTextByLangFunc)(581, os.str()); break;
        case 82 : texte = (this->*getTextByLangFunc)(582, os.str()); break;
        case 83 : texte = (this->*getTextByLangFunc)(583, os.str()); break;
        case 84 : texte = (this->*getTextByLangFunc)(584, os.str()); break;
        case 85 : texte = (this->*getTextByLangFunc)(585, os.str()); break;
        case 86 : texte = (this->*getTextByLangFunc)(586, os.str()); break;
        case 87 : texte = (this->*getTextByLangFunc)(587, os.str()); break;
        case 89 : texte = (this->*getTextByLangFunc)(589, os.str()); break;
        case 90 : texte = (this->*getTextByLangFunc)(590, os.str()); break;
        case 91 : texte = (this->*getTextByLangFunc)(591, os.str()); break;
        case 92 : texte = (this->*getTextByLangFunc)(592, os.str()); break;
        case 93 : texte = (this->*getTextByLangFunc)(593, os.str()); break;
        case 94 : texte = (this->*getTextByLangFunc)(594, os.str()); break;
        case 95 : texte = (this->*getTextByLangFunc)(595, os.str()); break;
        case 96 : texte = (this->*getTextByLangFunc)(596, os.str()); break;
        case 97 : texte = (this->*getTextByLangFunc)(597, os.str()); break;
        case 98 : texte = (this->*getTextByLangFunc)(598, os.str()); break;
        case 99 : texte = (this->*getTextByLangFunc)(599, os.str()); break;
        case 100 : texte = (this->*getTextByLangFunc)(600, os.str()); break;
        case 101 : texte = (this->*getTextByLangFunc)(601, os.str());; break;
        case 102 : texte = (this->*getTextByLangFunc)(602, os.str()); break;
        case 103 : texte = (this->*getTextByLangFunc)(603, os.str()); break;
        case 104 : texte = (this->*getTextByLangFunc)(604, os.str()); break;
        case 105 : texte = (this->*getTextByLangFunc)(605, os.str()); break;
        case 106 : texte = (this->*getTextByLangFunc)(606, os.str());
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=105; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=29;
            else idsuiv=108; break;
        case 107 : texte = (this->*getTextByLangFunc)(607, os.str()); break;
        case 108 : texte = (this->*getTextByLangFunc)(608, os.str());break;
        case 109 : texte = (this->*getTextByLangFunc)(609, os.str()); break;
        case 110 : texte = (this->*getTextByLangFunc)(610, os.str()); break;
        case 111 : texte = (this->*getTextByLangFunc)(611, os.str()); break;
        case 112 : texte = (this->*getTextByLangFunc)(612, os.str()); break;
        case 113 : texte = (this->*getTextByLangFunc)(613, os.str()); break;
        case 114 : texte = (this->*getTextByLangFunc)(614, os.str()); 
            if (gpJeu->getJoueur()->getVie()+gpJeu->getJoueur()->getBoostVie()
            == gpJeu->getJoueur()->getVieMax()) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=29;
            else idsuiv=129; break;
        case 115 : texte = (this->*getTextByLangFunc)(615, os.str()); break;
        case 116 : texte = (this->*getTextByLangFunc)(616, os.str());
            if (gpJeu->getJoueur()->getMagie()+gpJeu->getJoueur()->getBoostMagie()
            == gpJeu->getJoueur()->getMagieMax() || !gpJeu->getJoueur()->hasObjet(O_LANTERNE)) {
                id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=29;
            else idsuiv=129; break;
        case 117 : texte = (this->*getTextByLangFunc)(617, os.str()); break;
        case 118 : texte = (this->*getTextByLangFunc)(618, os.str());
            if (gpJeu->getJoueur()->getMagie()+gpJeu->getJoueur()->getBoostMagie()
            == gpJeu->getJoueur()->getMagieMax() || !gpJeu->getJoueur()->hasObjet(O_LANTERNE)) {
                id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 119 : texte = (this->*getTextByLangFunc)(619, os.str()); break;
        case 120 : texte = (this->*getTextByLangFunc)(620, os.str());
            if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax() 
            || !gpJeu->getJoueur()->hasObjet(O_ARC)) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 121 : texte = (this->*getTextByLangFunc)(621, os.str()); break;
        case 122 : texte = (this->*getTextByLangFunc)(622, os.str()); 
            if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax() 
            || !gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=128; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=29;
            else idsuiv=129; break;
        case 123 : texte = (this->*getTextByLangFunc)(623, os.str()); break;
        case 124 : texte = (this->*getTextByLangFunc)(624, os.str()); 
            idsuiv=29; break;
        case 125 : texte = (this->*getTextByLangFunc)(625, os.str()); break;
        case 126 : texte = (this->*getTextByLangFunc)(626, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<50) idsuiv=29;
            else idsuiv=129; break;
        case 127 : texte = (this->*getTextByLangFunc)(627, os.str()); break;
        case 128 : texte = (this->*getTextByLangFunc)(628, os.str()); break;
        case 129 : texte = (this->*getTextByLangFunc)(629, os.str()); break;
        case 130 : texte = (this->*getTextByLangFunc)(630, os.str()); break;
        case 131 : texte = (this->*getTextByLangFunc)(631, os.str()); break;
        case 132 : texte = (this->*getTextByLangFunc)(632, os.str()); break;
        case 133 : texte = (this->*getTextByLangFunc)(633, os.str()); idsuiv=134; break;
        case 134 : texte = (this->*getTextByLangFunc)(634, os.str()); idsuiv=136; break;
        case 136 : texte = (this->*getTextByLangFunc)(636, os.str()); idsuiv=137; break;
        case 137 : texte = (this->*getTextByLangFunc)(637, os.str()); idsuiv=138; break;
        case 138 : texte = (this->*getTextByLangFunc)(638, os.str()); idsuiv=139; break;
        case 139 : texte = (this->*getTextByLangFunc)(639, os.str()); idsuiv=140; break;
        case 140 : texte = (this->*getTextByLangFunc)(640, os.str()); idsuiv=141; break;
        case 141 : texte = (this->*getTextByLangFunc)(641, os.str()); idsuiv=142; break;
        case 142 : texte = (this->*getTextByLangFunc)(642, os.str()); idsuiv=143; break;
        case 143 : texte = (this->*getTextByLangFunc)(643, os.str()); idsuiv=144; break;
        case 144 : texte = (this->*getTextByLangFunc)(644, os.str());; break;
        case 145 : texte = (this->*getTextByLangFunc)(645, os.str()); break;
        case 146 : texte = (this->*getTextByLangFunc)(646, os.str()); break;
        case 147 : texte = (this->*getTextByLangFunc)(647, os.str()); break;
        case 148 : texte = (this->*getTextByLangFunc)(648, os.str()); break;
        case 150 : texte = (this->*getTextByLangFunc)(650, os.str()); break;
        case 151 : texte = (this->*getTextByLangFunc)(651, os.str()); break;
        case 152 : texte = (this->*getTextByLangFunc)(652, os.str()); break;
        case 153 : texte = (this->*getTextByLangFunc)(653, os.str()); 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=29; break;
        case 154 : texte = (this->*getTextByLangFunc)(654, os.str()); break;
        case 155 : texte = (this->*getTextByLangFunc)(655, os.str()); break;
        case 156 : texte = (this->*getTextByLangFunc)(656, os.str()); break;
        case 157 : texte = (this->*getTextByLangFunc)(657, os.str()); break;
        case 158 : texte = (this->*getTextByLangFunc)(658, os.str()); break;
        case 159 : texte = (this->*getTextByLangFunc)(659, os.str());
            buffer = (this->*getTextByLangFunc)(660, os.str()); break;
        case 160 : texte = (this->*getTextByLangFunc)(661, os.str()); break;
        case 161 : texte = (this->*getTextByLangFunc)(662, os.str());
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=163; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=29;
            else idsuiv=108; break;
        case 162 : texte = (this->*getTextByLangFunc)(663, os.str()); break;
        case 163 : texte = (this->*getTextByLangFunc)(664, os.str()); break;
        case 164 : texte = (this->*getTextByLangFunc)(665, os.str()); break;
        case 165 : texte = (this->*getTextByLangFunc)(666, os.str());
            if (gpJeu->getJoueur()->getEpee()==1) {id=166; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_GANTS)==1 && gpJeu->getJoueur()->getObjet()==8) {
                id=169; chercheText();break;}
            if (gpJeu->getJoueur()->hasObjet(O_ARC)==2 && gpJeu->getJoueur()->getObjet()==0 
            && gpJeu->getJoueur()->nbCristaux()==7) {
                id=172; chercheText();break;}
            break;
        case 166 : texte = (this->*getTextByLangFunc)(667, os.str()); break;
        case 167 : texte = (this->*getTextByLangFunc)(668, os.str()); break;
        case 168 : texte = (this->*getTextByLangFunc)(669, os.str()); break;
        case 169 : texte = (this->*getTextByLangFunc)(670, os.str()); break;
        case 170 : texte = (this->*getTextByLangFunc)(671, os.str()); break;
        case 171 : texte = (this->*getTextByLangFunc)(672, os.str()); break;
        case 172 : texte = (this->*getTextByLangFunc)(673, os.str()); break;
        case 173 : texte = (this->*getTextByLangFunc)(674, os.str()); break;
        case 174 : texte = (this->*getTextByLangFunc)(675, os.str()); break;
        case 175 : texte = (this->*getTextByLangFunc)(676, os.str()); break;
        case 176 : texte = (this->*getTextByLangFunc)(677, os.str());
            if (gpJeu->getJoueur()->hasBouteille(0)!=1
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=175; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=29;
            else idsuiv=108; break;
        case 177 : texte = (this->*getTextByLangFunc)(678, os.str()); break;
        case 178 : texte = (this->*getTextByLangFunc)(679, os.str()); break;
        case 179 : texte = (this->*getTextByLangFunc)(680, os.str());
            buffer = (this->*getTextByLangFunc)(681, os.str()); break;
        case 181 : texte = (this->*getTextByLangFunc)(682, os.str()); break;
        case 182 : texte = (this->*getTextByLangFunc)(683, os.str()); break;
        case 183 : texte = (this->*getTextByLangFunc)(684, os.str()); break;
        case 184 : texte = (this->*getTextByLangFunc)(685, os.str());
            buffer = (this->*getTextByLangFunc)(686, os.str()); break;
        case 186 : texte = (this->*getTextByLangFunc)(687, os.str()); break;
        case 187 : texte = (this->*getTextByLangFunc)(688, os.str());
            buffer = (this->*getTextByLangFunc)(689, os.str()); break;
        
        case 189 : texte = (this->*getTextByLangFunc)(690, os.str()); idsuiv=190; break;
        case 190 : texte = (this->*getTextByLangFunc)(691, os.str()); idsuiv=191; break;
        case 191 : texte = (this->*getTextByLangFunc)(692, os.str()); idsuiv=192; break;
        case 192 : texte = (this->*getTextByLangFunc)(693, os.str()); idsuiv=193; break;
        case 193 : texte = (this->*getTextByLangFunc)(694, os.str()); idsuiv=194; break;
        case 194 : texte = (this->*getTextByLangFunc)(695, os.str()); idsuiv=195; break;
        case 195 : texte = (this->*getTextByLangFunc)(696, os.str()); break;
        
        
        case 196 : 
            if (gpJeu->getJoueur()->getCoeur(43)) {
                if (gpJeu->getJoueur()->nbEnnemis() >= 46) {id=205; chercheText();return;}
                else {id=204; chercheText();return;}
            }
            for (int i = 38; i < 44; i++) 
                if (!gpJeu->getJoueur()->getCoeur(i) 
                && (gpJeu->getJoueur()->nbEnnemis()/7)+37>=i) {
                    id=203; chercheText();return;
                }
            tmp = 7-(gpJeu->getJoueur()->nbEnnemis()%7);
            os << tmp;
            if (tmp>1) texte = (this->*getTextByLangFunc)(697, os.str());
            else texte = (this->*getTextByLangFunc)(698, os.str());
            break;
        case 203 : texte = (this->*getTextByLangFunc)(699, os.str()); break;
        case 204 : texte = (this->*getTextByLangFunc)(700, os.str()); break;
        case 205 : texte = (this->*getTextByLangFunc)(701, os.str()); break;
        
        case 206 : texte = (this->*getTextByLangFunc)(702, os.str()); break;
        case 207 : texte = (this->*getTextByLangFunc)(703, os.str()); break;
        case 208 : texte = (this->*getTextByLangFunc)(704, os.str()); break;
        case 209 : texte = (this->*getTextByLangFunc)(705, os.str()); break;
        case 210 : texte = (this->*getTextByLangFunc)(706, os.str()); break;
        case 211 : texte = (this->*getTextByLangFunc)(707, os.str()); break;
        case 212 : texte = (this->*getTextByLangFunc)(708, os.str()); break;
        case 213 : texte = (this->*getTextByLangFunc)(709, os.str()); break;
        case 214 : texte = (this->*getTextByLangFunc)(710, os.str()); break;
        
        case 215 :texte = (this->*getTextByLangFunc)(711, os.str()); break;
        case 216 :texte = (this->*getTextByLangFunc)(712, os.str()); break;
        case 217 :texte = (this->*getTextByLangFunc)(713, os.str()); break;
        
        case 223 : texte = (this->*getTextByLangFunc)(714, os.str());
            buffer = (this->*getTextByLangFunc)(715, os.str()); break;
        case 224 : texte = (this->*getTextByLangFunc)(716, os.str()); break;
        case 225 : texte = (this->*getTextByLangFunc)(717, os.str()); break;
        case 226 : texte = (this->*getTextByLangFunc)(718, os.str()); break;
        case 227 : texte = (this->*getTextByLangFunc)(719, os.str()); break;
        
        case 228 : texte = (this->*getTextByLangFunc)(720, os.str()); idsuiv = 229; break;
        case 229 : texte = (this->*getTextByLangFunc)(721, os.str()); idsuiv = 230; break;
        case 230 : texte = (this->*getTextByLangFunc)(722, os.str()); idsuiv=231; break;
        case 231 : texte = (this->*getTextByLangFunc)(723, os.str()); idsuiv=232; break;
        case 232 : texte = (this->*getTextByLangFunc)(724, os.str()); 
            buffer=(this->*getTextByLangFunc)(725, os.str()); break;
        case 233 : texte = (this->*getTextByLangFunc)(726, os.str()); idsuiv = 234; break;
        case 234 : texte = (this->*getTextByLangFunc)(727, os.str()); idsuiv=235; break;
        case 235 : texte = (this->*getTextByLangFunc)(728, os.str()); break;
        case 236 : texte = (this->*getTextByLangFunc)(729, os.str()); break;
    }
    
    
}

void Texte::affiche(SDL_Surface* gpScreen, std::string s, int a, int b) {
    for (int i = 0; i < (int)s.length(); i++) {
        afficheLettre(gpScreen, s.at(i),a,b);
        a+=6;
    }
}

void Texte::afficheTexteAvecId(SDL_Surface* gpScreen, int id, std::string s, int a, int b) {
    std::string texte = (this->*getTextByLangFunc)(id, s);
    affiche(gpScreen, texte, a, b);
}

void Texte::draw(SDL_Surface* gpScreen) {
    
    if (cadre) drawCadre(gpScreen);
    
    if (id==3 && texte == "Tu as trouvé un quart de coeur !!!") {
        SDL_Rect src; SDL_Rect dst;
        src.x=16*(gpJeu->getJoueur()->nbQuarts()%4);
        if(src.x==0)src.x=16*4;
        src.y=0; src.w=16; src.h=16; dst.x=160-8; dst.y=120-8+16*5;
        SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
    }
    
    int a = x+8; int b = y+8;
    for (int i = 0; i < av; i++) {
        afficheLettre(gpScreen, texte.at(i),a,b);
        a+=6;
        if (a > x+w-16) {a=x+8; b+=16;}
    }
    
    if(SDL_GetTicks() > lastAnimTime + vitesse && def && av < (int)texte.length()) {
        lastAnimTime = SDL_GetTicks();
        do av++;
        while (av < (int)texte.length() && texte.at(av-1) == ' ');
        if (texte.at(av-1) != ' ') gpJeu->getAudio()->playSound(0,1);
    }
}


void processConditionalText(std::string getTextFunc(int), int id) {
    ostringstream os;
    int tmp;

}

bool Texte::isFinished() {return (av==(int)texte.length());}

int Texte::getId() {return id;}

void Texte::changeId(int i) {
    id=i; idsuiv=0; buffer="";
    chercheText();
    decoupeText();
    if (av>(int)texte.length()) av=(int)texte.length();
}

void Texte::drawCadre(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=8; src.h=8; src.x = 103; src.y = 100; dst.x = x; dst.y = y;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.y = 109; src.w=8;
    for (int j = 8; j < h-8; j+=16) {
        dst.y = y + j;
        src.x = 103; dst.x = x; src.h=16;
        while (dst.y + src.h > y+h && src.h>0) src.h--;
        if (src.h>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
        src.x = 129; dst.x = x+w-8;
        if (src.h>0)SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.h=8; src.x = 103; src.y = 126; dst.x = x; dst.y = y+h-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

void Texte::setTexte(int idTxt, int vx, int vy, int vw, int vh, bool cadr, bool defil, int vit) {
    if (idTxt == 0) return;
    id = idTxt; 
    idsuiv = 0;
    buffer = "";
    chercheText();
    
    x = vx; y = vy; w = vw; h = vh;
    decoupeText();
        
    def=defil;
    if (def) av = 0;
    else av = texte.length();
    
    cadre = cadr;
    
    vitesse = vit;
}

void Texte::decoupeText() {
    //compte le nombre de caractères possibles et largeur et en hauteur
    int nbcol = (w-16)/6 -1;
    int nblig = (h-16)/16;
    int tailleMax = nbcol * nblig;
    int taille;
    
    //parcours du texte à afficher; à chaque début de mot, 
    //vérifie que le mot peut tenir sur la ligne
    for (int i = 0; i < (int)texte.length(); i++) {
        
        //supprime les espaces isolés en début de ligne
        if (texte.at(i)==' ' && texte.at(i+1)!=' ' && i%nbcol == 0) texte.erase(i,1);
        //recherche du début du prochain mot
        while(texte.at(i)==' ' && i < (int)texte.length()-1) i++;
        
        //saute une ligne si trouve une étoile
        if (texte.at(i)=='*') {
            texte.erase(i,1);//replace(i, 1, " ");
            int nb = (nbcol)-(i%(nbcol));
            for (int j = 0; j < nb; j++) texte.insert(i," ");
            continue;
        }
        
        //si le mot dépasse
        taille = tailleMot(i);
        if ((i%nbcol)+taille>nbcol) {
            if  (i < tailleMax) {
                //si le mot ne tient pas sur une ligne, on le coupe avec des tirets
                if (taille>nbcol) {
                    texte.insert(((i/nbcol)+1)*nbcol-1,"--");
                    i = 1+((i/nbcol)+1)*nbcol;
                }
                //sinon, on ajoute des espaces pour faire commencer le mot à la ligne
                else while((i%nbcol) != 0) {texte.insert(i," "); i++;}
            }
        }
        
    }
    
    // si le texte est trop grand, on le coupe en deux
    if ((int)texte.length() > tailleMax) {
        buffer = texte.substr(tailleMax);
        texte = texte.substr(0, tailleMax);
    }
}

int Texte::tailleMot(int deb) {
    int i = deb;
    int total = 0;
    while (texte.at(i)!=' ') {total++; i++; if (i >= (int)texte.length()) return total;}
    return total;
}

void Texte::afficheLettre(SDL_Surface* gpScreen, char c, int vx, int vy) {
    SDL_Rect src;
    SDL_Rect dst;
    
    int val = (int)c;
    
    dst.x=vx; dst.y=vy;
    src.h=16;src.w=8;
    
    if(val==32) return;
    
    //minuscules a-z
    if(val>=97 && val<=122) {
		src.x=4+16*((val-97)%10); 
		src.y=52+16*((val-97)/10);
	}
	//majuscules A-Z
	else if(val>=65 && val<=90) {src.x=6+16*((val-65)%10); src.y=2+16*((val-65)/10);}
	//chiffres
    else if(val>=48 && val<=57) {src.x=3+16*((val-48)%5); src.y=103+16*((val-48)/5);}
	else {
		switch(val){
			// Caractères spéciaux
			// /
			case 47: src.x=52;src.y=151;break;
			// @ hylien
			case 64: src.x=4;src.y=151;break;
            // + hylien
			case 43: src.x=20;src.y=151;break;
            // = hylien
			case 61: src.x=36;src.y=151;break;
			// ç
			case -25:
			case 231: src.x=148;src.y=34;break;
			// é
			case -23: 
			case 233: src.x=100;src.y=84;break;
			// ê
			case -22:
			case 234: src.x=116;src.y=84;break;
			// è
			case -24:
			case 232: src.x=132;src.y=84;break;
			// ë
			case -21:
			case 235: src.x=132;src.y=151;break;
			// à
			case -32:
			case 224: src.x=148;src.y=84;break;
			// â
			case -30:
			case 226: src.x=148;src.y=103;break;
			// ä
			case -28:
			case 228: src.x=148;src.y=135;break;
			// î
			case -18:
			case 238: src.x=84;src.y=119;break;
			// ï
			case -17:
			case 239: src.x=116;src.y=151;break;
			// û
			case -5:
			case 251: src.x=84;src.y=103;break;
			// ù
			case -7:
			case 249: src.x=148;src.y=151;break;
			// ü
			case -4:
			case 252: src.x=116;src.y=135;break;
			// ö
			case -10:
			case 246: src.x=132;src.y=135;break;
			// ô
			case -12:
			case 244: src.x=148;src.y=119;break;
			
			// Ponctuation
			//ponctuation
			// -
			case 45: src.x=102;src.y=34;break;
			// .
			case 46: src.x=118;src.y=34;break;
			// ,
			case 44: src.x=134;src.y=34;break;
			// !
			case 33: src.x=3;src.y=135;break;
			// ?
			case 63: src.x=19;src.y=135;break;
			// (
			case 40: src.x=35;src.y=135;break;
			// )
			case 41: src.x=51;src.y=135;break;            
			// ' ( avec @ )
			case 39: src.x=67;src.y=135;break;
			// :
			case 58: src.x=83;src.y=135;break;
			// ... ( avec % )
			case 37: src.x=101;src.y=135;break;
			// >
			case 62: src.x=100;src.y=151;break;
			// <
			case 60: src.x=84;src.y=151;break;
		}
	}
    
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

bool Texte::hasNext() {
    return (buffer != "" || idsuiv > 0);
}

bool Texte::suite() {
    if (av < (int)texte.length()) {
        av = texte.length();
        return true;
    }
    if (!hasNext()) {
        gpJeu->getAudio()->playSound(18);
        return gpJeu->finTexte(id);
    }
    if (buffer != "") {
        texte = buffer;
        buffer = "";
    }
    else {
        id = idsuiv;
        idsuiv = 0;
        chercheText();
    }
    decoupeText();
    if (def) av = 0;
    else av = texte.length();
    gpJeu->getAudio()->playSound(17);
    return true;
}
