﻿#include "includes.h"

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/

Client g_cl{ };

// init routine.
ulong_t __stdcall Client::init(void* arg) {
	// if not in interwebz mode, the driver will not set the username.
	g_cl.m_user = XOR("supremacy");

	// stop here if we failed to acquire all the data needed from csgo.
	if (!g_csgo.init())
		return 0;

	return 1;
}

// Fix aquacure
void Client::DrawHUD() {

	// setup safe conditions
	if (g_csgo.m_engine->IsInGame() && g_csgo.m_engine->IsConnected())
	{
		// deathmatch
		if (g_cl.m_local->m_iHealth() > 0)
			iLife = true;
	}

	// force some cheat cvars
	g_vars.cheat_cvars();

	// draw custom watermark
	g_watermark.Watermark();

	// draw specific lines instead of original zooming
	g_scope.custom_scope();

	// draw nemesis like indicators >_<
	g_indicators.Indicators();

	// once i've seen this on youtube - ok let's code our own hehe
	// draws desync and choke state with active bar
	g_indicators.StateIndicators();

	// draw bar at the right
	g_scorepoint.Scorepoint();

	// llamahook v2 killstreaks
	g_killstreaks.Killstreaks();
}

// some improvements >_<
void Client::KillFeed() {
	static bool clear_notices = false;
	static bool old_setting = g_menu.main.misc.killfeed.get();
	static void(__thiscall * clear_death_notices_addr)(uintptr_t);
	static uintptr_t* death_notices_addr;

	if (!(g_csgo.m_engine->IsConnected()) || !(g_csgo.m_engine->IsInGame()) || g_cl.m_local == nullptr)
		return;

	if (!g_cl.m_local) {

		// invalidate the clear death notice address if local goes invalid.
		if (clear_death_notices_addr) {
			clear_death_notices_addr = nullptr;
		}

		// invalidate the death notice address if local goes invalid.
		if (death_notices_addr) {
			death_notices_addr = nullptr;
		}

		// that's it, exit out.
		return;
	}

	// only do the following if local is alive.
	if (g_cl.m_local->m_iHealth() > 0) {
		// get the death notice addr.
		if (!death_notices_addr) {
			death_notices_addr = game::FindElement(XOR("CCSGO_HudDeathNotice"));
		}

		// get the clear death notice addr.
		if (!clear_death_notices_addr) {
			clear_death_notices_addr = pattern::find(g_csgo.m_client_dll, XOR("55 8B EC 83 EC 0C 53 56 8B 71 58")).as< void(__thiscall*)(uintptr_t) >();
		}

		// only do the following if both addresses were found and are valid.
		if (clear_death_notices_addr && death_notices_addr) {
			// grab the local death notice time.
			float* local_death_notice_time = (float*)((uintptr_t)death_notices_addr + 0x50);
			static float backup_local_death_notice_time = *local_death_notice_time;

			// extend killfeed time.
			if (local_death_notice_time && g_menu.main.misc.killfeed.get()) {
				*local_death_notice_time = std::numeric_limits<float>::max();
			}

			// if we disable the option, clear the death notices.
			if (old_setting != g_menu.main.misc.killfeed.get()) {
				if (!g_menu.main.misc.killfeed.get()) {
					if (local_death_notice_time) {
						// reset back to the regular death notice time.
						*local_death_notice_time = backup_local_death_notice_time;
					}

					clear_notices = true;
				}
				old_setting = g_menu.main.misc.killfeed.get();
			}

			// if we have the option enabled and we need to clear the death notices.
			if (g_menu.main.misc.killfeed.get()) {
				//if (g_cl.m_round_flags == 0 && death_notices_addr - 0x14) {
				if (g_cl.m_local->m_iHealth() < 1 && death_notices_addr - 0x14) {
					clear_notices = true;
				}
			}

			// clear the death notices.
			if (clear_notices) {
				clear_death_notices_addr(((uintptr_t)death_notices_addr - 0x14));
				clear_notices = false;
			}
		}
	}
	// if enabled and we are died
	if (g_cl.m_local->m_iHealth() < 1)
	{
		// invalidate clear death notice address.
		if (clear_death_notices_addr) {
			clear_death_notices_addr = nullptr;
		}

		// invalidate death notice address.
		if (death_notices_addr) {
			death_notices_addr = nullptr;
		}
		// remove if enabled and we died
		if(g_menu.main.misc.killfeed.get())
			clear_notices = true;
	}
}

