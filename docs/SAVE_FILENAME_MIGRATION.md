# Pokémon Mosaic: preserving existing saves

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
