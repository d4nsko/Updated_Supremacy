#include "includes.h"

safe_conditions m_safe {};

// Everything here is just a cancer checkout's...
// conditions, non target/non local or invalid and is not present
bool safe_conditions::IsNotProcessing()
{
	return (!g_cl.m_local || g_cl.m_local == nullptr || g_cl.m_local->m_iHealth() < 1 || !g_cl.m_local->GetActiveWeapon() || !g_cl.m_processing);
}

// already spawned and ready
bool safe_conditions::IsReady()
{
	return iLife == true;
}

// returns invalid conditions
bool safe_conditions::InvalidCommand(CUserCmd* cmd)
{
	return (!cmd->m_command_number || !g_cl.m_local || g_cl.m_local == nullptr || g_cl.m_local->m_iHealth() < 1 || !g_cl.m_local->GetActiveWeapon());
}

// returns valid conditions
bool safe_conditions::ValidCommand(CUserCmd* cmd)
{
	return (cmd->m_command_number && g_cl.m_local && g_cl.m_local != nullptr && g_cl.m_local->m_iHealth() > 0 && g_cl.m_local->GetActiveWeapon());
}

// not valid
bool safe_conditions::NonSendPacket()
{
	return (iLife == false || !g_cl.m_final_packet || !g_cl.m_packet || !g_cl.m_local || g_cl.m_local == nullptr || !g_cl.m_local->GetActiveWeapon());
}

// fsn
bool safe_conditions::IsPlayerReady()
{
	// returns if local player is already spawned, holding a weapon and ready (ticks reset)
	return iLife == true && g_cl.m_local && g_cl.m_local != nullptr && g_cl.m_local->m_iHealth() > 0 && g_cl.m_local->GetActiveWeapon();
}