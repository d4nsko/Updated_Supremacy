#pragma once

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/

class AimbotTab : public Tab {
public:
	// col1.
	Checkbox	  enable;
	Checkbox	  silent;
	Dropdown	  selection;
	MultiDropdown hitbox;
	MultiDropdown hitbox_history;
	MultiDropdown multipoint;
	Slider		  scale;
	Slider		  body_scale;
	Slider		  minimal_damage;
	Checkbox	  minimal_damage_hp;
	Checkbox	  penetrate;
	Slider		  penetrate_minimal_damage;
	Checkbox	  penetrate_minimal_damage_hp;
	Checkbox      knifebot;
	Checkbox	  zeusbot;

	// col2.
	Dropdown      zoom;
	Checkbox      nospread;
	Checkbox      norecoil;
	Checkbox      hitchance;
	Slider	      hitchance_amount;
	Checkbox      lagfix;
	Checkbox	  correct;
	MultiDropdown baim1;
	MultiDropdown baim2;
	Slider        baim_hp;
	Keybind       baim_key;
	Keybind       override_dmg_key;
	Slider        override_dmg_value;
	Keybind		  autostop;
	Checkbox	  autostop_always_on;
	Keybind		  doubletap;

public:
	void init() {
		// title.
		SetTitle(XOR("aimbot"));

		enable.setup(XOR("enable"), XOR("enable"));
		RegisterElement(&enable);

		silent.setup(XOR("silent aimbot"), XOR("silent"));
		RegisterElement(&silent);

		selection.setup(XOR("target selection"), XOR("selection"), { XOR("distance"), XOR("crosshair"), XOR("damage"), XOR("health"), XOR("lag"), XOR("height") });
		RegisterElement(&selection);

		hitbox.setup(XOR("hitbox"), XOR("hitbox"), { XOR("head"), XOR("chest"), XOR("body"), XOR("arms"), XOR("legs") });
		RegisterElement(&hitbox);

		hitbox_history.setup(XOR("hitbox history"), XOR("hitbox_history"), { XOR("head"), XOR("chest"), XOR("body"), XOR("arms"), XOR("legs") });
		RegisterElement(&hitbox_history);

		multipoint.setup(XOR("multi-point"), XOR("multipoint"), { XOR("head"), XOR("chest"), XOR("body"), XOR("legs") });
		RegisterElement(&multipoint);

		scale.setup("", XOR("hitbox_scale"), 1.f, 100.f, false, 0, 90.f, 1.f, XOR(L"%"));
		scale.AddShowCallback(callbacks::IsMultipointOn);
		RegisterElement(&scale);

		body_scale.setup(XOR("body hitbox scale"), XOR("body_hitbox_scale"), 1.f, 100.f, true, 0, 50.f, 1.f, XOR(L"%"));
		body_scale.AddShowCallback(callbacks::IsMultipointBodyOn);
		RegisterElement(&body_scale);

		minimal_damage.setup(XOR("minimal damage"), XOR("minimal_damage"), 1.f, 100.f, true, 0, 40.f, 1.f);
		RegisterElement(&minimal_damage);

		minimal_damage_hp.setup(XOR("scale damage on hp"), XOR("minimal_damage_hp"));
		RegisterElement(&minimal_damage_hp);

		penetrate.setup(XOR("penetrate walls"), XOR("penetrate"));
		RegisterElement(&penetrate);

		penetrate_minimal_damage.setup("", XOR("penetrate_minimal_damage"), 1.f, 100.f, false, 0, 30.f, 1.f);
		penetrate_minimal_damage.AddShowCallback(callbacks::IsPenetrationOn);
		RegisterElement(&penetrate_minimal_damage);

		penetrate_minimal_damage_hp.setup(XOR("scale penetration damage on hp"), XOR("penetrate_minimal_damage_hp"));
		penetrate_minimal_damage_hp.AddShowCallback(callbacks::IsPenetrationOn);
		RegisterElement(&penetrate_minimal_damage_hp);

		knifebot.setup(XOR("aimbot with knife"), XOR("knifebot"));
		RegisterElement(&knifebot);

		zeusbot.setup(XOR("aimbot with taser"), XOR("zeusbot"));
		RegisterElement(&zeusbot);

		// col2.
		zoom.setup(XOR("auto scope"), XOR("zoom"), { XOR("off"), XOR("always"), XOR("hitchance fail") });
		RegisterElement(&zoom, 1);

		nospread.setup(XOR("compensate spread"), XOR("nospread"));
		nospread.AddShowCallback(callbacks::IsConfigNS);
		RegisterElement(&nospread, 1);

		norecoil.setup(XOR("compensate recoil"), XOR("norecoil"));
		RegisterElement(&norecoil, 1);

		hitchance.setup(XOR("hitchance"), XOR("hitchance"));
		hitchance.AddShowCallback(callbacks::IsConfigMM);
		RegisterElement(&hitchance, 1);

		hitchance_amount.setup("", XOR("hitchance_amount"), 1.f, 100.f, false, 0, 50.f, 1.f, XOR(L"%"));
		hitchance_amount.AddShowCallback(callbacks::IsConfigMM);
		hitchance_amount.AddShowCallback(callbacks::IsHitchanceOn);
		RegisterElement(&hitchance_amount, 1);

		lagfix.setup(XOR("predict fake-lag"), XOR("lagfix"));
		RegisterElement(&lagfix, 1);

		correct.setup(XOR("correct anti-aim"), XOR("correct"));
		RegisterElement(&correct, 1);

		baim1.setup(XOR("prefer body aim"), XOR("baim1"), { XOR("always"), XOR("lethal"), XOR("lethal x2"), XOR("fake"), XOR("in air") });
		RegisterElement(&baim1, 1);

		baim2.setup(XOR("only body aim"), XOR("baim2"), { XOR("always"), XOR("health"), XOR("fake"), XOR("in air") });
		RegisterElement(&baim2, 1);

		baim_hp.setup("", XOR("baim_hp"), 1.f, 50.f, false, 0, 20.f, 1.f, XOR(L"hp"));
		baim_hp.AddShowCallback(callbacks::IsBaimHealth);
		RegisterElement(&baim_hp, 1);

		baim_key.setup(XOR("smart body aim toggle"), XOR("body aim on key"));
		baim_key.SetToggleCallback(callbacks::ToggleBAIM);
		RegisterElement(&baim_key, 1);

		override_dmg_key.setup(XOR("override damage"), XOR("override_dmg"));
		override_dmg_key.SetToggleCallback(callbacks::ToggleDMG);
		RegisterElement(&override_dmg_key, 1);

		override_dmg_value.setup(" ", XOR("dmg_override"), 1.f, 100.f, false, 0, 1.f, 1.f, XOR(L"hp"));
		override_dmg_value.AddShowCallback(callbacks::IsOverrideDamage);
		RegisterElement(&override_dmg_value, 1);

		autostop_always_on.setup(XOR("automatic stop always on"), XOR("auto_stop_always"));
		RegisterElement(&autostop_always_on, 1);

		autostop.setup(XOR("automatic stop"), XOR("autostop"));
		autostop.AddShowCallback(callbacks::AUTO_STOP);
		RegisterElement(&autostop, 1);

		doubletap.setup(XOR("double tap"), XOR("doubletap"));
		doubletap.SetToggleCallback(callbacks::ToggleDT);
		RegisterElement(&doubletap, 1);
	}
};

