#include "Emulator.h"
#include "GB/CPU.h"
#include "GB/Memory.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_properties.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <chrono>
#include <iostream>

Emulator::Emulator(AppDetails details)
	: details(details)
{
	MakeDirectories();
}

ReturnError Emulator::Initialise()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        return ReturnError::SDL_Init;
    }

	window = SDL_CreateWindow(details.title.c_str(), details.width, details.height, SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		SDL_Quit();
		return ReturnError::SDL_Window;
	}

	renderer = SDL_CreateRenderer(window, nullptr);

	if (!renderer)
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		return ReturnError::SDL_Renderer;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	running = true;
	return ReturnError::Success;
}

void Emulator::Deinitialise()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Emulator::Run()
{
	SDL_Event event;

	std::chrono::time_point<std::chrono::high_resolution_clock> prevTime = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::high_resolution_clock> currTime;

	double deltaTime = 0;
	unsigned int frames = 0;
	double fpsInterval = 0;

	while (running)
	{
		currTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - prevTime);
		prevTime = currTime;

		deltaTime = duration.count() / 1000.0f;

		frames++;
		fpsInterval += deltaTime;
		if (fpsInterval >= 1.0f)
		{
			fps = frames;
			frames = 0;
			fpsInterval = 0;
		}

		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT)
			{
				running = false;
			}
		}

		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
		{
			SDL_Delay(10);
			continue;
		}

		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

		ImGuiID dockspaceID = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), dockspaceFlags);

		static bool firstTime = true;
		if (firstTime)
		{
			firstTime = false;

			ImGui::DockBuilderRemoveNode(dockspaceID);
			ImGui::DockBuilderAddNode(dockspaceID, dockspaceFlags | ImGuiDockNodeFlags_DockSpace);
			ImGui::DockBuilderSetNodeSize(dockspaceID, ImGui::GetWindowSize());

			ImGuiID mainDockspaceID = dockspaceID;
			ImGuiID right = ImGui::DockBuilderSplitNode(mainDockspaceID, ImGuiDir_Right, 0.60f, nullptr, &mainDockspaceID);
			ImGuiID left = ImGui::DockBuilderSplitNode(mainDockspaceID, ImGuiDir_Left, 1.5f, nullptr, &mainDockspaceID);
			ImGuiID leftTop = ImGui::DockBuilderSplitNode(left, ImGuiDir_Up, 1.5f, nullptr, &mainDockspaceID);
			ImGuiID leftBottom = ImGui::DockBuilderSplitNode(left, ImGuiDir_Down, 1.5f, nullptr, &mainDockspaceID);

			ImGui::DockBuilderDockWindow("Viewport", mainDockspaceID);
			ImGui::DockBuilderDockWindow("Memory", right);
			ImGui::DockBuilderDockWindow("CPU State", left);
			ImGui::DockBuilderDockWindow("Disassembly", leftBottom);
			ImGui::DockBuilderFinish(dockspaceID);
		}

		Update((float)deltaTime);

		ImGui::Render();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

		SDL_RenderPresent(renderer);
	}

	Deinitialise();
}

