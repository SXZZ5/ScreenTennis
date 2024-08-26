/*#include <SDL.h>
#include <stdio.h>

SDL_Rect scalinglogic(SDL_Surface* surface)
{
    SDL_Rect screen;
    SDL_GetDisplayBounds(0,&screen);

    //SDL_Rect image = {10,0,surface->h,surface->w};

    int height = screen.h;
    int ration = surface->h/height;
    int width = (surface->w) / ration;
    printf("height: %d\n", height);
    printf("ration: %d\n", ration);
    printf("width: %d\n", width);

    SDL_Rect drawto = {10,0,width,height};
    return drawto;

}
int main(int argc, char* argv[])
{
    int init = SDL_Init(SDL_INIT_EVERYTHING);
    if(init < 0){
        printf("Failed to initialise SDL \n");
        printf("Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window* window = SDL_CreateWindow("MISS U",
                                          50,50,640,480,
                                          SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(window == NULL){
        printf("Window not created \n");
        printf("Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Surface* frontbuffer = SDL_GetWindowSurface(window);
    if(frontbuffer == NULL){
        printf("Couldn't get front buffer\n");
        printf("Error: %s\n", SDL_GetError());
        return 0;
    }

    const char * path = "C:\\Users\\Sushi\\Downloads\\IMG20230227171319.bmp";
    SDL_Surface* image1 = SDL_LoadBMP(path);
    if(image1 == NULL){
        printf("Failed to load image \n");
        printf("Error: %s\n", SDL_GetError());
    }

    const char* path2 = "C:\\Users\\Sushi\\Downloads\\photo.bmp";
    SDL_Surface* image2 = SDL_LoadBMP(path2);
    if(image2 == NULL){
        printf("failed to load the second image");
        printf("Error:%s\n", SDL_GetError());
    }


    SDL_Event event;
    bool quit = false;
    int flag = 1;
    while(quit == false){
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT: quit = true;
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                if (flag == 1){
                    SDL_Rect drawto = scalinglogic(image1);
                    SDL_BlitScaled(image1,NULL,frontbuffer,&drawto);
                    SDL_UpdateWindowSurface(window);
                    flag = 2;
                }
                else{
                    SDL_Rect drawto = scalinglogic(image2);
                    SDL_BlitScaled(image2,NULL,frontbuffer,&drawto);
                    SDL_UpdateWindowSurface(window);
                    flag = 1;
                }
                break;
            }

        }
    }

    SDL_FreeSurface(image1); SDL_FreeSurface(image2);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;

}
*/

