# Historical Pokémon World branding resources

> **Mosaic rebrand status (2 November 2026):** This directory documents legacy Pokémon World artwork and its historical exporter. It is not the active Mosaic title pipeline. The currently active (still Grand Anthology-branded) GBA title uses `src/title_screen_world.c` and `tools/build_anthology_title.py`; its native image will be replaced **last**, after text, internal naming, ROM basename, and other visuals. Do not run the old World exporter as part of current Mosaic branding.

`logos/pokemon-world.png` is the shared stacked logo used by the main README and
the title exporter. World is intentionally shifted right relative to Pokémon:
44 pixels in the 1774-pixel master, producing the approved 4-pixel offset when
the logo is rendered 160 pixels wide in-game. Keep the overall stack centered;
PRESS START remains centered on the screen independently.

After editing the master, run:

```sh
node tools/export-world-title.mjs
make modern -j8
test/overworld/mgba-run.sh test/overworld/lua/WorldTitle.lua
```

The exporter rebuilds the native title resources and the legacy
`.github/pokemon_world_logo.png` thumbnail. It checks the wordmark's offset and
the GBA palette, tilemap and VRAM limits. Refresh
`screenshots/01-title-screen.png` from the emulator after a title change.

`box/box-front.png` is a flattened cover with the same proportional adjustment
to World (19 pixels at its printed size). `logos/world.png` is the standalone
wordmark: it has no Pokémon lettering to align against and keeps its own center.

The current 20-image gallery lives in [`screenshots/showcase/`](screenshots/showcase/README.md),
with ROM/capture hashes. The six original screenshots are retained as historical assets.

## Grand Anthology redesign candidates

The full-resolution [standalone project logo and simplified regional title-screen concepts](concepts/README.md) from 26 October 2026 are archived for future branding and GBA art work. They are **not yet applied** to the game, the README banner, or the existing Pokémon World logo pipeline.