class AntiAimTab : public Tab {
public:
	// col 1.
	Checkbox enable;
	Checkbox pitch;
	Checkbox yaw;
	Checkbox desync;
	Checkbox invert_onshot;
	Checkbox on_velocity;
	Dropdown desync_mode;
	Slider   desync_yaw;
	Keybind side_flip;
	Keybind fakeduck;
	Keybind left_side;
	Keybind right_side;
	Keybind back_side;

	// col 2.

	Checkbox      lag_enable;
	MultiDropdown lag_active;
	Dropdown      lag_mode;
	Slider        lag_limit;
	Checkbox      lag_land;
	Checkbox	  jitter;
	Slider		  jitter_yaw;
	Checkbox	  draw_angles;

public:
	void init() {
		SetTitle(XOR("anti-aim"));

		enable.setup(XOR("enable"), XOR("enable"));
		RegisterElement(&enable);

		pitch.setup(XOR("pitch"), XOR("pitch"));
		RegisterElement(&pitch);

		yaw.setup(XOR("yaw"), XOR("yaw"));
		RegisterElement(&yaw);

		desync.setup(XOR("desync"), XOR("desync"));
		RegisterElement(&desync);

		desync_mode.setup("", XOR("anti-aim desync mode"), { XOR("manual keybinds"), XOR("setup offset"),  XOR("lby based") }, false);
		RegisterElement(&desync_mode);

		desync_yaw.setup(XOR("fake offset"), XOR("desync_yaw"), 0.f, 60.f, true, 0, 0.f, 1.f);
		RegisterElement(&desync_yaw);

		side_flip.setup(XOR("inverter key"), XOR("side_flip"));
		side_flip.SetToggleCallback(callbacks::ToggleDesyncSide);
		RegisterElement(&side_flip);

		invert_onshot.setup(XOR("swap on shot"), XOR("shot_invert"));
		RegisterElement(&invert_onshot);

		on_velocity.setup(XOR("velocity switch"), XOR("on_velocity"));
		RegisterElement(&on_velocity);

		//
		left_side.setup(XOR("left keybind"), XOR("left_side"));
		left_side.SetToggleCallback(callbacks::ToggleLeftSide);
		RegisterElement(&left_side);

		right_side.setup(XOR("right keybind"), XOR("right_side"));
		right_side.SetToggleCallback(callbacks::ToggleRightSide);
		RegisterElement(&right_side);

		back_side.setup(XOR("back keybind"), XOR("back_side"));
		back_side.SetToggleCallback(callbacks::ToggleBackSide);
		RegisterElement(&back_side);

		fakeduck.setup(XOR("fake duck"), XOR("fakeduck"));
		RegisterElement(&fakeduck);

		// col 2.
		lag_enable.setup(XOR("fake-lag"), XOR("lag_enable"));
		RegisterElement(&lag_enable, 1);

		lag_active.setup("", XOR("lag_active"), { XOR("always") ,XOR("move"), XOR("air"), XOR("crouch") }, false);
		RegisterElement(&lag_active, 1);

		lag_mode.setup("", XOR("lag_mode"), { XOR("max"), XOR("break"), XOR("random"), XOR("break step") }, false);
		RegisterElement(&lag_mode, 1);

		lag_limit.setup(XOR("limit"), XOR("lag_limit"), 2, 14, true, 0, 2, 1.f);
		RegisterElement(&lag_limit, 1);

		lag_land.setup(XOR("on land"), XOR("lag_land"));
		RegisterElement(&lag_land, 1);

		jitter.setup(XOR("enable jitter"), XOR("jitter_enable"));
		RegisterElement(&jitter, 1);

		jitter_yaw.setup(XOR("jitter offset"), XOR("jitter_yaw"), 0.f, 180.f, true, 0, 0.f, 1.f);
		RegisterElement(&jitter_yaw, 1);

		draw_angles.setup(XOR("draw angles"), XOR("draw_angles"));
		RegisterElement(&draw_angles, 1);
	}
};

class PlayersTab : public Tab {
public:
	MultiDropdown box;
	Colorpicker   box_enemy;
	Colorpicker   box_friendly;
	Checkbox      dormant;
	Checkbox      offscreen;
	Colorpicker   offscreen_color;
	MultiDropdown name;
	Colorpicker   name_color;
	MultiDropdown health;
	MultiDropdown flags_enemy;
	MultiDropdown flags_friendly;
	MultiDropdown weapon;
	Dropdown      weapon_mode;
	Checkbox      ammo;
	Colorpicker   ammo_color;

	// col2.
	MultiDropdown skeleton;
	Colorpicker   skeleton_enemy;
	Colorpicker   skeleton_friendly;

