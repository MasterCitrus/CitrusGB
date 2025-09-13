#pragma once

#include "Entry.h"

#include <vector>

class Log
{
public:

	void Draw();

	void Add(Entry entry);
private:
	std::vector<Entry> entries;
};