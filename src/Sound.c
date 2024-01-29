#include "Sound.h"
Music music_intro;
Music music_main;
Music music_gameover;
void InitializeAudioSystem(){
    InitAudioDevice();
    music_intro = LoadMusicStream("resources/title.mp3");
    music_main = LoadMusicStream("resources/main.mp3");
    music_gameover = LoadMusicStream("resources/gameover.mp3");
}
void PlayMusic(Music music){
    PlayMusicStream(music);
}
void LoopMusic(Music music){
    UpdateMusicStream(music);
    float timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);
    if(timePlayed > 1.0f){
        StopMusicStream(music);
        PlayMusicStream(music);
    }
}

void UnloadAudioSystem(){
    UnloadMusicStream(music_intro);
    UnloadMusicStream(music_main);
    UnloadMusicStream(music_gameover);
    CloseAudioDevice();
}