# OmniTool (cheat-only HM assistance)

Mosaic supports the **OmniTool** as a passive **Key Item** for species-only runs.
It is deliberately **not obtainable** from regular shops, story gifts, hidden
pickups, or normal exploration.

## How to obtain

Open the player-facing **Cheats** menu from the Start menu, then choose
**Give OmniTool**. It is reusable, requires a free Key Items slot, and does not
teach, change or replace any Pokémon move.

## Rules

- The OmniTool must be in the Bag.
- **The first party Pokémon** must exist and must not be an Egg. It is always
  credited as the actor in scripted interactions and field animations.
- You must own the corresponding badge **from your current region**. Older
  badges from other regions do not substitute. The OmniTool never overrides
  badge requirements; this differs from Mosaic's separate ordinary field tools.
- Map conditions and follower/escort limitations still apply.
- Cut, Rock Smash, Strength, Surf, Dive and Waterfall activate at existing
  world obstacles/water; **Fly and Flash** appear on the first Pokémon's
  party action menu once their badges unlock them.
- Non-HM moves such as Dig, Teleport, Rock Climb and Defog are not granted.
- Johto Whirlpool is already controlled by its own Badge 7 world script and
  does not require a Pokémon HM or the OmniTool.

### Badge mappings (zero-based gym index)

| Move | Kanto | Johto | Hoenn |
| --- | --- | --- | --- |
| Cut | 1 | 1 | 0 |
| Flash | 0 | 0 | 1 |
| Rock Smash | 5 | 2 | 2 |
| Strength | 3 | 2 | 3 |
| Surf | 4 | **3 (Fog)** | 4 |
| Fly | 2 | 4 | 5 |
| Dive | 6 | 6 | 6 |
| Waterfall | 6 | 7 | 7 |

The Johto Surf gate intentionally uses Morty's Fog Badge, not Chuck's Storm
Badge, because you must Surf to reach Chuck. Other legacy per-region mappings
are preserved.

## Save compatibility and scope

The new `ITEM_OMNI_TOOL` enum value is **appended** after `ITEM_HUB_RETURN` and
before `ITEMS_COUNT`; no existing item ID or saved item value is renumbered.
Its presence in the Bag is the only persisted change. No story flag or Pokémon
data is modified.

Implementation surfaces: `src/field_move.c` (shared strict badge/lead predicate),
`src/scrcmd.c` (object/obstacle scripts), `src/field_player_avatar.c`
(Surf initiation), `src/party_menu.c` and `src/swsh_party_menu.c`
(Fly/Flash), `src/debug.c` (Cheats grant). Static regression:
`test/overworld/ValidateMosaicOmniTool.py`. Gameplay CI builds a real
optimized GBA ROM separately; human runtime inspection remains valuable.
