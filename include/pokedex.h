#ifndef GUARD_POKEDEX_H
#define GUARD_POKEDEX_H
#include "constants/regions.h"
#include "constants/pokedex.h"

extern void (*gPokedexVBlankCB)(void);

void ResetPokedex(void);
u16 GetNationalPokedexCount(u8 caseID);
u16 GetMosaicRegionalDexSize(enum Region region);
u16 MosaicRegionalToNationalOrder(enum Region region, u16 index);
u16 MosaicNationalToRegionalOrder(enum Region region, u16 national);
bool8 IsInMosaicRegionalDex(enum Region region, enum NationalDexOrder number);
u16 GetMosaicRegionalPokedexCount(enum Region region, u8 caseID);
bool16 HasAllMosaicRegionalMons(enum Region region);
u32 GetRegionalPokedexCount(u8 caseID);
u16 GetHoennPokedexCount(u8 caseID);
u16 GetKantoPokedexCount(u8 caseID);
u8 DisplayCaughtMonDexPage(enum Species species, bool32 isShiny, u32 personality);
u32 Pokedex_CreateCaughtMonSprite(enum Species species, s32 x, s32 y);
s8 GetSetPokedexFlag(enum NationalDexOrder nationalDexNo, u8 caseID);
void DrawFootprint(u8 windowId, enum Species species);
u16 CreateMonSpriteFromNationalDexNumber(enum NationalDexOrder nationalNum, s16 x, s16 y, u16 paletteSlot);
bool16 HasAllRegionalMons(void);
bool16 HasAllHoennMons(void);
bool16 HasAllKantoMons(void);
void ResetPokedexScrollPositions(void);
bool16 HasAllMons(void);
void CB2_OpenPokedex(void);
void PrintMonMeasurements(enum Species species, u32 owned);
u8* ConvertMonHeightToString(u32 height);
u8* ConvertMonWeightToString(u32 weight);

#endif // GUARD_POKEDEX_H
