// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
    int ShuffleHerbs() {

        auto itemsCounter = 0;
        auto world = ogame->GetGameWorld();

        if (world) {
            zCArray<zCVob*> arrMob;

            world->SearchVobListByBaseClass(oCItem::classDef, arrMob, NULL);

            zCArray<zSTRING> herbNames;
            zCArray<zVEC3> herbPositions;

            for (size_t i = 0; i < arrMob.GetNumInList(); ++i) {
                auto item = arrMob[i];
                auto itemName = item->GetObjectName();

                if (itemName.StartWith("ITPL") && !itemName.HasWordI("BEET") && !itemName.HasWordI("SUPER_HERB")) {
                    
                    herbNames.Insert(itemName);
                    herbPositions.Insert(item->GetPositionWorld());

                    item->RemoveVobFromWorld();
                    item->Release();
                }
            }

            for (size_t i = 0; i < herbNames.GetNumInList(); ++i)
            {
                itemsCounter += 1;
                auto herbName = herbNames[i];

                auto positionIndex = randomizer.Random(0, herbPositions.GetNumInList() - 1);
                auto position = herbPositions[positionIndex];

                auto herb = world->CreateVob_novt(zVOB_TYPE_ITEM, herbName);
                herb->SetPositionWorld(position);
                world->AddVob(herb);
                herb->Release();

                herbPositions.RemoveIndex(positionIndex);
            }
        }

        return itemsCounter;
    }
}