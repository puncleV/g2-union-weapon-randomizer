// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	const int BIT_ITEM_QUESTITEM = (1 << 19);

	bool IsQuestItem(oCItem* item) {
		if ((item->hitp & BIT_ITEM_QUESTITEM) != 0) {
			return true;
		}
		return false;
	}

	bool IsIgnoredOrTestItem(oCItem* item) {
		return item == nullptr || item->GetObjectName().HasWordI("ITMW_TEST") || item->GetObjectName().HasWordI("BELIAR") || item->GetObjectName().HasWordI("URIZEL") || item->GetObjectName().HasWordI("FERROSSWORD") ||
			item->GetObjectName().HasWordI("ABIGEILSPAGE") || item->GetObjectName().HasWordI("TRIBUTEDAGGER") || item->GetObjectName().HasWordI("ITNW_2H_KATANA") || item->GetObjectName().HasWordI("TARACOT") ||
			item->GetObjectName().HasWordI("ADANOSMOLOT") || item->GetObjectName().HasWordI("ASSBLADE") || item->GetObjectName().HasWordI("HOLY_HAMMER") || item->GetObjectName().HasWordI("ALRIKSSWORD") ||
			item->GetObjectName().HasWordI("ITMW_2H_ROD") || item->GetObjectName().HasWordI("DS_MONWEAPON_HALLOWEEN") || item->GetObjectName().HasWordI("GREATARBALET") || item->GetObjectName().HasWordI("MAGICCOSSBOW") ||
			item->GetObjectName().HasWordI("FAKESWORD") || item->GetObjectName().HasWordI("PAL_CLOACK") || item->GetObjectName().HasWordI("SENYAK") || item->GetObjectName().HasWordI("HALLEBERDE_CLAW") || item->GetObjectName().HasWordI("ITMW_STAFF_CLAW") ||
			item->GetObjectName().HasWordI("ITMW_1H_THIEF_01_RIGHT");
	}

	bool IsItemSymbol(zCPar_Symbol* symbol) {
		if (symbol->type != zPAR_TYPE_INSTANCE) {
			return false;
		}

		//  Instance isn't global scope
		if (symbol->name.HasWord(".")) {
			return false;
		}

		auto baseClass = parser->GetBaseClass(symbol);

		// Symbol isn't a item class
		if (baseClass != parser->GetIndex(oCItem::classDef->scriptClassName)) {
			return false;
		}

		return true;
	}

	// duals - LEFT RIGHT
	zCArray<int> getMeleeWeaponsList() {
		zCArray<int> weapons_list;

		auto c_item = parser->GetIndex(oCItem::classDef->scriptClassName);
		if (c_item == -1) {
			return 0;
		}

		int itemsCreated = 0;
		for (int i = 0; i < parser->symtab.GetNumInList(); i++) {
			zCPar_Symbol* symbol = parser->symtab.table[i];

			if (i == parser->instance_help) {
				continue;
			}

			if (!IsItemSymbol(symbol)) {
				continue;
			}

			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, i));

			if (item == nullptr || item->mainflag != ITM_CAT_NF || item->HasFlag(ITM_FLAG_SHIELD) || IsIgnoredOrTestItem(item)) {
				continue;
			}

			item->Release();

			weapons_list.Insert(i);
		}

		return weapons_list;
	}

	zCArray<int> getRangeWeaponsList() {
		zCArray<int> weapons_list;
		auto c_item = parser->GetIndex(oCItem::classDef->scriptClassName);
		if (c_item == -1) {
			return 0;
		}

		int itemsCreated = 0;
		for (int i = 0; i < parser->symtab.GetNumInList(); i++) {
			zCPar_Symbol* symbol = parser->symtab.table[i];

			if (i == parser->instance_help) {
				continue;
			}

			if (!IsItemSymbol(symbol)) {
				continue;
			}

			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, i));

			if (item == nullptr || item->mainflag != ITM_CAT_FF || IsIgnoredOrTestItem(item)) {
				continue;
			}
			item->Release();

			weapons_list.Insert(i);
		}

		return weapons_list;
	}

	oCItem* FindRandomItemThatHasString(zCArray<int> itemsList, zSTRING string) {

		for (auto iterator = 0;iterator < itemsList.GetNumInList();iterator += 1)
		{
			int itemId = itemsList[iterator];

			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob(zVOB_TYPE_ITEM, itemId));

			if (item->GetObjectName().HasWordI(string)) {
				return item;
			}

			item->Release();
		}

		return nullptr;
	}

	bool IsDual(oCItem* item) {
		return item->GetObjectName().HasWordI("right") || item->GetObjectName().HasWordI("left");
	}

	zSTRING OppositDualHand(oCItem* item) {
		if (item->GetObjectName().HasWordI("right")) {
			return "left";
		}

		return "right";
	}
}