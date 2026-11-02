> **Current instruction, 2 November 2026:** The maintainer has completed Hoenn and resumed Mosaic rebranding in phases. **Pass 1** covers active prose, intro attribution, website copy, and documentation; Pass 2 covers internal symbol/ROM filename/test migration; Pass 3 covers other visuals; the **native GBA title-screen image is explicitly last**. Older 'do not start rebrand' or 'title image second' notes below are historical and superseded. Preserve ordinary GBA compatibility, original Pokémon World credit, and the completed-game save.

# Pokémon Mosaic: repository split and rebrand handoff

## What the user wants

Pokémon Mosaic is a **separate three-region Pokémon World-derived game that must remain compatible with ordinary GBA emulators**. Pokémon Grand Anthology is a **separate nine-region-and-beyond project that will use the custom XGBA emulator**. Never merge XGBA-only ROM or save features into Mosaic automatically. The user selected the name **Pokémon Mosaic** and independently created the public repository `DevElectrum/pokemon-mosaic`.

## Exact source lineage and rollback

- Current Mosaic was copied with complete Git history from `DevElectrum/grand-anthology` **main at commit `ee129df07e5d8b4ce8d6ebe134fa4399eb921997`**. This is the source the user has been playing through Kanto and Johto, continuing into Hoenn.
- The user pushed that unchanged source as the first Mosaic `main`, then requested the identity split.
- `archive/pre-mosaic-rebrand-20261031` points to the exact source checkpoint, providing immediate rollback.
- The original `DevElectrum/grand-anthology` is untouched by the Mosaic rebrand; it retains the experimental `xgba/expansion-lab` branch separately.
- The two new Mosaic commits, `b263d092` (game and docs) and `9a022819` (website), change identity rather than underlying gameplay.

## Current implemented identity changes

- Player-visible main-menu title `Pokémon Mosaic`; new-game opening says `Welcome to POKéMON MOSAIC!`, page three says `MOSAIC!`; obsolete save warnings now name Mosaic but retain all original version/refusal logic.
- GBA header display title `PKMN MOSAIC` (within the 12-byte GBA header limit), **game code `BPEE` and revision 0 remain unchanged**.
- Makefile still emits `pokemonworld-release.gba` by default because scripts and existing `.sav` basenames depend on it. `FILE_NAME` was made overrideable using `?=`; it can be set explicitly later after CI and save-filename migration checks.
- README, current AGENTS/HANDOFF pointers, field-guide heading, website SEO/navbar/attribution links, home page, status, randomizer description, website package name and Mosaic-themed favicon have been rebranded. The website source is **not a new deployed site**. The original `grand-anthology.pages.dev` belongs to the other project.
- Upstream Pokémon World authorship and credit links, all copyright notices, internal `ANTHOLOGY_*` identifiers and historical docs/CI citations have been deliberately preserved. Do NOT use a repository-wide string replacement; it would erase history, risk the live save layout, or falsify old CI provenance.

## Remaining distinct task: visual title art

The GBA native title art at `graphics/title_screen/world/grand_anthology_title.png` is a finely crafted sunset/pixel landscape with a large Pokémon logo and text `GRAND ANTHOLOGY` embedded in pixels. The build pipeline `tools/build_anthology_title.py` produces native 8bpp tiles/palette/map from that PNG; `src/title_screen_world.c` assumes exact 577 tiles and test/overworld/lua/WorldTitle.lua compares raw VRAM contents. The Mosaic visual must therefore be redesigned deliberately as a proper 240x160 indexed PNG and its tilecount guard/test revised together. Do not rename binary files or replace with a poor-quality placeholder without the user's approval. No replacement image was generated or accepted yet; title screen still visually says Grand Anthology at this checkpoint. The imported README concept banner and generated website title illustration likewise remain inherited legacy artwork pending brand design.

## CI and acceptance

At first check, Mosaic website workflow run https://github.com/DevElectrum/pokemon-mosaic/actions/runs/41253940157 **passed**, including source-level generator, website tests, static site build and deployment-size audit. Game source validators passed in https://github.com/DevElectrum/pokemon-mosaic/actions/runs/41253890293; exact optimized ROM compilation and actual mGBA smoke https://github.com/DevElectrum/pokemon-mosaic/actions/runs/41253890323 were still in progress at that check. Verify final outcomes before declaring runtime acceptance. The existing historical CI runs still link to the original repo; old URLs are intentionally not rewritten.

