// Supported with union (c) 2020 Union team
// Union SOURCE file
namespace GOTHIC_ENGINE {
	int (*innerEvalFunc)(const zSTRING&, zSTRING&);

	int RandomiseMeleeWeapons() {
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto npcsCount = 0;

		if (world) {
			auto list = world->voblist_npcs;
			for (size_t i = 0; i < list->GetNumInList(); ++i)
			{
				oCNpc* npc = list->Get(i);

				if (npc == oCNpc::player || !npc->IsHuman())
					continue;

				randomizeMeleeWeapon(npc);
			}
		}

		return npcsCount;
	}

	int RandomiseRangedWeapons(int extraWeaponsPercent = 0) {
		rangedWeaponsList = getRangeWeaponsList();

		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto npcsCount = 0;

		if (world) {
			auto list = world->voblist_npcs;
			for (size_t i = 0; i < list->GetNumInList(); ++i)
			{
				oCNpc* npc = list->Get(i);

				if (npc == oCNpc::player || !npc->IsHuman())
					continue;

				randomizeRangedWeapon(npc);
			}
		}

		rangedWeaponsList.DeleteList();

		return npcsCount;
	}

	bool weaponRandomizerHandler(const zSTRING& inpstr, zSTRING& msg) {
		if (inpstr.HasWordI("MELEE_RANDOMIZE")) {
			auto result = RandomiseMeleeWeapons();
			msg = "Changed weapons of: " + Z result + " npcs.";

			return true;
		}

		if (inpstr.HasWordI("RANGE_RANDOMISE")) {
			auto result = RandomiseRangedWeapons(0);
			msg = "Changed weapons of: " + Z result + " npcs.";

			return true;
		}

		return false;
	}

	int ConsoleEvalFunc(const zSTRING& inpstr, zSTRING& msg) {
		if (innerEvalFunc && innerEvalFunc(inpstr, msg))
			return true;

		if (inpstr.HasWordI("punclevutils")) {
			if (inpstr.HasWordI("debug")) {
				IS_DEBUG = IS_DEBUG ? 0 : 1;
				msg = "Debug: " + IS_DEBUG;
				return true;
			}
			else {
				return weaponRandomizerHandler(inpstr, msg);
			}
		}


		return false;
	}

	void RegisterEvalFunc() {
		int evalNum = 0;

		for (int i = 1; i < zCON_MAX_EVAL; i++)
			if (zcon->evalfunc[i])
				evalNum = i;

		innerEvalFunc = zcon->evalfunc[evalNum];
		zcon->evalfunc[evalNum] = &ConsoleEvalFunc;
	}

	void RegisterCommands() {
		RegisterEvalFunc();
		zcon->Register("punclevutils RANGE_RANDOMISE", "Randomize NPCs melee weapons");
		zcon->Register("punclevutils MELEE_RANDOMIZE", "Randomize NPCs ranged weapons");
	}
}