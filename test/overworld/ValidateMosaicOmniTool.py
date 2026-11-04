#!/usr/bin/env python3
"""Regression guards for cheat-only OmniTool field-move behavior."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

def read(path):
    return (ROOT / path).read_text()

ids = read("include/constants/items.h")
items = read("src/data/items.h")
fields = read("src/field_move.c")
header = read("include/field_move.h")
scripts = read("src/scrcmd.c")
avatar = read("src/field_player_avatar.c")
debug = read("src/debug.c")
classic = read("src/party_menu.c")
swsh = read("src/swsh_party_menu.c")

assert ids.index("ITEM_HUB_RETURN,") < ids.index("ITEM_OMNI_TOOL,") < ids.index("ITEMS_COUNT,")
row = items.split("[ITEM_OMNI_TOOL] =", 1)[1].split("\n    },", 1)[0]
for token in ("ITEM_NAME(\"OmniTool\")", ".price = 0", ".importance = 1",
              ".pocket = POCKET_KEY_ITEMS", ".fieldUseFunc = ItemUseOutOfBattle_CannotUse"):
    assert token in row, token
assert "bool32 CanUseOmniToolFieldMove(enum FieldMove fieldMove);" in header

badges = fields.split("bool32 IsFieldMoveBadgeUnlocked(", 1)[1].split(
    "bool32 CanUseOmniToolFieldMove(", 1)[0]
omni = fields.split("bool32 CanUseOmniToolFieldMove(", 1)[1].split(
    "static bool32 IsFieldMoveUnlocked_Cut(", 1)[0]
for name in ("CUT", "FLASH", "ROCK_SMASH", "STRENGTH", "SURF", "FLY", "DIVE", "WATERFALL"):
    assert "case FIELD_MOVE_" + name + ":" in badges
    assert "return IsFieldMoveBadgeUnlocked(FIELD_MOVE_" + name + ");" in fields
assert "enum Region region = GetCurrentRegion();" in badges
assert "HasBadge(region, region == REGION_JOHTO ? 3 : 4)" in badges  # Morty Surf
assert "HasBadge(region, region == REGION_KANTO ? 6 : 7)" in badges
assert "return FALSE;" in badges  # non-HMs never authorized
for token in ("CheckBagHasItem(ITEM_OMNI_TOOL, 1)", "IsFieldMoveBadgeUnlocked(fieldMove)",
              "MON_DATA_SPECIES", "SPECIES_NONE", "MON_DATA_IS_EGG", "gPlayerParty[0]"):
    assert token in omni, token

check = scripts.split("bool8 ScrCmd_checkfieldmove(", 1)[1].split("bool8 ScrCmd_addmoney(", 1)[0]
assert check.index("if (CanUseOmniToolFieldMove(fieldMove))") < check.index("for (u32 i = 0; i < PARTY_SIZE; i++)")
assert "gSpecialVar_Result = 0;" in check
assert "gSpecialVar_0x8004 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES);" in check
surf = avatar.split("bool8 PartyHasMonWithSurf(", 1)[1].split("bool8 IsPlayerSurfingNorth(", 1)[0]
assert "CanUseOmniToolFieldMove(FIELD_MOVE_SURF)" in surf

for menu in (classic, swsh):
    action = menu.split("static void SetPartyMonFieldSelectionActions(", 2)[-1]
    for name in ("FLY", "FLASH"):
        assert "slotId == 0 && CanUseOmniToolFieldMove(FIELD_MOVE_" + name + ")" in action
        assert "MonKnowsMove(&mons[slotId], MOVE_" + name + ")" in action
    assert "sPartyMenuInternal->numActions < 5" in action
assert "Give OmniTool" in debug
assert "AddBagItem(ITEM_OMNI_TOOL, 1)" in debug

# This is intentionally a CHEAT ONLY item: no map script/ordinary shop gives it.
for directory in ("data/maps", "data/scripts"):
    for path in (ROOT / directory).rglob("*.inc"):
        assert "ITEM_OMNI_TOOL" not in path.read_text(errors="replace"), path

print("PASS: OmniTool ID, badge gates, lead mon, Surf/scripts, dual party menus, release cheat grant")
