/*

    Zelda Return of the Hylian

    Copyright (C) 2005-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/
																
#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <SDL/SDL_mixer.h>

class Audio {
    public :
        Audio();
        ~Audio();
        void playSound(int id, int chl = -1);
        void playMusic(int id);
        void stopMusic();
        void replayMusic();
        void playSpecial(int id);
        void stopSpecial();
        void setVolume(int volume);
        void setVolson(int volson);
    private :
        void loadSounds();
        void freeSounds();
        void freeMusic();
        Mix_Chunk* getSound(const char *son);
        Mix_Music* getMusic(const char *zik);
        Mix_Music* choixMusique(int id);
        Mix_Music* choixSpecial(int id);
        
        bool SOUND;
        int previous_volume;
        int musiqueId;
        int specialId;
#ifdef __vita__
        char* mem;
        FILE* f;
#endif
        Mix_Chunk** sons;
        Mix_Music* music;

};

#endif  // Audio.h
