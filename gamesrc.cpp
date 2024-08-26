#include <stdio.h>
#include <SDL.h>


//This file has set scene for the game.
//Shooter platform has been setup at the bottom of the screen and a target has been set (for now at the center).
//Ab motion and sprites wagerah seekhne honge.


//thodi der ke liye, window ko not-resizable kar deta hoon. Taaki motion fixed plane me draw karu.

const char* guide = "1. Left white bar is for player 1, right white bar is for player 2.\n 2. For Player 1: Move UP: Press \"W\" key. Move DOWN: Press \"S\" key.\n 3. For Player 2: Move UP: Press \"UP-Arrow\" key, Move DOWN: Press \"DOWN-Arrow\" key.\n 4. The game begins when \"ENTER\" key is pressed. \n 5. The ball moves to the right at the start of the game.\n 6. The task for each player is to not let the ball cross their corresponding bars.\n 7. If the game feels too slow, press \"G\" to increase speeds. \n 8. Speed cannot be increased more than 10 times.\n 9. Press \"F\" to decrease speeds. \n 10. Prefer to choose speed before starting the game \n";

int G = 1;

void showSplashScreen(SDL_Renderer* rencontext, SDL_Window* window){
    const char * path = "EA.bmp";
    SDL_Surface* image = SDL_LoadBMP(path);
    if(image == NULL){
        printf("Could not load splash screen\n");
        printf("Error:%s\n", SDL_GetError());
    }

    SDL_Texture* splash = SDL_CreateTextureFromSurface(rencontext, image);
    SDL_FreeSurface(image);

    SDL_RenderClear(rencontext);
    SDL_RenderCopy(rencontext,splash,NULL,NULL);
    SDL_RenderPresent(rencontext);
    SDL_DestroyTexture(splash);

    SDL_Delay(1500);

    SDL_RenderClear(rencontext);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"GAME GUIDE", guide,window);
/*
    const char* path2 = "splash2.bmp";
    SDL_Surface* image2= SDL_LoadBMP(path2);
    SDL_Texture* splash2 = SDL_CreateTextureFromSurface(rencontext,image2);
    SDL_FreeSurface(image2);

    SDL_RenderClear(rencontext);
    SDL_RenderCopy(rencontext,splash2,NULL,NULL);
    SDL_RenderPresent(rencontext);
    SDL_DestroyTexture(splash2);

    SDL_Delay(100); */


    return;
}

const int a = 20;
SDL_Rect screen = { };
struct Motion{
    int velx = 0;
    int vely = 0;

    int dirx = 0;
    int diry = 0;
};

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
    SDL_Quit();
}

