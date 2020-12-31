#include "includes.h"

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/


hud_scope g_scope{ };

// super custom scope, awesome
void hud_scope::custom_scope()
{
	if (!g_csgo.m_engine->IsInGame() || !g_csgo.m_engine->IsConnected())
		return;

	if (g_cl.m_local->m_iHealth() < 1 || !g_menu.main.visuals.noscope.get())
		return;

	// draw it, cute >_<
	if (scopeValue == true)
	{
		int w, h;
		g_csgo.m_engine->GetScreenSize(w, h);

		auto CurSpeed = g_cl.m_local->m_vecVelocity();
		auto Speed = CurSpeed.length_2d();
		int SpeedValue = Speed;

		// make the lines now animated :D
		if (SpeedValue > 4)	SpeedValue = 4;
		else if (SpeedValue < 2)	SpeedValue = 2;

		// >_>
		render::rect_filled_fade_scope(w / 2 - SpeedValue, 0, w / 2 + SpeedValue, h, { 10, 10, 10, 200 }, 150, 150);
		render::rect_filled_fade_scope(0, h / 2 - SpeedValue, w, h / 2 + SpeedValue, { 10, 10, 10, 200 }, 150, 150);
	}
}