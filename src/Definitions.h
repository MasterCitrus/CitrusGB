#pragma once

// Unsigned Bytes
typedef unsigned char u8;
typedef unsigned short u16;

// Signed bytes
typedef char s8;
typedef short s16;

#define UNCOPYABLE(ClassName)			\
	ClassName(const ClassName&) = delete; \
	ClassName& operator=(const ClassName&) = delete;

#define UNMOVEABLE(ClassName) \
	ClassName(ClassName&&) = delete; \
	ClassName& operator=(ClassName&&) = delete;