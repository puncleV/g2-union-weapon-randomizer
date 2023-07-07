# Punclev Utils Union Plugin

A collection of marvin commands for Gothic 2NoR to make your game unpredictable. Balance is not a goal of this mod, fun is!

## Usage

1. [Build a project](https://worldofplayers.ru/threads/41466/)
2. Activate Marvin
3. Open console
4. Type a marvin command
6. Look at how broken game become
7. ???
8. profit!


## Marvin commands

### Randomize melee weapons

```
weaponsrandomizer MELEEWPNS
```

### Randomize ranged weapons

```
weaponsrandomizer RANGEDWPNS
weaponsrandomizer RANGEDWPNS_ADD
```
RANGEDWPNS_ADD - will also add ranged weapons randomly



### Add random loot

```
lootrandomizer ADD
lootrandomizer ADD ADD_TO_PLAYER
```
ADD_TO_PLAYER - will add the loot directly to player's inventory (for test\check purpose)

### Randomize chests content
Shuffles all chests content on the map

```
chestsrandomizer SHUFFLE
```

### Add chests content

```
chestsrandomizer ADD
chestsrandomizer ADD ADD_TO_PLAYER
```
ADD_TO_PLAYER - will add the loot directly to player's inventory (for test\check purpose)

### Herbs randomizer

Shuffles all herbs on the map

```
herbsrandomizer SHUFFLE
```

### All in one

```
punclevutils all
```
Will randomise weapons, add loot, etc.

## Gothic.ini parameters example

```
[PUNCLEVUTILS]
Loot0ListActive=1; Adds extra possible loot
Loot0Item0=ITMI_GOLD
Loot0Item1=ITMI_SLEEPSACK
Loot0Chance=100
Loot0ChanceOutOf=1000

Loot1ListActive=0
Loot1Item0=ITPO_ELIGORFIRE
Loot1Chance=5
Loot1ChanceOutOf=1000

ExtraLootChance=15; out of 1000 (Horinis default), checks for each NPC on location independently
ChestsExtraLootChance=450; out of 1000 (Horinis default), checks for each CHEST on location independently
OverrideLootTable=0; 0 - use both: loot tables from gothic.ini and default ones
ValueBasedStrengthMultiplier=250; for each added item checks the price and for each 250 price value -> increasing NPC strength
BaseStrengthMultiplierForAddedLoot=1; minimum multiplier for increasing NPC strength for an extra loot
StrengthenEnemyStatsPerMultiplier=25; this value multiplied by multiplier adds up to strength, dexterity of an NPC
StrengthenEnemyDefencePerMultiplier=1; this value multiplied by multiplier adds up to defence of an NPC

StrengthenEnemyBaseHP=150; this value devided by NPC's max HP (with some randomness) adds up to max HP for each given extra loot item 

ExtraLootHpFactorOther=700; bigger value -> less loot, per each 700 HP incresing loot chance by ExtraLootHpFactorMultiplier (2.5% default Horinis)
ExtraLootHpFactorHorinis=400; bigger value -> less loot
ExtraLootHpFactorMultiplier=25; bigger value -> more loot for those who has more than ExtraLootHpFactorHorinis HP

ExtraLootHorinisFactor=1000; bigger value -> less loot
ExtraLootOtherFactor=1250; bigger value -> less loot
```

Calculation of extra power for enemies with added loot
```
multiplier = ItemPrice / ValueBasedStrengthMultiplier + BaseStrengthMultiplierForAddedLoot

strength\agility += StrengthenEnemyStatsPerMultiplier * multiplier
health += random(...); Less HP monster have bigger boost it will receive
defence += StrengthenEnemyDefencePerMultiplier  * multiplier
```

Calculation of a loot chance to add to a given NPC
```
ExtraLootChance + ( npcHp / ExtraLootHpFactor) * ExtraLootHpFactorMultiplier;

Default value for a meatbug with 15HP: 15 + ( 15 / 400 ) * 25 = 15 OUT OF 1000 = 1.5% ;
Default value for an enemy with 10000HP: 15 + ( 10000 / 400 ) * 25 = 15 + 625 = 640 OUT OF 1000 = 64% ;

Default value for an enemy with 10000HP NOT IN HORINIS: 15 + ( 10000 / 700) * 25 = 15 + 362= 377 OUT OF 1250 = 30% ;
```

## Oficial forum thread

https://rpgrussia.com/resources/nabor-marvin-komand-dlja-randomizacii-i-prochego.4372/

## References

1. [Union tutorials](https://worldofplayers.ru/forums/1129/)
2. [Good examples i checked when build this mode](https://github.com/Franisz/zUtilities)

### Credits

Big thanks to [Haart](https://www.twitch.tv/lhaart) for the idea and support.