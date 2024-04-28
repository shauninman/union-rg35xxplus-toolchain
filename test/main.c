#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/input.h>

void logErrorToFile(const char *msg)
{
    FILE *file = fopen("./error_log.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%s\n", msg);
        fclose(file);
    }
    else
    {
        // If file creation failed, try creating the file
        file = fopen("./error_log.txt", "w");
        if (file != NULL)
        {
            fprintf(file, "%s\n", msg);
            fclose(file);
        }
    }
}

int main(int argc, char *argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        logErrorToFile(SDL_GetError());
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0)
    {
        logErrorToFile(SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow("",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        logErrorToFile(SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        logErrorToFile(SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_RenderSetLogicalSize(renderer, 640, 480);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // Load font
    TTF_Font *font = TTF_OpenFont("./BPreplayBold.ttf", 24);
    if (font == NULL)
    {
        logErrorToFile(SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Create surface and texture for text
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Hello, world!", textColor);
    if (surface == NULL)
    {
        logErrorToFile(SDL_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        logErrorToFile(SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Clear the window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render text
    SDL_Rect dstrect = {10, 10, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    // Update the window
    SDL_RenderPresent(renderer);

    SDL_Event event;
    int quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                quit = 1;
            }
        }
    }

    // Clean up
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
