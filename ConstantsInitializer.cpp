// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	void updateConstantsWithOptions() {
		CHANCE_TO_ADD_RANGED_WEAPON = zoptions->ReadInt("PUNCLEVUTILS", "ChanceToAddRangedWeapon", 300);

		IS_DEBUG = zoptions->ReadBool("PUNCLEVUTILS", "Debug", FALSE);
		SHOULD_SHUFFLE_MELEE_WEAPON = zoptions->ReadBool("PUNCLEVUTILS", "ShouldRandomizeMeleeWeapons", FALSE);
		SHOULD_SHUFFLE_RANGED_WEAPON = zoptions->ReadBool("PUNCLEVUTILS", "ShouldRandomizeRangedWeapons", FALSE);
	}
}