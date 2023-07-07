// Supported with union (c) 2020 Union team
// Union SOURCE file

#include<array>
namespace GOTHIC_ENGINE {
	auto const SHUFFLED_AND_LOOT_ADDED_HITP = 9;

    bool oCMobContainer::isRandomized() {
        return (this->hitp & SHUFFLED_AND_LOOT_ADDED_HITP) == SHUFFLED_AND_LOOT_ADDED_HITP;
    }

    void addRandomLootToChest(oCMobContainer* chest, std::vector<Loot> lootTable = NPC_LOOT_TABLE) {
        for (size_t i = 0; i < lootTable.size(); ++i)
        {
            auto loot = lootTable[i];
            loot.tryAddToChest(chest);
        }
    }

    void exchangeContentWithAnyOtherChest(oCMobContainer* chest) {
        zCArray<zCVob*> arrMob;
        oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
        std::vector<oCMobContainer*> chestsList;

        if (world) {
            world->SearchVobListByClass(oCMobContainer::classDef, arrMob, NULL);
            for (auto i = 0; i < arrMob.GetNumInList(); i += 1) {
                chestsList.push_back(dynamic_cast<oCMobContainer*>(arrMob[i]));
            }
        }

        std::vector<oCMobContainer*> nonTouchedChests;
        for (auto i = 0; i < chestsList.size(); i += 1)
        {
            oCMobContainer* chest = chestsList[i];

            if (chest->containList.GetNumInList() > 0 && !(chest->isRandomized())) {
                nonTouchedChests.push_back(chest);
            }
        }

        for (auto attempt = 0; attempt < 3; attempt += 1) {
            auto chestToSwitchWith = randomizer.getRandomArrayElement(nonTouchedChests);

            std::vector<oCItem*> chestItems;
            std::vector<oCItem*> secondChestItems;

            for (size_t j = 0; j < chest->containList.GetNumInList(); ++j) {
                if (IsQuestItem(chest->containList[j]) || IsIgnoredOrTestItem(chest->containList[j])) {
                    continue;
                }

                chestItems.push_back(chest->containList[j]);
                chest->Remove(chest->containList[j]);
            }

            for (size_t j = 0; j < chestToSwitchWith->containList.GetNumInList(); ++j) {
                if (IsQuestItem(chestToSwitchWith->containList[j]) || IsIgnoredOrTestItem(chestToSwitchWith->containList[j])) {
                    continue;
                }

                secondChestItems.push_back(chestToSwitchWith->containList[j]);
                chestToSwitchWith->Remove(chestToSwitchWith->containList[j]);
            }

            for (size_t j = 0; j < chestItems.size(); ++j) {
                chestToSwitchWith->Insert(chestItems[j]);
            }

            for (size_t j = 0; j < secondChestItems.size(); ++j) {
                chest->Insert(secondChestItems[j]);
            }
        }

        chestsList.clear();
    }

	void oCMobContainer::randomize() {
		if (!isRandomized()) {
			oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
            
            if (SHOULD_SHUFFLE_CHESTS) {
                exchangeContentWithAnyOtherChest(this);

                this->hitp |= SHUFFLED_AND_LOOT_ADDED_HITP;
            }

            if (SHOULD_ADD_LOOT_TO_CHESTS) {
                if (randomizer.Random(0, getRandomLootUpperound(world)) <= EXTRA_LOOT_CHEST_BASE_CHANCE) {
                    addRandomLootToChest(this);
                }

                if (randomizer.Random(0, getRandomLootUpperound(world)) <= 10) {
                    addRandomLootToChest(this, bossLoot);
                }

                this->hitp |= SHUFFLED_AND_LOOT_ADDED_HITP;
            }
		}
	};
}