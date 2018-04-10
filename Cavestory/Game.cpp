#include "Game.h"
#include "Graphics.h"
#include "Input.h"
#include "easylogging++.h"

#include <SDL.h>



namespace {
	constexpr int FPS = 50;
	constexpr int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->GameLoop();
}

Game::~Game()
{
}

void Game::GameLoop()
{
	Graphics graphics;
	Input input;
	SDL_Event event;

	int LastUpdateTime = SDL_GetTicks();

	while (true) {
		input.BeginNewFrame();

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_KEYDOWN) {
				// Check if the key is not held down
				if (event.key.repeat == 0) {
					input.KeyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.KeyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				LOG(INFO) << "EXITING: " << event.type;
				return;
			}
		}
		if (input.WasKeyPressed(SDL_SCANCODE_ESCAPE)) {
			LOG(INFO) << "ESCAPE KEY. EXITING";
			return;
		}
	}

	const int CURRENT_TIME_MS = SDL_GetTicks();
	int DeltaTime = CURRENT_TIME_MS - LastUpdateTime;
	this->Update(std::min<int>(DeltaTime, MAX_FRAME_TIME));
	LastUpdateTime = CURRENT_TIME_MS;
}

void Game::Draw(Graphics & graphics)
{
}

void Game::Update(float DeltaTime)
{
}