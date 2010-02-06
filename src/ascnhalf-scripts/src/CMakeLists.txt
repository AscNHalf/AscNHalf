SET(event_SRCS
   EventScripts/Event_DarkPortal.cpp
   EventScripts/Event_DarkPortal.h
   EventScripts/Halloween.cpp
   EventScripts/WinterVeil.cpp
   EventScripts/Setup.cpp
   EventScripts/Setup.h
   Common/Base.cpp
   Common/Base.h
   Common/EasyFunctions.h
   Common/Instance_Base.cpp
   Common/Instance_Base.h
)

message("* Event script sources found.")

SET(gossip_SRCS
   GossipScripts/Gossip_Battlemaster.cpp
   GossipScripts/Gossip_BoreanTundra.cpp
   GossipScripts/Gossip_DarkmoonFaire.cpp
   GossipScripts/Gossip_Innkeepers.cpp
   GossipScripts/Gossip_Moonglade.cpp
   GossipScripts/Gossip_Mulgore.cpp
   GossipScripts/Gossip_Shattrath.cpp
   GossipScripts/Gossip_Stormwind.cpp
   GossipScripts/Gossip_StrandOfTheAncients.cpp
   GossipScripts/Gossip_Tanaris.cpp
   GossipScripts/Gossip_Teldrassil.cpp
   GossipScripts/Gossip_Theramore.cpp
   GossipScripts/Gossip_Trainer.cpp
   GossipScripts/Gossip_WyrmrestTemple.cpp
   GossipScripts/Setup.cpp
   GossipScripts/Setup.h
   Common/Base.cpp
   Common/Base.h
   Common/EasyFunctions.h
   Common/Instance_Base.cpp
   Common/Instance_Base.h

)

message("* Gossip script sources found.")


SET(extra_SRCS
   ExtraScripts/NeutralGuards.cpp
   ExtraScripts/Setup.cpp
   ExtraScripts/Setup.h
   Common/Base.cpp
   Common/Base.h
   Common/EasyFunctions.h
   Common/Instance_Base.cpp
   Common/Instance_Base.h
)

message("* Extra script sources found.")

SET(spell_SRCS
   SpellHandlers/DruidSpells.cpp       
   SpellHandlers/QIspells.cpp
   SpellHandlers/HunterSpells.cpp      
   SpellHandlers/RogueSpells.cpp
   SpellHandlers/ItemSpells_1.cpp      
   SpellHandlers/MageSpells.cpp        
   SpellHandlers/ShamanSpells.cpp
   SpellHandlers/OldSpellCPPStuff.cpp  
   SpellHandlers/WarlockSpells.cpp
   SpellHandlers/PaladinSpells.cpp     
   SpellHandlers/WarriorSpells.cpp
   SpellHandlers/PriestSpells.cpp
   SpellHandlers/Setup.cpp
   SpellHandlers/Setup.h
   Common/Base.cpp
   Common/Base.h
   Common/EasyFunctions.h
   Common/Instance_Base.cpp
   Common/Instance_Base.h
)

message("* Spell Handlers found.")

SET(quest_SRCS
   QuestScripts/ArathiHighlands.cpp
   QuestScripts/Azuremyst_Isle.cpp
   QuestScripts/Azshara.cpp
   QuestScripts/BladeEdge_Mountains.cpp
   QuestScripts/BlastedLands.cpp
   QuestScripts/BloodmystIsle.cpp
   QuestScripts/Darkshore.cpp
   QuestScripts/DeathKnight.cpp
   QuestScripts/Desolace.cpp
   QuestScripts/Dragonblight.cpp
   QuestScripts/Druid.cpp
   QuestScripts/Duskwood.cpp
   QuestScripts/Dustwallow_Marsh.cpp
   QuestScripts/Eastern_Plaguelands.cpp
   QuestScripts/EversongWoods.cpp
   QuestScripts/FirstAid.cpp
   QuestScripts/Ghostlands.cpp
   QuestScripts/Hellfire_Peninsula.cpp
   QuestScripts/HillsbradFoothills.cpp
   QuestScripts/Howling_Fjord.cpp
   QuestScripts/Isle_of_QuelDanas.cpp
   QuestScripts/LochModan.cpp
   QuestScripts/Mage.cpp
   QuestScripts/Mulgore.cpp
   QuestScripts/Nagrand.cpp
   QuestScripts/Netherstorm.cpp
   QuestScripts/Old_Hillsbrad.cpp
   QuestScripts/Paladin.cpp
   QuestScripts/QuestGossip.cpp
   QuestScripts/QuestHooks.cpp
   QuestScripts/RedridgeMountains.cpp
   QuestScripts/Shadowmoon.cpp
   QuestScripts/SholazarBasin.cpp
   QuestScripts/SilvermoonCity.cpp
   QuestScripts/Silverpine_Forest.cpp
   QuestScripts/Stormwind.cpp
   QuestScripts/StranglethornVale.cpp
   QuestScripts/Tanaris.cpp
   QuestScripts/Teldrassil.cpp
   QuestScripts/Terrokar_Forest.cpp
   QuestScripts/The_Barrens.cpp
   QuestScripts/ThousandNeedles.cpp
   QuestScripts/TirisfalGlades.cpp
   QuestScripts/Undercity.cpp
   QuestScripts/UnGoro.cpp
   QuestScripts/Unsorted.cpp
   QuestScripts/Warrior.cpp
   QuestScripts/Westfall.cpp
   QuestScripts/Zangarmarsh.cpp
   QuestScripts/Setup.cpp
   QuestScripts/Setup.h
   Common/Base.cpp
   Common/Base.h
   Common/EasyFunctions.h
   Common/Instance_Base.cpp
   Common/Instance_Base.h
)

