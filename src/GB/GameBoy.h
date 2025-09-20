#pragma once

#include <memory>

class APU;
class Cartridge;
class CPU;
class GPU;
class Memory;

class GameBoy
{
public:
	GameBoy();
	~GameBoy();

	CPU* GetCPU() const { return cpu.get(); }
	Memory* GetMemory() const { return memory.get(); }

private:
	std::unique_ptr<CPU> cpu;
	std::unique_ptr<Memory> memory;
};