#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <math.h>

const unsigned int ScreenWidth = 1080;
const unsigned int ScreenHeight = 720;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event e;

bool isRunning = true;

void Setup()
{
	// Initialize SDL API // 
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialize SDL, Error: " << SDL_GetError() << std::endl;
	}

	if (SDL_CreateWindowAndRenderer(ScreenWidth, ScreenHeight, 0, &window, &renderer) < 0)
	{
		std::cout << "Failed to create window and renderer, Error: " << SDL_GetError() << std::endl;
	}

	SDL_SetWindowTitle(window, "BYTE");
}

void Update()
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			isRunning = false;
		}
	}
}

void Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect rect;
	rect.x = ScreenWidth / 2 - 100;
	rect.y = ScreenHeight / 2 - 100;
	rect.w = 200;
	rect.h = 200;

	SDL_SetRenderDrawColor(renderer, 40, 255, 40, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[])
{
	Setup();

	while (isRunning)
	{
		Update();
		Render();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}