	MultiDropdown glow;
	Colorpicker   glow_enemy;
	Colorpicker   glow_friendly;
	Slider        glow_blend;
	MultiDropdown chams_enemy;
	Colorpicker   chams_enemy_vis;
	Colorpicker   chams_enemy_invis;
	Slider        chams_enemy_blend;
	Checkbox      chams_enemy_history;
	Colorpicker   chams_enemy_history_col;
	Slider        chams_enemy_history_blend;
	MultiDropdown chams_friendly;
	Colorpicker   chams_friendly_vis;
	Colorpicker   chams_friendly_invis;
	Slider        chams_friendly_blend;
	Checkbox      chams_local;
	Colorpicker   chams_local_col;
	Slider        chams_local_blend;
	Checkbox      chams_local_scope;

public:
	void init() {
		SetTitle(XOR("players"));

		box.setup(XOR("boxes"), XOR("box"), { XOR("enemy"), XOR("friendly") });
		RegisterElement(&box);

		box_enemy.setup(XOR("box enemy color"), XOR("box_enemy"), { 150, 200, 60 });
		RegisterElement(&box_enemy);

		box_friendly.setup(XOR("box friendly color"), XOR("box_friendly"), { 255, 200, 0 });
		RegisterElement(&box_friendly);

		dormant.setup(XOR("dormant enemies"), XOR("dormant"));
		RegisterElement(&dormant);

		offscreen.setup(XOR("enemy offscreen esp"), XOR("offscreen"));
		RegisterElement(&offscreen);

		offscreen_color.setup(XOR("offscreen esp color"), XOR("offscreen_color"), colors::white);
		RegisterElement(&offscreen_color);

		name.setup(XOR("name"), XOR("name"), { XOR("enemy"), XOR("friendly") });
		RegisterElement(&name);

		name_color.setup(XOR("name color"), XOR("name_color"), colors::white);
		RegisterElement(&name_color);

		health.setup(XOR("health"), XOR("health"), { XOR("enemy"), XOR("friendly") });
		RegisterElement(&health);

		flags_enemy.setup(XOR("flags enemy"), XOR("flags_enemy"), { XOR("money"), XOR("armor"), XOR("scoped"), XOR("flashed"), XOR("reloading"), XOR("bomb"), XOR("fake duck"), XOR("resolver"), XOR("health") });
		RegisterElement(&flags_enemy);

		flags_friendly.setup(XOR("flags friendly"), XOR("flags_friendly"), { XOR("money"), XOR("armor"), XOR("scoped"), XOR("flashed"), XOR("reloading"), XOR("bomb"), XOR("fake duck") });
		RegisterElement(&flags_friendly);

		weapon.setup(XOR("weapon"), XOR("weapon"), { XOR("enemy"), XOR("friendly") });
		RegisterElement(&weapon);

		weapon_mode.setup("", XOR("weapon_mode"), { XOR("text"), XOR("icon"), XOR("both") }, false);
		RegisterElement(&weapon_mode);

		ammo.setup(XOR("ammo"), XOR("ammo"));
		RegisterElement(&ammo);

		ammo_color.setup(XOR("color"), XOR("ammo_color"), colors::burgundy);
		RegisterElement(&ammo_color);

		// col2.
		skeleton.setup(XOR("skeleton"), XOR("skeleton"), { XOR("enemy"), XOR("friendly") });
		RegisterElement(&skeleton, 1);

		skeleton_enemy.setup(XOR("enemy color"), XOR("skeleton_enemy"), { 255, 255, 255 });
		RegisterElement(&skeleton_enemy, 1);

		skeleton_friendly.setup(XOR("friendly color"), XOR("skeleton_friendly"), { 255, 255, 255 });
		RegisterElement(&skeleton_friendly, 1);

		glow.setup(XOR("glow"), XOR("glow"), { XOR("enemy"), XOR("friendly") });
		RegisterElement(&glow, 1);

		glow_enemy.setup(XOR("enemy color"), XOR("glow_enemy"), { 150, 200, 60 });
		RegisterElement(&glow_enemy, 1);

		glow_friendly.setup(XOR("friendly color"), XOR("glow_friendly"), { 150, 200, 60 });
		RegisterElement(&glow_friendly, 1);

		glow_blend.setup("", XOR("glow_blend"), 1.f, 100.f, false, 0, 60.f, 1.f, XOR(L"%"));
		RegisterElement(&glow_blend, 1);

		chams_enemy.setup(XOR("chams enemy"), XOR("chams_enemy"), { XOR("visible"), XOR("invisible") });
		RegisterElement(&chams_enemy, 1);

		chams_enemy_vis.setup(XOR("color visible"), XOR("chams_enemy_vis"), { 150, 200, 60 });
		RegisterElement(&chams_enemy_vis, 1);

		chams_enemy_invis.setup(XOR("color invisible"), XOR("chams_enemy_invis"), { 60, 180, 225 });
		RegisterElement(&chams_enemy_invis, 1);

		chams_enemy_blend.setup("", XOR("chams_enemy_blend"), 1.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&chams_enemy_blend, 1);

		chams_enemy_history.setup(XOR("chams history"), XOR("chams_history"));
		RegisterElement(&chams_enemy_history, 1);

		chams_enemy_history_col.setup(XOR("color"), XOR("chams_history_col"), { 255, 255, 200 });
		RegisterElement(&chams_enemy_history_col, 1);

		chams_enemy_history_blend.setup("", XOR("chams_history_blend"), 1.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&chams_enemy_history_blend, 1);

		chams_friendly.setup(XOR("chams friendly"), XOR("chams_friendly"), { XOR("visible"), XOR("invisible") });
		RegisterElement(&chams_friendly, 1);

		chams_friendly_vis.setup(XOR("color visible"), XOR("chams_friendly_vis"), { 255, 200, 0 });
		RegisterElement(&chams_friendly_vis, 1);

		chams_friendly_invis.setup(XOR("color invisible"), XOR("chams_friendly_invis"), { 255, 50, 0 });
		RegisterElement(&chams_friendly_invis, 1);

		chams_friendly_blend.setup("", XOR("chams_friendly_blend"), 1.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&chams_friendly_blend, 1);

		chams_local.setup(XOR("chams local"), XOR("chams_local"));
		RegisterElement(&chams_local, 1);

		chams_local_col.setup(XOR("color"), XOR("chams_local_col"), { 255, 255, 200 });
		RegisterElement(&chams_local_col, 1);

		chams_local_blend.setup("", XOR("chams_local_blend"), 1.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&chams_local_blend, 1);

		chams_local_scope.setup(XOR("blend when scoped"), XOR("chams_local_scope"));
		RegisterElement(&chams_local_scope, 1);
	}
};

class VisualsTab : public Tab {
public:
	Checkbox      items;
	Checkbox      ammo;
	Colorpicker   item_color;
	Checkbox      proj;
	Colorpicker   proj_color;
	MultiDropdown proj_range;
	Colorpicker   proj_range_color;
	MultiDropdown planted_c4;
	Checkbox      disableteam;
	Dropdown	  world;
	Checkbox      transparent_props;
	Checkbox      enemy_radar;

