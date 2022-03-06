#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

void init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur d'initialisation de la SDL : %s\n" ,SDL_GetError()); 
        exit(EXIT_FAILURE);
    }
}

void clear(SDL_Renderer *r)
{
    if(SDL_SetRenderDrawColor(r ,30 ,80 ,30 ,255) != 0)
    {
        printf("Erreur creation rendu : %s\n" ,SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_RenderClear(r);
}

void quit(SDL_Window *w, SDL_Renderer *r)
{
    // SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit(); 
}