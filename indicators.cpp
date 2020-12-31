#include "includes.h"

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/

hud_indicators g_indicators{ };

// Hardcoded too much
// indicators
void hud_indicators::Indicators()
{
	if (!g_csgo.m_engine->IsInGame() || !g_csgo.m_engine->IsConnected())
		return;

	if (!g_menu.main.misc.indicators.get())
		return;

	g_csgo.m_engine->GetScreenSize(m_width, m_height);

	Color color = g_gui.m_color;

	// main window
	// alien calculations hehe
	int	x{ 8 };

	render::rect_filled(x + 10, m_height / 2 + 10, 200, 65, { 10, 10, 10, 160 });
	// overlay black.
	render::rect_filled(x + 10, m_height / 2 + 10, 200, 15 + 2, { 10, 10, 10, 200 });
	// line.
	render::rect_filled(x + 10, m_height / 2 + 10, 200, 2, { color.r(), color.g(), color.b(), 255 });
	// black outline.
	render::rect(x + 10 - 1, m_height / 2 + 9, 202, 65 + 1, { 10, 10, 10, 200 });
	// text.
	render::hud.string(x + 10 + 100, m_height / 2 + 14, { 255, 255, 255, 255 }, "indicators", render::ALIGN_CENTER);
	render::hud.string(x + 10 + 6, m_height / 2 + 30, { 255, 255, 255, 255 }, "double tap", render::ALIGN_LEFT);
	render::hud.string(x + 10 + 6, m_height / 2 + 40, { 255, 255, 255, 255 }, "smart baim", render::ALIGN_LEFT);
	render::hud.string(x + 10 + 6, m_height / 2 + 50, { 255, 255, 255, 255 }, "damage set", render::ALIGN_LEFT);
	render::hud.string(x + 10 + 6, m_height / 2 + 60, { 255, 255, 255, 255 }, "manual yaw", render::ALIGN_LEFT);

	// condition dt
	if (!g_aimbot.m_double_tap)
		render::hud.string(x + 10 + 195, m_height / 2 + 30, { color.r(), color.g(), color.b(), 255 }, "disabled", render::ALIGN_RIGHT);
	else
		render::hud.string(x + 10 + 195, m_height / 2 + 30, { 255, 255, 255, 255 }, "toggled", render::ALIGN_RIGHT);

	// baim
	if (!g_aimbot.m_baim_toggle)
		render::hud.string(x + 10 + 195, m_height / 2 + 40, { color.r(), color.g(), color.b(), 255 }, "disabled", render::ALIGN_RIGHT);
	else
		render::hud.string(x + 10 + 195, m_height / 2 + 40, { 255, 255, 255, 255 }, "toggled", render::ALIGN_RIGHT);

	// min dmg
	if (!g_aimbot.m_damage_toggle)
		render::hud.string(x + 10 + 195, m_height / 2 + 50, { color.r(), color.g(), color.b(), 255 }, "disabled", render::ALIGN_RIGHT);
	else
		render::hud.string(x + 10 + 195, m_height / 2 + 50, { 255, 255, 255, 255 }, "toggled", render::ALIGN_RIGHT);

	// desync type manual
	if (g_menu.main.antiaim.desync_mode.get() != 0 || !g_menu.main.antiaim.desync.get())
		render::hud.string(x + 10 + 195, m_height / 2 + 60, { color.r(), color.g(), color.b(), 255 }, "disabled", render::ALIGN_RIGHT);
	else
		render::hud.string(x + 10 + 195, m_height / 2 + 60, { 255, 255, 255, 255 }, "toggled", render::ALIGN_RIGHT);

	// let's make something different now... >_<
	// why everyone loves the centered status position?
	if (g_hvh.invert)
		render::hud.string(m_width / 2 + 64, m_height / 2 + 59, { color.r(), color.g(), color.b(), 255 }, "anti-aim inverter: on", render::ALIGN_LEFT);
	else
		render::hud.string(m_width / 2 + 64, m_height / 2 + 59, { 255, 255, 255, 255 }, "anti-aim inverter: off", render::ALIGN_LEFT);

	// manual map keys and arrows
	if(g_hvh.angle_side == 1)
		render::hud.string(m_width / 2 + 64, m_height / 2 + 67, { color.r(), color.g(), color.b(), 255 }, "manual keybind: left", render::ALIGN_LEFT);
	if (g_hvh.angle_side == 2)
		render::hud.string(m_width / 2 + 64, m_height / 2 + 67, { color.r(), color.g(), color.b(), 255 }, "manual keybind: right", render::ALIGN_LEFT);
	if (g_hvh.angle_side == 3)
		render::hud.string(m_width / 2 + 64, m_height / 2 + 67, { color.r(), color.g(), color.b(), 255 }, "manual keybind: back", render::ALIGN_LEFT);

	if(g_hvh.angle_side == NULL)
		render::hud.string(m_width / 2 + 64, m_height / 2 + 67, { 255, 255, 255, 255 }, "manual keybind: disabled", render::ALIGN_LEFT);

	// draw arrows only if manual state is on
	if (g_menu.main.antiaim.desync_mode.get() == 0)
	{
		if (g_hvh.angle_side == 2)
		{
			render::arrows.string(m_width / 2 + 70, m_height / 2 - 31, { color.r(), color.g(), color.b(), 150 }, "Q", render::ALIGN_CENTER);
			render::arrows.string(m_width / 2 - 70, m_height / 2 - 31, { 255, 255, 255, 50 }, "R", render::ALIGN_CENTER);
			render::arrows.string(m_width / 2 + 1, m_height / 2 - 31 + 70, { 255, 255, 255, 50 }, "T", render::ALIGN_CENTER);
		}
		if (g_hvh.angle_side == 1)
		{
			render::arrows.string(m_width / 2 + 70, m_height / 2 - 31, { 255, 255, 255, 50 }, "Q", render::ALIGN_CENTER);
			render::arrows.string(m_width / 2 - 70, m_height / 2 - 31, { color.r(), color.g(), color.b(), 150 }, "R", render::ALIGN_CENTER);
			render::arrows.string(m_width / 2 + 1, m_height / 2 - 31 + 70, { 255, 255, 255, 50 }, "T", render::ALIGN_CENTER);
		}
		if (g_hvh.angle_side == 3)
		{
			render::arrows.string(m_width / 2 + 70, m_height / 2 - 31, { 255, 255, 255, 50 }, "Q", render::ALIGN_CENTER);
			render::arrows.string(m_width / 2 - 70, m_height / 2 - 31, { 255, 255, 255, 50 }, "R", render::ALIGN_CENTER);
			render::arrows.string(m_width / 2 + 1, m_height / 2 - 31 + 70, { color.r(), color.g(), color.b(), 150 }, "T", render::ALIGN_CENTER);
		}
		// this is just useless, draws on status or not
		if (g_hvh.angle_side == NULL)
		{
			render::arrows.string(m_width / 2 + 70, m_height / 2 - 31, { 255, 255, 255, 50 }, "Q", render::ALIGN_CENTER);
			render::arrows.string(m_width / 2 - 70, m_height / 2 - 31, { 255, 255, 255, 50 }, "R", render::ALIGN_CENTER);
			render::arrows.string(m_width / 2 + 1, m_height / 2 - 31 + 70, { 255, 255, 255, 50 }, "T", render::ALIGN_CENTER);
		}
	}

	// is ducking?
	if (g_hvh.m_fakeduck)
		render::hud.string(m_width / 2 + 64, m_height / 2 + 75, { color.r(), color.g(), color.b(), 255 }, "fakeduck status: enabled", render::ALIGN_LEFT);
	else
		render::hud.string(m_width / 2 + 64, m_height / 2 + 75, { 255, 255, 255, 255 }, "fakeduck status: disabled", render::ALIGN_LEFT);

}

