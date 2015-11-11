/*===========================================
        - Template Code -
============================================*/
#include <grrlib.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <asndlib.h>
//#include <mp3player.h>

// Image
#include "foreground.h"
// Sound
#include "sound_16bit_mono_44100_raw.h"
#include "music_raw.h"
// Music
//#include "music_mp3.h"

int main(int argc, char **argv) {
    u32 wpaddown, paddown;
    u32 color = 0x00000000;

    GRRLIB_Init();
    WPAD_Init();
    PAD_Init();
//    MP3Player_Init();
//    MP3Player_Volume(100);
    ASND_Init();
    ASND_Pause(0);

    // Load image
    GRRLIB_texImg *ForeGroundTex = GRRLIB_LoadTexture(foreground);
    f32 posx = rmode->fbWidth/2 - ForeGroundTex->w/2;
    f32 posy = rmode->efbHeight/2- ForeGroundTex->h/2;
    f32 scale = 1;

    srand(time(NULL));

    ASND_SetInfiniteVoice(0, VOICE_MONO_16BIT, 44100, 0,
        (void *)music_raw, music_raw_size, 155, 155);

    while(1) {
        WPAD_ScanPads();
        PAD_ScanPads();
        wpaddown = WPAD_ButtonsDown(0);
        paddown = PAD_ButtonsDown(0);
        GRRLIB_FillScreen(color);

        GRRLIB_DrawImg(posx, posy, ForeGroundTex, 0, scale, scale, 0xFFFFFFFF);

        GRRLIB_Render();

        if(wpaddown & WPAD_BUTTON_HOME) {
            exit(0);
        }
        else if(wpaddown || paddown) {
            ASND_SetVoice(1, VOICE_MONO_16BIT, 44100, 0,
                (void *)sound_16bit_mono_44100_raw, sound_16bit_mono_44100_raw_size, 155, 155, NULL);
            color = (rand() & 0xFFFFFF) <<8 | 0xFF;
            scale = (0.7 * ((float)rand() / RAND_MAX)) + 0.7;
            posx = ((rmode->fbWidth  - (ForeGroundTex->w * scale)) * (float)rand() / RAND_MAX);
            posy = ((rmode->efbHeight- (ForeGroundTex->h * scale)) * (float)rand() / RAND_MAX);
        }

        /*if(!MP3Player_IsPlaying()) {
            MP3Player_PlayBuffer(music_mp3, music_mp3_size, NULL);
        }*/
    }
//    MP3Player_Stop();
    ASND_Pause(1);
    ASND_End();
    GRRLIB_Exit();
    GRRLIB_FreeTexture(ForeGroundTex);
    return 0;
}
