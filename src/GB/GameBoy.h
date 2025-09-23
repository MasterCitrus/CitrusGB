#pragma once

#include "GBDefinitions.h"

#include <memory>
#include <string>

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
	Cartridge* GetCart() const { return cart.get(); }
	GPU* GetGPU() const { return gpu.get(); }
	APU* GetAPU() const { return apu.get(); }

	void Init();
	void Update();

	void LoadROM(const std::string& rom);
	void EjectROM();
	void Reset();

	int GetCycles() const { return cycles; }

private:
	int cycles = 0;
	std::unique_ptr<CPU> cpu;
	std::unique_ptr<Memory> memory;
	std::unique_ptr<Cartridge> cart;
	std::unique_ptr<GPU> gpu;
	std::unique_ptr<APU> apu;
	bool running = false;
};