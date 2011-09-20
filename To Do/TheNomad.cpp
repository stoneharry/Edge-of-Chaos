#include "StdAfx.h"
#include "Setup.h"

#pragma warning(disable:4305)

//Just to organize thingies instead of using raw positions and manual spawning, this make things easier.
struct SpawnTable
{
	float x, y, z, o;
};
SpawnTable h_locs[] = 
{
	{ -8083.986, -1617.297, 133.457, 2.80 },
	{ -8102.141, -1618.892, 133.193, 0.36 },
	{ -8101.444, -1635.854, 132.833, 0.98 },
	{ -8120.060, -1631.386, 133.053, 0.61 },
	{ -8095.202, -1639.398, 132.717, 1.81 }
};

class TheNomad : public CreatureAIScript
{
protected:
	unsigned int step;
	Creature *Ghouls[4];
public:
	ADD_CREATURE_FACTORY_FUNCTION(TheNomad);
	TheNomad(Creature *pCreature) : CreatureAIScript(pCreature)
	{
		for(int i = 0; i < 4; i++)
			Ghouls[i] = NULL;
		step = 0;
		RegisterAIUpdateEvent(1000);
	}

	// This doesn't trigger nor it works..
	/*void OnSpawn()
	{
		step = 0;
		RegisterAIUpdateEvent(1000);
	}*/

	void AIUpdate()
	{
		step += 1; //step++;
		if(step == 30)
		{
			switch(rand()%4)
			{
			case 0:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "It's quiet... Too quiet.");
				break;
			case 1:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "This land is obsessed with wrath, it must be purified.");
				break;
			case 2:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Sent out on a mission to clear this land, but what if it's impossible to clear such evil?");
				break;
			case 3:
				_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Maybe I'm wrong, but maybe there is hope left in Burning Steppes. A hope to destroy evil.");
				break;
			}
		}

		if(step == 120)
		{
			for(int i = 0; i < 4; i++)
				Ghouls[i] = _unit->GetMapMgr()->GetInterface()->SpawnCreature(257002, h_locs[i].x, h_locs[i].y, h_locs[i].z, h_locs[i].o, true, true, 0, 0, 1);
		}
		else if(step == 127)
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Filthy ghouls taste your own medecine.");
			//_unit->EventAddEmote((EmoteType)14, 4000);
			//_unit->CastSpellAoF(-8096.375, -1615.144, 133.259, dbcSpell.LookupEntry(59084), true);
			for(int i = 0; i < 4; i++)
			{
				Ghouls[i]->CastSpell(Ghouls[i], dbcSpell.LookupEntry(43119), true);
				Ghouls[i]->Root();
				Ghouls[i]->Emote(EMOTE_ONE_SHOT_STUN);
				//Ghouls[i]->DealDamage(Ghouls[i], Ghouls[i]->GetUInt32Value(UNIT_FIELD_HEALTH), 0, 0, 0, true);
			}
		}
		else if(step == 131)
		{
			for(int i = 0; i < 4; i++)
			{
				Ghouls[i]->RemoveAura(43119);
				Ghouls[i]->DealDamage(Ghouls[i], Ghouls[i]->GetUInt32Value(UNIT_FIELD_HEALTH), 0, 0, 0, true);
			}
		}
		else if(step == 140)
		{
			for(int i = 0; i < 4; i++)
				Ghouls[i]->Despawn(1, 0); //Despawn the dead corpses
			step = 0; //Reset things
		}
	}
};

class TheFuckingGhouls : public CreatureAIScript
{
protected:
	bool didemote;
	//bool a_emote;
	unsigned int step;
public:
	ADD_CREATURE_FACTORY_FUNCTION(TheFuckingGhouls);
	TheFuckingGhouls(Creature *pCreature) : CreatureAIScript(pCreature)
	{
		_unit->m_noRespawn = true;
		didemote = false;
		//a_emote = false;
		step = 0;
		RegisterAIUpdateEvent(1000);
		_unit->EventAddEmote((EmoteType)449, 4000);
		_unit->Root();
	}

	void AIUpdate()
	{
		if( (didemote) && (_unit->GetPositionX() != -8075.777 || _unit->GetPositionY() != -1597.055 || _unit->GetPositionZ() != 139.321))
			_unit->GetAIInterface()->MoveTo(-8075.777, -1597.055, 139.321, 0.87);
		/*if(!a_emote)
		{
			//_unit->Emote(EMOTE_ONESHOT_EMERGE);
			_unit->EventAddEmote((EmoteType)449, 4000);
			_unit->Root();
			a_emote = true;
		}*/
		if(step < 5)
			step += 1;
		if(step == 4)
		{
			_unit->Unroot();
			didemote = true;
		}
	}
};

void SetupTheNomad(ScriptMgr *mgr)
{
	mgr->register_creature_script(257001, &TheNomad::Create);			//our little nomad xD
	mgr->register_creature_script(257002, &TheFuckingGhouls::Create);	//The ghouls must walk to the nomad and play a little visuality.
}