	// col2.
	Checkbox      novisrecoil;
	Checkbox      nosmoke;
	Checkbox      nofog;
	Checkbox      noflash;
	Checkbox      noscope;
	Checkbox      fov;
	Slider        fov_amt;
	Checkbox      fov_scoped;
	Checkbox      viewmodel_fov;
	Slider        viewmodel_fov_amt;
	Checkbox      spectators;
	Checkbox      force_xhair;
	Checkbox      spread_xhair;
	Colorpicker   spread_xhair_col;
	Slider        spread_xhair_blend;
	Checkbox      pen_crosshair;
	Checkbox      tracers;
	Checkbox      impact_beams;
	Colorpicker   impact_beams_color;
	Colorpicker   impact_beams_hurt_color;
	Slider        impact_beams_time;
	Keybind       thirdperson;
	Slider		  thirdperson_distance;

public:
	void init() {
		SetTitle(XOR("visuals"));

		items.setup(XOR("dropped weapons"), XOR("items"));
		RegisterElement(&items);

		ammo.setup(XOR("dropped weapons ammo"), XOR("ammo"));
		RegisterElement(&ammo);

		item_color.setup(XOR("color"), XOR("item_color"), colors::white);
		RegisterElement(&item_color);

		proj.setup(XOR("projectiles"), XOR("proj"));
		RegisterElement(&proj);

		proj_color.setup(XOR("color"), XOR("proj_color"), colors::white);
		RegisterElement(&proj_color);

		proj_range.setup(XOR("projectile range"), XOR("proj_range"), { XOR("frag"), XOR("molly") });
		RegisterElement(&proj_range);

		proj_range_color.setup(XOR("color"), XOR("proj_range_color"), colors::burgundy);
		RegisterElement(&proj_range_color);

		planted_c4.setup(XOR("planted c4"), XOR("planted_c4"), { XOR("on screen (2D)"), XOR("on bomb (3D)") });
		RegisterElement(&planted_c4);

		disableteam.setup(XOR("do not render teammates"), XOR("disableteam"));
		RegisterElement(&disableteam);

		world.setup(XOR("world"), XOR("world"), { XOR("off"), XOR("night"), XOR("fullbright") });
		world.SetCallback(Visuals::ModulateWorld);
		RegisterElement(&world);

		transparent_props.setup(XOR("transparent props"), XOR("transparent_props"));
		transparent_props.SetCallback(Visuals::ModulateWorld);
		RegisterElement(&transparent_props);

		enemy_radar.setup(XOR("force enemies on radar"), XOR("enemy_radar"));
		RegisterElement(&enemy_radar);

		// col2.
		novisrecoil.setup(XOR("remove visual recoil"), XOR("novisrecoil"));
		RegisterElement(&novisrecoil, 1);

		nosmoke.setup(XOR("remove smoke grenades"), XOR("nosmoke"));
		RegisterElement(&nosmoke, 1);

		nofog.setup(XOR("remove fog"), XOR("nofog"));
		RegisterElement(&nofog, 1);

		noflash.setup(XOR("remove flashbangs"), XOR("noflash"));
		RegisterElement(&noflash, 1);

		noscope.setup(XOR("remove scope"), XOR("noscope"));
		RegisterElement(&noscope, 1);

		fov.setup(XOR("override fov"), XOR("fov"));
		RegisterElement(&fov, 1);

		fov_amt.setup("", XOR("fov_amt"), 60.f, 140.f, false, 0, 90.f, 1.f, XOR(L"°"));
		RegisterElement(&fov_amt, 1);

		fov_scoped.setup(XOR("override fov when scoped"), XOR("fov_scoped"));
		RegisterElement(&fov_scoped, 1);

		viewmodel_fov.setup(XOR("override viewmodel fov"), XOR("viewmodel_fov"));
		RegisterElement(&viewmodel_fov, 1);

		viewmodel_fov_amt.setup("", XOR("viewmodel_fov_amt"), 60.f, 140.f, false, 0, 90.f, 1.f, XOR(L"°"));
		RegisterElement(&viewmodel_fov_amt, 1);

		spectators.setup(XOR("show spectator list"), XOR("spectators"));
		RegisterElement(&spectators, 1);

		force_xhair.setup(XOR("force crosshair"), XOR("force_xhair"));
		RegisterElement(&force_xhair, 1);

		spread_xhair.setup(XOR("visualize spread"), XOR("spread_xhair"));
		RegisterElement(&spread_xhair, 1);

		spread_xhair_col.setup(XOR("visualize spread color"), XOR("spread_xhair_col"), colors::burgundy);
		RegisterElement(&spread_xhair_col, 1);

		spread_xhair_blend.setup("", XOR("spread_xhair_blend"), 10.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&spread_xhair_blend, 1);

		pen_crosshair.setup(XOR("penetration crosshair"), XOR("pen_xhair"));
		RegisterElement(&pen_crosshair, 1);

		tracers.setup(XOR("grenade simulation"), XOR("tracers"));
		RegisterElement(&tracers, 1);

		impact_beams.setup(XOR("impact beams"), XOR("impact_beams"));
		RegisterElement(&impact_beams, 1);

		impact_beams_color.setup(XOR("impact beams color"), XOR("impact_beams_color"), colors::light_blue);
		RegisterElement(&impact_beams_color, 1);

		impact_beams_hurt_color.setup(XOR("impact beams hurt color"), XOR("impact_beams_hurt_color"), colors::red);
		RegisterElement(&impact_beams_hurt_color, 1);

		impact_beams_time.setup(XOR("impact beams time"), XOR("impact_beams_time"), 1.f, 10.f, true, 0, 1.f, 1.f, XOR(L"s"));
		RegisterElement(&impact_beams_time, 1);

		thirdperson.setup(XOR("thirdperson"), XOR("thirdperson"));
		thirdperson.SetToggleCallback(callbacks::ToggleThirdPerson);
		RegisterElement(&thirdperson, 1);

		thirdperson_distance.setup(XOR(" "), XOR("thirdperson_distance"), 50.f, 300.f, false, 0, 150.f, 1.f, XOR(L"%"));
		RegisterElement(&thirdperson_distance, 1);
	}
};

class MovementTab : public Tab {
public:
	Checkbox bhop;
	Checkbox airduck;
	Checkbox autostrafe;
	Checkbox low_velo_slide;
	Checkbox slide_on_stop;
	Keybind  fakewalk;

public:
	void init() {
		SetTitle(XOR("movement"));

		bhop.setup(XOR("automatic jump"), XOR("bhop"));
		RegisterElement(&bhop);

		airduck.setup(XOR("duck in air"), XOR("airduck"));
		RegisterElement(&airduck);

		autostrafe.setup(XOR("automatic strafe"), XOR("autostrafe"));
		RegisterElement(&autostrafe);

		fakewalk.setup(XOR("fake-walk"), XOR("fakewalk"));
		RegisterElement(&fakewalk, 1);

		low_velo_slide.setup(XOR("slide on shift"), XOR("autoslide"));
		RegisterElement(&low_velo_slide);

		slide_on_stop.setup(XOR("slide on zoom"), XOR("zoomslide"));
		RegisterElement(&slide_on_stop);
	}
};