void Client::OnPaint() {
	// update screen size.
	g_csgo.m_engine->GetScreenSize(m_width, m_height);

	// render stuff.
	g_visuals.think();

	g_grenades.paint();

	g_notify.think();

	DrawHUD();

	g_visuals.IndicateAngles();

	KillFeed();	

	// menu goes last.
	g_gui.think();
}

void Client::OnMapload() {
	// store class ids.
	g_netvars.SetupClassData();

	if (!g_csgo.m_engine)
		return;

	// createmove will not have been invoked yet.
	// but at this stage entites have been created.
	// so now we can retrive the pointer to the local player.
	m_local = g_csgo.m_entlist->GetClientEntity< Player* >(g_csgo.m_engine->GetLocalPlayer());

	// world materials.
	Visuals::ModulateWorld();

	// load skins
	g_skins.load();

	m_sequences.clear();

	// if the INetChannelInfo pointer has changed, store it for later.
	g_csgo.m_net = g_csgo.m_engine->GetNetChannelInfo();

	if (g_csgo.m_net) {
		g_hooks.m_net_channel.reset();
		g_hooks.m_net_channel.init(g_csgo.m_net);
		g_hooks.m_net_channel.add(INetChannel::PROCESSPACKET, util::force_cast(&Hooks::ProcessPacket));
		g_hooks.m_net_channel.add(INetChannel::SENDDATAGRAM, util::force_cast(&Hooks::SendDatagram));
	}
}

void Client::StartMove(CUserCmd* cmd) {
	// save some usercmd stuff.
	m_cmd = cmd;
	m_tick = cmd->m_tick;
	m_view_angles = cmd->m_view_angles;
	m_buttons = cmd->m_buttons;

	// get local ptr.
	m_local = g_csgo.m_entlist->GetClientEntity< Player* >(g_csgo.m_engine->GetLocalPlayer());
	if (!m_local)
		return;

	g_csgo.m_net = g_csgo.m_engine->GetNetChannelInfo();

	if (!g_csgo.m_net)
		return;

	if (m_processing && m_tick_to_recharge > 0 && !m_charged) {
		m_tick_to_recharge--;
		if (m_tick_to_recharge == 0) {
			m_charged = true;
		}
		cmd->m_tick = INT_MAX;
		*m_packet = true;
	}

	// store max choke
	// TODO; 11 -> m_bIsValveDS
	m_max_lag = 14;
	m_lag = g_csgo.m_cl->m_choked_commands;
	m_lerp = game::GetClientInterpAmount();
	m_latency = g_csgo.m_net->GetLatency(INetChannel::FLOW_OUTGOING);
	math::clamp(m_latency, 0.f, 1.f);
	m_latency_ticks = game::TIME_TO_TICKS(m_latency);
	m_server_tick = g_csgo.m_cl->clock_drift_mgr.m_server_tick;
	m_arrival_tick = m_server_tick + m_latency_ticks;

	// processing indicates that the localplayer is valid and alive.
	m_processing = m_local && m_local->m_iHealth() > 0;
	if (!m_processing)
		return;

	// make sure prediction has ran on all usercommands.
	// because prediction runs on frames, when we have low fps it might not predict all usercommands.
	// also fix the tick being inaccurate.
	g_inputpred.update();

	// store some stuff about the local player.
	m_flags = m_local->m_fFlags();

	// ...
	m_shot = false;
}

void Client::BackupPlayers(bool restore) {
	if (restore) {
		// restore stuff.
		for (int i{ 1 }; i <= g_csgo.m_globals->m_max_clients; ++i) {
			Player* player = g_csgo.m_entlist->GetClientEntity< Player* >(i);

			if (!g_aimbot.IsValidTarget(player))
				continue;

			g_aimbot.m_backup[i - 1].restore(player);
		}
	}

	else {
		// backup stuff.
		for (int i{ 1 }; i <= g_csgo.m_globals->m_max_clients; ++i) {
			Player* player = g_csgo.m_entlist->GetClientEntity< Player* >(i);

			if (!g_aimbot.IsValidTarget(player))
				continue;

			g_aimbot.m_backup[i - 1].store(player);
		}
	}
}

