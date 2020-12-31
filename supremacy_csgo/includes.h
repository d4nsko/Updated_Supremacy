#pragma once

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/
#pragma warning( disable : 4307 ) // '*': integral constant overflow
#pragma warning( disable : 4244 ) // possible loss of data
#pragma warning( disable : 4800 ) // forcing value to bool 'true' or 'false'
#pragma warning( disable : 4838 ) // conversion from '::size_t' to 'int' requires a narrowing conversion
#pragma warning( disable : 26812) // disabling a warning when including a header works normally for most warning
#pragma warning( disable : 26820) // disabling a warning when using const auto instead of &
#pragma warning( disable : 26495) // disabling a warning when non initialized
#pragma warning( disable : 6290) // bit operation
#pragma warning( disable : 26451) // bit operation
#pragma warning( disable : 26498) // con 5
#pragma warning( disable : 6387) // null
#pragma warning( disable : 6011) // null

// You can define _SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING or _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS to acknowledge that you have received this warning.
#define _SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

using ulong_t = unsigned long;

// Variables for temp coords. To make it more simple for understand, just like this
extern int iKills, posX, posY;
// scorepoint
extern int iTotal, iCombo, iYpos, iAlpha, iFly, iOut;
// collect players and bind
extern int iPlayers[64], iLife;
// custom scope
extern bool scopeValue;
// hitmarker, hit value and headshot
extern float iHitDmg; 
extern bool iHit, iHeadshot;
// precache custom models each map
extern bool LoadModel;

// windows / stl includes.
#include <Windows.h>
#include <cstdint>
#include <intrin.h>
#include <xmmintrin.h>
#include <array>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <chrono>
#include <thread>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <deque>
#include <functional>
#include <map>
#include <shlobj.h>
#include <filesystem>
#include <streambuf>

// our custom wrapper.
#include "unique_vector.h"
#include "tinyformat.h"

// other includes.
#include "hash.h"
#include "xorstr.h"
#include "pe.h"
#include "winapir.h"
#include "address.h"
#include "util.h"
#include "modules.h"
#include "pattern.h"
#include "vmt.h"
#include "stack.h"
#include "nt.h"
#include "x86.h"
#include "syscall.h"

// hack includes.
#include "interfaces.h"
#include "sdk.h"
#include "csgo.h"
#include "safe_conditions.h"
#include "penetration.h"
#include "netvars.h"
#include "entoffsets.h"
#include "entity.h"
#include "client.h"
#include "gamerules.h"
#include "hooks.h"
#include "render.h"
#include "pred.h"
#include "lagrecord.h"
#include "visuals.h"
#include "movement.h"
#include "bonesetup.h"
#include "hvh.h"
#include "lagcomp.h"
#include "aimbot.h"
#include "netdata.h"
#include "chams.h"
#include "resolver.h"
#include "grenades.h"
#include "events.h"
#include "shots.h"
#include "watermark.h"
#include "spoofed_cvars.h"
#include "custom_scope.h"
#include "indicators.h"
#include "scorepoint.h"
#include "killstreaks.h"
#include "killstreak_reset.h"
#include "agent_changer.h"
#include "skins.h"

// gui includes.
#include "json.h"
#include "base64.h"
#include "element.h"
#include "checkbox.h"
#include "dropdown.h"
#include "multidropdown.h"
#include "slider.h"
#include "colorpicker.h"
#include "edit.h"
#include "keybind.h"
#include "button.h"
#include "tab.h"
#include "form.h"
#include "gui.h"
#include "notify.h"
#include "callbacks.h"
#include "menu.h"
#include "config.h"

// calc box pos
extern vec3_t iPlayerOrigin, iPlayermins, iPlayermaxs;
extern vec2_t iPlayerbottom, iPlayertop;

extern matrix3x4_t fakelagmatrix[128];