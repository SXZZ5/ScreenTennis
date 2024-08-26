/*#include <stdio.h>
#include <SDL.h>


//This file has set scene for the game.
//Shooter platform has been setup at the bottom of the screen and a target has been set (for now at the center).
//Ab motion and sprites wagerah seekhne honge.

const int a = 50;
SDL_Rect screen = { };

bool init(){
    bool success = false;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("failed to init sdl\n");
        printf("Error:%s\n", SDL_GetError());
        success = false;
    }
    else {
        success = true;
    }

    return success;
}

void shutdown(SDL_Renderer* renderer, SDL_Window* window){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_Window* openwindow(){
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("Basic Scene for game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,400,400,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if(window == NULL){
        printf("window not opened\n");
        printf("Error:%s\n", SDL_GetError());
    }
    return window;
}

SDL_Renderer* openRenderer(SDL_Window* window){
    SDL_Renderer* rencontext = NULL;
    rencontext = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(rencontext == NULL){
        printf("rendering context not obtained\n");
        printf("Error:%s\n", SDL_GetError());
    }
    return rencontext;
}

void createTargetRect(SDL_Rect* rectangle, SDL_Window* window){
   rectangle->w = a;
   rectangle->h = a;

   int height = 0, width = 0;
   SDL_GL_GetDrawableSize(window,&width,&height);
   int posx = 0, posy = 0;
   SDL_GetWindowPosition(window,&posx, &posy);
   rectangle->y = (0.5*height - 0.5*a);
   rectangle->x = (0.5*width - 0.5*a);

   printf("Window Size: height = %d, width = %d \n",height,width);
   printf("Window Position: posx = %d, posy = %d \n",posx,posy);

   printf("TARGET RECTANGLE\n");
   printf("x = %d, y = %d \n", rectangle->x, rectangle->y);
   printf("w = %d, h = %d \n", rectangle->w, rectangle->h);
}

void createShooterRect(SDL_Rect* rectangle, SDL_Window* window){
    rectangle->w = 4*a;
    rectangle->h = 0.5*a;

    int height = 0, width = 0;
    SDL_GL_GetDrawableSize(window,&width,&height);

    rectangle->y = height - 0.5*a;
    rectangle->x = 0.5*width - 2*a;

   printf("SHOOTER RECTANGLE\n");
   printf("x = %d, y = %d \n", rectangle->x, rectangle->y);
   printf("w = %d, h = %d \n", rectangle->w, rectangle->h);
}

void createXaxis(SDL_Window* window, SDL_Point* xa, SDL_Point* xb){
    int height = 0, width = 0;
    SDL_GetWindowSize(window,&width,&height);

    xa->x = 0; xa->y = height/2;
    xb->x = width; xb->y = height/2;
}

void createYaxis(SDL_Window* window, SDL_Point* ya, SDL_Point* yb){
    int height = 0, width = 0;
    SDL_GetWindowSize(window, &width,&height);

    ya->x = width/2; ya->y = 0;
    yb->x = width/2; yb->y = height;
}

int main(int argc, char* argv[])
{
    if(init() == false){
        return 0;
    }


    SDL_GetDisplayUsableBounds(0,&screen);

    SDL_Window* window = openwindow();
    SDL_Renderer* rencontext = openRenderer(window);

    //SDL_GetWindowBordersSize(window,&borders.y, &borders.x,&borders.h, &borders.w);


    if(SDL_SetRenderDrawColor(rencontext,242, 92, 222, 255) < 0){
        printf("Error in setting color of renderer");
        printf("Error:%s\n", SDL_GetError());
    }

    bool quit = false;
    SDL_Event event = { };

    //if(SDL_RenderClear(rencontext) < 0){
    //        printf("Failed to clear renderer\n");
    //        printf("Error:%s\n", SDL_GetError());
    //}

    while(quit == false){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                quit = true;
            }

                SDL_Rect target = { };
                SDL_Rect shooter = { };

                createTargetRect(&target, window);
                createShooterRect(&shooter,window);

                SDL_SetRenderDrawColor(rencontext,242, 92, 222, 255);
                SDL_RenderClear(rencontext);

                SDL_SetRenderDrawColor(rencontext,108, 142, 245,255);
                SDL_RenderFillRect(rencontext, &target);

                SDL_SetRenderDrawColor(rencontext,255,255,255,255);
                SDL_RenderFillRect(rencontext,&shooter);

                SDL_Point xa = { }, xb = { }, ya = { }, yb = { };
                createXaxis(window,&xa,&xb);
                createYaxis(window,&ya,&yb);

                SDL_SetRenderDrawColor(rencontext, 181, 255, 33, 255);
                SDL_RenderDrawLine(rencontext, xa.x, xa.y, xb.x, xb.y);
                SDL_RenderDrawLine(rencontext, ya.x, ya.y, yb.x, yb.y);

                SDL_RenderPresent(rencontext);

        }

    }

    shutdown(rencontext, window);
    return 1;

}
*/
