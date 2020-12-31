#include "includes.h"

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/

hud_effects g_watermark{ };

// watermark
void hud_effects::Watermark()
{
	if (!g_csgo.m_engine->IsInGame() || !g_csgo.m_engine->IsConnected())
		return;

	if (!g_menu.main.misc.watermark.get())
		return;

	g_csgo.m_engine->GetScreenSize(m_width, m_height);

	// get time.
	time_t t = std::time(nullptr);
	std::ostringstream time;
	time << std::put_time(std::localtime(&t), ("%H:%M:%S"));

	// get round trip time in milliseconds.
	int ms = std::max(0, (int)std::round(g_cl.m_latency * 1000.f));

	// get tickrate.
	int rate = (int)std::round(1.f / g_csgo.m_globals->m_interval);

	// getting player name before game init is unsafe
	std::string text = tfm::format(XOR("supremacy [beta] | %s | rtt: %ims | rate: %i | %s"), game::GetPlayerName(g_csgo.m_engine->GetLocalPlayer()), ms, rate, time.str().data());
	render::FontSize_t size = render::hud.size(text);

	Color color = g_gui.m_color;

	// background.
	render::rect_filled(m_width - size.m_width - 20, 10, size.m_width + 10, size.m_height + 2, { 10, 10, 10, 160 });
	// line
	render::rect_filled(m_width - size.m_width - 20, 9, size.m_width + 10, 2, { color.r(), color.g(), color.b(), 255 });
	// text.
	render::hud.string(m_width - 15, 12, { 255, 255, 255, 255 }, text, render::ALIGN_RIGHT);
}