void Emulator::Update(float deltaTime)
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{

			if (ImGui::MenuItem("Open Rom"))
			{
				LoadROMFile();
			}
			if (ImGui::MenuItem("Reset"))
			{

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Options"))
		{

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	//log.Draw();

	// CPU State UI

	ImGui::Begin("CPU State");
	if (ImGui::BeginTable("Registers", 2, ImGuiTableFlags_Borders))
	{
		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("AF: %s", std::format("{:#04X}", gb.GetCPU()->GetAF().GetRegister()).c_str());
		ImGui::TableSetColumnIndex(1);
		ImGui::Text("BC: %s", std::format("{:#04X}", gb.GetCPU()->GetBC().GetRegister()).c_str());

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("DE: %s", std::format("{:#04X}", gb.GetCPU()->GetDE().GetRegister()).c_str());
		ImGui::TableSetColumnIndex(1);
		ImGui::Text("HL: %s", std::format("{:#04X}", gb.GetCPU()->GetHL().GetRegister()).c_str());

		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("SP: %s", std::format("{:#04X}", gb.GetCPU()->GetSP()).c_str());
		ImGui::TableSetColumnIndex(1);
		ImGui::Text("PC: %s", std::format("{:#04X}", gb.GetCPU()->GetPC()).c_str());

		ImGui::EndTable();
	}
	bool zero = gb.GetCPU()->GetZeroFlag();
	ImGui::Text("Z");
	ImGui::SameLine();
	ImGui::Checkbox("##ZeroFlag", &zero);
	ImGui::SameLine();
	bool subtract = gb.GetCPU()->GetSubtractFlag();
	ImGui::Text("S");
	ImGui::SameLine();
	ImGui::Checkbox("##SubtractFlag", &subtract);
	ImGui::SameLine();
	bool halfCarry = gb.GetCPU()->GetHalfCarryFlag();
	ImGui::Text("HC");
	ImGui::SameLine();
	ImGui::Checkbox("##HalfCarryFlag", &halfCarry);
	ImGui::SameLine();
	bool carry = gb.GetCPU()->GetCarryFlag();
	ImGui::Text("HC");
	ImGui::SameLine();
	ImGui::Checkbox("##CarryFlag", &carry);
	ImGui::End();

	ImGui::Begin("Disassembly");
	ImGui::End();

	ImGui::Begin("Memory");
	ImGui::End();

	//ImGui::Begin("Table Area");
	//if (ImGui::BeginTable("Test Table", 2))
	//{
	//	ImGui::TableNextRow();
	//	ImGui::TableSetColumnIndex(0);
	//	ImGui::Text("Test 1");
	//	ImGui::TableSetColumnIndex(1);
	//	ImGui::Text("Test 2");
	//	
	//	ImGui::TableNextRow();
	//	ImGui::TableSetColumnIndex(0);
	//	ImGui::Text("Test 1");
	//	ImGui::TableSetColumnIndex(1);
	//	ImGui::Text("Test 2");

	//	ImGui::TableNextRow();
	//	ImGui::TableSetColumnIndex(0);
	//	ImGui::Text("Test 1");
	//	ImGui::TableSetColumnIndex(1);
	//	ImGui::Text("Test 2");
	//	ImGui::EndTable();
	//}
	//ImGui::End();
}

void Emulator::MakeDirectories()
{
	directory = std::filesystem::current_path();
	romdirectory = directory;
	bootromdirectory = directory;

	romdirectory += "\\roms";
	bootromdirectory += "\\bootroms";

	if (std::filesystem::exists(romdirectory) && std::filesystem::exists(bootromdirectory))
	{
		return;
	}

	std::filesystem::create_directory(romdirectory);
	std::filesystem::create_directory(bootromdirectory);
}

void Emulator::LoadROMFile()
{
	SDL_DialogFileFilter filters[] = {
		{"All ROMs", "gb;gbc"},
		{"GameBoy Rom", "gb"},
		{"GameBoy Colour", "gbc"},
		{"All Files", "*"}
	};

	SDL_PropertiesID props = SDL_CreateProperties();
	SDL_SetPointerProperty(props, SDL_PROP_FILE_DIALOG_FILTERS_POINTER, filters);
	SDL_SetNumberProperty(props, SDL_PROP_FILE_DIALOG_NFILTERS_NUMBER, 4);
	SDL_SetPointerProperty(props, SDL_PROP_FILE_DIALOG_WINDOW_POINTER, window);
	SDL_SetStringProperty(props, SDL_PROP_FILE_DIALOG_LOCATION_STRING, romdirectory.string().c_str());
	SDL_SetBooleanProperty(props, SDL_PROP_FILE_DIALOG_MANY_BOOLEAN, false);
	SDL_SetStringProperty(props, SDL_PROP_FILE_DIALOG_TITLE_STRING, "Open ROM File");
	SDL_SetStringProperty(props, SDL_PROP_FILE_DIALOG_ACCEPT_STRING, "Open");
	SDL_SetStringProperty(props, SDL_PROP_FILE_DIALOG_CANCEL_STRING, "Cancel");
	
	SDL_ShowFileDialogWithProperties(SDL_FILEDIALOG_OPENFILE, OpenFileCallback, nullptr, props);
}

void OpenFileCallback(void* userdata, const char* const* filelist, int filter_index)
{

}
