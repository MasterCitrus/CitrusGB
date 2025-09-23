#include "GameBoy.h"
#include "APU.h"
#include "Cartridge.h"
#include "CPU.h"
#include "GPU.h"
#include "Memory.h"

GameBoy::GameBoy()
{
	cart = std::make_unique<Cartridge>();
	memory = std::make_unique<Memory>();
	cpu = std::make_unique<CPU>(memory.get());
}

GameBoy::~GameBoy()
{
}

void GameBoy::Init()
{
	memory->SetCart(cart.get());
	memory->LoadBootROM();
}

void GameBoy::Update()
{
	if (running)
	{
		cpu->Step();
		cycles += cpu->GetTCycles();
	}
}

void GameBoy::LoadROM(const std::string& rom)
{
	if (!cart->LoadROM(rom)) return;

	running = true;
}

void GameBoy::EjectROM()
{
	running = false;
	cart->EjectROM();
	Reset();
}

void GameBoy::Reset()
{
	cpu->Reset();
	memory->Reset();
}
