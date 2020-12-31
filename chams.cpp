#include "includes.h"
#include "studiorender.h"

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/

// TODO - Create material hook instead of Find for MM
// Some binds are retarded >_<

Chams g_chams{ };

bool IsLocalPlayerValid()
{
	// returns if local player is already spawned, holding a weapon and ready
	return g_cl.m_local && g_cl.m_local != nullptr && g_cl.m_local->m_iHealth() > 0 && g_cl.m_local->GetActiveWeapon() && iLife == true;
}

void Chams::SetColor(Color col, IMaterial* mat) {
	if (mat)
		mat->ColorModulate(col);
	g_csgo.m_render_view->SetColorModulation(col);
}

void Chams::SetAlpha(float alpha, IMaterial* mat) {
	if (mat)
		mat->AlphaModulate(alpha);
	g_csgo.m_render_view->SetBlend(alpha);
}

void Chams::SetupMaterial(IMaterial* mat, Color col, bool z_flag, bool enabled) {
	SetColor(col);

	// mat->SetFlag( MATERIAL_VAR_HALFLAMBERT, flags );
	mat->SetFlag(MATERIAL_VAR_ZNEARER, z_flag);
	mat->SetFlag(MATERIAL_VAR_NOFOG, z_flag);
	mat->SetFlag(MATERIAL_VAR_IGNOREZ, z_flag);
	mat->SetFlag(MATERIAL_VAR_WIREFRAME, enabled);

	g_csgo.m_model_render->ForcedMaterialOverride(mat);
}

