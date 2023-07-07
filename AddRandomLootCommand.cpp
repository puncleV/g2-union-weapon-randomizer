#include <array>
#include <set>
namespace GOTHIC_ENGINE {
	int AddRandomLoot() {
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto npcsCount = 0;
		if (world) {
			auto randomUpperBound = getRandomLootUpperound(world);
			auto hpFactor = world->GetObjectName().HasWordI("NEWWORLD") ? EXTRA_LOOT_HP_FACTOR_HORINIS : EXTRA_LOOT_HP_FACTOR_OTHER;

			auto list = world->voblist_npcs;
			for (size_t i = 0; i < list->GetNumInList(); ++i)
			{
				oCNpc* npc = list->Get(i);

				addLootToNPC(npc);
			}
		}

		return npcsCount;
	}
}