void hud_indicators::StateIndicators()
{
	if (!g_csgo.m_engine->IsInGame() || !g_csgo.m_engine->IsConnected())
		return;

	if (!g_menu.main.misc.indicators_status.get())
		return;

	g_csgo.m_engine->GetScreenSize(m_width, m_height);

	Color color = g_gui.m_color;

	int	x{ 8 };

	// what we are btw trying to draw...
	float dsync_height = g_cl.m_local->m_flPoseParameter()[11] * 58;	// this?
	float choke_value = g_csgo.m_cl->m_choked_commands;

	// dsync
	render::big_combo.string(x + 10, m_height / 1.6 - 25, { 255, 255, 255, 255 }, "DSYNC", render::ALIGN_LEFT);

	// outline
	render::rect_filled(x + 10, m_height / 1.6, 97, 6, { 10, 10, 10, 160 });
	// line.
	render::rect_filled(x + 10, m_height / 1.6, dsync_height * 1.67, 6, { color.r(), color.g(), color.b(), 255 });	// 97/58

	// choke
	render::big_combo.string(x + 10, m_height / 1.6 + 10, { 255, 255, 255, 255 }, "CHOKE", render::ALIGN_LEFT);

	// outline
	render::rect_filled(x + 10, m_height / 1.6 + 35, 97, 6, { 10, 10, 10, 160 });
	// line.
	render::rect_filled(x + 10, m_height / 1.6 + 35, choke_value * (97/14.f), 6, { color.r(), color.g(), color.b(), 255 });
}