SDL_Window* openwindow(){
    SDL_Window* window = NULL;
    window = SDL_CreateWindow("GAME",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,700,600,SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
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

void createShooter1Rect(SDL_Rect* rectangle, SDL_Window* window){
    rectangle->w = 0.5*a;
    rectangle->h = 5*a;

    int height = 0, width = 0;
    SDL_GL_GetDrawableSize(window,&width,&height);

    rectangle->y = 0.5*(height - rectangle->h);
    rectangle->x = 0.25*width - rectangle->w;

    printf("SHOOTER RECTANGLE\n");
    printf("x = %d, y = %d \n", rectangle->x, rectangle->y);
    printf("w = %d, h = %d \n", rectangle->w, rectangle->h);

    return;
}

void createShooter2Rect(SDL_Rect* rectangle, SDL_Window* window){
    rectangle->w = 0.5*a;
    rectangle->h = 5*a;

    int height = 0, width = 0;
    SDL_GL_GetDrawableSize(window,&width,&height);

    rectangle->y = 0.5*(height - rectangle->h);
    rectangle->x = 0.75*width - rectangle->w;

    printf("SHOOTER RECTANGLE\n");
    printf("x = %d, y = %d \n", rectangle->x, rectangle->y);
    printf("w = %d, h = %d \n", rectangle->w, rectangle->h);

    return;
}

void createStrikerRect(SDL_Rect* rectangle, SDL_Window* window){
    rectangle->w = 12;
    rectangle->h = 12;

    int height = 0, width = 0;
    SDL_GL_GetDrawableSize(window,&width,&height);
    int posx = 0, posy = 0;
    SDL_GetWindowPosition(window,&posx, &posy);
    rectangle->y = (0.5*height) - 6;
    rectangle->x = (0.5*width) - 6;

    printf("Window Size: height = %d, width = %d \n",height,width);
    printf("Window Position: posx = %d, posy = %d \n",posx,posy);

    printf("TARGET RECTANGLE\n");
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

void moveObj(SDL_Rect* striker, SDL_Window* window, Motion* strikerMotion){
    //generic Object moving logic hai. Striker to bas naam hai.
    //Actually repurposing code. Don't want to replace names itna.
    int& dirStrikerX = strikerMotion->dirx;
    int& dirStrikerY = strikerMotion->diry;

    striker->x += dirStrikerX*strikerMotion->velx;
    striker->y += dirStrikerY*strikerMotion->vely;

    SDL_Rect limits = { };
    SDL_GetWindowSize(window,&limits.w,&limits.h);

    if((striker->x + striker->w) > limits.w){
        printf("striker collided with right edge of window\n");
        dirStrikerX = -1;
        striker->x += strikerMotion->velx*dirStrikerX;
    }
    else if((striker->x) < 0){
        dirStrikerX = 1;
        striker->x += strikerMotion->velx*dirStrikerX;
    }

    if((striker->y) < 0){
        printf("striker collided with left edge of window \n");
        dirStrikerY = 1;
        striker->y += strikerMotion->vely*dirStrikerY;
    }
    else if((striker->y + striker->h) > limits.h){
        dirStrikerY = -1;
        striker->y += strikerMotion->vely*dirStrikerY;
    }
    return;
}

SDL_Texture* loadStriker(SDL_Renderer* rencontext){
    printf("TRYING TO LOAD STRIKER");
    const char* path = "dot.bmp";
    SDL_Surface* tmpsurf = NULL;
    tmpsurf = SDL_LoadBMP(path);
    if(tmpsurf == NULL){
        printf("Could not load striker bmp\n");
        printf("Error:%s\n", SDL_GetError());
        return NULL;
    }

    SDL_Texture* striker = SDL_CreateTextureFromSurface(rencontext,tmpsurf);
    if(striker == NULL){
        printf("failed to create striker texture");
        printf("Error:%s\n",SDL_GetError());
    }
    SDL_FreeSurface(tmpsurf);

    return striker;

}

void detacher(Motion* strikerMotion,Motion* shooterMotion){
    strikerMotion->dirx = shooterMotion->dirx;
    return;
}

bool checkCollision(SDL_Rect* obj1, SDL_Rect* obj2){
    int lefta, righta, topa, bottoma;
    lefta = obj1->x; righta = lefta + obj1->w;
    topa = obj1->y; bottoma = topa + obj1->h;

    int leftb, rightb, topb, bottomb;
    leftb = obj2->x; rightb = leftb + obj2->w;
    topb = obj2->y; bottomb = topb + obj2->h;
    if( bottoma <= topb )
    {
        return false;
    }

    if( topa >= bottomb )
    {
        return false;
    }

    if( righta <= leftb )
    {
        return false;
    }

    if( lefta >= rightb )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;

}

void reflect(Motion* toReflect, Motion* fromReflect){
    if(toReflect->dirx == 1) toReflect->dirx = -1;
    else toReflect->dirx = 1;

    toReflect->diry = fromReflect->diry;
}

int main(int argc, char* argv[])
{
    if(init() == false){
        return 0;
    }


    SDL_GetDisplayUsableBounds(0,&screen);

    SDL_Window* window = openwindow();
    SDL_Renderer* rencontext = openRenderer(window);

    showSplashScreen(rencontext, window);

    //SDL_GetWindowBordersSize(window,&borders.y, &borders.x,&borders.h, &borders.w);


    if(SDL_SetRenderDrawColor(rencontext,242, 92, 222, 255) < 0){
        printf("Error in setting color of renderer");
        printf("Error:%s\n", SDL_GetError());
    }

    SDL_Rect shooter1 = { };
    SDL_Rect shooter2 = { };
    createShooter1Rect(&shooter1, window);
    createShooter2Rect(&shooter2, window);

    loadStriker(rencontext);
    SDL_Rect striker = { };
    SDL_Texture* goti = NULL;
    goti = loadStriker(rencontext);
    if(goti == NULL){
        printf("goti loading failed \n");
        printf("Error:%s\n",SDL_GetError());
    }
    createStrikerRect(&striker, window);


    int ht = 0, wd = 0;
    SDL_GetWindowSize(window,&wd,&ht);
    SDL_Rect left = {0,0,1,ht};
    SDL_Rect right = {wd-1,0,1,ht};

    //initialise striker and shooter motion.
    Motion shooter1Motion = {0,0,1,1};
    Motion strikerMotion = {0,0,1,1};
    Motion shooter2Motion = {0,0,1,1};

    bool quit = false;
    SDL_Event event = { };
    int framecount = 0;
    while(quit == false){
            framecount++;

            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    quit = true;
                    continue;
                }

                if(event.type == SDL_KEYDOWN){
                    //if(event.key.repeat != 0) continue;
                    if(event.key.keysym.sym == SDLK_s){
                        shooter1Motion.diry = +1;
                        shooter1Motion.vely = G;
                    }
                    else if(event.key.keysym.sym == SDLK_w){
                        shooter1Motion.diry = -1;
                        shooter1Motion.vely = G;
                    }
                    else if(event.key.keysym.sym == SDLK_DOWN){
                        shooter2Motion.diry = +1;
                        shooter2Motion.vely = G;
                    }
                    else if(event.key.keysym.sym == SDLK_UP){
                        shooter2Motion.diry = -1;
                        shooter2Motion.vely = G;
                    }
                    else if(event.key.keysym.sym == SDLK_RETURN){
                        strikerMotion.velx = G;
                        strikerMotion.vely = G;
                    }
                    else if(event.key.keysym.sym == SDLK_g || event.key.keysym.sym == SDLK_f) {
                        if(event.key.keysym.sym == SDLK_g){
                            printf("Recieved keypress: G\n");
                            G++;
                            printf("G:%d\n", G);
                            if(G >= 10) G = 10;
                        }
                        if(event.key.keysym.sym == SDLK_f){
                            printf("Received keypress: F \n");
                            G--;
                            printf("G:%d\n",G);
                            if(G == 0) G = 1;
                        }

                        if(strikerMotion.velx != 0) strikerMotion.velx = G;
                        if(strikerMotion.vely != 0) strikerMotion.vely = G;
                        if(shooter2Motion.velx != 0) shooter2Motion.velx = G;
                        if(shooter2Motion.vely != 0) shooter2Motion.vely = G;
                        if(shooter1Motion.velx != 0) shooter1Motion.velx = G;
                        if(shooter1Motion.vely != 0) shooter1Motion.vely = G;
                    }
                }

            }

            if(checkCollision(&striker,&left)){
                printf("detected collision with left edge of window \n");
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"END OF GAME", "Player 2 WON", window);
                quit = true;
                break;
            }
            if(checkCollision(&striker,&right)){
                printf("detected collision with right edge of window \n");
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"END OF GAME", "Player 1 WON", window);
                quit = true;
                break;
            }

            if(framecount < 10000){
                continue;
            }

            SDL_SetRenderDrawColor(rencontext, 255, 158, 228, 255);
            // SDL_SetRenderDrawColor(rencontext, 202, 234, 235, 255);
            SDL_RenderClear(rencontext);

            SDL_Point xa = { }, xb = { }, ya = { }, yb = { };
            createXaxis(window,&xa,&xb);
            createYaxis(window,&ya,&yb);
            SDL_SetRenderDrawColor(rencontext, 181, 255, 33, 255);
            SDL_RenderDrawLine(rencontext, xa.x, xa.y, xb.x, xb.y);
            SDL_RenderDrawLine(rencontext, ya.x, ya.y, yb.x, yb.y);

            SDL_SetRenderDrawColor(rencontext,255,255,255,255);

            moveObj(&shooter1,window,&shooter1Motion);
            moveObj(&shooter2,window,&shooter2Motion);
            moveObj(&striker,window,&strikerMotion);

            if(checkCollision(&striker,&shooter1)){
                reflect(&strikerMotion, &shooter1Motion);
                moveObj(&striker,window,&strikerMotion);
            }
            else if(checkCollision(&striker,&shooter2)){
                reflect(&strikerMotion, &shooter2Motion);
                moveObj(&striker,window,&strikerMotion);
            }

            SDL_RenderFillRect(rencontext,&shooter1);
            SDL_RenderFillRect(rencontext,&shooter2);
            SDL_RenderCopy(rencontext,goti,NULL,&striker);

            SDL_RenderPresent(rencontext);
            framecount = 0;

    }

    SDL_DestroyTexture(goti);
    shutdown(rencontext, window);
    return 1;

}