message("* Quest scripts found.")

SET(pvp_SRCS
   WorldPvPScripts/Setup.cpp
   WorldPvPScripts/ZoneTerokkarForest.cpp
   WorldPvPScripts/ZoneHellfirePeninsula.cpp
   WorldPvPScripts/ZoneZangarmarsh.cpp
   WorldPvPScripts/ZoneSilithus.cpp
   Common/Base.cpp
   Common/Base.h
   Common/EasyFunctions.h
   Common/Instance_Base.cpp
   Common/Instance_Base.h
)

message("* World PVP scripts found.")

SET(misc_SRCS
   MiscScripts/BGScripts.cpp
   MiscScripts/Creatures.cpp
   MiscScripts/DarkmoonFaireObjects.cpp
   MiscScripts/GameObjects.cpp
   MiscScripts/QuelDanasPortal.cpp
   MiscScripts/RandomScripts.cpp
   MiscScripts/Setup.cpp
   MiscScripts/Setup.h
   Common/Base.cpp
   Common/Base.h
   Common/EasyFunctions.h
   Common/Instance_Base.cpp
   Common/Instance_Base.h
)

message("* Misc scripts found.")

SET(instance_SRCS
   InstanceScripts/Instance_Arcatraz.cpp
   InstanceScripts/Instance_AuchenaiCrypts.cpp
   InstanceScripts/Instance_AzjolNerub.cpp
   InstanceScripts/Instance_BlackfathomDeeps.cpp
   InstanceScripts/Instance_BlackMorass.cpp
   InstanceScripts/Instance_BlackrockDepths.cpp
   InstanceScripts/Instance_BlackrockSpire.cpp
   InstanceScripts/Instance_BloodFurnace.cpp
   InstanceScripts/Instance_Botanica.cpp
   InstanceScripts/Instance_CullingOfStratholme.cpp
   InstanceScripts/Instance_Deadmines.cpp
   InstanceScripts/Instance_DireMaul.cpp
   InstanceScripts/Instance_DrakTharonKeep.cpp
   InstanceScripts/Instance_HallsOfLightning.cpp
   InstanceScripts/Instance_HallsOfStone.cpp
   InstanceScripts/Instance_HellfireRamparts.cpp
   InstanceScripts/Instance_MagistersTerrace.cpp
   InstanceScripts/Instance_ManaTombs.cpp
   InstanceScripts/Instance_Mauradon.cpp
   InstanceScripts/Instance_Nexus.cpp
   InstanceScripts/Instance_OldHillsbradFoothills.cpp
   InstanceScripts/Instance_RagefireChasm.cpp
   InstanceScripts/Instance_RazorfenDowns.cpp
   InstanceScripts/Instance_ScarletMonastery.cpp
   InstanceScripts/Instance_Scholomance.cpp
   InstanceScripts/Instance_SethekkHalls.cpp
   InstanceScripts/Instance_ShadowfangKeep.cpp
   InstanceScripts/Instance_ShadowLabyrinth.cpp
   InstanceScripts/Instance_TheMechanar.cpp
   InstanceScripts/Instance_TheShatteredHalls.cpp
   InstanceScripts/Instance_TheSlavePens.cpp
   InstanceScripts/Instance_TheSteamvault.cpp
   InstanceScripts/Instance_TheStockade.cpp
   InstanceScripts/Instance_TheUnderbog.cpp
   InstanceScripts/Instance_Uldaman.cpp
   InstanceScripts/Instance_UtgardeKeep.cpp
   InstanceScripts/Instance_WailingCaverns.cpp
   InstanceScripts/Instance_ZulFarrak.cpp
   InstanceScripts/Raid_BlackTemple.cpp
   InstanceScripts/Raid_BlackwingLair.cpp
   InstanceScripts/Raid_CoT_BattleOfMountHyjal.cpp
   InstanceScripts/Raid_GruulsLair.cpp
   InstanceScripts/Raid_Karazhan.cpp
   InstanceScripts/Raid_Magtheridons_Lair.cpp
   InstanceScripts/Raid_MoltenCore.cpp
   InstanceScripts/Raid_Naxxramas.cpp
   InstanceScripts/Raid_Naxxramas.h
   InstanceScripts/Raid_OnyxiasLair.cpp
   InstanceScripts/Raid_SerpentshrineCavern.cpp
   InstanceScripts/Raid_TheEye.cpp
   InstanceScripts/Raid_TheObsidianSanctum.cpp
   InstanceScripts/Raid_Ulduar.cpp
   InstanceScripts/Raid_Ulduar.h
   InstanceScripts/Raid_WorldBosses.cpp
   InstanceScripts/Raid_ZulAman.cpp
   InstanceScripts/Raid_ZulGurub.cpp
   InstanceScripts/SUNWELL_PLAT/Raid_SunwellPlateau.cpp
   InstanceScripts/SUNWELL_PLAT/SUNWELL_KALECGOS.cpp
   InstanceScripts/Setup.cpp
   InstanceScripts/Setup.h
)

message("* Instance scripts found.")

add_library(event SHARED ${event_SRCS})
add_library(gossip SHARED ${gossip_SRCS})
add_library(extra SHARED ${extra_SRCS})
add_library(spell SHARED ${spell_SRCS})
add_library(quest SHARED ${quest_SRCS})
add_library(pvp SHARED ${pvp_SRCS})
add_library(misc SHARED ${misc_SRCS})
add_library(instance SHARED ${instance_SRCS})