class MiscTab : public Tab {
public:
	// col1.
	MultiDropdown buy1;
	MultiDropdown buy2;
	MultiDropdown buy3;
	MultiDropdown notifications;
	Keybind       last_tick_defuse;
	Keybind       fake_latency;
	Slider		  fake_latency_amt;
	Checkbox      chams_local_hand;
	Colorpicker   chams_local_hand_col;
	Slider        chams_local_hand_blend;

	Checkbox      enable_wireframe;
	Checkbox      enable_hand_wireframe;
	MultiDropdown wire_active;

	Checkbox      enable_model;
	Checkbox      enable_hand_model;
	MultiDropdown model_active;

	Checkbox      enable_hand_half_wire;
	Slider        chams_wire_hand_blend;

	Checkbox      enable_hand_glow;
	Slider        chams_glow_hand_blend;

	Checkbox      half_wire_enable;
	MultiDropdown half_wire;
	Slider        chams_half_wire_blend;

	Checkbox      enable_glow_tex;
	Dropdown	  glow_active_mat;
	MultiDropdown enable_glow_active;
	Slider        glow_pl_blend;
	Dropdown	  glow_active_mat_hand;

	// col2.
	Checkbox hitmarker;
	Checkbox ragdoll_force;
	Checkbox killfeed;
	Checkbox killeffect;
	Checkbox hitbox_matrix;
	Checkbox dev_cvars;
	Checkbox cheat_cvars;
	Checkbox post_process_dis;
	Checkbox killstreak_fx;
	Checkbox watermark;
	Checkbox indicators;
	Checkbox indicators_status;
	Checkbox fakelag_matrix;

public:
	void init() {
		SetTitle(XOR("misc"));

		/*buy1.setup( XOR( "auto buy items" ), XOR( "auto_buy1" ),
			{
				XOR( "galilar" ),
				XOR( "famas" ),
				XOR( "ak47" ),
				XOR( "m4a1" ),
				XOR( "m4a1_silencer" ),
				XOR( "ssg08" ),
				XOR( "aug" ),
				XOR( "sg556" ),
				XOR( "awp" ),
				XOR( "scar20" ),
				XOR( "g3sg1" ),
				XOR( "nova" ),
				XOR( "xm1014" ),
				XOR( "mag7" ),
				XOR( "m249" ),
				XOR( "negev" ),
				XOR( "mac10" ),
				XOR( "mp9" ),
				XOR( "mp7" ),
				XOR( "ump45" ),
				XOR( "p90" ),
				XOR( "bizon" ),
			} );
		RegisterElement( &buy1 );

		buy2.setup( "", XOR( "auto_buy2" ),
			{
				XOR( "glock" ),
				XOR( "hkp2000" ),
				XOR( "usp_silencer" ),
				XOR( "elite" ),
				XOR( "p250" ),
				XOR( "tec9" ),
				XOR( "fn57" ),
				XOR( "deagle" ),
			}, false );
		RegisterElement( &buy2 );

		buy3.setup( "", XOR( "auto_buy3" ),
			{
				XOR( "vest" ),
				XOR( "vesthelm" ),
				XOR( "taser" ),
				XOR( "defuser" ),
				XOR( "heavyarmor" ),
				XOR( "molotov" ),
				XOR( "incgrenade" ),
				XOR( "decoy" ),
				XOR( "flashbang" ),
				XOR( "hegrenade" ),
				XOR( "smokegrenade" ),
			}, false );
		RegisterElement( &buy3 );*/

		notifications.setup(XOR("notifications"), XOR("notifications"), { XOR("matchmaking"), XOR("damage"), XOR("purchases"), XOR("bomb"), XOR("defuse") });
		RegisterElement(&notifications);

		last_tick_defuse.setup(XOR("last tick defuse"), XOR("last_tick_defuse"));
		RegisterElement(&last_tick_defuse);

		fake_latency.setup(XOR("fake latency"), XOR("fake_latency"));
		fake_latency.SetToggleCallback(callbacks::ToggleFakeLatency);
		RegisterElement(&fake_latency);

		fake_latency_amt.setup("", XOR("fake_latency_amt"), 50.f, 200.f, false, 0, 150.f, 50.f, XOR(L"ms"));
		RegisterElement(&fake_latency_amt);

		chams_local_hand.setup(XOR("chams viewmodel"), XOR("chams_viewmodel"));
		RegisterElement(&chams_local_hand);

		chams_local_hand_col.setup(XOR("color"), XOR("chams_viewmodel_col"), { 255, 255, 200 });
		RegisterElement(&chams_local_hand_col);

		chams_local_hand_blend.setup("", XOR("chams_local_viewmodel_blend"), 1.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&chams_local_hand_blend);

		enable_hand_wireframe.setup(XOR("enable hand wireframe"), XOR("enable_hand_wireframe"));
		RegisterElement(&enable_hand_wireframe);

		enable_wireframe.setup(XOR("enable players wireframe"), XOR("enable_wireframe"));
		RegisterElement(&enable_wireframe);

		wire_active.setup("", XOR("wire_active"), { XOR("local"), XOR("enemy"), XOR("teammates") }, false);
		RegisterElement(&wire_active);

		enable_hand_model.setup(XOR("draw original hand model"), XOR("enable_hand_model"));
		RegisterElement(&enable_hand_model);

		enable_model.setup(XOR("draw original player models"), XOR("enable_model"));
		RegisterElement(&enable_model);

		model_active.setup("", XOR("model_active"), { XOR("local"), XOR("enemy"), XOR("teammates") }, false);
		RegisterElement(&model_active);

		enable_hand_half_wire.setup(XOR("apply xray hand effect"), XOR("enable_xray_model"));
		RegisterElement(&enable_hand_half_wire);

		chams_wire_hand_blend.setup("", XOR("chams_wire_viewmodel_blend"), 1.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&chams_wire_hand_blend);

		half_wire_enable.setup(XOR("apply xray player effect"), XOR("enable_xray"));
		RegisterElement(&half_wire_enable);

		half_wire.setup("", XOR("half_wire_active"), { XOR("local"), XOR("enemy"), XOR("teammates") }, false);
		RegisterElement(&half_wire);

		chams_half_wire_blend.setup("", XOR("chams_half_wire_player_blend"), 1.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&chams_half_wire_blend);

		hitmarker.setup(XOR("hitmarker"), XOR("hitmarker"));
		RegisterElement(&hitmarker, 1);

		ragdoll_force.setup(XOR("ragdoll force"), XOR("ragdoll_force"));
		RegisterElement(&ragdoll_force, 1);

		killfeed.setup(XOR("preserve killfeed"), XOR("killfeed"));
		killfeed.SetCallback(callbacks::ToggleKillfeed);
		RegisterElement(&killfeed, 1);

		killstreak_fx.setup(XOR("killstreaks"), XOR("skillstreaks"));
		RegisterElement(&killstreak_fx, 1);

		dev_cvars.setup(XOR("unlock hidden cvars"), XOR("hidden_cvars"));
		dev_cvars.SetCallback(callbacks::UnlockHiddenConvars);
		RegisterElement(&dev_cvars, 1);

		post_process_dis.setup(XOR("disable postprocess"), XOR("postprocess_disable"));
		RegisterElement(&post_process_dis, 1);

		watermark.setup(XOR("draw watermark"), XOR("draw_watermark"));
		RegisterElement(&watermark, 1);

		indicators.setup(XOR("draw indicators"), XOR("draw_indicators"));
		RegisterElement(&indicators, 1);

		indicators_status.setup(XOR("draw status"), XOR("draw_status"));
		RegisterElement(&indicators_status, 1);

		killeffect.setup(XOR("draw killeffect"), XOR("draw_killeffect"));
		RegisterElement(&killeffect, 1);

		hitbox_matrix.setup(XOR("draw hitbox matrix"), XOR("draw_hitbox_matrix"));
		RegisterElement(&hitbox_matrix, 1);

		enable_glow_tex.setup(XOR("luminate player models"), XOR("enable_glow_tex"));
		RegisterElement(&enable_glow_tex, 1);

		enable_glow_active.setup("", XOR("glow_active_tex"), { XOR("local"), XOR("enemy"), XOR("teammates") }, false);
		RegisterElement(&enable_glow_active, 1);

		glow_active_mat.setup(XOR("luminate material"), XOR("glow_active_mat"), { XOR("none"),  XOR("default"), XOR("shine"), XOR("frog"), XOR("blue"),  XOR("pulse"), XOR("gold"), XOR("wildfire"), XOR("velvet") });
		RegisterElement(&glow_active_mat, 1);

		glow_pl_blend.setup("", XOR("chams_glow_mat_player_blend"), 1.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&glow_pl_blend, 1);

		enable_hand_glow.setup(XOR("apply hand luminate"), XOR("enable_glow_model"));
		RegisterElement(&enable_hand_glow, 1);

		glow_active_mat_hand.setup(XOR("arms luminate material"), XOR("glow_active_mat_hand"), { XOR("none"),  XOR("default"), XOR("shine"), XOR("frog"), XOR("blue"),  XOR("pulse"), XOR("gold"), XOR("wildfire"), XOR("velvet") });
		RegisterElement(&glow_active_mat_hand, 1);

		chams_glow_hand_blend.setup("", XOR("chams_glow_viewmodel_blend"), 1.f, 100.f, false, 0, 100.f, 1.f, XOR(L"%"));
		RegisterElement(&chams_glow_hand_blend, 1);

		fakelag_matrix.setup(XOR("draw fakelag matrix"), XOR("fakelag_matrix"));
		RegisterElement(&fakelag_matrix, 1);
	}
};

