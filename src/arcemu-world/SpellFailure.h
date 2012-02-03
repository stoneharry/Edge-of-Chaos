/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2011 <http://www.ArcEmu.org/>
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

#ifndef _SPELLFAILURE_H
#define _SPELLFAILURE_H

enum SpellCastResult
{
    SPELL_FAILED_SUCCESS                        = 0x00,
    SPELL_FAILED_AFFECTING_COMBAT               = 0x01,
    SPELL_FAILED_ALREADY_AT_FULL_HEALTH         = 0x02,
    SPELL_FAILED_ALREADY_AT_FULL_MANA           = 0x03,
    SPELL_FAILED_ALREADY_AT_FULL_POWER          = 0x04,
    SPELL_FAILED_ALREADY_BEING_TAMED            = 0x05,
    SPELL_FAILED_ALREADY_HAVE_CHARM             = 0x06,
    SPELL_FAILED_ALREADY_HAVE_SUMMON            = 0x07,
    SPELL_FAILED_ALREADY_OPEN                   = 0x08,
    SPELL_FAILED_AURA_BOUNCED                   = 0x09,
    SPELL_FAILED_AUTOTRACK_INTERRUPTED          = 0x0A,
    SPELL_FAILED_BAD_IMPLICIT_TARGETS           = 0x0B,
    SPELL_FAILED_BAD_TARGETS                    = 0x0C,
    SPELL_FAILED_CANT_BE_CHARMED                = 0x0D,
    SPELL_FAILED_CANT_BE_DISENCHANTED           = 0x0E,
    SPELL_FAILED_CANT_BE_DISENCHANTED_SKILL     = 0x0F,
    SPELL_FAILED_CANT_BE_MILLED                 = 0x10,
    SPELL_FAILED_CANT_BE_PROSPECTED             = 0x11,
    SPELL_FAILED_CANT_CAST_ON_TAPPED            = 0x12,
    SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE      = 0x13,
    SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED      = 0x14,
    SPELL_FAILED_CANT_STEALTH                   = 0x15,
    SPELL_FAILED_CASTER_AURASTATE               = 0x16,
    SPELL_FAILED_CASTER_DEAD                    = 0x17,
    SPELL_FAILED_CHARMED                        = 0x18,
    SPELL_FAILED_CHEST_IN_USE                   = 0x19,
    SPELL_FAILED_CONFUSED                       = 0x1A,
    SPELL_FAILED_DONT_REPORT                    = 0x1B,
    SPELL_FAILED_EQUIPPED_ITEM                  = 0x1C,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS            = 0x1D,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND   = 0x1E,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND    = 0x1F,
    SPELL_FAILED_ERROR                          = 0x20,
    SPELL_FAILED_FIZZLE                         = 0x21,
    SPELL_FAILED_FLEEING                        = 0x22,
    SPELL_FAILED_FOOD_LOWLEVEL                  = 0x23,
    SPELL_FAILED_HIGHLEVEL                      = 0x24,
    SPELL_FAILED_HUNGER_SATIATED                = 0x25,
    SPELL_FAILED_IMMUNE                         = 0x26,
    SPELL_FAILED_INCORRECT_AREA                 = 0x27,
    SPELL_FAILED_INTERRUPTED                    = 0x28,
    SPELL_FAILED_INTERRUPTED_COMBAT             = 0x29,
    SPELL_FAILED_ITEM_ALREADY_ENCHANTED         = 0x2A,
    SPELL_FAILED_ITEM_GONE                      = 0x2B,
    SPELL_FAILED_ITEM_NOT_FOUND                 = 0x2C,
    SPELL_FAILED_ITEM_NOT_READY                 = 0x2D,
    SPELL_FAILED_LEVEL_REQUIREMENT              = 0x2E,
    SPELL_FAILED_LINE_OF_SIGHT                  = 0x2F,
    SPELL_FAILED_LOWLEVEL                       = 0x30,
    SPELL_FAILED_LOW_CASTLEVEL                  = 0x31,
    SPELL_FAILED_MAINHAND_EMPTY                 = 0x32,
    SPELL_FAILED_MOVING                         = 0x33,
    SPELL_FAILED_NEED_AMMO                      = 0x34,
    SPELL_FAILED_NEED_AMMO_POUCH                = 0x35,
    SPELL_FAILED_NEED_EXOTIC_AMMO               = 0x36,
    SPELL_FAILED_NEED_MORE_ITEMS                = 0x37,
    SPELL_FAILED_NOPATH                         = 0x38,
    SPELL_FAILED_NOT_BEHIND                     = 0x39,
    SPELL_FAILED_NOT_FISHABLE                   = 0x3A,
    SPELL_FAILED_NOT_FLYING                     = 0x3B,
    SPELL_FAILED_NOT_HERE                       = 0x3C,
    SPELL_FAILED_NOT_INFRONT                    = 0x3D,
    SPELL_FAILED_NOT_IN_CONTROL                 = 0x3E,
    SPELL_FAILED_NOT_KNOWN                      = 0x3F,
    SPELL_FAILED_NOT_MOUNTED                    = 0x40,
    SPELL_FAILED_NOT_ON_TAXI                    = 0x41,
    SPELL_FAILED_NOT_ON_TRANSPORT               = 0x42,
    SPELL_FAILED_NOT_READY                      = 0x43,
    SPELL_FAILED_NOT_SHAPESHIFT                 = 0x44,
    SPELL_FAILED_NOT_STANDING                   = 0x45,
    SPELL_FAILED_NOT_TRADEABLE                  = 0x46,
    SPELL_FAILED_NOT_TRADING                    = 0x47,
    SPELL_FAILED_NOT_UNSHEATHED                 = 0x48,
    SPELL_FAILED_NOT_WHILE_GHOST                = 0x49,
    SPELL_FAILED_NOT_WHILE_LOOTING              = 0x4A,
    SPELL_FAILED_NO_AMMO                        = 0x4B,
    SPELL_FAILED_NO_CHARGES_REMAIN              = 0x4C,
    SPELL_FAILED_NO_CHAMPION                    = 0x4D,
    SPELL_FAILED_NO_COMBO_POINTS                = 0x4E,
    SPELL_FAILED_NO_DUELING                     = 0x4F,
    SPELL_FAILED_NO_ENDURANCE                   = 0x50,
    SPELL_FAILED_NO_FISH                        = 0x51,
    SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED    = 0x52,
    SPELL_FAILED_NO_MOUNTS_ALLOWED              = 0x53,
    SPELL_FAILED_NO_PET                         = 0x54,
    SPELL_FAILED_NO_POWER                       = 0x55,
    SPELL_FAILED_NOTHING_TO_DISPEL              = 0x56,
    SPELL_FAILED_NOTHING_TO_STEAL               = 0x57,
    SPELL_FAILED_ONLY_ABOVEWATER                = 0x58,
    SPELL_FAILED_ONLY_DAYTIME                   = 0x59,
    SPELL_FAILED_ONLY_INDOORS                   = 0x5A,
    SPELL_FAILED_ONLY_MOUNTED                   = 0x5B,
    SPELL_FAILED_ONLY_NIGHTTIME                 = 0x5C,
    SPELL_FAILED_ONLY_OUTDOORS                  = 0x5D,
    SPELL_FAILED_ONLY_SHAPESHIFT                = 0x5E,
    SPELL_FAILED_ONLY_STEALTHED                 = 0x5F,
    SPELL_FAILED_ONLY_UNDERWATER                = 0x60,
    SPELL_FAILED_OUT_OF_RANGE                   = 0x61,
    SPELL_FAILED_PACIFIED                       = 0x62,
    SPELL_FAILED_POSSESSED                      = 0x63,
    SPELL_FAILED_REAGENTS                       = 0x64,
    SPELL_FAILED_REQUIRES_AREA                  = 0x65,
    SPELL_FAILED_REQUIRES_SPELL_FOCUS           = 0x66,
    SPELL_FAILED_ROOTED                         = 0x67,
    SPELL_FAILED_SILENCED                       = 0x68,
    SPELL_FAILED_SPELL_IN_PROGRESS              = 0x69,
    SPELL_FAILED_SPELL_LEARNED                  = 0x6A,
    SPELL_FAILED_SPELL_UNAVAILABLE              = 0x6B,
    SPELL_FAILED_STUNNED                        = 0x6C,
    SPELL_FAILED_TARGETS_DEAD                   = 0x6D,
    SPELL_FAILED_TARGET_AFFECTING_COMBAT        = 0x6E,
    SPELL_FAILED_TARGET_AURASTATE               = 0x6F,
    SPELL_FAILED_TARGET_DUELING                 = 0x70,
    SPELL_FAILED_TARGET_ENEMY                   = 0x71,
    SPELL_FAILED_TARGET_ENRAGED                 = 0x72,
    SPELL_FAILED_TARGET_FRIENDLY                = 0x73,
    SPELL_FAILED_TARGET_IN_COMBAT               = 0x74,
    SPELL_FAILED_TARGET_IS_PLAYER               = 0x75,
    SPELL_FAILED_TARGET_IS_PLAYER_CONTROLLED    = 0x76,
    SPELL_FAILED_TARGET_NOT_DEAD                = 0x77,
    SPELL_FAILED_TARGET_NOT_IN_PARTY            = 0x78,
    SPELL_FAILED_TARGET_NOT_LOOTED              = 0x79,
    SPELL_FAILED_TARGET_NOT_PLAYER              = 0x7A,
    SPELL_FAILED_TARGET_NO_POCKETS              = 0x7B,
    SPELL_FAILED_TARGET_NO_WEAPONS              = 0x7C,
    SPELL_FAILED_TARGET_NO_RANGED_WEAPONS       = 0x7D,
    SPELL_FAILED_TARGET_UNSKINNABLE             = 0x7E,
    SPELL_FAILED_THIRST_SATIATED                = 0x7F,
    SPELL_FAILED_TOO_CLOSE                      = 0x80,
    SPELL_FAILED_TOO_MANY_OF_ITEM               = 0x81,
    SPELL_FAILED_TOTEM_CATEGORY                 = 0x82,
    SPELL_FAILED_TOTEMS                         = 0x83,
    SPELL_FAILED_TRY_AGAIN                      = 0x84,
    SPELL_FAILED_UNIT_NOT_BEHIND                = 0x85,
    SPELL_FAILED_UNIT_NOT_INFRONT               = 0x86,
    SPELL_FAILED_WRONG_PET_FOOD                 = 0x87,
    SPELL_FAILED_NOT_WHILE_FATIGUED             = 0x88,
    SPELL_FAILED_TARGET_NOT_IN_INSTANCE         = 0x89,
    SPELL_FAILED_NOT_WHILE_TRADING              = 0x8A,
    SPELL_FAILED_TARGET_NOT_IN_RAID             = 0x8B,
    SPELL_FAILED_TARGET_FREEFORALL              = 0x8C,
    SPELL_FAILED_NO_EDIBLE_CORPSES              = 0x8D,
    SPELL_FAILED_ONLY_BATTLEGROUNDS             = 0x8E,
    SPELL_FAILED_TARGET_NOT_GHOST               = 0x8F,
    SPELL_FAILED_TRANSFORM_UNUSABLE             = 0x90,
    SPELL_FAILED_WRONG_WEATHER                  = 0x91,
    SPELL_FAILED_DAMAGE_IMMUNE                  = 0x92,
    SPELL_FAILED_PREVENTED_BY_MECHANIC          = 0x93,
    SPELL_FAILED_PLAY_TIME                      = 0x94,
    SPELL_FAILED_REPUTATION                     = 0x95,
    SPELL_FAILED_MIN_SKILL                      = 0x96,
    SPELL_FAILED_NOT_IN_ARENA                   = 0x97,
    SPELL_FAILED_NOT_ON_SHAPESHIFT              = 0x98,
    SPELL_FAILED_NOT_ON_STEALTHED               = 0x99,
    SPELL_FAILED_NOT_ON_DAMAGE_IMMUNE           = 0x9A,
    SPELL_FAILED_NOT_ON_MOUNTED                 = 0x9B,
    SPELL_FAILED_TOO_SHALLOW                    = 0x9C,
    SPELL_FAILED_TARGET_NOT_IN_SANCTUARY        = 0x9D,
    SPELL_FAILED_TARGET_IS_TRIVIAL              = 0x9E,
    SPELL_FAILED_BM_OR_INVISGOD                 = 0x9F,
    SPELL_FAILED_EXPERT_RIDING_REQUIREMENT      = 0xA0,
    SPELL_FAILED_ARTISAN_RIDING_REQUIREMENT     = 0xA1,
    SPELL_FAILED_NOT_IDLE                       = 0xA2,
    SPELL_FAILED_NOT_INACTIVE                   = 0xA3,
    SPELL_FAILED_PARTIAL_PLAYTIME               = 0xA4,
    SPELL_FAILED_NO_PLAYTIME                    = 0xA5,
    SPELL_FAILED_NOT_IN_BATTLEGROUND            = 0xA6,
    SPELL_FAILED_NOT_IN_RAID_INSTANCE           = 0xA7,
    SPELL_FAILED_ONLY_IN_ARENA                  = 0xA8,
    SPELL_FAILED_TARGET_LOCKED_TO_RAID_INSTANCE = 0xA9,
    SPELL_FAILED_ON_USE_ENCHANT                 = 0xAA,
    SPELL_FAILED_NOT_ON_GROUND                  = 0xAB,
    SPELL_FAILED_CUSTOM_ERROR                   = 0xAC,
    SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW         = 0xAD,
    SPELL_FAILED_TOO_MANY_SOCKETS               = 0xAE,
    SPELL_FAILED_INVALID_GLYPH                  = 0xAF,
    SPELL_FAILED_UNIQUE_GLYPH                   = 0xB0,
    SPELL_FAILED_GLYPH_SOCKET_LOCKED            = 0xB1,
    SPELL_FAILED_NO_VALID_TARGETS               = 0xB2,
    SPELL_FAILED_ITEM_AT_MAX_CHARGES            = 0xB3,
    SPELL_FAILED_NOT_IN_BARBERSHOP              = 0xB4,
    SPELL_FAILED_FISHING_TOO_LOW                = 0xB5,
    SPELL_FAILED_ITEM_ENCHANT_TRADE_WINDOW      = 0xB6,
    SPELL_FAILED_SUMMON_PENDING                 = 0xB7,
    SPELL_FAILED_MAX_SOCKETS                    = 0xB8,
    SPELL_FAILED_PET_CAN_RENAME                 = 0xB9,
    SPELL_FAILED_TARGET_CANNOT_BE_RESURRECTED	= 0xBA,
    SPELL_FAILED_UNKNOWN                        = 0xBB
};
#define SPELL_CANCAST_OK SPELL_FAILED_SUCCESS

