#ifndef __RECOMPEVENTS_H__
#define __RECOMPEVENTS_H__

// Events exported by base recomp

// Invoked at the start of game_tick, after the framebuffers have been swapped but before any game logic has ran.
#define RECOMP_ON_GAME_TICK_START_CALLBACK RECOMP_CALLBACK("*", recomp_on_game_tick_start)
// Invoked on game_tick after game logic has ran but before the display list and tick has been ended.
// Use to add logic to the end of the game_tick logic.
#define RECOMP_ON_GAME_TICK_CALLBACK RECOMP_CALLBACK("*", recomp_on_game_tick)

// void recomp_on_tex_load(s32 *id)
#define RECOMP_ON_TEX_LOAD_CALLBACK RECOMP_CALLBACK("*", recomp_on_tex_load)
// void recomp_on_tex_loaded_frame_rom(s32 id, s32 frame, Texture *tex)
#define RECOMP_ON_TEX_LOADED_FRAME_ROM_CALLBACK RECOMP_CALLBACK("*", recomp_on_tex_loaded_frame_rom)
// void recomp_on_tex_loaded_frame(s32 id, s32 frame, Texture *tex)
#define RECOMP_ON_TEX_LOADED_FRAME_CALLBACK RECOMP_CALLBACK("*", recomp_on_tex_loaded_frame)
// void recomp_on_tex_loaded(s32 id, Texture *tex)
#define RECOMP_ON_TEX_LOADED_CALLBACK RECOMP_CALLBACK("*", recomp_on_tex_loaded)

// void recomp_on_model_load(s32 *id)
#define RECOMP_ON_MODEL_LOAD_CALLBACK RECOMP_CALLBACK("*", recomp_on_model_load)
// void recomp_on_model_loaded_rom(s32 id, Model *model)
#define RECOMP_ON_MODEL_LOADED_ROM_CALLBACK RECOMP_CALLBACK("*", recomp_on_model_loaded_rom)
// void recomp_on_model_loaded(s32 id, Model *model)
#define RECOMP_ON_MODEL_LOADED_CALLBACK RECOMP_CALLBACK("*", recomp_on_model_loaded)

// void recomp_on_model_instance_loaded(s32 id, ModelInstance *modelInst)
#define RECOMP_ON_MODEL_INSTANCE_LOADED_CALLBACK RECOMP_CALLBACK("*", recomp_on_model_instance_loaded)

// void recomp_on_block_loaded_rom(s32 id, Block *block)
#define RECOMP_ON_BLOCK_LOADED_ROM_CALLBACK RECOMP_CALLBACK("*", recomp_on_block_loaded_rom)
// void recomp_on_block_loaded(s32 id, Block *block)
#define RECOMP_ON_BLOCK_LOADED_CALLBACK RECOMP_CALLBACK("*", recomp_on_block_loaded)

#endif