void Client::DoMove() {
	penetration::PenetrationOutput_t tmp_pen_data{ };

	// backup strafe angles (we need them for input prediction)
	m_strafe_angles = m_cmd->m_view_angles;

	// run movement code before input prediction.
	g_movement.JumpRelated();
	g_movement.Strafe();
	g_movement.FakeWalk();
	g_movement.AutoStop();

	// predict input.
	g_inputpred.run();

	// restore original angles after input prediction
	m_cmd->m_view_angles = m_view_angles;

	// convert viewangles to directional forward vector.
	math::AngleVectors(m_view_angles, &m_forward_dir);

	// store stuff after input pred.
	m_shoot_pos = m_local->GetShootPosition();

	// reset shit.
	m_weapon = nullptr;
	m_weapon_info = nullptr;
	m_weapon_id = -1;
	m_weapon_type = WEAPONTYPE_UNKNOWN;
	m_player_fire = m_weapon_fire = false;

	// store weapon stuff.
	m_weapon = m_local->GetActiveWeapon();

	if (m_weapon) {
		m_weapon_info = m_weapon->GetWpnData();
		m_weapon_id = m_weapon->m_iItemDefinitionIndex();
		m_weapon_type = m_weapon_info->WeaponType;	// this sometimes returns -1, so i made manual check

		// ensure weapon spread values / etc are up to date.
		if (!m_weapon->IsGrenade())
			m_weapon->UpdateAccuracyPenalty();

		// run autowall once for penetration crosshair if we have an appropriate weapon.
		if (m_weapon_type != WEAPONTYPE_KNIFE && m_weapon_type != WEAPONTYPE_EQUIPMENT && !m_weapon->IsGrenade()) {
			penetration::PenetrationInput_t in;
			in.m_from = m_local;
			in.m_target = nullptr;
			in.m_pos = m_shoot_pos + (m_forward_dir * m_weapon_info->flRange);
			in.m_damage = 1.f;
			in.m_damage_pen = 1.f;
			in.m_can_pen = true;

			// run autowall.
			penetration::run(&in, &tmp_pen_data);
		}

		// set pen data for penetration crosshair.
		m_pen_data = tmp_pen_data;

		// can the player fire.
		m_player_fire = g_csgo.m_globals->m_curtime >= m_local->m_flNextAttack() && !g_csgo.m_gamerules->m_bFreezePeriod() && !(g_cl.m_flags & FL_FROZEN);

		UpdateRevolverCock();
		m_weapon_fire = CanFireWeapon(game::TICKS_TO_TIME(g_cl.m_local->m_nTickBase()));
	}

	// last tick defuse.
	// todo - dex;  figure out the range for CPlantedC4::Use?
	//              add indicator if valid (on ground, still have time, not being defused already, etc).
	//              move this? not sure where we should put it.
	if (g_input.GetKeyState(g_menu.main.misc.last_tick_defuse.get()) && g_visuals.m_c4_planted) {
		float defuse = (m_local->m_bHasDefuser()) ? 5.f : 10.f;
		float remaining = g_visuals.m_planted_c4_explode_time - g_csgo.m_globals->m_curtime;
		float dt = remaining - defuse - (g_cl.m_latency / 2.f);

		m_cmd->m_buttons &= ~IN_USE;
		if (dt <= game::TICKS_TO_TIME(2))
			m_cmd->m_buttons |= IN_USE;
	}

	// grenade prediction.
	g_grenades.think();

	// run fakelag.
	g_hvh.SendPacket();

	// run aimbot.
	g_aimbot.think();

	// run antiaims.
	g_hvh.AntiAim();

}

void Client::EndMove(CUserCmd* cmd) {
	// update client-side animations.
	// >_< By the logic it's almost done in frame state each frame, why here again?
	// UpdateInformation();

	// if matchmaking mode, anti untrust clamp.
	if (g_menu.main.config.mode.get() == 0)
		m_cmd->m_view_angles.SanitizeAngle();

	// fix our movement.
	g_movement.FixMove(cmd, m_strafe_angles);

	// this packet will be sent.
	if (*m_packet) {
		g_hvh.m_step_switch = (bool)g_csgo.RandomInt(0, 1);

		// we are sending a packet, so this will be reset soon.
		// store the old value.
		m_old_lag = m_lag;

		// get radar angles.
		m_radar = cmd->m_view_angles;
		m_radar.normalize();

		// get current origin.
		vec3_t cur = m_local->m_vecOrigin();

		// get prevoius origin.
		vec3_t prev = m_net_pos.empty() ? cur : m_net_pos.front().m_pos;

		// check if we broke lagcomp.
		m_lagcomp = (cur - prev).length_sqr() > 4096.f;

		// save sent origin and time.
		m_net_pos.emplace_front(g_csgo.m_globals->m_curtime, cur);
	}

	// store some values for next tick.
	m_old_packet = *m_packet;
	m_old_shot = m_shot;
}