void Chams::init() {
	// find stupid materials.
	debugambientcube = g_csgo.m_material_system->FindMaterial(XOR("debug/debugambientcube"), nullptr);
	debugambientcube->IncrementReferenceCount();

	debugdrawflat = g_csgo.m_material_system->FindMaterial(XOR("debug/debugdrawflat"), nullptr);
	debugdrawflat->IncrementReferenceCount();

	// this materials are for xray 
	half_wire = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/dogtags/dogtags_lightray"), nullptr);
	half_wire->IncrementReferenceCount();

	// player body
	// setup and bind - two different bounds for each type of body part
	if (g_menu.main.misc.glow_active_mat.get() == 1)
		// glass
		custom_material = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/cologne_prediction/cologne_prediction_glass"), nullptr);

	// TODO - fix colorpicker first
	// add envmaptint finvar
	else if (g_menu.main.misc.glow_active_mat.get() == 2)
	{
		// white, enough
		static bool loaded{ false };
		if (!loaded)
		{
			std::ofstream("csgo/materials/shine_mat.vmt") << R"#("VertexLitGeneric" {
				"$additive" "1"
				"$envmap" "models/effects/cube_white"
				"$envmaptint" "[1 1 1]"
				"$envmapfresnel" "1"
				"$envmapfresnelminmaxexp" "[0 16 12]"
				"$alpha" "0.8"
			})#";
			loaded = true;
		}

		custom_material = g_csgo.m_material_system->FindMaterial(XOR("shine_mat"), nullptr);
	}

	// default green
	else if (g_menu.main.misc.glow_active_mat.get() == 3)
	{
		static bool loaded{ false };
		if (!loaded)
		{
			std::ofstream("csgo/materials/frog.vmt") << R"#("VertexLitGeneric" {
				"$additive" "1"
				"$envmap" "models/effects/cube_white"
				"$envmaptint" "[0 0.1 0.2]"
				"$envmapfresnel" "1"
				"$envmapfresnelminmaxexp" "[0 1 2]"
				"$alpha" "0.8"
			})#";
			loaded = true;
		}

		custom_material = g_csgo.m_material_system->FindMaterial(XOR("frog"), nullptr);
	}

	else if (g_menu.main.misc.glow_active_mat.get() == 4)
		custom_material = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/trophy_majors/crystal_blue"), nullptr);

	else if (g_menu.main.misc.glow_active_mat.get() == 5)
		custom_material = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/dogtags/dogtags_outline"), nullptr);

	else if (g_menu.main.misc.glow_active_mat.get() == 6)
		custom_material = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/trophy_majors/gold"), nullptr);

	else if (g_menu.main.misc.glow_active_mat.get() == 7)
		custom_material = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/wildfire_gold/wildfire_gold_detail"), nullptr);

	else if (g_menu.main.misc.glow_active_mat.get() == 8)
		custom_material = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/trophy_majors/velvet"), nullptr);

	if (g_menu.main.misc.glow_active_mat.get() > 0)
		custom_material->IncrementReferenceCount();

	// arms
	// setup and bind
	if ( g_menu.main.misc.glow_active_mat_hand.get() == 1)
		custom_material_arm = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/cologne_prediction/cologne_prediction_glass"), nullptr);

	else if (g_menu.main.misc.glow_active_mat_hand.get() == 2)
	{
		// white, enough
		static bool loaded{ false };
		if (!loaded)
		{
			std::ofstream("csgo/materials/shine_mat.vmt") << R"#("VertexLitGeneric" {
				"$additive" "1"
				"$envmap" "models/effects/cube_white"
				"$envmaptint" "[1 1 1]"
				"$envmapfresnel" "1"
				"$envmapfresnelminmaxexp" "[0 16 12]"
				"$alpha" "0.8"
			})#";
			loaded = true;
		}

		custom_material_arm = g_csgo.m_material_system->FindMaterial(XOR("shine_mat"), nullptr);
	}

	else if (g_menu.main.misc.glow_active_mat_hand.get() == 3)
	{
		static bool loaded{ false };
		if (!loaded)
		{
			// TODO
			std::ofstream("csgo/materials/frog.vmt") << R"#("VertexLitGeneric" {
				"$additive" "1"
				"$envmap" "models/effects/cube_white"
				"$envmaptint" "[0 0.1 0.2]"
				"$envmapfresnel" "1"
				"$envmapfresnelminmaxexp" "[0 1 2]"
				"$alpha" "0.8"
			})#";
			loaded = true;
		}

		custom_material_arm = g_csgo.m_material_system->FindMaterial(XOR("frog"), nullptr);
	}

	else if (g_menu.main.misc.glow_active_mat_hand.get() == 4)
		custom_material_arm = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/trophy_majors/crystal_blue"), nullptr);

	else if (g_menu.main.misc.glow_active_mat_hand.get() == 5)
		custom_material_arm = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/dogtags/dogtags_outline"), nullptr);

	else if (g_menu.main.misc.glow_active_mat_hand.get() == 6)
		custom_material_arm = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/trophy_majors/gold"), nullptr);

	else if (g_menu.main.misc.glow_active_mat_hand.get() == 7)
		custom_material_arm = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/wildfire_gold/wildfire_gold_detail"), nullptr);

	else if (g_menu.main.misc.glow_active_mat_hand.get() == 8)
		custom_material_arm = g_csgo.m_material_system->FindMaterial(XOR("models/inventory_items/trophy_majors/velvet"), nullptr);

	if (g_menu.main.misc.glow_active_mat_hand.get() > 0)
		custom_material_arm->IncrementReferenceCount();

	// white, enough
	static bool loaded{ false };
	if (!loaded)
	{
		std::ofstream("csgo/materials/fakelag_mat.vmt") << R"#("VertexLitGeneric" {
				"$additive" "1"
				"$envmap" "models/effects/cube_white"
				"$envmaptint" "[1 1 1]"
				"$envmapfresnel" "1"
				"$envmapfresnelminmaxexp" "[0 16 12]"
				"$alpha" "0.8"
			})#";
		loaded = true;
	}

	fakelag_material = g_csgo.m_material_system->FindMaterial(XOR("fakelag_mat"), nullptr);
}

