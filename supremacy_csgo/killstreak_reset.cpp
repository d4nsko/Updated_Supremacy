﻿#include "includes.h"

/*
░██████╗██╗░░░██╗██████╗░██████╗░███████╗███╗░░░███╗░█████╗░░█████╗░██╗░░░██╗  ░█████╗░░██████╗██╗░██████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔════╝████╗░████║██╔══██╗██╔══██╗╚██╗░██╔╝  ██╔══██╗██╔════╝╚═╝██╔════╝░██╔══██╗
╚█████╗░██║░░░██║██████╔╝██████╔╝█████╗░░██╔████╔██║███████║██║░░╚═╝░╚████╔╝░  ██║░░╚═╝╚█████╗░░░░██║░░██╗░██║░░██║
░╚═══██╗██║░░░██║██╔═══╝░██╔══██╗██╔══╝░░██║╚██╔╝██║██╔══██║██║░░██╗░░╚██╔╝░░  ██║░░██╗░╚═══██╗░░░██║░░╚██╗██║░░██║
██████╔╝╚██████╔╝██║░░░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║╚█████╔╝░░░██║░░░  ╚█████╔╝██████╔╝██╗╚██████╔╝╚█████╔╝
╚═════╝░░╚═════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░╚════╝░░░░╚═╝░░░  ░╚════╝░╚═════╝░╚═╝░╚═════╝░░╚════╝░
*/

hud_reset g_reset{ };

// TODO arrays...
// each variables, not array store
int iKills = 0, posX, posY;
int iTotal = 2568, iCombo = 0, iYpos, iAlpha, iFly, iOut;	//xd

// Pos
void hud_reset::SetupPosition()
{
	// store, do shit ot v2 does >_<
	iKills++, iCombo++, iTotal += 500, iYpos = 60, iAlpha = NULL, iFly = NULL, iOut = 255;

	// store all
	posX = NULL, posY = NULL;

	if (iKills >= 9) 
		iKills = 1;	// reset last
}