#ifndef __OS_VITA_H__
#define __OS_VITA_H__


#include <stdlib.h>
#include <vitasdk.h>
#include "../Jeu.h"

/*
Languages
ID 	Description
0 	JP
1 	EN Supported and default for unsupported
2 	FR Supported
3 	DE Supported
4 	IT 
5 	ES Supported
6 	ZH
7 	KO
8 	NL
9 	PT
10 	RU
11 	TW 
*/

enum Languages { 
    LANG_EN = 1,
    LANG_FR = 2
};

const int MIN_LANG = LANG_EN, MAX_LANG = LANG_FR, DEFAULT_LANG = LANG_EN;

int getLanguage(void);
void setLanguage(Jeu* gpJeu, int languageID);
int SDL_GetKeyStateVita(void* p);

#endif