#include<iostream>
#include<SDL2/SDL.h>
#include<cmath>
#include "constant.h"

typedef struct Circle {
    float x;
    float y;
    float radius;
} Circle;

#undef main
int game_is_running =False;
SDL_Window * window = NULL;
SDL_Renderer* renderer = NULL;
int last_frame_time = 0;



using namespace std;

void DrawFilledCircle(SDL_Renderer *renderer, Circle &c1,SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < c1.radius * 2; w++) {
        for (int h = 0; h < c1.radius * 2; h++) {
            int dx = c1.radius - w; 
            int dy = c1.radius - h; 
            if ((dx*dx + dy*dy) <= (c1.radius * c1.radius)) {
                SDL_RenderDrawPoint(renderer, c1.x + dx, c1.y + dy);
            }
        }
    }
}




void onCollision(SDL_Renderer* renderer, Circle& c1, Circle& c2) {
    
    DrawFilledCircle(renderer, c1, SDL_Color{255, 0, 0, 255});
    DrawFilledCircle(renderer, c2, SDL_Color{255, 0, 0, 255});

    SDL_RenderPresent(renderer);
    
     
    SDL_Delay(30);

    DrawFilledCircle(renderer, c1, SDL_Color{30, 50, 0, 255}); 
    DrawFilledCircle(renderer, c2, SDL_Color{128,0,32,255}); 

    SDL_RenderPresent(renderer);
}


int initialize_window() {
   if ( SDL_Init(SDL_INIT_EVERYTHING) != 0) {
         fprintf(stderr,"ERror initializing sdl \n") ;
         return False;
    }

    window = SDL_CreateWindow("this is me", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED ,WIDTH,HEIGHT,SDL_WINDOW_BORDERLESS);
    if(!window) {
        fprintf(stderr,"ERROR initializing window..\n");
        return False;
    }

    renderer=SDL_CreateRenderer(window,-1,0);
    if(!renderer) {
        fprintf(stderr,"error creating sdl renderer \n");
        return False;
    }
    return True;

}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


bool checkCollision(Circle& c1,Circle& c2) {
    float dx = c1.x - c2.x;
    float dy = c1.y - c2.y;
    float distance = sqrt(dx * dx + dy * dy);


    if (distance <= (c1.radius + c2.radius)) {
        return true; 
    }
    return false;
}





int main(int argc,char *argv[]) {
    game_is_running = initialize_window();
    Circle c_circle{WIDTH/2,HEIGHT/2,60} ;
    Circle m_circle{0,HEIGHT/2,90};

    
    while(game_is_running) {
        
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        

        if(checkCollision(c_circle,m_circle)){
            onCollision(renderer,m_circle,c_circle);
            
        }
        else  {
    
            DrawFilledCircle(renderer,m_circle,SDL_Color{30,50,0,230});
            DrawFilledCircle(renderer,c_circle,SDL_Color{128,0,32,255});
           
        }    

       
        SDL_RenderPresent(renderer);

       

        int time_to_wait = Frame_Target_Time-(SDL_GetTicks()-last_frame_time);
        if(time_to_wait>0 && time_to_wait<=Frame_Target_Time) {
            SDL_Delay(time_to_wait);
        }
    
        float delta_time =(SDL_GetTicks()-last_frame_time)/1000.0f;

        last_frame_time= SDL_GetTicks();

        if(m_circle.x > WIDTH + m_circle.radius ) m_circle.x = - m_circle.radius;

        else
        m_circle.x += (160*delta_time);
        

        SDL_Event event;
        SDL_PollEvent(&event);

        switch(event.type) {

            case SDL_KEYDOWN:

                if(event.key.keysym.sym == SDLK_DOWN){

                    if(c_circle.y>=HEIGHT+c_circle.radius-5) c_circle.y= 5- c_circle.radius;
                    else
                    c_circle.y+= 10; 
                    break;  

                }     

                if(event.key.keysym.sym == SDLK_LEFT){ 

                    if(c_circle.x <= 5 - c_circle.radius) c_circle.x = WIDTH+ c_circle.radius - 5;
                    else
                    c_circle.x-= 10;
                    break;

                }      

                if(event.key.keysym.sym == SDLK_RIGHT){

                    if(c_circle.x >= WIDTH + c_circle.radius - 5) c_circle.x = 5- c_circle.radius;
                    else
                    c_circle.x += 10; 
                    break;  

                }

                if(event.key.keysym.sym == SDLK_UP){

                    if(c_circle.y <= 5- c_circle.radius) c_circle.y= HEIGHT+ c_circle.radius -5;
                    else
                    c_circle.y -= 10;   
                    break; 

                }
                
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    game_is_running = False;

                break;



            case SDL_QUIT:

                game_is_running = False;
                break;


        }
       
    } 
    destroy_window();
}