enum SpellCustomErrors
{
    SPELL_CUSTOM_ERROR_NONE                             =  0,
    SPELL_CUSTOM_ERROR_CUSTOM_MSG                       =  1, // Something bad happened, and we want to display a custom message!
    SPELL_CUSTOM_ERROR_ALEX_BROKE_QUEST                 =  2, // Alex broke your quest! Thank him later!
    SPELL_CUSTOM_ERROR_NEED_HELPLESS_VILLAGER           =  3, // This spell may only be used on Helpless Wintergarde Villagers that have not been rescued.
    SPELL_CUSTOM_ERROR_NEED_WARSONG_DISGUISE            =  4, // Requires that you be wearing the Warsong Orc Disguise.
    SPELL_CUSTOM_ERROR_REQUIRES_PLAGUE_WAGON            =  5, // You must be closer to a plague wagon in order to drop off your 7th Legion Siege Engineer.
    SPELL_CUSTOM_ERROR_CANT_TARGET_FRIENDLY_NONPARTY    =  6, // You cannot target friendly units outside your party.
    SPELL_CUSTOM_ERROR_NEED_CHILL_NYMPH                 =  7, // You must target a weakened chill nymph.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_ENKILAH               =  8, // The Imbued Scourge Shroud will only work when equipped in the Temple City of En'kilah.
    SPELL_CUSTOM_ERROR_REQUIRES_CORPSE_DUST             =  9, // Requires Corpse Dust
    SPELL_CUSTOM_ERROR_CANT_SUMMON_GARGOYLE             = 10, // You cannot summon another gargoyle yet.
    SPELL_CUSTOM_ERROR_NEED_CORPSE_DUST_IF_NO_TARGET    = 11, // Requires Corpse Dust if the target is not dead and humanoid.
    SPELL_CUSTOM_ERROR_MUST_BE_AT_SHATTERHORN           = 12, // Can only be placed near Shatterhorn
    SPELL_CUSTOM_ERROR_MUST_TARGET_PROTO_DRAKE_EGG      = 13, // You must first select a Proto-Drake Egg.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_TREE            = 14, // You must be close to a marked tree.
    SPELL_CUSTOM_ERROR_MUST_TARGET_TURKEY               = 15, // You must target a Fjord Turkey.
    SPELL_CUSTOM_ERROR_MUST_TARGET_HAWK                 = 16, // You must target a Fjord Hawk.
    SPELL_CUSTOM_ERROR_TOO_FAR_FROM_BOUY                = 17, // You are too far from the bouy.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_OIL_SLICK       = 18, // Must be used near an oil slick.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_BOUY            = 19, // You must be closer to the buoy!
    SPELL_CUSTOM_ERROR_WYRMREST_VANQUISHER              = 20, // You may only call for the aid of a Wyrmrest Vanquisher in Wyrmrest Temple, The Dragon Wastes, Galakrond's Rest or The Wicked Coil.
    SPELL_CUSTOM_ERROR_MUST_TARGET_ICE_HEART_JORMUNGAR  = 21, // That can only be used on a Ice Heart Jormungar Spawn.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_SINKHOLE        = 22, // You must be closer to a sinkhole to use your map.
    SPELL_CUSTOM_ERROR_REQUIRES_HAROLD_LANE             = 23, // You may only call down a stampede on Harold Lane.
    SPELL_CUSTOM_ERROR_REQUIRES_GAMMOTH_MAGNATAUR       = 24, // You may only use the Pouch of Crushed Bloodspore on Gammothra or other magnataur in the Bloodspore Plains and Gammoth.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_RESURRECTION_CHAMBER  = 25, // Requires the magmawyrm resurrection chamber in the back of the Maw of Neltharion.
    SPELL_CUSTOM_ERROR_CANT_CALL_WINTERGARDE_HERE       = 26, // You may only call down a Wintergarde Gryphon in Wintergarde Keep or the Carrion Fields.
    SPELL_CUSTOM_ERROR_MUST_TARGET_WILHELM              = 27, // What are you doing? Only aim that thing at Wilhelm!
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_HEALTH                = 28, // Not enough health!
    SPELL_CUSTOM_ERROR_NO_NEARBY_CORPSES                = 29, // There are no nearby corpses to use
    SPELL_CUSTOM_ERROR_TOO_MANY_GHOULS                  = 30, // You've created enough ghouls. Return to Gothik the Harvester at Death's Breach.
    SPELL_CUSTOM_ERROR_GO_FURTHER_FROM_SUNDERED_SHARD   = 31, // Your companion does not want to come here.  Go further from the Sundered Shard.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_CAT_FORM              = 32, // Must be in Cat Form
    SPELL_CUSTOM_ERROR_MUST_BE_DEATH_KNIGHT             = 33, // Only Death Knights may enter Ebon Hold.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_FERAL_FORM            = 34, // Must be in Cat Form, Bear Form, or Dire Bear Form
    SPELL_CUSTOM_ERROR_MUST_BE_NEAR_HELPLESS_VILLAGER   = 35, // You must be within range of a Helpless Wintergarde Villager.
    SPELL_CUSTOM_ERROR_CANT_TARGET_ELEMENTAL_MECHANICAL = 36, // You cannot target an elemental or mechanical corpse.
    SPELL_CUSTOM_ERROR_MUST_HAVE_USED_DALARAN_CRYSTAL   = 37, // This teleport crystal cannot be used until the teleport crystal in Dalaran has been used at least once.
    SPELL_CUSTOM_ERROR_YOU_ALREADY_HOLD_SOMETHING       = 38, // You are already holding something in your hand. You must throw the creature in your hand before picking up another.
    SPELL_CUSTOM_ERROR_YOU_DONT_HOLD_ANYTHING           = 39, // You don't have anything to throw! Find a Vargul and use Gymer Grab to pick one up!
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_VALDURAN        = 40, // Bouldercrag's War Horn can only be used within 10 yards of Valduran the Stormborn.
    SPELL_CUSTOM_ERROR_NO_PASSENGER                     = 41, // You are not carrying a passenger. There is nobody to drop off.
    SPELL_CUSTOM_ERROR_CANT_BUILD_MORE_VEHICLES         = 42, // You cannot build any more siege vehicles.
    SPELL_CUSTOM_ERROR_ALREADY_CARRYING_CRUSADER        = 43, // You are already carrying a captured Argent Crusader. You must return to the Argent Vanguard infirmary and drop off your passenger before you may pick up another.
    SPELL_CUSTOM_ERROR_CANT_DO_WHILE_ROOTED             = 44, // You can't do that while rooted.
    SPELL_CUSTOM_ERROR_REQUIRES_NEARBY_TARGET           = 45, // Requires a nearby target.
    SPELL_CUSTOM_ERROR_NOTHING_TO_DISCOVER              = 46, // Nothing left to discover.
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_TARGETS               = 47, // No targets close enough to bluff.
    SPELL_CUSTOM_ERROR_CONSTRUCT_TOO_FAR                = 48, // Your Iron Rune Construct is out of range.
    SPELL_CUSTOM_ERROR_REQUIRES_GRAND_MASTER_ENGINEER   = 49, // Requires Grand Master Engineer
    SPELL_CUSTOM_ERROR_CANT_USE_THAT_MOUNT              = 50, // You can't use that mount.
    SPELL_CUSTOM_ERROR_NOONE_TO_EJECT                   = 51, // There is nobody to eject!
    SPELL_CUSTOM_ERROR_TARGET_MUST_BE_BOUND             = 52, // The target must be bound to you.
    SPELL_CUSTOM_ERROR_TARGET_MUST_BE_UNDEAD            = 53, // Target must be undead.
    SPELL_CUSTOM_ERROR_TARGET_TOO_FAR                   = 54, // You have no target or your target is too far away.
    SPELL_CUSTOM_ERROR_MISSING_DARK_MATTER              = 55, // Missing Reagents: Dark Matter
    SPELL_CUSTOM_ERROR_CANT_USE_THAT_ITEM               = 56, // You can't use that item
    SPELL_CUSTOM_ERROR_CANT_DO_WHILE_CYCYLONED          = 57, // You can't do that while Cycloned
    SPELL_CUSTOM_ERROR_TARGET_HAS_SCROLL                = 58, // Target is already affected by a scroll
    SPELL_CUSTOM_ERROR_POISON_TOO_STRONG                = 59, // That anti-venom is not strong enough to dispel that poison
    SPELL_CUSTOM_ERROR_MUST_HAVE_LANCE_EQUIPPED         = 60, // You must have a lance equipped.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_MAIDEN          = 61, // You must be near the Maiden of Winter's Breath Lake.
    SPELL_CUSTOM_ERROR_LEARNED_EVERYTHING               = 62, // You have learned everything from that book
    SPELL_CUSTOM_ERROR_PET_IS_DEAD                      = 63, // Your pet is dead
    SPELL_CUSTOM_ERROR_NO_VALID_TARGETS                 = 64, // There are no valid targets within range.
    SPELL_CUSTOM_ERROR_GM_ONLY                          = 65, // Only GMs may use that. Your account has been reported for investigation.
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_58                = 66, // You must reach level 58 to use this portal.
    SPELL_CUSTOM_ERROR_AT_HONOR_CAP                     = 67, // You already have the maximum amount of honor.
    SPELL_CUSTOM_ERROR_68                               = 68, // ""
    SPELL_CUSTOM_ERROR_69                               = 69, // ""
    SPELL_CUSTOM_ERROR_70                               = 70, // ""
    SPELL_CUSTOM_ERROR_71                               = 71, // ""
    SPELL_CUSTOM_ERROR_72                               = 72, // ""
    SPELL_CUSTOM_ERROR_73                               = 73, // ""
    SPELL_CUSTOM_ERROR_74                               = 74, // ""
    SPELL_CUSTOM_ERROR_MUST_HAVE_DEMONIC_CIRCLE         = 75, // You must have a demonic circle active.
    SPELL_CUSTOM_ERROR_AT_MAX_RAGE                      = 76, // You already have maximum rage
    SPELL_CUSTOM_ERROR_REQUIRES_350_ENGINEERING         = 77, // Requires Engineering (350)
    SPELL_CUSTOM_ERROR_SOUL_BELONGS_TO_LICH_KING        = 78, // Your soul belongs to the Lich King
    SPELL_CUSTOM_ERROR_ATTENDANT_HAS_PONY               = 79, // Your attendant already has an Argent Pony
    SPELL_CUSTOM_ERROR_80                               = 80, // ""
    SPELL_CUSTOM_ERROR_81                               = 81, // ""
    SPELL_CUSTOM_ERROR_82                               = 82, // ""
    SPELL_CUSTOM_ERROR_MUST_HAVE_FIRE_TOTEM             = 83, // You must have a Fire Totem active.
    SPELL_CUSTOM_ERROR_CANT_TARGET_VAMPIRES             = 84, // You may not bite other vampires.
    SPELL_CUSTOM_ERROR_PET_ALREADY_AT_YOUR_LEVEL        = 85, // Your pet is already at your level.
    SPELL_CUSTOM_ERROR_MISSING_ITEM_REQUIREMENS         = 86, // You do not meet the level requirements for this item.
    SPELL_CUSTOM_ERROR_TOO_MANY_ABOMINATIONS            = 87, // There are too many Mutated Abominations.
    SPELL_CUSTOM_ERROR_ALL_POTIONS_USED                 = 88, // The potions have all been depleted by Professor Putricide.
    SPELL_CUSTOM_ERROR_89                               = 89, // ""
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_65                = 90, // Requires level 65
    SPELL_CUSTOM_ERROR_91                               = 91, // ""
    SPELL_CUSTOM_ERROR_92                               = 92, // ""
    SPELL_CUSTOM_ERROR_93                               = 93, // ""
    SPELL_CUSTOM_ERROR_94                               = 94, // ""
    SPELL_CUSTOM_ERROR_95                               = 95, // ""
    SPELL_CUSTOM_ERROR_MAX_NUMBER_OF_RECRUITS           = 96, // You already have the max number of recruits.
    SPELL_CUSTOM_ERROR_MAX_NUMBER_OF_VOLUNTEERS         = 97, // You already have the max number of volunteers.
    SPELL_CUSTOM_ERROR_FROSTMOURNE_RENDERED_RESSURECT   = 98, // Frostmourne has rendered you unable to ressurect.
    SPELL_CUSTOM_ERROR_CANT_MOUNT_WITH_SHAPESHIFT       = 99, // You can't mount while affected by that shapeshift.
};

