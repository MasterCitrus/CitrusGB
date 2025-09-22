#pragma once

enum class GPUMode
{
	None,
	OAM,
	Drawing,
	HBlank,
	VBlank,
};

class GPU
{
public:

	// Input M-Cycles
	void Step(int cycles);

private:
	int dots = 0;
	GPUMode mode = GPUMode::None;
};