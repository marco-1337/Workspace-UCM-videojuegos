#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

using uint = unsigned int;

void firstTest()
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	constexpr uint winWidth = 800;
	constexpr uint winHeight = 600;

	constexpr int FRAME_RATE = 50;
	constexpr int ANIMATION_UPDATE_RATE = 100;
	constexpr int SPEED = 10;

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Texture* textureBG;
	string filename = "..\\images\\background1.png";
	SDL_Surface* surface = IMG_Load(filename.c_str());
	textureBG = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Texture* textureDog;
    filename = "..\\images\\dog.png";
	surface = IMG_Load(filename.c_str());
	textureDog = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	SDL_Rect destRect;

	destRect.w = destRect.h = 100;
	destRect.x = 0;
	destRect.y = winHeight - winHeight/4; 

	SDL_Rect srcRect;

	// Para saber cuanto mide la textura en total del perro y poder dividir frames
	int dogTextW, dogTextH;
	SDL_QueryTexture(textureDog, nullptr, nullptr, &dogTextW, &dogTextH);

	srcRect.w = dogTextW / 6;
	srcRect.h = dogTextH / 1;
	srcRect.x = srcRect.y = 0; 

	SDL_Event event;
	bool exit = false;

	uint32_t startTime, frameTime;
	uint32_t animStartTime, animTime;
	startTime = animStartTime = SDL_GetTicks();

	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else 
	{
		while (!exit) 
		{
			while (SDL_PollEvent(&event) && !exit) 
			{
				if (event.type == SDL_QUIT)
					exit = true;
			}

			frameTime = SDL_GetTicks() - startTime;
			animTime = SDL_GetTicks() - animStartTime;

			if (frameTime >= FRAME_RATE) 
			{
				if (destRect.x + SPEED > (int)winWidth)
				{
					destRect.x = ((destRect.x + SPEED) - destRect.w) - winWidth;
				}
				else
					destRect.x += SPEED;

				startTime = SDL_GetTicks();
			}

			if (animTime >= ANIMATION_UPDATE_RATE) 
			{
				if (srcRect.x/(dogTextW / 6) == 5)
				{
					srcRect.x = 0;
				}
				else
					srcRect.x += dogTextW / 6;

				animStartTime = SDL_GetTicks();
			}

			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, textureBG, nullptr, nullptr);
			SDL_RenderCopy(renderer, textureDog, &srcRect, &destRect);

			SDL_RenderPresent(renderer);
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	firstTest();
	return 0;
}
