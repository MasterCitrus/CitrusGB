#include "GameBoy.h"
#include "CPU.h"
#include "Memory.h"

GameBoy::GameBoy()
{
	memory = std::make_unique<Memory>();
	cpu = std::make_unique<CPU>(memory.get());
}

GameBoy::~GameBoy()
{
}
