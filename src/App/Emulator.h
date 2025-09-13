#pragma once

#include "Log/Log.h"

#include <SDL3/SDL_dialog.h>

#include <filesystem>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

enum class ReturnError
{
	Success = 0,
	SDL_Init,
	SDL_Window,
	SDL_Renderer,
};

struct AppDetails
{
	unsigned int width;
	unsigned int height;
	std::string title;
};

class Emulator
{
public:
	Emulator(AppDetails details);

	ReturnError Initialise();
	void Deinitialise();

	void Run();

	void Update(float deltaTime);

private:

	void MakeDirectories();

	void LoadROMFile();

private:
	AppDetails details;
	Log log;
	std::filesystem::path directory;;
	std::filesystem::path romdirectory;
	std::filesystem::path bootromdirectory;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	unsigned int fps = 0;
	bool running = false;
};

static void SDLCALL OpenFileCallback(void* userdata, const char* const* filelist, int filter_index);