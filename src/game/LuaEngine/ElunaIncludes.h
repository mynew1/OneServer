/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

// Required
#include "AccountMgr.h"
#include "AuctionHouseMgr.h"
#include "Cell.h"
#include "CellImpl.h"
#include "Chat.h"
#include "Channel.h"
#include "DBCStores.h"
#include "GossipDef.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Group.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Language.h"
#include "Mail.h"
#include "MapManager.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Player.h"
#include "Pet.h"
#include "ReputationMgr.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellMgr.h"
#include "TemporarySummon.h"
#include "WorldPacket.h"
#include "WorldSession.h"

#ifdef TRINITY
#include "Config.h"
#include "ScriptedCreature.h"
#include "SpellInfo.h"
#include "WeatherMgr.h"
#include "Battleground.h"
#include "revision.h"
#else
#include "Config/Config.h"
#include "AggressorAI.h"
#include "revision_nr.h"
#include "BattleGroundMgr.h"
#endif

#if (!defined(TBC) && !defined(CLASSIC))
#include "Vehicle.h"
#endif

#ifndef CLASSIC
#include "ArenaTeam.h"
#endif

#ifndef CLASSIC
typedef Opcodes                 OpcodesList;
#endif

#ifdef MANGOS
#define CORE_NAME               "MaNGOS"
#define CORE_VERSION            REVISION_NR
#endif

#ifdef CMANGOS
#define CORE_NAME               "cMaNGOS"
#define CORE_VERSION            REVISION_NR
#endif

#ifdef TRINITY
#define CORE_NAME               "TrinityCore"
#define CORE_VERSION            _DATE
#define eWorld                  (sWorld)
#define eMapMgr                 (sMapMgr)
#define eConfigMgr              (sConfigMgr)
#define eGuildMgr               (sGuildMgr)
#define eObjectMgr              (sObjectMgr)
#define eAccountMgr             (sAccountMgr)
#define eObjectAccessor         (sObjectAccessor)
#define REGEN_TIME_FULL
typedef ThreatContainer::StorageType ThreatList;

#ifdef CATA
#define NUM_MSG_TYPES           NUM_OPCODE_HANDLERS
#endif
#endif

#ifndef TRINITY
#define eWorld                  (&sWorld)
#define eMapMgr                 (&sMapMgr)
#define eConfigMgr              (&sConfig)
#define eGuildMgr               (&sGuildMgr)
#define eObjectMgr              (&sObjectMgr)
#define eAccountMgr             (&sAccountMgr)
#define eObjectAccessor         (&sObjectAccessor)
#define SERVER_MSG_STRING       SERVER_MSG_CUSTOM
#define TOTAL_LOCALES           MAX_LOCALE
#define DIALOG_STATUS_SCRIPTED_NO_STATUS    DIALOG_STATUS_UNDEFINED
#define TARGETICONCOUNT         TARGET_ICON_COUNT
#define MAX_TALENT_SPECS        MAX_TALENT_SPEC_COUNT

#ifndef CLASSIC
#define PLAYER_FIELD_LIFETIME_HONORABLE_KILLS   PLAYER_FIELD_LIFETIME_HONORBALE_KILLS
#endif

#ifdef TBC
#define SPELL_AURA_MOD_KILL_XP_PCT  SPELL_AURA_MOD_XP_PCT
#endif

typedef TemporarySummon TempSummon;
typedef SpellEntry SpellInfo;
enum SelectAggroTarget
{
    SELECT_TARGET_RANDOM = 0,   // Just selects a random target
    SELECT_TARGET_TOPAGGRO,     // Selects targes from top aggro to bottom
    SELECT_TARGET_BOTTOMAGGRO,  // Selects targets from bottom aggro to top
    SELECT_TARGET_NEAREST,
    SELECT_TARGET_FARTHEST
};
#endif
