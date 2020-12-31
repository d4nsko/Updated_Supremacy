#include "includes.h"

spoofed_cvars g_vars{ };

// some retarded cvar spoofing >_>
// disable them or hook normally...
void spoofed_cvars::cheat_cvars()
{
	// >_< rage cheat, who cares...
	static auto sv_cheats_cvar = g_csgo.m_cvar->FindVar(HASH("sv_cheats"));
	sv_cheats_cvar->SetValue(1);

	// Post procñess spoof
	static auto mat_postporcess_cvar = g_csgo.m_cvar->FindVar(HASH("mat_postprocess_enable"));

	if (g_menu.main.misc.post_process_dis.get())
		mat_postporcess_cvar->SetValue(0);
	else
		mat_postporcess_cvar->SetValue(1);

	// just settings i like to use
	// bloom 
	static auto bloom_cvar = g_csgo.m_cvar->FindVar(HASH("mat_bloom_scalefactor_scalar"));
	bloom_cvar->SetValue(2);

	static auto bloom_scale_cvar = g_csgo.m_cvar->FindVar(HASH("mat_bloomamount_rate"));
	bloom_scale_cvar->SetValue(5.05f / 255.f);

	// lambert
	static auto model_bright_cvar = g_csgo.m_cvar->FindVar(HASH("r_modelAmbientMin"));
	model_bright_cvar->SetValue(0.2f);
}