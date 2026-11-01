#!/usr/bin/env python3
"""Guard ordinary shop acquisition of the previously unstocked held items."""
import json
import re
from pathlib import Path

root = Path(__file__).resolve().parents[2]

items = """
FLAME_ORB TOXIC_ORB DAMP_ROCK HEAT_ROCK SMOOTH_ROCK ICY_ROCK ABSORB_BULB ZOOM_LENS GRIP_CLAW RED_CARD RING_TARGET BINDING_BAND EJECT_BUTTON ADRENALINE_ORB TERRAIN_EXTENDER PROTECTIVE_PADS THROAT_SPRAY EJECT_PACK HEAVY_DUTY_BOOTS BLUNDER_POLICY ROOM_SERVICE UTILITY_UMBRELLA ABILITY_SHIELD CLEAR_AMULET PUNCHING_GLOVE COVERT_CLOAK MIRROR_HERB LIGHT_BALL LEEK THICK_CLUB METAL_POWDER QUICK_POWDER LUCKY_EGG DESTINY_KNOT BERSERK_GENE
""".split()

shops = {
    "CeladonCity_DepartmentStore_4F_Frlg": (
        "data/maps/CeladonCity_DepartmentStore_4F_Frlg/scripts.inc",
        "CeladonCity_DepartmentStore_4F_Items",
        ".2byte ITEM_NONE",
    ),
    "GoldenrodCity_DepartmentStore_4F": (
        "data/maps/GoldenrodCity_DepartmentStore_4F/scripts.inc",
        "GoldenrodDeptStore4_Pokemart_FeathersAndMints",
        "pokemartlistend",
    ),
    "LilycoveCity_DepartmentStore_2F": (
        "data/maps/LilycoveCity_DepartmentStore_2F/scripts.inc",
        "LilycoveCity_DepartmentStore_2F_Pokemart1",
        "pokemartlistend",
    ),
    "RegionHub": (
        "data/maps/RegionHub/scripts.inc",
        "RegionHub_Items_BattleDepot",
        "pokemartlistend",
    ),
}

catalog = {}
catalog_path = root / "data/catalog/world_acquisition.jsonl"
for line in catalog_path.read_text().splitlines():
    row = json.loads(line)
    if row.get("kind") == "item":
        catalog[row["symbol"]] = row

guide = (root / "docs/GRAND_ANTHOLOGY_FIELD_GUIDE.md").read_text()
for item in items:
    symbol = "ITEM_" + item
    assert symbol in catalog, "Missing catalog entry: " + symbol
    row = catalog[symbol]
    found = set()
    for source in row["sources"]:
        if source.get("method") == "pokemart":
            found.add(source.get("map"))
    assert found == set(shops), "Catalog shop coverage missing: " + symbol
    assert row["known_path_status"] == "source_candidate_only"
    expected = "| " + str(row["id"]) + " | **" + row["name"] + "** | Sold at"
    assert expected in guide, "Field guide missing shop: " + symbol

for region, shop in shops.items():
    path, label, terminator = shop
    source = (root / path).read_text()
    start = source.index(label + ":")
    end = source.index(terminator, start)
    stock = source[start:end]
    entries = re.findall(r"\\.2byte\\s+(ITEM_[A-Z0-9_]+)", stock)
    for item in items:
        symbol = "ITEM_" + item
        assert entries.count(symbol) == 1, "Shop stock missing or duplicated: " + region + "/" + symbol
    assert entries.count("ITEM_LOADED_DICE") == 1, "Loaded Dice changed in " + region
    assert len(entries) < 255, "Shop inventory outgrows practical list capacity: " + region

print("PASS: 35 held items + Loaded Dice stocked in all four shops; atlas and guide agree")
