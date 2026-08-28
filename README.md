# Skill Issue Roaster

Every time you die in Geometry Dash, you get a fresh passive-aggressive roast, complete with a "New Best"-style bounce-in animation.

## Features

- 20 roasts
- Your death percent is baked into several of the roasts
- Bounce-in pop animation at the moment of death, cleared on respawn
- Toggleable overlay in the mod settings

## Installation

### Through Geode (recommended)

1. Install the [Geode](https://geode-sdk.org) mod loader for Geometry Dash 2.2081
2. Grab `bwomp.skill-issue-roaster.geode` from [Releases](https://github.com/BwompBwompBwomp/skill-issue-roaster/releases)
3. Drop it into your mods folder, or drag it onto the game window

### From source

```sh
git clone https://github.com/BwompBwompBwomp/skill-issue-roaster
cd skill-issue-roaster
GEODE_SDK=/path/to/geode/sdk geode build
```

## Supported platforms

- macOS (universal arm64 + x86_64) — GD 2.2081
- Windows — GD 2.2081 (build on Windows)

## Add your own roasts

Edit `kRoasts` in `src/main.cpp`. Use `{:.0f}%` anywhere in a line to insert the player's death percent.

Example roast samples:

```cpp
"Skill issue.",
"{:.0f}% never stood a chance",
"practice mode is free. use it",
"L. rubber-stamped.",
```

## Feedback

Issues and roast submissions welcome via [GitHub Issues](https://github.com/BwompBwompBwomp/skill-issue-roaster/issues).
