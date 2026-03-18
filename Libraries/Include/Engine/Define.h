#pragma once

#pragma warning(disable : 4244 4267 4819 4838 4996)

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define New DBG_NEW
#endif
#endif