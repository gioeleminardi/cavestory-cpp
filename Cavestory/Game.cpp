#include "Game.h"
#include "Graphics.h"
#include "Input.h"
#include "easylogging++.h"
#include <SDL.h>

namespace {
	constexpr int FPS = 50;
	constexpr int MAX_FRAME_TIME = 1000 / FPS; //Each Frame must stay for a max of this time period (50fps = 20ms)
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

	this->_player = Player(graphics, 100, 100);
	this->_level = Level("Map1", Vector2(100, 100), graphics);

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
		if (input.IsKeyHeld(SDL_SCANCODE_LEFT)) {
			this->_player.MoveLeft();
		}
		else if (input.IsKeyHeld(SDL_SCANCODE_RIGHT)) {
			this->_player.MoveRight();
		}

		if (!input.IsKeyHeld(SDL_SCANCODE_LEFT) && !input.IsKeyHeld(SDL_SCANCODE_RIGHT)) {
			this->_player.StopMoving();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int DeltaTime = CURRENT_TIME_MS - LastUpdateTime;
		this->Update(static_cast<float>(std::min<int>(DeltaTime, MAX_FRAME_TIME)));
		LastUpdateTime = CURRENT_TIME_MS;
		this->Draw(graphics);
	}
}

void Game::Draw(Graphics & graphics)
{
	graphics.Clear();
	this->_level.Draw(graphics);
	this->_player.Draw(graphics);
	graphics.Flip();
}

void Game::Update(float DeltaTime)
{
	//LOG(INFO) << "DeltaTime: " << DeltaTime;
	this->_player.Update(DeltaTime);
	this->_level.Update(DeltaTime);
}
