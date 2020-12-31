#include "includes.h"

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/

hud_killstreaks g_killstreaks{ };

void hud_killstreaks::Killstreaks()
{
	if (!g_csgo.m_engine->IsInGame() || !g_csgo.m_engine->IsConnected())
		return;

	g_csgo.m_engine->GetScreenSize(m_width, m_height);

	// super retarded shit, but let it stay only 2000 frames, not more :D
	if (posX < 2000) 
		posX++;
	if (posY < 2000) 
		posY--;

	// fx
	if (iFly < 255 && iOut == 255) 
		iFly++;

	if (iFly > 250) 
		iOut--;

	if (iOut < 5 && iFly > 0) 
		iFly--;

	// push killstreaks and point text
	if (g_menu.main.misc.killstreak_fx.get())
	{
		// type 1
		if (iKills == 1)
			render::big_point.string(m_width / 2 + posX, m_height / 2 - posY, { 255, 102, 102, 255 }, "FIRST BLOOD", render::ALIGN_CENTER), render::big_combo.string(m_width - 290, m_height / 1.65 - 35, { 255, 178, 102, iFly }, "+500 POINT", render::ALIGN_LEFT);
		else if (iKills == 2)
			render::big_point.string(m_width / 2 - posX, m_height / 2 + posY, { 178, 255, 102, 255 }, "DOUBLE KILL", render::ALIGN_CENTER), render::big_combo.string(m_width - 290, m_height / 1.65 - 35, { 255, 178, 102, iFly }, "+500 POINT", render::ALIGN_LEFT);
		else if (iKills == 3)
			render::big_point.string(m_width / 2 - posX, m_height / 2 - posY, { 102, 178, 255, 255 }, "TRIPLE KILL", render::ALIGN_CENTER), render::big_combo.string(m_width - 290, m_height / 1.65 - 35, { 255, 178, 102, iFly }, "+500 POINT", render::ALIGN_LEFT);
		else if (iKills == 4)
			render::big_point.string(m_width / 2 + posX, m_height / 2 + posY, { 255, 255, 102, 255 }, "ULTRA KILL", render::ALIGN_CENTER), render::big_combo.string(m_width - 290, m_height / 1.65 - 35, { 255, 178, 102, iFly }, "+500 POINT", render::ALIGN_LEFT);
		else if (iKills == 5)
			render::big_point.string(m_width / 2 - posX, m_height / 2 + posY, { 255, 178, 102, 255 }, "MONSTER KILL", render::ALIGN_CENTER), render::big_combo.string(m_width - 290, m_height / 1.65 - 35, { 255, 178, 102, iFly }, "+500 POINT", render::ALIGN_LEFT);
		else if (iKills == 6)
			render::big_point.string(m_width / 2 + posX, m_height / 2 - posY, { 102, 102, 255, 255 }, "UNSTOPPABLE", render::ALIGN_CENTER), render::big_combo.string(m_width - 290, m_height / 1.65 - 35, { 255, 178, 102, iFly }, "+500 POINT", render::ALIGN_LEFT);
		else if (iKills == 7)
			render::big_point.string(m_width / 2 + posX, m_height / 2 + posY, { 255, 51, 153, 255 }, "GODLIKE", render::ALIGN_CENTER), render::big_combo.string(m_width - 290, m_height / 1.65 - 35, { 255, 178, 102, iFly }, "+500 POINT", render::ALIGN_LEFT);
		else if (iKills == 8)
			render::big_point.string(m_width / 2 - posX, m_height / 2 + posY, { 255, 255, 51, 255 }, "LUDICROUS KILL", render::ALIGN_CENTER), render::big_combo.string(m_width - 290, m_height / 1.65 - 35, { 255, 178, 102, iFly }, "+500 POINT", render::ALIGN_LEFT);
	}
}