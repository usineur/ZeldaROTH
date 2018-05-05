/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL/SDL.h>

#include "Audio.h"

#ifdef __vita__
#include <sys/stat.h>
#endif

Audio::Audio() : musiqueId(0), specialId(0) {
    SOUND = true;
    music = NULL;
#ifdef __vita__
    f = NULL;
    mem = NULL;
#endif
    
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) == -1) SOUND = false;
    
    if (SOUND) {
#ifdef __vita__
        Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 2048);
#else
        Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
#endif
        previous_volume = Mix_VolumeMusic(32);
        loadSounds();
        setVolson(32);
    }
}

Audio::~Audio() {
    if (SOUND) {
        freeSounds();
        Mix_PauseMusic();
        Mix_VolumeMusic(previous_volume);
        Mix_HaltMusic();
        freeMusic();
        Mix_CloseAudio();
    }
}

void Audio::setVolume(int volume) {
	Mix_VolumeMusic(volume);
}

void Audio::setVolson(int volson) {
    for (int i = 0; i < 40; i++)
		Mix_VolumeChunk(sons[i], volson);
}

void Audio::loadSounds() {
    sons = new Mix_Chunk*[40];

    sons[0] = getSound("text"); // lettres
    sons[1] = getSound("menu1"); // menu 1
    sons[2] = getSound("menu2"); // menu 2
    sons[3] = getSound("menu3"); // menu 3
    sons[4] = getSound("menu4"); // menu 4
    sons[5] = getSound("timewarp"); // time retour
    sons[6] = getSound("tombe"); // tombe (ennemi)
    sons[7] = getSound("hitenemy"); //shot 1
    sons[8] = getSound("killenemy"); // shot 2
    sons[9] = getSound("surprise"); // surprise
    sons[10] = getSound("monte"); // monte
    sons[11] = getSound("descend"); // descend
    sons[12] = getSound("chute"); // chute
    sons[13] = getSound("item"); // item
    sons[14] = getSound("rupee"); // rubis
    sons[15] = getSound("heart"); // coeur
    sons[16] = getSound("bomb"); // bombe
    sons[17] = getSound("textnext"); // suite texte
    sons[18] = getSound("textend"); // fin texte
    sons[19] = getSound("happy"); // trouve objet
    sons[20] = getSound("door"); // ouvre porte
    sons[21] = getSound("pics"); // pics contre mur
    sons[22] = getSound("sword"); // Epée
    sons[23] = getSound("SwordCharging"); // chargée
    sons[24] = getSound("Sword360"); // spin
    sons[25] = getSound("shoot"); // flèche
    sons[26] = getSound("hookshot"); // grappin
    sons[27] = getSound("stamp"); // pose bombe
    sons[28] = getSound("magic"); // magie
    sons[29] = getSound("burn"); // brûle
    sons[30] = getSound("hammer"); // marteau
    sons[31] = getSound("plouf"); // plouf
    sons[32] = getSound("danger"); // danger
    sons[33] = getSound("hurt"); // link se blesse
    sons[34] = getSound("porte"); // porte objet
    sons[35] = getSound("lance"); // lance objet
    sons[36] = getSound("casse"); // casse objet
    sons[37] = getSound("charge"); // charge magie
    sons[38] = getSound("buisson"); // coupe buisson
    sons[39] = getSound("pousse"); // pousse caisse
}

void Audio::freeSounds() {
    if (SOUND) {
        for (int i = 0; i < 40; i++) Mix_FreeChunk(sons[i]);
        delete[] sons;
    }
}

void Audio::freeMusic() {
    Mix_FreeMusic(music);
#ifdef __vita__
    if (mem != NULL) {
        free(mem);
        mem = NULL;
    }
    if (f != NULL) {
        fclose(f);
        f = NULL;
    }
#endif
}

