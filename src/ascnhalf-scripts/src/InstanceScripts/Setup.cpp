/*
 * Sun++ Scripts for Aspire MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 * Copyright (C) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "StdAfx.h"
#include "Setup.h"
#define SKIP_ALLOCATOR_SHARING 1
#include <ScriptSetup.h>

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_MISC;
}

extern "C" SCRIPT_DECL void _exp_script_register(ScriptMgr* mgr)	// Comment any script to disable it
{
	//Instances
	SetupArcatraz(mgr);
	SetupAuchenaiCrypts(mgr);
	SetupAzjolNerub(mgr);
	SetupTheBlackMorass(mgr);
	SetupBlackrockDepths(mgr);
	SetupBlackrockSpire(mgr);
	SetupBloodFurnace(mgr);
	SetupBotanica(mgr);
	SetupCullingOfStratholme(mgr);
	SetupDrakTharonKeep(mgr);
	SetupDeadmines(mgr);
	SetupDireMaul(mgr);
	SetupHellfireRamparts(mgr);
	SetupHallsOfStone(mgr);
	SetupHallsofLightning(mgr);
	SetupManaTombs(mgr);
	SetupMaraudon(mgr);
	//SetupNexus(mgr);
	SetupOldHillsbradFoothills(mgr);
	SetupRagefireChasm(mgr);
	SetupRazorfenDowns(mgr);
	SetupScarletMonastery(mgr);
	SetupScholomance(mgr);
	SetupSethekkHalls(mgr);
	SetupShadowfangKeep(mgr);
	SetupShadowLabyrinth(mgr);
	SetupTheMechanar(mgr);
	SetupTheShatteredHalls(mgr);
	SetupTheSlavePens(mgr);
	SetupTheSteamvault(mgr);
	SetupTheUnderbog(mgr);
	SetupUldaman(mgr);
	SetupUtgardeKeep(mgr);
	SetupTheStockade(mgr);
	SetupWailingCaverns(mgr);
	SetupMagistersTerrace(mgr);
	//Raids
	SetupBlackTemple(mgr);
	SetupBlackwingLair(mgr);
	SetupBattleOfMountHyjal(mgr);
	SetupGruulsLair(mgr);
	SetupKarazhan(mgr);
	SetupMoltenCore(mgr);
	SetupNaxxramas(mgr);
	SetupOnyxiasLair(mgr);
	SetupTheEye(mgr);
	//SetupTheObsidianSanctum(mgr);
	SetupUlduar(mgr);
	SetupZulFarrak(mgr);
	SetupZulGurub(mgr);
	SetupSerpentshrineCavern(mgr);
	SetupMagtheridonsLair(mgr);
	//SetupSunwellPlateau(mgr);
	SetupWorldBosses(mgr); 
	SetupZulAman(mgr);
	//Other
	//SetupGenericAI(mgr);
}

#ifdef WIN32

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    return TRUE;
}

#endif
