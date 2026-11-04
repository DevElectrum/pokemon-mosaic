#!/usr/bin/env python3
"""Guard Johto and regional HM badge requirements, including shared OmniTool checks."""
from pathlib import Path

root = Path(__file__).resolve().parents[2]
source = (root / "src/field_move.c").read_text()

shared = source.split("bool32 IsFieldMoveBadgeUnlocked(enum FieldMove fieldMove)", 1)[1].split(
    "bool32 CanUseOmniToolFieldMove(enum FieldMove fieldMove)", 1
)[0]
assert "enum Region region = GetCurrentRegion();" in shared

def badge_case(name):
    start = f"case FIELD_MOVE_{name}:"
    assert shared.count(start) == 1, name
    return shared.split(start, 1)[1].split("case FIELD_MOVE_", 1)[0]

def field_move(name):
    start = f"static bool32 IsFieldMoveUnlocked_{name}(void)"
    assert source.count(start) == 1, name
    return source.split(start, 1)[1].split("static bool32 IsFieldMoveUnlocked_", 1)[0]

for suffix, field in (("Cut", "CUT"), ("Flash", "FLASH"),
                      ("RockSmash", "ROCK_SMASH"), ("Strength", "STRENGTH"),
                      ("Surf", "SURF"), ("Fly", "FLY"),
                      ("Dive", "DIVE"), ("Waterfall", "WATERFALL")):
    assert f"return IsFieldMoveBadgeUnlocked(FIELD_MOVE_{field});" in field_move(suffix), suffix

assert "region == REGION_HOENN ? 0 : 1" in badge_case("CUT"), "Cut: Hive / Cascade / Stone"
assert "region == REGION_HOENN ? 1 : 0" in badge_case("FLASH"), "Flash: Zephyr / Boulder / Knuckle"
assert "region == REGION_JOHTO ? 2 : 3" in badge_case("STRENGTH"), "Strength: Plain / fourth gym elsewhere"
fly = badge_case("FLY")
assert "region == REGION_KANTO" in fly and "HasBadge(region, 2)" in fly
assert "region == REGION_JOHTO" in fly and "HasBadge(region, 4)" in fly
assert "return HasBadge(region, 5)" in fly, "Hoenn Fly: Feather"

# Existing per-tool badge bypasses remain unchanged, but the OmniTool uses
# ONLY the shared strict badge gate. Surf in Johto uses Morty's Fog Badge.
assert "region == REGION_KANTO ? 5 : 2" in badge_case("ROCK_SMASH")
assert "region == REGION_JOHTO ? 3 : 4" in badge_case("SURF")
assert "region == REGION_KANTO ? 6 : 7" in badge_case("WATERFALL")
for name in ("Cut", "Strength", "RockSmash", "Surf", "Waterfall", "Dive"):
    assert "CheckBagHasItem" in field_move(name), name
omni = source.split("bool32 CanUseOmniToolFieldMove(enum FieldMove fieldMove)", 1)[1].split(
    "static bool32 IsFieldMoveUnlocked_Cut", 1
)[0]
assert "IsFieldMoveBadgeUnlocked(fieldMove)" in omni
assert "CheckBagHasItem(ITEM_OMNI_TOOL, 1)" in omni

gyms = (
    ("VioletCity_Gym", "FLAG_JOHTO_BADGE_1", "FLASH"),
    ("AzaleaTown_Gym", "FLAG_JOHTO_BADGE_2", "CUT"),
    ("GoldenrodCity_Gym", "FLAG_JOHTO_BADGE_3", "STRENGTH"),
    ("CianwoodGym", "FLAG_JOHTO_BADGE_5", None),
)
for path, flag, move in gyms:
    text = (root / "data/maps" / path / "scripts.inc").read_text()
    assert f"setflag {flag}" in text, path
    if move:
        assert move in text, (path, move)

print("PASS: regional field move gates match Johto's Zephyr/Hive/Plain/Storm badges")
