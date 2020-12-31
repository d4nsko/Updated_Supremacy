#include "includes.h"

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/

// set fakelag matrix
matrix3x4_t fakelagmatrix[128];

bool Hooks::ShouldDrawParticles( ) {
	return g_hooks.m_client_mode.GetOldMethod< ShouldDrawParticles_t >( IClientMode::SHOULDDRAWPARTICLES )( this );
}

bool Hooks::ShouldDrawFog( ) {
	// remove fog.
	if( g_menu.main.visuals.nofog.get( ) )
		return false;

	return g_hooks.m_client_mode.GetOldMethod< ShouldDrawFog_t >( IClientMode::SHOULDDRAWFOG )( this );
}

void Hooks::OverrideView( CViewSetup* view ) {
	// damn son.
	g_cl.m_local = g_csgo.m_entlist->GetClientEntity< Player* >( g_csgo.m_engine->GetLocalPlayer( ) );

	if (g_csgo.m_engine->IsInGame() && g_csgo.m_engine->IsConnected())
	{

		if (!g_cl.m_local || g_cl.m_local == nullptr || g_cl.m_local->m_iHealth() < 1 || !g_cl.m_local->GetActiveWeapon())
			return;

		// g_grenades.think( );
		g_visuals.ThirdpersonThink();

		if (g_cl.m_local && g_cl.m_local->m_iHealth() > 0 && g_input.GetKeyState(g_menu.main.antiaim.fakeduck.get()))
			view->m_origin.z = g_cl.m_local->GetAbsOrigin().z + 64.f;
	}

    // call original.
	g_hooks.m_client_mode.GetOldMethod< OverrideView_t >( IClientMode::OVERRIDEVIEW )( this, view );
}

// Make changes here carefully
// Can't debug properly, logical manual fixes lul...
bool Hooks::CreateMove(float time, CUserCmd* cmd) {
	Stack   stack;
	bool    ForwardCreateMove;

	// let original run first.
	ForwardCreateMove = g_hooks.m_client_mode.GetOldMethod< CreateMove_t >(IClientMode::CREATEMOVE)(this, time, cmd);

	// get bSendPacket off the stack.
	g_cl.m_packet = stack.next().local(0x1c).as< bool* >();

	// get bFinalTick off the stack.
	g_cl.m_final_packet = stack.next().local(0x1b).as< bool* >();

	// nothing received
	// need to checkout this later - without this crap, forward just crashes time 2 time
	if (!ForwardCreateMove || m_safe.NonSendPacket())
		return false;

	// called from CInput::ExtraMouseSample -> return original.
	// comes with many states
	if(m_safe.InvalidCommand(cmd))
		return ForwardCreateMove;

	if (g_csgo.m_engine->IsInGame() && g_csgo.m_engine->IsConnected())
	{
		if (m_safe.ValidCommand(cmd))	// yep, alive and ready
		{
			// cancer again, debug points here, so...
			if (ForwardCreateMove && cmd->m_command_number != NULL)
				g_csgo.m_engine->SetViewAngles(cmd->m_view_angles);

			// random_seed isn't generated in ClientMode::CreateMove yet, we must set generate it ourselves.
			cmd->m_random_seed = g_csgo.MD5_PseudoRandom(cmd->m_command_number) & 0x7fffffff;

			// invoke move function.
			g_cl.OnTick(cmd);

			if (g_hvh.m_should_work) {
				if (*g_cl.m_packet)
					g_cl.m_angle = cmd->m_view_angles;
				else
					g_cl.m_real_angle = cmd->m_view_angles;
			}
			else {
				g_cl.m_angle = g_cl.m_real_angle = cmd->m_view_angles;
			}

			if (g_menu.main.misc.fakelag_matrix.get())
			{
				if (*g_cl.m_packet)	// doesn't matter
					g_cl.m_local->SetupBones(fakelagmatrix, 128, BONE_USED_BY_HITBOX, g_csgo.m_globals->m_curtime);
			}
		}
	}

	// if not - return
	return false;
}

bool Hooks::DoPostScreenSpaceEffects( CViewSetup* setup ) {
	g_visuals.RenderGlow( );

	return g_hooks.m_client_mode.GetOldMethod< DoPostScreenSpaceEffects_t >( IClientMode::DOPOSTSPACESCREENEFFECTS )( this, setup );
}