class ConfigTab : public Tab {
public:
	Colorpicker menu_color;
	Dropdown	agent_change;
	Checkbox enable_agent;

	Dropdown mode;
	Dropdown config;
	Keybind  key1;
	Keybind  key2;
	Keybind  key3;
	Keybind  key4;
	Keybind  key5;
	Keybind  key6;
	Button   save;
	Button   load;

	Checkbox enable_skins;

	Edit     id_deagle;
	Edit     id_elite;
	Edit     id_fiveseven;
	Edit     id_glock;
	Edit     id_ak47;
	Edit     id_aug;
	Edit     id_awp;
	Edit     id_famas;
	Edit     id_g3sg1;
	Edit     id_galil;
	Edit     id_m249;
	Edit     id_m4a4;
	Edit     id_mac10;
	Edit     id_p90;
	Edit     id_ump45;
	Edit     id_xm1014;
	Edit     id_bizon;
	Edit     id_mag7;
	Edit     id_negev;
	Edit     id_sawedoff;
	Edit     id_tec9;
	Edit     id_p2000;
	Edit     id_mp7;
	Edit     id_mp9;
	Edit     id_nova;
	Edit     id_p250;
	Edit     id_scar20;
	Edit     id_sg553;
	Edit     id_ssg08;
	Edit     id_m4a1s;
	Edit     id_usps;
	Edit     id_cz75a;
	Edit     id_revolver;

	// col 2.
	Dropdown knife;
	Edit	 knife_id;
	Dropdown glove;
	Edit	 glove_id;
	Button   update_skins;
public:

	void init() {
		SetTitle(XOR("config"));

		enable_agent.setup(XOR("enable agent changer"), XOR("enable_agent_model"));
		RegisterElement(&enable_agent);

		// setup models here
		agent_change.setup(XOR("setup agent"), XOR("agent_changer"), { XOR("agent fbi"),  XOR("CS Online 2: Mila"), XOR("empty"), XOR("empty") });
		RegisterElement(&agent_change);

		enable_skins.setup(XOR("enable weapon changer"), XOR("skins_enable"));
		enable_skins.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&enable_skins);

		// weapons...
		id_deagle.setup(XOR("paintkit id"), XOR("id_deagle"), 4);
		id_deagle.SetCallback(callbacks::SkinUpdate);
		id_deagle.AddShowCallback(callbacks::DEAGLE);
		RegisterElement(&id_deagle);

		id_elite.setup(XOR("paintkit id"), XOR("id_elite"), 4);
		id_elite.SetCallback(callbacks::SkinUpdate);
		id_elite.AddShowCallback(callbacks::ELITE);
		RegisterElement(&id_elite);

		id_fiveseven.setup(XOR("paintkit id"), XOR("id_fiveseven"), 4);
		id_fiveseven.SetCallback(callbacks::SkinUpdate);
		id_fiveseven.AddShowCallback(callbacks::FIVESEVEN);
		RegisterElement(&id_fiveseven);

		id_glock.setup(XOR("paintkit id"), XOR("id_glock"), 4);
		id_glock.SetCallback(callbacks::SkinUpdate);
		id_glock.AddShowCallback(callbacks::GLOCK);
		RegisterElement(&id_glock);

