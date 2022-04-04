#pragma once
#include<crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#define CRTDBG_MAP_ALLOC
#endif
#endif // _DEBUG