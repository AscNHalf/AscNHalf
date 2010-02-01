/*
 * AscNHalf MMORPG Server
 * Copyright (C) 2008 - 2009 AspireDev <http://www.aspiredev.org/>
 * Copyright (C) 2010 AscNHalf Team <http://ascnhalf.scymex.info/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdAfx.h"

// Update when new Heirlooms are added.

void Item::HeirloomInfo(ItemPrototype* proto)
{
	uint32 Itemid = proto->ItemId;

	switch(Itemid)
	{
	case 44102: // Aged Pauldrons of The Five Thunders
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 303;
			proto->ScaleFlags = 129;
		}break;

	case 42944: // Balanced Heartseeker
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 2;
			proto->ScaleFlags = 516;
		}break;

	case 44096: // Battleworn Thrash Blade
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 297;
			proto->ScaleFlags = 516;
		}break;

	case 42943: // Bloodied Arcanite Reaper
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 1;
			proto->ScaleFlags = 1032;
		}break;

	case 42950: // Champion Herod's Shoulder
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 8;
			proto->ScaleFlags = 129;
		}break;

	case 48677: // Champion's Deathdealer Breastplate
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 331;
			proto->ScaleFlags = 4194312;
		}break;

	case 42946: // Charmed Ancient Bone Bow
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 4;
			proto->ScaleFlags = 8202;
		}break;

	case 42948: // Devout Aurastone Hammer
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 6;
			proto->ScaleFlags = 34820;
		}break;

	case 42947: // Dignified Headmaster's Charge
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 5;
			proto->ScaleFlags = 36872;
		}break;

	case 42992: // Discerning Eye of the Beast
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 271;
			proto->ScaleFlags = 2;
		}break;

	case 50255: // Dread Pirate Ring
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 371;
			proto->ScaleFlags = 262144;
		}break;

	case 44103: // Exceptional Stormshroud Shoulders
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 304;
			proto->ScaleFlags = 65;
		}break;

	case 44107: // Exquisite Sunderseer Mantle
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 306;
			proto->ScaleFlags = 33;
		}break;

	case 44095: // Grand Staff of Jordan
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 296;
			proto->ScaleFlags = 36872;
		}break;

	case 44098: // Inherited Insignia of the Alliance
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 299;
			proto->ScaleFlags = 2;
		}break;

	case 44097: // Inherited Insignia of the Horde
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 298;
			proto->ScaleFlags = 2;
		}break;

	case 44105: // Lasting Feralheart Spaulders
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 305;
			proto->ScaleFlags = 65;
		}break;

	case 42951: // Mystical Pauldrons of Elements
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 9;
			proto->ScaleFlags = 129;
		}break;

	case 48683: // Mystical Vest of Elements
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 332;
			proto->ScaleFlags = 4194312;
		}break;

	case 48685: // Polished Breastplate of Valor
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 333;
			proto->ScaleFlags = 8388616;
		}break;

	case 42949: // Polished Spaulders of Valor
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 7;
			proto->ScaleFlags = 257;
		}break;

	case 48687: // Preened Ironfeather Breastplate
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 334;
			proto->ScaleFlags = 2097160;
		}break;

	case 42984: // Preened Ironfeather Shoulders
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 11;
			proto->ScaleFlags = 65;
		}break;

	case 44100: // Pristine Lightforge Spaulders
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 301;
			proto->ScaleFlags = 257;
		}break;

	case 44101: // Prized Beastmaster's Mantle
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 302;
			proto->ScaleFlags = 129;
		}break;

	case 44092: // Reforged Truesilver Champion
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 293;
			proto->ScaleFlags = 1032;
		}break;

	case 48718: // Repurposed Lava Dredger
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 352;
			proto->ScaleFlags = 1032;
		}break;

	case 44091: // Sharpened Scarlet Kris
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 292;
			proto->ScaleFlags = 516;
		}break;

	case 42952: // Stained Shadowcraft Spaulders
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 10;
			proto->ScaleFlags = 65;
		}break;

	case 48689: // Stained Shadowcraft Tunic
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 335;
			proto->ScaleFlags = 2097160;
		}break;

	case 44099: // Strengthened Stockade Pauldrons
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 300;
			proto->ScaleFlags = 257;
		}break;

	case 42991: // Swift Hand of Justice
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 251;
			proto->ScaleFlags = 2;
		}break;

	case 42985: // Tattered Dreadmist Mantle
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 16;
			proto->ScaleFlags = 33;
		}break;

	case 48691: // Tattered Dreadmist Robe
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 336;
			proto->ScaleFlags = 1048584;
		}break;

	case 44094: // The Blessed Hammer of Grace
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 295;
			proto->ScaleFlags = 34820;
		}break;

	case 44093: // Upgraded Dwarven Hand Cannon
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 294;
			proto->ScaleFlags = 8208;
		}break;

	case 42945: // Venerable Dal'Rend's Sacred Charge
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 3;
			proto->ScaleFlags = 516;
		}break;

	case 48716: // Venerable Mass of McGowan
		{
			proto->heirloom = true;
			proto->ScaleDistributeId = 351;
			proto->ScaleFlags = 516;
		}break;
	}
	return;
}
