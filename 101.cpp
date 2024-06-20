#include<iostream>
#include<SDL2/SDL.h>
#include"constant.h"


#undef main

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

float radius = 110;
float px = WIDTH/2;
float py = HEIGHT/2;
 
int program_is_running =0;

using namespace std;

void DrawFilledCircle(SDL_Renderer *renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}


int initialize_window(){
    if(SDL_Init(SDL_INIT_EVERYTHING)!= 0) {
        fprintf(stderr,"error initializing sdl");
        return 0;
    }

    window = SDL_CreateWindow("yoyo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_BORDERLESS);
    if(!window) {
        fprintf(stderr,"the window had occured an error intializing");
        return 0;
    }

    renderer= SDL_CreateRenderer(window,-1,0);
    if(!renderer){
        fprintf(stderr,"error initializing the renderer");
        return 0;
    }

    return 1;

}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            program_is_running = 0;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
                program_is_running = 0 ;
            break;    
    }
}


void render() {
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,30,50,0,230);
    DrawFilledCircle(renderer,px,py,radius);
    SDL_RenderPresent(renderer);

    
}



void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

int main(int argc,char *argv[]) {
    program_is_running = initialize_window();

    while(program_is_running) {
        process_input();
        render();
    }
    destroy_window();
}