void Client::OnTick(CUserCmd* cmd) {
	// store some data and update prediction.
	StartMove(cmd);

	// not much more to do here.
	if (!m_processing)
		return;

	// save the original state of players.
	BackupPlayers(false);

	// run all movement related code.
	DoMove();

	// store stome additonal stuff for next tick
	// sanetize our usercommand if needed and fix our movement.
	EndMove(cmd);

	// restore the players.
	BackupPlayers(true);

	// restore curtime/frametime
	// and prediction seed/player.
	g_inputpred.restore();

	g_aimbot.DoubleTap();

	if (g_aimbot.m_double_tap)
	{
		if (!g_aimbot.CanDT())
			m_charged = false;
		else if (!m_charged && m_tick_to_recharge == 0) {
			//m_tick_to_recharge = 13;
			m_tick_to_recharge = 16;
		}
	}
}

void Client::UpdateInformation() {
	// this is fucked up and debug pointer stuck here even with checkout in framestage, so let's force this...
	if(m_safe.IsNotProcessing())
		return;

	CCSGOPlayerAnimState* state = g_cl.m_local->m_PlayerAnimState();
	if (!state)
		return;

	if (g_cl.m_lag > 0)
		return;

	// prevent from overflow
	if (state && m_safe.IsReady())
	{
		// update time.
		m_anim_frame = g_csgo.m_globals->m_curtime - m_anim_time;
		m_anim_time = g_csgo.m_globals->m_curtime;

		// save updated data.
		m_speed = state->m_flSpeed;
		m_ground = state->m_bOnGround;
	}
}

void Client::UpdateAnimations() {
	// same as above...
	if (m_safe.IsNotProcessing())
		return;

	CCSGOPlayerAnimState* state = g_cl.m_local->m_PlayerAnimState();
	if (!state) {
		return;
	}

	if (!g_csgo.m_cl) {
		return;
	}

	// ... ticks
	if (state && m_safe.IsReady())
	{
		const auto backup_frametime = g_csgo.m_globals->m_frametime;
		const auto backup_curtime = g_csgo.m_globals->m_curtime;

		state->m_flGoalFeetYaw = g_cl.m_real_angle.y;

		if (state->m_iLastClientSideAnimationUpdateFramecount == g_csgo.m_globals->m_frame)
			state->m_iLastClientSideAnimationUpdateFramecount -= 1.f;

		// later TODO
		static int bSkipAnimationFrame = *reinterpret_cast<int*>(uintptr_t(g_cl.m_local) + 0x274);
		*reinterpret_cast<int*>(uintptr_t(g_cl.m_local) + 0x274) = NULL;

		static float angle = state->m_flGoalFeetYaw;

		if (g_cl.m_local->m_flSimulationTime() != g_cl.m_local->m_flOldSimulationTime())
		{
			g_cl.m_local->GetAnimLayers(g_cl.m_real_layers);

			g_cl.m_update = true;

			game::UpdateAnimationState(state, g_cl.m_angle);
			g_cl.m_local->UpdateClientSideAnimation();

			g_cl.m_update = false;

			angle = state->m_flGoalFeetYaw;

			g_cl.m_local->SetAnimLayers(g_cl.m_real_layers);
			g_cl.m_local->GetPoseParameters(g_cl.m_real_poses);

		}
		state->m_flGoalFeetYaw = angle;

		*reinterpret_cast<int*>(uintptr_t(g_cl.m_local) + 0x274) = bSkipAnimationFrame;

		// let our legs slide while shifting if non of slide is enabled
		if (g_menu.main.movement.low_velo_slide.get() && g_input.GetKeyState(g_menu.main.movement.fakewalk.get()))
			g_cl.m_local->m_AnimOverlay()[6].m_weight = 0.0f;	// >_< premium
	}
}

void Client::print(const std::string text, ...) {
	va_list     list;
	int         size;
	std::string buf;

	if (text.empty())
		return;

	va_start(list, text);

	// count needed size.
	size = std::vsnprintf(0, 0, text.c_str(), list);

	// allocate.
	buf.resize(size);

	// print to buffer.
	std::vsnprintf(buf.data(), size + 1, text.c_str(), list);

	va_end(list);

	Color color = g_gui.m_color;

	// print to console.
	g_csgo.m_cvar->ConsoleColorPrintf({ color.r(), color.g(), color.b(), 255 }, XOR("[supremacy] "));
	g_csgo.m_cvar->ConsoleColorPrintf(colors::white, buf.c_str());
}

