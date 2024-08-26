
#include <stdio.h>
#include <SDL.h>

/*  RENDERING
    //I should probably rely on renderer method to paint
    the screen. Reason being, it is supposed to be faster and
    is also doing the scaling better.(idk why).
    1. Initialize SDL.
    2. Create window. Get backbuffer or client area.
    3. Get a renderer for the window.
    4. Create a texture. (here, we created texture from surface)
    5. Render a color onto the backbuffer => Clear backbuffer.
    6. Render your texture to backbuffer.
    7. Update window. (Actually paint screen.) Render"Present".

    - ya to ek window ki drawing surface ko SDL_Surface me le sakte ho, ya to exactly correspondingly
    renderer le sakte ho uss window ke liye. Dono nahi kar sakte. (Which means, actual screen painting ke time
    hardware-based rendering or software rendering me se ek cheez choose karni hi padegi).
    - Texture creation and preparation ke liye tum surfaces and software blitting bhi use kar sakte ho. But, almost
    harcheez ka Rendering-based alternative hai hi, if you look for it.

*/






















SDL_Rect scalinglogic(SDL_Texture* texture, SDL_Window* window)
{
    SDL_Rect screen = { };
    SDL_GetWindowSize(window,&screen.w,&screen.h);
    SDL_GetWindowPosition(window,&screen.x,&screen.y);
    int hh = 0, ww = 0;
    SDL_QueryTexture(texture,NULL,NULL,&ww,&hh);

    int height = screen.h;
    int ration = hh/height;
    int width = ww/ration;
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
        printf("Init failed \n");
        printf("Error: %s\n",SDL_GetError());
        return init;
    }

    SDL_Window* window = SDL_CreateWindow("Renderers",10,10,640,480,SDL_WINDOW_SHOWN);
    if(window == NULL){
        printf("Couldn't create window\n");
        printf("Error:%s\n", SDL_GetError());
        return 0;
    }

    /*SDL_Surface* backbuffer = SDL_GetWindowSurface(window);
    if(backbuffer == NULL){
        printf("Backbuffer could not be obtained\n");
        return 0;
    }*/

    //load image into a surface. Then make a texture from the surface.
    const char* path = "C:\\Users\\Sushi\\Downloads\\IMG20230227171319.bmp";
    SDL_Surface * image = SDL_LoadBMP(path);
    if(image == NULL){
        printf("Could not load image\n");
        printf("Error:%s\n", SDL_GetError());
        return 0;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,
                                            SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        printf("rendering context not made\n");
        printf("Error:%s\n", SDL_GetError());
        return 0;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,image);
    if(texture == NULL){
        printf("creating texture from surface failed\n");
        printf("Error:%s\n", SDL_GetError());
        return 0;
    }

    SDL_FreeSurface(image);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

    bool quit = false;
    SDL_Event event = { };
    while(quit != true){
        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT){
            quit = true;
        }
        SDL_RenderClear(renderer);
        SDL_Rect todraw = scalinglogic(texture,window);
        SDL_RenderCopy(renderer,texture,NULL,&todraw);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}

