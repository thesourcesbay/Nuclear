#include "stdafx.h"
#include <Windows.h>
#include <psapi.h>
#include "xor.h"
#include "Spoof.h"
#include <rpcndr.h>
#include "nig.h"
#include "nuclear.cpp"

void DRAWMENU(int index)
{
	vector<const wchar_t*> pTabs;

	wchar_t strAimbot[7];
	memcpy(strAimbot, E(L"AIMBOT"), 7 * 2);

	wchar_t strVisuals[7];
	memcpy(strVisuals, E(L"VISUALS"), 8 * 2);

	wchar_t strMisc[7];
	memcpy(strMisc, E(L"MISC"), 5 * 2);

	pTabs.push_back(strAimbot);
	pTabs.push_back(strVisuals);
	pTabs.push_back(strMisc);

	auto inp = g_MenuInitialPos + FVector2D({ 20, 35 });

	static char logo_buff[256];
	static wchar_t logo_buff_wide[256];
	sprintf(logo_buff, E("NUCLEAR FORTNITE (Built: %s %s)"), E(__DATE__), E(__TIME__));
	AnsiToWide(logo_buff, logo_buff_wide);
	K2_DrawText(GCanvas, GetFont(), logo_buff_wide, g_MenuInitialPos + FVector2D({ 20, 11 }), FVector2D(1.0f, 1.0f), Colors::Black, 1.0f, FLinearColor(0, 0, 0, 255), FVector2D(), false, false, false, FLinearColor(0, 0, 0, 1.0f));

	auto tabsz = (g_MenuW - 40) / pTabs.size();
	tabsz -= 2;
	FVector2D ip = inp + FVector2D(2, 2);

	auto i = 0;
	for (int fuck = 0; fuck < pTabs.size(); fuck++)
	{
		auto tab = pTabs.at(fuck);


		auto clr2 = Colors::White;
		auto clr = Colors::Black;
		if (g_MenuIndex == i)
		{
			clr = Colors::White;
			clr2 = Colors::Black;
		}

		RegisterButtonControl(ip, tabsz, 22, clr2, i);

		S2(GetFont(), { ip.X + tabsz / 2 - (lstrlenW((LPCWSTR)tab) * 10) / 2, ip.Y + 3 }, clr, (wchar_t*)tab);
		K2_DrawText(GCanvas, GetFont(), tab, { ip.X + tabsz / 2 - (lstrlenW((LPCWSTR)tab) * 10) / 2, ip.Y + 3 }, FVector2D(1.0f, 1.0f), clr, 1.0f, FLinearColor(0, 0, 0, 255), FVector2D(), false, false, false, FLinearColor(0, 0, 0, 1.0f));
		K2_DrawText(GCanvas, GetFont(), logo_buff_wide, g_MenuInitialPos + FVector2D({ 20, 11 }), FVector2D(1.0f, 1.0f), Colors::Black, 1.0f, FLinearColor(0, 0, 0, 255), FVector2D(), false, false, false, FLinearColor(0, 0, 0, 1.0f));

		ip.X += tabsz + 2;
		i++;
	}

	g_Clientarea = inp + FVector2D(0, 35);


	if (index == 0)
	{
		auto loc = g_Clientarea;
		Render_Toggle(loc, E(L"Enable aimbot"), &G::AimbotEnable);
		Render_Toggle(loc, E(L"Building weaks spot aimbot on CAPS_LOCK"), &G::WeakSpotAimbot);
		Render_Toggle(loc, E(L"Disable collision when aimbotting (noclip) (F2 on/off)"), &G::CollisionDisableOnAimbotKey);
		Render_Toggle(loc, E(L"Bodyaim"), &G::Baim);
		Render_Slider(E(L"FOV"), 0, 90, &AimbotFOV, &loc);
		Render_Slider(E(L"Smooth"), 0, 1, &G::Smooth, &loc);
		Render_Slider(E(L"Aimbot key"), 0, 200, &AimbotKey, &loc);
		Render_Slider(E(L"WeakSpot aimbot key"), 0, 200, &WeakSpotAimbotKey, &loc);
		AimbotKey = (float)(int)(AimbotKey);
		WeakSpotAimbotKey = (float)(int)(WeakSpotAimbotKey);
		MenuCheckbox({ 0, 20 * 3 }, E(L"Aim at bots"), &G::AimbotTargetZombies);
	}
	if (index == 1)
	{
		auto loc = g_Clientarea;
		Render_Toggle(loc, E(L"Enable hack"), &G::EnableHack);
		Render_Toggle(loc, E(L"Supply crates / Llamas"), &G::EspSupplyDrops);
		Render_Toggle(loc, E(L"Rifts"), &G::EspRifts);
		Render_Toggle(loc, E(L"Loot / dropped items"), &G::EspLoot);
		Render_Toggle(loc, E(L"Vehicles"), &G::EspVehicles);
		Render_Toggle(loc, E(L"Traps"), &G::EspTraps);
		Render_Toggle(loc, E(L"Chests / ammo (F1)"), &G::Chests);
		Render_Toggle(loc, E(L"Player weapons"), &G::EspWeapon);
		Render_Toggle(loc, E(L"Player name"), &G::EspPlayerName);
		Render_Toggle(loc, E(L"Player skeleton"), &G::Skeletons);
		Render_Toggle(loc, E(L"Player box"), &G::EspBox);
		Render_Toggle(loc, E(L"Draw red snaplines in RED radius"), &G::SnaplinesIn50m);
		Render_Toggle(loc, E(L"Draw snaplines (always)"), &G::Snaplines);
		Render_Toggle(loc, E(L"Slicing on snaplines"), &G::PunktierSnaplines);
		Render_Toggle(loc, E(L"CornerBox"), &G::CornerBox);
		Render_Toggle(loc, E(L"Draw local player / self"), &G::DrawSelf);

		loc.Y = g_Clientarea.Y;
		loc.X += g_MenuW / 2;

		Render_Slider(E(L"Supply / Loot distance"), 50, 500, &G::LootRenderDist, &loc);
		Render_Slider(E(L"Chests / ammo distance"), 50, 500, &G::ChestsRdist, &loc);
		Render_Slider(E(L"Overall ESP render distance"), 1, 650, &G::RenderDist, &loc);
		Render_Slider(E(L"RED distance"), 1, 300, &G::RedDistance, &loc);
		Render_Slider(E(L"Loot minimal tier"), 1, 5, &G::LootTier, &loc);
		Render_Slider(E(L"Snapline slicing power"), 1, 20, &G::PunktierPower, &loc);
		Render_Slider(E(L"CornerBox corner lines scale"), 0, 1, &G::CornerBoxScale, &loc);
		Render_Slider(E(L"CornerBox thickness"), 1, 4, &G::CornerBoxThicc, &loc);
	}
	if (index == 2)
	{
		auto loc = g_Clientarea;
		Render_Toggle(loc, E(L"Projectile TP"), &G::ProjectileTpEnable);
		Render_Toggle(loc, E(L"Flying vehicles"), &G::FlyingCars);
		Render_Toggle(loc, E(L"Outline enable"), &G::Outline);
		Render_Toggle(loc, E(L"Show time consumed"), &G::ShowTimeConsumed);
		Render_Toggle(loc, E(L"Use engine W2S"), &G::UseEngineW2S);
		Render_Toggle(loc, E(L"Refresh resolution each 1 second"), &G::RefreshEach1s);
	}
}