enum PetTameFailure
{
    PETTAME_INVALIDCREATURE                                      = 1,
    PETTAME_TOOMANY                                              = 2,
    PETTAME_CREATUREALREADYOWNED                                 = 3,
    PETTAME_NOTTAMEABLE                                          = 4,
    PETTAME_ANOTHERSUMMONACTIVE                                  = 5,
    PETTAME_UNITSCANTTAME                                        = 6,
    PETTAME_NOPETAVAILABLE                                       = 7,
    PETTAME_INTERNALERROR                                        = 8,
    PETTAME_TOOHIGHLEVEL                                         = 9,
    PETTAME_DEAD                                                 = 10,
    PETTAME_NOTDEAD                                              = 11,
    PETTAME_CANTCONTROLEXOTIC                                    = 12,
    PETTAME_UNKNOWNERROR                                         = 13,
};

enum MOUNT_FAILURE
{
    ERR_MOUNT_NOTMOUNTABLE                                       = 0,
    ERR_MOUNT_TOOFARAWAY                                         = 1,
    ERR_MOUNT_ALREADYMOUNTED                                     = 2,
    ERR_MOUNT_INVALIDMOUNTEE                                     = 3,
    ERR_MOUNT_NOTYOURPET                                         = 4,
    ERR_MOUNT_OTHER                                              = 5,
    ERR_MOUNT_LOOTING                                            = 6,
    ERR_MOUNT_RACECANTMOUNT                                      = 7,
    ERR_MOUNT_SHAPESHIFTED                                       = 8,
    ERR_MOUNT_FORCEDDISMOUNT                                     = 9
};

enum DISMOUNT_FAILURE
{
    ERR_DISMOUNT_NOPET											 = 0,
    ERR_DISMOUNT_NOTMOUNTED                                      = 1,
    ERR_DISMOUNT_NOTYOURPET                                      = 2
};
#endif

