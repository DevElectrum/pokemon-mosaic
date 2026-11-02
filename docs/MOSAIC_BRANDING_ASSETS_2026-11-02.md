# Mosaic approved visuals: installation and placement (2 November 2026)

## Approved originals, immutable

- `graphics/branding/logos/pokemon-mosaic-master.png` — RGBA 1254×1254, SHA-256 `77b5c1095cf4595109b7ac1b1dac13be7c27fc258c85acf43f64f72e994849ff`
- `graphics/branding/artwork/pokemon-mosaic-hero-master.png` — RGB 1916×821, SHA-256 `d21c489d38ec00fbad4ff077e72c54bf5a51f850902d728f5ca8f9496c09b962`

## Website-optimized derivative files

- `graphics/branding/logos/pokemon-mosaic-mark.webp` — 160×160, website header
- `graphics/branding/logos/pokemon-mosaic-logo-web.webp` — 640×640, website About page
- `graphics/branding/artwork/pokemon-mosaic-hero-web.webp` — 1599×685, GitHub README banner, homepage hero, website social preview metadata

Website `scripts/generate.mjs` copies installed WebP assets to `public/visuals/`. The website currently builds **without the binaries** by showing its inherited image as a fallback. The new hero is shown above the home-page introduction so it is never covered by a text block. The final image installation also changes the README image link and site hero CSS to the new WebP. The simple existing mosaic favicon remains in place, because the detailed crest is not legible at favicon size.

## Current handoff state

**The image masters are NOT yet present in GitHub source as of this documentation commit.** They are in the supplied, SHA-256-verified `pokemon-mosaic-visuals-repo-ready.zip` artifact in the conversation. On Nyx, download and extract that ZIP to `~/Downloads`, pull Mosaic main, then run:

```sh
python3 ~/Downloads/mosaic-visuals-repo-bundle/install.py ~/Projects/pokemon-mosaic --push
```

The installer refuses to overwrite different existing assets, verifies checksums, updates the README and website image reference together, and commits only the approved image and documentation files. Do not mark this work as fully installed before the PNG/WebP files actually appear on `main`.

**Deliberately deferred:** Native 240×160 GBA title picture, generator, palette and tiles (absolute last branding step), historical Pokémon World and Grand Anthology art, and Mosaic screenshots from the forthcoming eeveelution-only Kanto/Johto/Hoenn run.
