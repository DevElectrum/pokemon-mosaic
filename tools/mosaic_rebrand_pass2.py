#!/usr/bin/env python3
"""Source-only Mosaic Pass 2 migration; never reads or writes emulator save files."""
from pathlib import Path
import argparse
import re

ROOT = Path(__file__).resolve().parents[1]
CODE = {'.c', '.h', '.inc', '.s', '.S', '.json', '.pory'}
TOOL = CODE | {'.py', '.lua', '.sh', '.mjs', '.js', '.md'}
PRESERVE = ['tools/build_anthology_title.py', 'graphics/title_screen/world/grand_anthology_title.png', '.github/assets/grand-anthology-readme-banner.jpg', 'ANTHOLOGY_CHANGELOG.md']
EXCLUDE = {'tools/build_anthology_title.py', 'tools/build_gba_title_candidate.py', 'tools/export-world-title.mjs', 'tools/public_source_snapshot.py', 'website/scripts/generate.mjs', 'test/overworld/lua/WorldTitle.lua', 'tools/mosaic_rebrand_pass2.py'}
HABITATS = ('rare', 'extra', 'aquatic')


def targets():
    for base, suffixes in [('src', CODE), ('include', CODE), ('asm', CODE), ('data', CODE), ('test', TOOL), ('tools', TOOL), ('website', TOOL)]:
        directory = ROOT / base
        if not directory.exists():
            continue
        for p in directory.rglob('*'):
            if p.is_file() and p.suffix in suffixes and p.relative_to(ROOT).as_posix() not in EXCLUDE:
                if '/review/' not in p.as_posix() and '/node_modules/' not in p.as_posix():
                    yield p
    for p in (ROOT / '.github/workflows').glob('*.yml'):
        yield p
    for name in ('Makefile', 'config.mk', 'README.md', 'INSTALL.md', 'FEATURES.md', 'CONTRIBUTING.md', 'AGENTS.md', 'data/catalog/README.md', 'docs/GRAND_ANTHOLOGY_FIELD_GUIDE.md', 'docs/NEXT_ASTRA_HANDOFF.md', 'docs/MOSAIC_REBRAND_HANDOFF.md', 'docs/PUBLIC_STATUS.md'):
        yield ROOT / name
    yield ROOT / 'data/catalog/world_acquisition.jsonl'


def apply_names(text, path, test_names):
    for n, original in enumerate(PRESERVE):
        text = text.replace(original, '__PRESERVED_PASS2_' + str(n) + '__')
    # Human documentation keeps original authorship, historical names and old URLs.
    if not path.endswith('.md') and path not in ('AGENTS.md',):
        for old, new in (('ANTHOLOGY', 'MOSAIC'), ('Anthology', 'Mosaic'), ('anthology', 'mosaic')):
            if path == 'src/title_screen_world.c' and old == 'anthology':
                continue
            text = text.replace(old, new)
    for n, original in enumerate(PRESERVE):
        text = text.replace('__PRESERVED_PASS2_' + str(n) + '__', original)
    for old, new in (('pokemonworld-release', 'pokemon-mosaic-release'), ('pokemonworld.', 'pokemon-mosaic.'), ('pokemonworld-', 'pokemon-mosaic-'), ('GRAND_ANTHOLOGY_FIELD_GUIDE.md', 'MOSAIC_FIELD_GUIDE.md')):
        text = text.replace(old, new)
    for kind in HABITATS:
        text = text.replace('anthology_' + kind + '_habitats.h', 'mosaic_' + kind + '_habitats.h')
    for old in test_names:
        text = text.replace(old, old.replace('Anthology', 'Mosaic'))
    return text