		id_ak47.setup(XOR("paintkit id"), XOR("id_ak47"), 4);
		id_ak47.SetCallback(callbacks::SkinUpdate);
		id_ak47.AddShowCallback(callbacks::AK47);
		RegisterElement(&id_ak47);

		id_aug.setup(XOR("paintkit id"), XOR("id_aug"), 4);
		id_aug.SetCallback(callbacks::SkinUpdate);
		id_aug.AddShowCallback(callbacks::AUG);
		RegisterElement(&id_aug);

		id_awp.setup(XOR("paintkit id"), XOR("id_awp"), 4);
		id_awp.SetCallback(callbacks::SkinUpdate);
		id_awp.AddShowCallback(callbacks::AWP);
		RegisterElement(&id_awp);

		id_famas.setup(XOR("paintkit id"), XOR("id_famas"), 4);
		id_famas.SetCallback(callbacks::SkinUpdate);
		id_famas.AddShowCallback(callbacks::FAMAS);
		RegisterElement(&id_famas);

		id_g3sg1.setup(XOR("paintkit id"), XOR("id_g3sg1"), 4);
		id_g3sg1.SetCallback(callbacks::SkinUpdate);
		id_g3sg1.AddShowCallback(callbacks::G3SG1);
		RegisterElement(&id_g3sg1);

		id_galil.setup(XOR("paintkit id"), XOR("id_galil"), 4);
		id_galil.SetCallback(callbacks::SkinUpdate);
		id_galil.AddShowCallback(callbacks::GALIL);
		RegisterElement(&id_galil);

		id_m249.setup(XOR("paintkit id"), XOR("id_m249"), 4);
		id_m249.SetCallback(callbacks::SkinUpdate);
		id_m249.AddShowCallback(callbacks::M249);
		RegisterElement(&id_m249);

		id_m4a4.setup(XOR("paintkit id"), XOR("id_m4a4"), 4);
		id_m4a4.SetCallback(callbacks::SkinUpdate);
		id_m4a4.AddShowCallback(callbacks::M4A4);
		RegisterElement(&id_m4a4);

		id_mac10.setup(XOR("paintkit id"), XOR("id_mac10"), 4);
		id_mac10.SetCallback(callbacks::SkinUpdate);
		id_mac10.AddShowCallback(callbacks::MAC10);
		RegisterElement(&id_mac10);

		id_p90.setup(XOR("paintkit id"), XOR("id_p90"), 4);
		id_p90.SetCallback(callbacks::SkinUpdate);
		id_p90.AddShowCallback(callbacks::P90);
		RegisterElement(&id_p90);

		id_ump45.setup(XOR("paintkit id"), XOR("id_ump45"), 4);
		id_ump45.SetCallback(callbacks::SkinUpdate);
		id_ump45.AddShowCallback(callbacks::UMP45);
		RegisterElement(&id_ump45);

		id_xm1014.setup(XOR("paintkit id"), XOR("id_xm1014"), 4);
		id_xm1014.SetCallback(callbacks::SkinUpdate);
		id_xm1014.AddShowCallback(callbacks::XM1014);
		RegisterElement(&id_xm1014);

		id_bizon.setup(XOR("paintkit id"), XOR("id_bizon"), 4);
		id_bizon.SetCallback(callbacks::SkinUpdate);
		id_bizon.AddShowCallback(callbacks::BIZON);
		RegisterElement(&id_bizon);

		id_mag7.setup(XOR("paintkit id"), XOR("id_mag7"), 4);
		id_mag7.SetCallback(callbacks::SkinUpdate);
		id_mag7.AddShowCallback(callbacks::MAG7);
		RegisterElement(&id_mag7);

		id_negev.setup(XOR("paintkit id"), XOR("id_negev"), 4);
		id_negev.SetCallback(callbacks::SkinUpdate);
		id_negev.AddShowCallback(callbacks::NEGEV);
		RegisterElement(&id_negev);

		id_sawedoff.setup(XOR("paintkit id"), XOR("id_sawedoff"), 4);
		id_sawedoff.SetCallback(callbacks::SkinUpdate);
		id_sawedoff.AddShowCallback(callbacks::SAWEDOFF);
		RegisterElement(&id_sawedoff);

		id_tec9.setup(XOR("paintkit id"), XOR("id_tec9"), 4);
		id_tec9.SetCallback(callbacks::SkinUpdate);
		id_tec9.AddShowCallback(callbacks::TEC9);
		RegisterElement(&id_tec9);

		id_p2000.setup(XOR("paintkit id"), XOR("id_p2000"), 4);
		id_p2000.SetCallback(callbacks::SkinUpdate);
		id_p2000.AddShowCallback(callbacks::P2000);
		RegisterElement(&id_p2000);

		id_mp7.setup(XOR("paintkit id"), XOR("id_mp7"), 4);
		id_mp7.SetCallback(callbacks::SkinUpdate);
		id_mp7.AddShowCallback(callbacks::MP7);
		RegisterElement(&id_mp7);

		id_mp9.setup(XOR("paintkit id"), XOR("id_mp9"), 4);
		id_mp9.SetCallback(callbacks::SkinUpdate);
		id_mp9.AddShowCallback(callbacks::MP9);
		RegisterElement(&id_mp9);

		id_nova.setup(XOR("paintkit id"), XOR("id_nova"), 4);
		id_nova.SetCallback(callbacks::SkinUpdate);
		id_nova.AddShowCallback(callbacks::NOVA);
		RegisterElement(&id_nova);

		id_p250.setup(XOR("paintkit id"), XOR("id_p250"), 4);
		id_p250.SetCallback(callbacks::SkinUpdate);
		id_p250.AddShowCallback(callbacks::P250);
		RegisterElement(&id_p250);

		id_scar20.setup(XOR("paintkit id"), XOR("id_scar20"), 4);
		id_scar20.SetCallback(callbacks::SkinUpdate);
		id_scar20.AddShowCallback(callbacks::SCAR20);
		RegisterElement(&id_scar20);

		id_sg553.setup(XOR("paintkit id"), XOR("id_sg553"), 4);
		id_sg553.SetCallback(callbacks::SkinUpdate);
		id_sg553.AddShowCallback(callbacks::SG553);
		RegisterElement(&id_sg553);

		id_ssg08.setup(XOR("paintkit id"), XOR("id_ssg08"), 4);
		id_ssg08.SetCallback(callbacks::SkinUpdate);
		id_ssg08.AddShowCallback(callbacks::SSG08);
		RegisterElement(&id_ssg08);

