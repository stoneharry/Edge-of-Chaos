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

#include "StdAfx.h"

class HandofReckoningDamage : public Spell
{
	SPELL_FACTORY_FUNCTION(HandofReckoningDamage);
	void DoAfterHandleEffect(Unit* target, uint32 i)
	{
		if(target && target->IsTauntable() && u_caster)
			u_caster->CastSpell(target, 67485, true);
	}
}

void SpellFactoryMgr::SetupPaladin()
{
	AddSpellById(62124, &HandofReckoningDamage::Create);
}
