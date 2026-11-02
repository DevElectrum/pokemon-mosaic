#!/usr/bin/env python3
"""Source-only Mosaic identity, ROM naming, and safe-save contract."""
from pathlib import Path
import subprocess

root = Path(__file__).resolve().parents[2]
subprocess.run(
    ["python3", "tools/mosaic_rebrand_pass2.py", "--check"],
    cwd=root,
    check=True,
)
assert (root / "docs/SAVE_FILENAME_MIGRATION.md").is_file()
assert (root / "docs/MOSAIC_FIELD_GUIDE.md").is_file()
makefile = (root / "Makefile").read_text()
assert "FILE_NAME ?= pokemon-mosaic" in makefile
assert "TITLE        ?= PKMN MOSAIC" in makefile
assert "GAME_CODE    ?= BPEE" in makefile
for name in (
    "Gameplay-P0.yml",
    "P0-mGBA-Release-Smoke.yml",
    "Qol-Multipliers.yml",
    "P0-Static-Validators.yml",
    "Website-Build.yml",
):
    workflow = (root / ".github/workflows" / name).read_text()
    assert "pokemonworld-release.gba" not in workflow, name
    assert "ValidateAnthology" not in workflow, name
    assert "src/data/anthology_" not in workflow, name
assert "graphics/title_screen/world/grand_anthology_title.png" in (
    root / ".github/workflows/P0-mGBA-Release-Smoke.yml"
).read_text()
print("PASS: Mosaic ROM/source/CI names, BPEE, save guide and deferred title art")
