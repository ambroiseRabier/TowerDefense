// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// Tower Defense
// to know: this file is for precompiled header
// to know: (include in every cpp file!): https://stackoverflow.com/questions/5234311/include-stdafx-h-in-header-or-source-file
// to know: http://www.acodersjourney.com/2016/05/top-10-c-header-file-mistakes-and-how-to-fix-them/
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdio>
#include <string>
#include <cassert>
#include <ctime>
#include <memory>
#include <list>
#include <utility>
#include <map>
#include <array>
#include <unordered_map>
#include <corecrt_math_defines.h>

// json lib
#include <nlohmann/json.hpp>
// for convenience
using json = nlohmann::json;
// to load file for json.
#include <fstream>

// or 
//#define _USE_MATH_DEFINES
//#include <math.h>
// ?
// I think cmath is already included inside std no ?
// or constexpr double pi() { return std::atan(1)*4; }
// https://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c#1727896

// to help find memory leaks: https://msdn.microsoft.com/en-us/library/x98tx3cf(v=VS.100).aspx
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// https://msdn.microsoft.com/en-us/library/x98tx3cf(v=vs.140).aspx
#ifdef _DEBUG
    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
    // allocations to be of _CLIENT_BLOCK type
#else
    #define DBG_NEW new
#endif




// TODO: reference additional headers your program requires here
