#include "GPU.h"

void GPU::Step(int cycles)
{
	dots += cycles * 4;

	if (dots < 80)
	{
		mode = GPUMode::OAM;
	}
	else if (dots == 80)
	{

	}
}