bool Client::CanFireWeapon(float curtime) {
	// the player cant fire.
	if (!m_player_fire)
		return false;

	if (m_weapon->IsGrenade())
		return false;

	// if we have no bullets, we cant shoot.
	if (m_weapon_type != WEAPONTYPE_KNIFE && m_weapon->m_iClip1() < 1)
		return false;

	// do we have any burst shots to handle?
	if ((m_weapon_id == GLOCK || m_weapon_id == FAMAS) && m_weapon->m_iBurstShotsRemaining() > 0) {
		// new burst shot is coming out.
		if (curtime >= m_weapon->m_fNextBurstShot())
			return true;
	}

	// r8 revolver.
	if (m_weapon_id == REVOLVER) {
		// mouse1.
		if (m_revolver_fire) {
			return true;
		}
		else {
			return false;
		}
	}

	// yeez we have a normal gun.
	if (curtime >= m_weapon->m_flNextPrimaryAttack())
		return true;

	return false;
}

bool Client::IsFiring(float curtime) {
	const auto weapon = g_cl.m_weapon;
	if (!weapon)
		return false;

	const auto IsZeus = m_weapon_id == Weapons_t::ZEUS;
	const auto IsKnife = !IsZeus && m_weapon_type == WEAPONTYPE_KNIFE;

	if (weapon->IsGrenade())
		return !weapon->m_bPinPulled() && weapon->m_fThrowTime() > 0.f && weapon->m_fThrowTime() < curtime;
	else if (IsKnife)
		return (g_cl.m_cmd->m_buttons & (IN_ATTACK) || g_cl.m_cmd->m_buttons & (IN_ATTACK2)) && CanFireWeapon(curtime);
	else
		return g_cl.m_cmd->m_buttons & (IN_ATTACK) && CanFireWeapon(curtime);
}

void Client::UpdateRevolverCock() {
	if (m_weapon_id != REVOLVER)
		return;

	static auto last_checked = 0;
	static auto last_spawn_time = 0.f;
	static auto tick_cocked = 0;
	static auto tick_strip = 0;

	const auto max_ticks = game::TIME_TO_TICKS(.25f) - 1;
	const auto tick_base = game::TIME_TO_TICKS(g_csgo.m_globals->m_curtime);

	if (m_local->m_flSpawnTime() != last_spawn_time) {
		last_spawn_time = m_local->m_flSpawnTime();
		tick_cocked = tick_base;
		tick_strip = tick_base - max_ticks - 1;
	}

	if (m_weapon->m_flNextPrimaryAttack() > g_csgo.m_globals->m_curtime) {
		m_cmd->m_buttons &= ~IN_ATTACK;
		m_revolver_fire = false;
		return;
	}

	if (last_checked == tick_base)
		return;

	last_checked = tick_base;
	m_revolver_fire = false;

	if (tick_base - tick_strip > 2 && tick_base - tick_strip < 14)
		m_revolver_fire = true;

	if (m_cmd->m_buttons & IN_ATTACK && m_revolver_fire)
		return;

	m_cmd->m_buttons |= IN_ATTACK;

	if (m_weapon->m_flNextSecondaryAttack() >= g_csgo.m_globals->m_curtime)
		m_cmd->m_buttons |= IN_ATTACK2;

	if (tick_base - tick_cocked > max_ticks * 2 + 1) {
		tick_cocked = tick_base;
		tick_strip = tick_base - max_ticks - 1;
	}

	const auto cock_limit = tick_base - tick_cocked >= max_ticks;
	const auto after_strip = tick_base - tick_strip <= max_ticks;

	if (cock_limit || after_strip) {
		tick_cocked = tick_base;
		m_cmd->m_buttons &= ~IN_ATTACK;

		if (cock_limit)
			tick_strip = tick_base;
	}
}

void Client::UpdateIncomingSequences() {
	if (!g_csgo.m_net)
		return;

	if (m_sequences.empty() || g_csgo.m_net->m_in_seq > m_sequences.front().m_seq) {
		// store new stuff.
		m_sequences.emplace_front(g_csgo.m_globals->m_realtime, g_csgo.m_net->m_in_rel_state, g_csgo.m_net->m_in_seq);
	}

	// do not save too many of these.
	while (m_sequences.size() > 2048)
		m_sequences.pop_back();
}