bool Chams::GenerateLerpedMatrix(int index, BoneArray* out) {
	LagRecord* current_record;
	AimPlayer* data;

	Player* ent = g_csgo.m_entlist->GetClientEntity< Player* >(index);
	if (!ent)
		return false;

	if (!g_aimbot.IsValidTarget(ent))
		return false;

	data = &g_aimbot.m_players[index - 1];
	if (!data || data->m_records.empty())
		return false;

	if (data->m_records.size() < 2)
		return false;

	auto* channel_info = g_csgo.m_engine->GetNetChannelInfo();
	if (!channel_info)
		return false;

	static float max_unlag = 0.2f;
	static auto sv_maxunlag = g_csgo.m_cvar->FindVar(HASH("sv_maxunlag"));
	if (sv_maxunlag) {
		max_unlag = sv_maxunlag->GetFloat();
	}

	for (auto it = data->m_records.rbegin(); it != data->m_records.rend(); it++) {
		current_record = it->get();

		bool end = it + 1 == data->m_records.rend();

		if (current_record && current_record->valid() && (!end && ((it + 1)->get()))) {
			if (current_record->m_origin.dist_to(ent->GetAbsOrigin()) < 1.f) {
				return false;
			}

			vec3_t next = end ? ent->GetAbsOrigin() : (it + 1)->get()->m_origin;
			float  time_next = end ? ent->m_flSimulationTime() : (it + 1)->get()->m_sim_time;

			float total_latency = channel_info->GetAvgLatency(0) + channel_info->GetAvgLatency(1);
			total_latency = std::clamp(total_latency, 0.f, max_unlag);

			float correct = total_latency + g_cl.m_lerp;
			float time_delta = time_next - current_record->m_sim_time;
			float add = end ? 1.f : time_delta;
			float deadtime = current_record->m_sim_time + correct + add;

			float curtime = g_csgo.m_globals->m_curtime;
			float delta = deadtime - curtime;

			float mul = 1.f / add;
			vec3_t lerp = math::Interpolate(next, current_record->m_origin, std::clamp(delta * mul, 0.f, 1.f));

			matrix3x4_t ret[128];

			std::memcpy(ret,
				current_record->m_bones,
				sizeof(ret));

			for (size_t i{ }; i < 128; ++i) {
				vec3_t matrix_delta = current_record->m_bones[i].GetOrigin() - current_record->m_origin;
				ret[i].SetOrigin(matrix_delta + lerp);
			}

			std::memcpy(out,
				ret,
				sizeof(ret));

			return true;
		}
	}

	return false;
}

