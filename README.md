# MGDF - Pass-The-File

## Context
This game jam is all about sharing a single save file, across multiple games. How you use the data within, is fully up to you!

The <b>M</b>ulti <b>G</b>ame <b>D</b>ata <b>F</b>ile is designed to be used in many ways, by many games.

## Rules
- All games must use the save file provided by the jam.
- No additional persistent data may be stored in any way.
- Games may not add new fields to the save file. (Games may ignore fields they do not need of course)
- Games must support the command-line argument: -load <file path> (example: game.exe -load "C:/games/mysave.mgdf")
- When launched with a valid file path, the game must load directly into a playable state.
- If launched without the -load argument, or if the specified file does not exist, the game may respond in any way the developer chooses (e.g., show a menu, start a new game, etc.).
- Games must autosave whenever data changes.
- If no save file exists when saving, the game must create a new one in the same folder as the executable.
- Due to the above rules and requirements, all games must be executable on Windows.

## The Launcher
A launcher will be provided where a player can select different save files, and which games to play, or to enter Shuffler mode. The launcher will be able so show some information about your game, which will be read by providing a "gameinfo.info" in the same folder as the executable.
Screenshots must be png format.
