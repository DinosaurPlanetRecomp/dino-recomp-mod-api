#ifndef __RECOMPEVENTS_H__
#define __RECOMPEVENTS_H__

// Events exported by base recomp

// Invoked at the start of game_tick, after the framebuffers have been swapped but before any game logic has ran.
#define RECOMP_ON_GAME_TICK_START_CALLBACK RECOMP_CALLBACK("*", recomp_on_game_tick_start)
// Invoked on game_tick after game logic has ran but before the display list and tick has been ended.
// Use to add logic to the end of the game_tick logic.
#define RECOMP_ON_GAME_TICK_CALLBACK RECOMP_CALLBACK("*", recomp_on_game_tick)

#endif