Mix_Chunk* Audio::getSound(const char* son) {
    char fSon[512];
#ifdef __vita__
    snprintf(fSon, sizeof(fSon), "%s/%s.ogg", "app0:data/sound", son);
#else
    snprintf(fSon, sizeof(fSon), "%s/%s.ogg", "data/sound", son);
#endif
    return Mix_LoadWAV(fSon);
}

Mix_Music* Audio::getMusic(const char* zik) {
    char fZik[512];
#ifdef __vita__
    struct stat info;
    snprintf(fZik, sizeof(fZik), "%s/%s.ogg", "app0:data/music", zik);
    stat(fZik, &info);
    f = fopen(fZik, "rb");
    mem = (char*)malloc(info.st_size);
    fread(mem, 1, info.st_size, f);
    return Mix_LoadMUS_RW(SDL_RWFromMem(mem, info.st_size));
#else
    snprintf(fZik, sizeof(fZik), "%s/%s.ogg", "data/music", zik);
    return Mix_LoadMUS(fZik);
#endif
}

void Audio::playSound(int id, int chl) {
    if (SOUND) Mix_PlayChannel(chl,sons[id],0);
}

void Audio::playMusic(int id) {
    if (SOUND) {
        if (musiqueId != id) {
	    musiqueId = id;            
            if (specialId == 0) {
		Mix_HaltMusic();
		freeMusic();
		music = choixMusique(id);
		Mix_PlayMusic(music,-1);
		specialId = 0;
	    }
        }
    }
}

void Audio::stopMusic() {
    if (SOUND) Mix_HaltMusic();
}

void Audio::replayMusic() {
    if (SOUND) Mix_PlayMusic(music,-1);
}

Mix_Music* Audio::choixMusique(int id) {
    switch (id) {
        case 1 : return getMusic("Foret");
        case 2 : return getMusic("Plaine");
        case 3 : return getMusic("Lac");
        case 4 : return getMusic("Mont");
        case 5 : return getMusic("Desert");
        case 6 : return getMusic("Ombre");
        case 7 : return getMusic("Feu");
        case 8 : return getMusic("Cocorico");
        case 9 : return getMusic("Chateau");
        case 10 : case 11 : return getMusic("Secret");
        case 12 : case 13 : case 14 : return getMusic("Donjon1");
        case 15 : return getMusic("DDesert");
        case 16 : case 17 : case 18 : return getMusic("Donjon2");
        case 19 : return getMusic("DSecret");
        case 20 : return getMusic("DFinal");
        case 21 : return getMusic("Home");
        case 22 : case 23 : return getMusic("Cave");
        case 24 : case 25 : case 26 : case 27 : return getMusic("Fee"); break;
//case 28 : case 32 : case 35 : case 36 : case 38 : case 41 : case 42 : case 43 : case 44 :
//    return getMusic("Maison"); break;
        case 29 : case 37 : case 40 : return getMusic("Potion"); break;
        case 30 : return getMusic("Bar"); break;
        case 31 : return getMusic("Magasin"); break;
        case 33 : case 34 : case 39 : return getMusic("Jeu"); break;
        case 45 : return getMusic("Titre"); break;
        case 46 : return getMusic("Selection"); break;
        case 47 : return getMusic("Debut"); break;
        default : return getMusic("Maison");
    }
}

void Audio::playSpecial(int id) {
    if (SOUND) {
        if (specialId != id) {
            Mix_HaltMusic();
            freeMusic();
            music = choixSpecial(id);
            Mix_PlayMusic(music,-1);
            specialId=id;
        }    
    }
}

void Audio::stopSpecial() {
    if (!specialId) return;
    int tmp = musiqueId;
    musiqueId = 0;
    specialId = 0;
    playMusic(tmp);
}

Mix_Music* Audio::choixSpecial(int id) {
    switch (id) {
        case 1 : return getMusic("Boss");
        case 2 : return getMusic("Mort");
        case 3 : return getMusic("Epee");
        case 4 : return getMusic("BossF");
        case 5 : return getMusic("Fin");
        default : return getMusic("Boss");
    }
}

