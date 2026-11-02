#!/usr/bin/env python3
"""Ensure Johto Gym victories mark their own subordinates, not Hoenn trainers.

This guards source/flags only; actual gameplay still needs an emulator test.
"""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[2]
source = (root / "data/scripts/set_gym_trainers.inc").read_text()
opponents = (root / "include/constants/opponents.h").read_text()
hoenn = [
    "RustboroCity_Gym", "DewfordTown_Gym", "MauvilleCity_Gym",
    "LavaridgeTown_Gym", "PetalburgCity_Gym", "FortreeCity_Gym",
    "MossdeepCity_Gym", "SootopolisCity_Gym",
]
johto = [
    ("VioletCity_Gym", "FALKNER"), ("AzaleaTown_Gym", "BUGSY"),
    ("GoldenrodCity_Gym", "WHITNEY"), ("EcruteakCity_Gym", "MORTY"),
    ("CianwoodGym", "CHUCK"), ("OlivineCity_Gym", "JASMINE"),
    ("MahoganyTown_Gym", "PRYCE"), ("BlackthornCity_Gym", "CLAIR"),
]


def block(label):
    pattern = "^" + re.escape(label) + r"::\s*\n(.*?)(?=^[A-Za-z_][A-Za-z_0-9]*::|\Z)"
    match = re.search(pattern, source, flags=re.M | re.S)
    assert match, "Missing Gym handler: " + label
    return match.group(1)


def flags(text):
    return re.findall(r"^\s*settrainerflag\s+(TRAINER_[A-Z0-9_]+)\b", text, flags=re.M)


def cases(text):
    return re.findall(r"^\s*case\s+(\d+),\s+(\w+)\b", text, flags=re.M)


assert cases(block("Common_EventScript_SetGymTrainers")) == [
    (str(i + 1), name + "_SetGymTrainers") for i, name in enumerate(hoenn)
], "Hoenn dispatcher must be preserved"
assert cases(block("Common_EventScript_SetGymTrainers_Johto")) == [
    (str(i + 1), name + "_SetGymTrainers_Johto") for i, (name, _) in enumerate(johto)
], "Johto dispatcher must map to its own eight Gyms"

numbers = {}
for name, value in re.findall(r"^#define\s+(TRAINER_[A-Z0-9_]+)\s+(\d+)\b", opponents, flags=re.M):
    if name not in numbers:
        numbers[name] = int(value)

hoenn_flags = []
for name in hoenn:
    hoenn_flags.extend(flags(block(name + "_SetGymTrainers")))

johto_flags = []
for name, leader in johto:
    script = (root / "data/maps" / name / "scripts.inc").read_text()
    calls = re.findall(r"\bcall\s+(Common_EventScript_SetGymTrainers(?:_Johto)?)\b", script)
    assert calls == ["Common_EventScript_SetGymTrainers_Johto"], name + " uses wrong handler"
    declared = flags(block(name + "_SetGymTrainers_Johto"))
    battles = re.findall(r"^\s*trainerbattle_\w+\s+(TRAINER_[A-Z0-9_]+)\b", script, flags=re.M)
    ordinary = {x for x in battles if not x.startswith("TRAINER_" + leader + "_")}
    assert len(declared) == len(ordinary) and set(declared) == ordinary, (
        name + " subordinate IDs do not match its map's battles"
    )
    johto_flags.extend(declared)

assert len(johto_flags) == 28, "Unexpected Johto subordinate count"
assert all(name in numbers for name in hoenn_flags + johto_flags), "Missing numeric trainer ID"
assert not {numbers[x] for x in hoenn_flags}.intersection(numbers[x] for x in johto_flags), (
    "Johto trainer flags alias Hoenn gym trainer flags"
)
assert not flags(block("OlivineCity_Gym_SetGymTrainers_Johto")), "Jasmine has no subordinate trainers"
print("PASS: 8 Johto gyms isolated from Hoenn; 28 trainer IDs verified")