		id_m4a1s.setup(XOR("paintkit id"), XOR("id_m4a1s"), 4);
		id_m4a1s.SetCallback(callbacks::SkinUpdate);
		id_m4a1s.AddShowCallback(callbacks::M4A1S);
		RegisterElement(&id_m4a1s);

		id_usps.setup(XOR("paintkit id"), XOR("id_usps"), 4);
		id_usps.SetCallback(callbacks::SkinUpdate);
		id_usps.AddShowCallback(callbacks::USPS);
		RegisterElement(&id_usps);

		id_cz75a.setup(XOR("paintkit id"), XOR("id_cz75a"), 4);
		id_cz75a.SetCallback(callbacks::SkinUpdate);
		id_cz75a.AddShowCallback(callbacks::CZ75A);
		RegisterElement(&id_cz75a);

		id_revolver.setup(XOR("paintkit id"), XOR("id_revolver"), 4);
		id_revolver.SetCallback(callbacks::SkinUpdate);
		id_revolver.AddShowCallback(callbacks::REVOLVER);
		RegisterElement(&id_revolver);

		knife.setup(XOR("knife model"), XOR("skins_knife_model"), { XOR("off"), XOR("bayonet"), XOR("bowie"), XOR("butterfly"), XOR("falchion"), XOR("flip"), XOR("gut"), XOR("huntsman"), XOR("karambit"), XOR("m9 bayonet"), XOR("daggers") });
		knife.SetCallback(callbacks::SkinUpdate);
		RegisterElement(&knife);

		knife_id.setup(XOR("knife paintkit id"), XOR("skins_knife_id"), 3);
		knife_id.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&knife_id);

		glove.setup(XOR("glove model"), XOR("skins_glove_model"), { XOR("off"), XOR("bloodhound"), XOR("sport"), XOR("driver"), XOR("handwraps"), XOR("moto"), XOR("specialist") });
		glove.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&glove);

		glove_id.setup(XOR("glove paintkit id"), XOR("skins_glove_id"), 3);
		glove_id.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&glove_id);

		// instead of turn on/off everytime
		update_skins.setup(XOR("update skins"));
		update_skins.SetCallback(callbacks::ForceFullUpdate);
		RegisterElement(&update_skins);

		// col 2.
		menu_color.setup(XOR("menu color"), XOR("menu_color"), colors::burgundy, &g_gui.m_color);
		RegisterElement(&menu_color, 1);

		mode.setup(XOR("safety mode"), XOR("mode"), { XOR("matchmaking"), XOR("no-spread") });
		RegisterElement(&mode, 1);

		config.setup(XOR("configuration"), XOR("cfg"), { XOR("1"), XOR("2"), XOR("3"), XOR("4"), XOR("5"), XOR("6") });
		config.RemoveFlags(ElementFlags::SAVE);
		RegisterElement(&config, 1);

		key1.setup(XOR("configuration key 1"), XOR("cfg_key1"));
		key1.RemoveFlags(ElementFlags::SAVE);
		key1.SetCallback(callbacks::SaveHotkeys);
		key1.AddShowCallback(callbacks::IsConfig1);
		key1.SetToggleCallback(callbacks::ConfigLoad1);
		RegisterElement(&key1, 1);

		key2.setup(XOR("configuration key 2"), XOR("cfg_key2"));
		key2.RemoveFlags(ElementFlags::SAVE);
		key2.SetCallback(callbacks::SaveHotkeys);
		key2.AddShowCallback(callbacks::IsConfig2);
		key2.SetToggleCallback(callbacks::ConfigLoad2);
		RegisterElement(&key2, 1);

		key3.setup(XOR("configuration key 3"), XOR("cfg_key3"));
		key3.RemoveFlags(ElementFlags::SAVE);
		key3.SetCallback(callbacks::SaveHotkeys);
		key3.AddShowCallback(callbacks::IsConfig3);
		key3.SetToggleCallback(callbacks::ConfigLoad3);
		RegisterElement(&key3, 1);

		key4.setup(XOR("configuration key 4"), XOR("cfg_key4"));
		key4.RemoveFlags(ElementFlags::SAVE);
		key4.SetCallback(callbacks::SaveHotkeys);
		key4.AddShowCallback(callbacks::IsConfig4);
		key4.SetToggleCallback(callbacks::ConfigLoad4);
		RegisterElement(&key4, 1);

		key5.setup(XOR("configuration key 5"), XOR("cfg_key5"));
		key5.RemoveFlags(ElementFlags::SAVE);
		key5.SetCallback(callbacks::SaveHotkeys);
		key5.AddShowCallback(callbacks::IsConfig5);
		key5.SetToggleCallback(callbacks::ConfigLoad5);
		RegisterElement(&key5, 1);

		key6.setup(XOR("configuration key 6"), XOR("cfg_key6"));
		key6.RemoveFlags(ElementFlags::SAVE);
		key6.SetCallback(callbacks::SaveHotkeys);
		key6.AddShowCallback(callbacks::IsConfig6);
		key6.SetToggleCallback(callbacks::ConfigLoad6);
		RegisterElement(&key6, 1);

		save.setup(XOR("save"));
		save.SetCallback(callbacks::ConfigSave);
		RegisterElement(&save, 1);

		load.setup(XOR("load"));
		load.SetCallback(callbacks::ConfigLoad);
		RegisterElement(&load, 1);
	}
};

class MainForm : public Form {
public:
	// aimbot.
	AimbotTab    aimbot;
	AntiAimTab   antiaim;

	// visuals.
	PlayersTab	 players;
	VisualsTab	 visuals;

	// misc.
	MovementTab  movement;
	MiscTab	     misc;
	ConfigTab	 config;

public:
	void init() {
		SetPosition(50, 50);
		SetSize(630, 500);

		// aim.
		RegisterTab(&aimbot);
		aimbot.init();

		RegisterTab(&antiaim);
		antiaim.init();

		// visuals.
		RegisterTab(&players);
		players.init();

		RegisterTab(&visuals);
		visuals.init();

		// misc.
		RegisterTab(&movement);
		movement.init();

		RegisterTab(&misc);
		misc.init();

		RegisterTab(&config);
		config.init();
	}
};

class Menu {
public:
	MainForm main;

public:
	void init() {

		Colorpicker::init();	// points here, so this was the second injection crash problem, moved here to fix bound bug, look at colorpicker init

		g_notify.add(tfm::format(XOR("Colorpicker successfully initialized\n")));

		main.init();

		g_gui.RegisterForm(&main, VK_END);
	}
};

extern Menu g_menu;