def renamed_files():
    paths = []
    for kind in HABITATS:
        old = ROOT / ('src/data/anthology_' + kind + '_habitats.h')
        new = ROOT / ('src/data/mosaic_' + kind + '_habitats.h')
        if old.exists():
            assert not new.exists()
            old.rename(new)
            paths.append(new.relative_to(ROOT).as_posix())
    for old in (ROOT / 'test/overworld').glob('ValidateAnthology*.py'):
        new = old.with_name(old.name.replace('Anthology', 'Mosaic'))
        assert not new.exists()
        old.rename(new)
        paths.append(new.relative_to(ROOT).as_posix())
    old = ROOT / 'docs/GRAND_ANTHOLOGY_FIELD_GUIDE.md'
    new = ROOT / 'docs/MOSAIC_FIELD_GUIDE.md'
    if old.exists():
        assert not new.exists()
        old.rename(new)
        old.write_text('# Historical field-guide link\n\nThe current [Pokémon Mosaic Field Guide](MOSAIC_FIELD_GUIDE.md) has moved to a new path.\n', encoding='utf-8')
        paths.append(new.relative_to(ROOT).as_posix())
    return paths


def update_current_docs():
    readme = ROOT / 'README.md'
    s = readme.read_text()
    begin = 'The inherited '
    start = s.find(begin, s.index('## Building locally'))
    end = s.find('\n\nYou need Git', start)
    assert start >= 0 and end >= 0
    s = s[:start] + 'The standard build now outputs **pokemon-mosaic-release.gba** with a **PKMN MOSAIC** cartridge header. To carry a saved game forward from the old filename, first follow the [copy-only save guide](docs/SAVE_FILENAME_MIGRATION.md). Never overwrite your only .sav.' + s[end:]
    readme.write_text(s)
    install = ROOT / 'INSTALL.md'
    s = install.read_text()
    s = s.replace('still** uses the temporary', 'now** uses the').replace('both still under the legacy filename until Pass 2', 'both using the new Mosaic filename')
    s = s.replace('Renaming that default, its CI consumers, and matching emulator save basenames belongs to rebranding Pass 2', 'ROM and CI filenames are updated together in rebranding Pass 2')
    s = s.replace('These temporary basenames **do not** determine the in-game brand: the header says', 'The ROM filename and GBA header now both use Mosaic branding: the header says')
    s = s.replace('Pass 2 will migrate the default to', 'Pass 2 migrated the default to')
    s += '\n\n## Preserve saves after the filename change\n\nRead [the copy-only save guide](docs/SAVE_FILENAME_MIGRATION.md) before starting the new ROM. The actual save format and game code BPEE remain unchanged.\n'
    install.write_text(s)
    workflow = ROOT / '.github/workflows/Gameplay-P0.yml'
    s = workflow.read_text()
    match = '          python3 test/overworld/ValidateJohtoGymTrainerIsolation.py\n'
    assert match in s
    s = s.replace(match, match + '          python3 test/overworld/ValidateMosaicBranding.py\n')
    workflow.write_text(s)
    save_doc = ROOT / 'docs/SAVE_FILENAME_MIGRATION.md'
    save_doc.write_text('''# Pokémon Mosaic: preserving existing saves

This naming change does NOT modify the existing BPEE game code, 128 KiB Flash
format, party, PC boxes, story flags, or save version. The native GBA title
picture will be changed in a later, separate pass.

## Linux / Nyx

Close the emulator and identify the actual .sav file in its configured save
folder. Back up your only save somewhere independent before copying. For a save
called pokemonworld-release.sav beside the old ROM, run:

```bash
cd /path/to/your/actual/save/directory
cp -- pokemonworld-release.sav pokemonworld-release.sav.pre-mosaic-backup
test ! -e pokemon-mosaic-release.sav
cp -- pokemonworld-release.sav pokemon-mosaic-release.sav
```

Never overwrite an existing destination or replace/delete the original. If your
old ROM was pokemonworld.gba, copy pokemonworld.sav to pokemon-mosaic.sav
instead. Emulators may save elsewhere or use .srm; inspect the emulator's
settings and copy/import that actual file, preserving a separate backup.

Start pokemon-mosaic-release.gba and verify CONTINUE, your team, PC, bag, Dex
and badges using the copied save. Keep the original old-ROM and old-save pair
intact until you have verified multiple successful cold restarts.

## Android / Pizza Boy

Close the emulator, export or locate its actual battery save in its own save
folder, make an independent backup, then copy/import under the new ROM basename.
Do not assume Android stores the save next to the ROM. Never replace your only
copy or overwrite a destination without checking.

**Existing Hoenn gym trainer flags** set by the old Johto flag bug remain as
recorded in the save. Renaming cannot retroactively repair those flags.
''')
    (ROOT / 'docs/NEXT_ASTRA_HANDOFF.md').write_text('## Mosaic Pass 2: internal identifiers and ROM filename (2 November 2026)\n\nSource identifiers and tests migrated from legacy Anthology naming to Mosaic while numeric event flags and game code BPEE remain constant. Default optimized ROM filename: pokemon-mosaic-release.gba. Copy-only save guidance: docs/SAVE_FILENAME_MIGRATION.md. The native GBA title picture and historic art generator remain explicitly last.\n\n' + (ROOT / 'docs/NEXT_ASTRA_HANDOFF.md').read_text())
    (ROOT / 'AGENTS.md').write_text('> **2 NOV 2026 REBRANDING PASS 2:** Internal Mosaic source symbol names, validators, field guide path, CI and ROM/test defaults are updated in a single verified refactor. Numeric save flag expressions, BPEE and Flash format stay unchanged. The old title picture and generator remain until the LAST visual pass. Use the backup/copy-only docs/SAVE_FILENAME_MIGRATION.md; never overwrite completed-game saves.\n\n' + (ROOT / 'AGENTS.md').read_text())


