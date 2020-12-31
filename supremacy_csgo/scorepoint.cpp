#include "includes.h"

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/

hud_scorepoint g_scorepoint{ };

// Counter-Strike Online 2 like Scorepoint
void hud_scorepoint::Scorepoint()
{
	if (!g_csgo.m_engine->IsInGame() || !g_csgo.m_engine->IsConnected())
		return;

	g_csgo.m_engine->GetScreenSize(m_width, m_height);

	Color color = g_gui.m_color;

	// CSO2 -> just for fun
	std::string score = tfm::format(XOR("%"), iTotal);

	// >_<
	if (iTotal > 9999)
		iTotal = 2568;

	if (iYpos >= 0)
		iYpos--;

	if (iAlpha < 255)
		iAlpha++;

	// line.
	if (g_menu.main.misc.killstreak_fx.get())
	{
		render::rect_filled(m_width - 300, m_height / 1.65 + 8, 400, 30, { 10, 10, 10, 160 });
		render::rect_filled(m_width - 300, m_height / 1.65 + 8, 5, 30, { color.r(), color.g(), color.b(), 255 });
		render::big_score.string(m_width - 290, m_height / 1.65 + 10, { 150, 150, 150, 160 }, "POINT", render::ALIGN_LEFT);

		std::string Combo = tfm::format(XOR("%i COMBO"), iCombo);

		render::big_combo.string(m_width - 187, m_height / 1.65 + 45, { 255, 255, 255, 160 }, Combo, render::ALIGN_RIGHT);

		render::big_score_num.string(m_width - 185, m_height / 1.65 - 12 + iYpos, { 255, 128, 0, iAlpha }, score, render::ALIGN_LEFT);
	}
}