## Next actions

1. Confirm complete optimized ROM and mGBA results; repair any actual regressions without altering save identity.
2. Decide and create approved Mosaic title art as a separately reviewable visual change; generate exact GBA BG tilemap/palette from its 240x160 indexed image, adjust exact-tile-count validation as needed, and update test labels and website art together.
3. Only after title/other assets are correctly renamed, optionally transition final ROM filename with explicit old .sav copy instructions. No automatic save migration or overwrite.
4. Keep a single normal-emulator gameplay acceptance pass; do not repeat Kanto/Johto campaigns.

## Handoff decision, 31 October 2026: leave remaining rebrand to another Astra

The maintainer explicitly instructed the present Astra **not to spend additional work on Mosaic's rebrand**. A different Astra should complete the remaining source/asset/website identity and verification from this checkpoint. Do not ask the maintainer to re-explain the two-project distinction. Mosaic is **3 regions, standard GBA emulator compatible**. Grand Anthology, housed at `DevElectrum/grand-anthology`, is **9 regions and beyond, modern battle rules, large bag and PC systems, custom XGBA emulator**.

### Accepted work already committed
- `b263d092`: README, agents/handoff intro, cartridge title `PKMN MOSAIC`, main menu and new-game intro branding, Makefile overrideable filename and source CI labeling
- `9a022819`: website layout, home/status/about/randomizer copy, repository links, favicon, website package and workflow labels
- Later documentation-only source records are in GitHub `main`, while `archive/pre-mosaic-rebrand-20261031` preserves the exact original imported code
- [Mosaic website build 41253940157](https://github.com/DevElectrum/pokemon-mosaic/actions/runs/41253940157) **PASS**
- [Mosaic optimized game build 41253890293](https://github.com/DevElectrum/pokemon-mosaic/actions/runs/41253890293) **PASS** for source validators and full ROM compilation
- [Mosaic mGBA smoke 41253890323](https://github.com/DevElectrum/pokemon-mosaic/actions/runs/41253890323) was **still in progress** (optimized ROM compilation underway) at this handoff; inspect final run before claiming emulator verification

### Remaining cohesive rebranding work
1. Replace the image `graphics/title_screen/world/grand_anthology_title.png` with properly designed **Pokémon Mosaic** native title art, keeping the 240x160 indexed GBA requirements and adjusting its generator, exact-tile-count compile guards and title Lua regression as needed. Old sunset/title art should not be silently claimed as Mosaic. For existing title pipeline see `tools/build_anthology_title.py`, `src/title_screen_world.c`, `Makefile`, `test/overworld/lua/WorldTitle.lua`. Preserve working input transitions.
2. Handle inherited `.github/assets/grand-anthology-readme-banner.jpg` and generated website title illustration; update `website/scripts/generate.mjs` references **only once new assets exist**. Retain properly credited provenance for upstream screenshots and artwork. Rebrand site labels, readme/public status and source-facing links carefully; do **not** deploy to the separate Grand Anthology's `grand-anthology.pages.dev` project.
3. Audit remaining player-visible strings (intro, credits and menu titles, screenshots/README) and changes to CI labels. Preserve original Pokémon World provenance in descriptive credits, original history/commit URLs and stable in-game save flags/constants, even if their names contain "Anthology" or "World".
4. If choosing a new final ROM basename, audit all `pokemonworld-release.gba` build/CI/test references first. Explain that emulators associate saves with ROM filenames, and **copy** (never rename/delete/overwrite the only) original `.sav` under the new basename. Keep game code `BPEE` and save ABI stable; standard mGBA/Pizza Boy compatibility is a hard requirement.
5. Run a single consolidated optimized build, website test, and focused mGBA title/New Game/Continue smoke, rather than repeated user-driven micro-tests. Record exact CI SHA and game verification accurately.

Historical documents and regression test symbol names are allowed to retain original naming where semantically necessary. **No title image or logo redesign is approved or completed at this checkpoint.**

