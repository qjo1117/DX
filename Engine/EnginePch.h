#pragma once

#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")



#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <memory>
#include <atomic>
#include <mutex>
#include <queue>
#include <stack>
#include <unordered_map>
#include <set>
#include <array>
#include <functional>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

#include "Macro.h"
#include "type.h"


using namespace std;

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;
using Vec4 = D3DXVECTOR4;
using Matrix = D3DXMATRIXA16;
using Color = D3DXCOLOR;

template<typename T>
using Ref = shared_ptr<T>;

template<typename T>
using WRef = weak_ptr<T>;

#include "Utils.h"