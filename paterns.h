#pragma once
#include "nuclear.cpp"

auto addr = FindPattern(E("40 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4C 89 45 DF F3 0F 10 4D ?"));
auto ss = FindPattern(E("E8 ? ? ? ? 48 8B 8C 24 ? ? ? ? 0F 28 00"));
auto ss2 = FindPattern(E("E8 ? ? ? ? 4C 8B 8D ? ? ? ? 48 8D 4D F0"));
auto ss3 = FindPattern(E("48 8B 0D ? ? ? ? 45 0F B6 C6 F2 0F 10 0D ? ? ? ? 66 0F5A C9 48 8B 11 FF 92 ? ? ? ? "));
auto callSite = FindPattern(E("48 8B 0D ? ? ? ? 4C 8B CF 44 8B C6 48 89 5C 24 20 48 8B D5 E8 ? ? ? ?"));
auto gettracevisibilityfn = FindPattern(E("48 8B C4 48 89 58 20 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 0F 29 70 B8 0F 29 78 A8 44 0F 29 40 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 20 45 8A E9"));
auto pUWorldRefFunc = FindPattern(E("48 89 05 ? ? ? ? 48 8B 8B ? ? ? ?"));
