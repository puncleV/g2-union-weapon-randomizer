// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	auto const WEAPON_RANDOMIZED_NPC_VAR_IDX = 391;
	auto const RANGED_WEAPON_RANDOMIZED_NPC_VAR_IDX = 392;

	bool npcCanWearWeapon(oCItem* item, oCNpc* npc) {
		for (size_t i = 0; i < ITM_COND_MAX; i++)
		{
			if (item->cond_atr[i] <= 0 && item->cond_atr[i] >= NPC_ATR_MAX) {
				return false;
			}

			if (npc->attribute[item->cond_atr[i]] < item->cond_value[i])
			{
				return false;
			}
		}

		return true;
	}

	void randomizeMeleeWeapon(oCNpc* npc) {
		for (;;) {
			int weaponId = meleeWeaponsList[randomizer.Random(0, meleeWeaponsList.GetNumInList() - 1)];
			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, weaponId));

			if (npcCanWearWeapon(item, npc)) {
				auto equippedWeapon = npc->GetEquippedMeleeWeapon();

				if (equippedWeapon != nullptr) {
					if (IsIgnoredOrTestItem(equippedWeapon)) {
						npc->UnequipItem(equippedWeapon);
					}

					if (!IsIgnoredOrTestItem(equippedWeapon)) {
						npc->RemoveFromInv(equippedWeapon, 1);
					}

					equippedWeapon->Release();

					npc->PutInInv(item);
					npc->EquipItem(item);

					if (IsDual(item)) {
						auto anotherDual = FindRandomItemThatHasString(meleeWeaponsList, OppositDualHand(item));

						if (anotherDual != nullptr) {
							npc->PutInInv(anotherDual);
							npc->EquipItem(anotherDual);
							anotherDual->Release();
						}
					}
				}

				item->Release();

				break;
			}
		}
	}
	
	void randomizeRangedWeapon(oCNpc* npc) {
		auto equippedRangedItem = npc->GetEquippedRangedWeapon();

		if (npc->GetEquippedRangedWeapon() != nullptr || randomizer.Random(0, 1000) <= CHANCE_TO_ADD_RANGED_WEAPON) {
			for (;;) {
				int weaponId = rangedWeaponsList[randomizer.Random(0, rangedWeaponsList.GetNumInList() - 1)];
				oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, weaponId));

				if (npcCanWearWeapon(item, npc)) {
					if (npc->GetEquippedRangedWeapon() != nullptr) {
						npc->UnequipItem(npc->RemoveFromInv(equippedRangedItem, 1));
						equippedRangedItem->Release();
					}

					npc->PutInInv(item);
					npc->EquipItem(item);

					item->Release();

					break;
				}

			}
		}
	}

	void oCNpc::setNpcVar(int varIdx, int value = 1) {
		parser->SetInstance("NPCVARINST", this);
		parser->CallFunc(parser->GetIndex("SetNpcVar"), varIdx, value);
	}

	int oCNpc::getNpcVar(int varIdx) {
		parser->SetInstance("NPCVARINST", this);
		auto value = *(int*)parser->CallFunc(parser->GetIndex("GetNpcVar"), varIdx);

		return value;
	}


	void goThroughNpcHandlers(oCNpc* npc) {
		if (!npc) {
			return;
		}

		if (rangedWeaponsList.GetNumInList() == 0) {
			rangedWeaponsList = getRangeWeaponsList();
		}

		if (meleeWeaponsList.GetNumInList() == 0) {
			meleeWeaponsList = getMeleeWeaponsList();
		}

		if (npc != oCNpc::player && npc->IsHuman() && !npc->IsDead()) {
			if (!npc->getNpcVar(WEAPON_RANDOMIZED_NPC_VAR_IDX) && SHOULD_SHUFFLE_MELEE_WEAPON) {
				randomizeMeleeWeapon(npc);
				npc->setNpcVar(WEAPON_RANDOMIZED_NPC_VAR_IDX, 1);
			}

			if (!npc->getNpcVar(RANGED_WEAPON_RANDOMIZED_NPC_VAR_IDX) && SHOULD_SHUFFLE_RANGED_WEAPON) {
				randomizeRangedWeapon(npc);
				npc->setNpcVar(RANGED_WEAPON_RANDOMIZED_NPC_VAR_IDX, 1);
			}
		}
	}

	zCArray<oCNpc*> oCNpc::getNpcInRadius(float radius) {
		ClearVobList();
		CreateVobList(radius);

		zCArray<zCVob*> vobList = this->vobList;
		zCArray<oCNpc*> npcList;
		zCVob* pVob = NULL;
		oCNpc* npc = NULL;

		for (int i = 0; i < vobList.GetNum(); i++) {
			pVob = vobList.GetSafe(i);
			if (!pVob)
				continue;
			npc = zDYNAMIC_CAST<oCNpc>(pVob);
			if (!npc)
				continue;
			if (npc->IsDead())
				continue;

			goThroughNpcHandlers(npc);
		}

		return npcList;
	}
}