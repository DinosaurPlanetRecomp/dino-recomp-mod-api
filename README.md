# Dinosaur Planet: Recompiled - Mod API
This repository contains headers for creating mods for [Dinosaur Planet: Recompiled](https://github.com/DinosaurPlanetRecomp/dino-recomp), including:

- Macros for annotating function patches, hooks, and more.
- Imports for all functions made available to mods from recomp itself.

## Writing Mods
Please see the [Recomp Modding](https://hackmd.io/fMDiGEJ9TBSjomuZZOgzNg) document for a general explanation of the N64 recomp modding framework.

> [!TIP]
> You will also need the [Decomp Bridge](https://github.com/DinosaurPlanetRecomp/dino-recomp-decomp-bridge) to create your mod. Please see the [official mod template](https://github.com/DinosaurPlanetRecomp/dino-recomp-mod-template) for an example setup.

## Versioning
Mod API releases are associated with a specific version of the recomp. For example, to target version 0.1.2 of the recomp you would use version 0.1.2 of this repository. The `minimum_recomp_version` property of your mod's TOML manifest should equal the version of this repository that you compile against.

Please do not use commits ahead of the latest tagged version for published mods as it does not guarantee your mod will work correctly on any stable recomp release.
