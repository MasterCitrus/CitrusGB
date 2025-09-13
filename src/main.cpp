#include <SDL3/SDL.h>
#include "App/Emulator.h"
#include <iostream>

int main()
{
	Emulator emu(AppDetails(800, 600, "Game Boy"));

	ReturnError message = emu.Initialise();

	switch (message)
	{
		case ReturnError::Success:
			emu.Run();
			break;
		case ReturnError::SDL_Init:
			std::cout << "SDL failed to initialise.\n";
			break;
		case ReturnError::SDL_Window:
			std::cout << "SDL window could not be created.\n";
			break;
		case ReturnError::SDL_Renderer:
			std::cout << "SDL renderer could not be created.\n";
			break;
	}
}