def validate():
    make = (ROOT / 'Makefile').read_text()
    assert 'FILE_NAME ?= pokemon-mosaic' in make
    assert 'TITLE        ?= PKMN MOSAIC' in make
    assert 'GAME_CODE    ?= BPEE' in make
    assert (ROOT / 'docs/MOSAIC_FIELD_GUIDE.md').exists()
    assert (ROOT / 'docs/SAVE_FILENAME_MIGRATION.md').exists()
    for kind in HABITATS:
        assert (ROOT / ('src/data/mosaic_' + kind + '_habitats.h')).exists()
    for file in targets():
        path = file.relative_to(ROOT).as_posix()
        if path == 'src/title_screen_world.c':
            assert 'graphics/title_screen/world/anthology_title_tiles.bin' in file.read_text()
            continue
        if file.suffix not in CODE or not file.is_file():
            continue
        text = file.read_text(encoding='utf-8', errors='replace')
        assert 'ANTHOLOGY_' not in text and 'Anthology_' not in text, path
    assert not list((ROOT / 'test/overworld').glob('ValidateAnthology*.py'))
    assert 'ValidateMosaicBranding.py' in (ROOT / '.github/workflows/Gameplay-P0.yml').read_text()
    print('PASS: Mosaic internal naming, save flag symbols, ROM/CI/test defaults')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    if args.check:
        validate()
        return
    flags = (ROOT / 'include/constants/flags.h').read_text()
    original = dict(re.findall(r'^#define\s+(FLAG_\w+)\s+([^\n]+)', flags, re.M))
    test_names = [p.name for p in (ROOT / 'test/overworld').glob('ValidateAnthology*.py')]
    changed = 0
    for file in targets():
        if not file.is_file() or file.stat().st_size > 10_000_000:
            continue
        try:
            before = file.read_text(encoding='utf-8')
        except UnicodeDecodeError:
            continue
        path = file.relative_to(ROOT).as_posix()
        after = apply_names(before, path, test_names)
        if path == 'Makefile':
            after = after.replace('FILE_NAME ?= pokemonworld', 'FILE_NAME ?= pokemon-mosaic')
            after = after.replace('.anthology-title.stamp', '.mosaic-title.stamp')
        if before != after:
            file.write_text(after, encoding='utf-8')
            changed += 1
    moved = renamed_files()
    new_flags = dict(re.findall(r'^#define\s+(FLAG_\w+)\s+([^\n]+)', (ROOT / 'include/constants/flags.h').read_text(), re.M))
    for name, val in original.items():
        assert new_flags.get(name.replace('ANTHOLOGY', 'MOSAIC'), '').split('//')[0].strip() == val.replace('ANTHOLOGY', 'MOSAIC').split('//')[0].strip(), name
    update_current_docs()
    print('Updated', changed, 'source files, moved', len(moved), 'source/document paths')
    validate()


if __name__ == '__main__':
    main()
