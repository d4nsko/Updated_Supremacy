#include "includes.h"

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/

agent_changer g_agents{ };

// Bind only once
bool ForceOnce = false;
bool LoadModel = false;

// This is how custom player models working.
// U need to precache them first and use only after that.
bool LockNLoad(const char* MdlName)
{
	// hooking INetworkStringTable
	INetworkStringTable* m_supremacy_model = g_csgo.m_networkstringtable->FindTable("modelprecache");

	if (m_supremacy_model)
	{
		g_csgo.m_model_info->FindOrLoadModel(MdlName);
		int modelindex = m_supremacy_model->AddString(false, MdlName);
		if (modelindex == NULL)	// if not exists, skip
			return false;
	}
	return true;
}

// setup models
void agent_changer::SetupAgents()
{
	// call this once
	if (!g_menu.main.config.enable_agent.get())
	{
		// Strip?
		// TODO backup and save default model
		g_cl.m_local->SetModelIndex(g_csgo.m_model_info->GetModelIndex("models/player/custom_player/legacy/ctm_sas_variantf.mdl"));
		ForceOnce = true;
		LoadModel = false;
		return;
	}
	// lock
	else
		ForceOnce = false;

	if (ForceOnce == false)
	{
		// For example let's precache Counter-Strike Online 2 player operators
		// Download them first OFC
		if (LoadModel == false)
		{
			// Don't change the models path, it's defined in .mdl source code
			LockNLoad("models/player/custom_player/kuristaja/cso2/mila/mila.mdl");

			LoadModel = true;	// we done here, no need to spam this
		}

		static int iModel = g_menu.main.config.agent_change.get();

		// setup your models here
		if (g_menu.main.config.agent_change.get() == 0)	// first
			iModel = g_csgo.m_model_info->GetModelIndex("models/player/custom_player/legacy/ctm_fbi_variantb.mdl");
		else if (g_menu.main.config.agent_change.get() == 1)
			iModel = g_csgo.m_model_info->GetModelIndex("models/player/custom_player/kuristaja/cso2/mila/mila.mdl");

		g_cl.m_local->SetModelIndex(iModel);	
	}
}