void Chams::DrawChams(void* ecx, uintptr_t ctx, const DrawModelState_t& state, const ModelRenderInfo_t& info, matrix3x4_t* bone) {

	AimPlayer* data;
	LagRecord* record;

	// this is just for sure again
	if (strstr(info.m_model->m_name, XOR("models/player")) != nullptr)
	{
		Player* m_entity = g_csgo.m_entlist->GetClientEntity<Player*>(info.m_index);

		// or crash >_< and prevents dead bodies from being colored
		if (!m_entity || m_entity->m_iHealth() < 1)
			return;

		g_csgo.m_model_render->ForcedMaterialOverride(nullptr);
		g_csgo.m_render_view->SetColorModulation(colors::white);
		g_csgo.m_render_view->SetBlend(1.f);

		bool active{ }, original_mdl{ }, xray_mdl{ }, x_glow{ };

		bool enemy = g_cl.m_local && m_entity->enemy(g_cl.m_local);

		// glow outline
		if (g_menu.main.misc.enable_glow_tex.get())
		{
			auto activation = g_menu.main.misc.enable_glow_active.GetActiveIndices();
			for (auto it = activation.begin(); it != activation.end(); it++)
			{
				// local player.
				if (*it == 0 && m_entity->m_bIsLocalPlayer())
				{
					x_glow = true;
					break;
				}

				// enemy.
				if (*it == 1 && enemy)
				{
					x_glow = true;
					break;
				}

				// teammates.
				if (*it == 2 && !m_entity->m_bIsLocalPlayer() && !enemy)
				{
					x_glow = true;
					break;
				}
			}
		}

		// draw wireframe
		if (g_menu.main.misc.enable_wireframe.get())
		{
			auto activation = g_menu.main.misc.wire_active.GetActiveIndices();
			for (auto it = activation.begin(); it != activation.end(); it++) 
			{
				// local player.
				if (*it == 0 && m_entity->m_bIsLocalPlayer())
				{
					active = true;
					break;
				}

				// enemy.
				if (*it == 1 && enemy)
				{
					active = true;
					break;
				}

				// teammates.
				if (*it == 2 && !m_entity->m_bIsLocalPlayer() && !enemy)
				{
					active = true;
					break;
				}
			}
		}

		// call orig model
		if (g_menu.main.misc.enable_model.get())
		{
			auto activation = g_menu.main.misc.model_active.GetActiveIndices();
			for (auto it = activation.begin(); it != activation.end(); it++)
			{
				// local player.
				if (*it == 0 && m_entity->m_bIsLocalPlayer())
				{
					original_mdl = true;
					break;
				}
				// enemy.
				if (*it == 1 && enemy)
				{
					original_mdl = true;
					break;
				}
				// teammates.
				if (*it == 2 && !m_entity->m_bIsLocalPlayer() && !enemy)
				{
					original_mdl = true;
					break;
				}
			}
		}

		// xray fx
		if (g_menu.main.misc.half_wire_enable.get())
		{
			auto activation = g_menu.main.misc.half_wire.GetActiveIndices();
			for (auto it = activation.begin(); it != activation.end(); it++)
			{
				// local player.
				if (*it == 0 && m_entity->m_bIsLocalPlayer())
				{
					xray_mdl = true;
					break;
				}
				// enemy.
				if (*it == 1 && enemy)
				{
					xray_mdl = true;
					break;
				}
				// teammates.
				if (*it == 2 && !m_entity->m_bIsLocalPlayer() && !enemy)
				{
					xray_mdl = true;
					break;
				}
			}
		}

		// ourself
		if (m_entity->m_bIsLocalPlayer()) 
		{
			if (g_menu.main.players.chams_local_scope.get() && /*m_entity->m_bIsScoped()*/scopeValue)
				SetAlpha(0.5f);

			else if (g_menu.main.players.chams_local.get()) 
			{

				// orig mdl
				if (original_mdl)
				{
					g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
				}

				// first
				if (g_menu.main.misc.fakelag_matrix.get())
				{
					if (fakelagmatrix)
					{
						Color colors = g_gui.m_color;	// doesn't matter
						SetAlpha(100.f / 100.f);
						SetupMaterial(fakelag_material, colors, false, false);
						g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, fakelagmatrix);
					}
				}

				// wire start
				SetAlpha(g_menu.main.players.chams_local_blend.get() / 100.f);

				// set material and color.
				if (active)
					SetupMaterial(debugambientcube, g_menu.main.players.chams_local_col.get(), false, true);
				else
					SetupMaterial(debugambientcube, g_menu.main.players.chams_local_col.get(), false, false);

				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);

				// set material and color for glow
				if (x_glow && g_menu.main.misc.glow_active_mat.get() > 0)
				{
					// glow start
					SetAlpha(g_menu.main.misc.glow_pl_blend.get() / 100.f);

					SetupMaterial(custom_material, g_menu.main.players.chams_local_col.get(), false, false);
					g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
				}

				// x ray, this btw overrides everything
				if (xray_mdl)
				{
					// override blend.
					SetAlpha(g_menu.main.misc.chams_half_wire_blend.get() / 100.f);

					// TODO separation
					SetupMaterial(half_wire, g_menu.main.players.chams_local_col.get(), false, true);
					g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
				}
			}
		}

		// history
		if (enemy && g_menu.main.players.chams_enemy_history.get())
		{
			if (g_aimbot.IsValidTarget(m_entity)) 
			{
				if (g_menu.main.players.chams_enemy_history.get()) 
				{
					data = &g_aimbot.m_players[m_entity->index() - 1];
					if (!data->m_records.empty())
					{
						record = g_resolver.FindLastRecord(data);
						if (record) 
						{
							// was the matrix properly setup?
							BoneArray arr[128];
							if (Chams::GenerateLerpedMatrix(m_entity->index(), arr)) 
							{
								// override blend.
								SetAlpha(g_menu.main.players.chams_enemy_history_blend.get() / 100.f);

								// set material and color.
								SetupMaterial(debugdrawflat, g_menu.main.players.chams_enemy_history_col.get(), true, false);

								g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, arr);
							}
						}
					}
				}
			}
		}

		// enemies
		if (enemy && g_menu.main.players.chams_enemy.get(0))
		{
			if (original_mdl)
			{
				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
			}

			if (g_menu.main.players.chams_enemy.get(1))
			{
				SetAlpha(g_menu.main.players.chams_enemy_blend.get() / 100.f);

				if (active)
					SetupMaterial(debugambientcube, g_menu.main.players.chams_enemy_invis.get(), true, true);
				else
					SetupMaterial(debugambientcube, g_menu.main.players.chams_enemy_invis.get(), true, false);

				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
			}

			// wire
			SetAlpha(g_menu.main.players.chams_enemy_blend.get() / 100.f);

			if (active)
				SetupMaterial(debugambientcube, g_menu.main.players.chams_enemy_vis.get(), false, true);
			else
				SetupMaterial(debugambientcube, g_menu.main.players.chams_enemy_vis.get(), false, false);

			g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);

			// set material for outline
			if (x_glow && g_menu.main.misc.glow_active_mat.get() > 0)
			{
				// glow start
				SetAlpha(g_menu.main.misc.glow_pl_blend.get() / 100.f);

				SetupMaterial(custom_material, g_menu.main.players.chams_enemy_vis.get(), true, false);
				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
			}

			// x ray
			if (xray_mdl)
			{
				// override blend.
				SetAlpha(g_menu.main.misc.chams_half_wire_blend.get() / 100.f);

				// TODO
				SetupMaterial(half_wire, g_menu.main.players.chams_enemy_vis.get(), true, true);
				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
			}
		}

		// teammates
		if (!m_entity->m_bIsLocalPlayer() && !enemy && g_menu.main.players.chams_friendly.get(0)) 
		{
			if (original_mdl)
			{
				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
			}

			if (g_menu.main.players.chams_friendly.get(1)) {

				SetAlpha(g_menu.main.players.chams_friendly_blend.get() / 100.f);

				if (active)
					SetupMaterial(debugambientcube, g_menu.main.players.chams_friendly_invis.get(), true, true);
				else
					SetupMaterial(debugambientcube, g_menu.main.players.chams_friendly_invis.get(), true, false);

				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
			}

			SetAlpha(g_menu.main.players.chams_friendly_blend.get() / 100.f);

			// do not mess it
			if (active)
				SetupMaterial(debugambientcube, g_menu.main.players.chams_friendly_vis.get(), false, true);
			else
				SetupMaterial(debugambientcube, g_menu.main.players.chams_friendly_vis.get(), false, false);

			g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);

			// set material and color for glow
			if (x_glow && g_menu.main.misc.glow_active_mat.get() > 0)
			{
				// glow start
				SetAlpha(g_menu.main.misc.glow_pl_blend.get() / 100.f);

				SetupMaterial(custom_material, g_menu.main.players.chams_friendly_vis.get(), true, false);
				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
			}

			// x ray
			if (xray_mdl)
			{
				// override blend.
				SetAlpha(g_menu.main.misc.chams_half_wire_blend.get() / 100.f);

				// TODO
				SetupMaterial(half_wire, g_menu.main.players.chams_friendly_vis.get(), true, true);
				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
			}
		}
	}

	// viewmodels
	if (strstr(info.m_model->m_name, XOR("arms")) != nullptr)
	{
		// make this only for ourselves
		if (IsLocalPlayerValid() && g_menu.main.misc.chams_local_hand.get())
		{
			if (g_menu.main.misc.enable_hand_model.get())
			{
				// call original arms to draw
				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
			}

			// override blend.
			SetAlpha(g_menu.main.misc.chams_local_hand_blend.get() / 100.f);

			// set material and color.
			if (g_menu.main.misc.enable_hand_wireframe.get())
				SetupMaterial(debugambientcube, g_menu.main.misc.chams_local_hand_col.get(), false, true);
			else
				SetupMaterial(debugambientcube, g_menu.main.misc.chams_local_hand_col.get(), false, false);

			g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);

			// glow outline
			if (g_menu.main.misc.enable_hand_glow.get() && g_menu.main.misc.glow_active_mat_hand.get() > 0)
			{
				// override blend.
				SetAlpha(g_menu.main.misc.chams_glow_hand_blend.get() / 100.f);

				// TODO
				SetupMaterial(custom_material_arm, g_menu.main.misc.chams_local_hand_col.get(), false, false);
				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
			}

			// x ray
			if (g_menu.main.misc.enable_hand_half_wire.get())
			{
				// override blend.
				SetAlpha(g_menu.main.misc.chams_wire_hand_blend.get() / 100.f);

				// TODO
				SetupMaterial(half_wire, g_menu.main.misc.chams_local_hand_col.get(), false, true);
				g_hooks.m_model_render.GetOldMethod< Hooks::DrawModelExecute_t >(IVModelRender::DRAWMODELEXECUTE)(ecx, ctx, state, info, bone);
			}
		}
	}
}