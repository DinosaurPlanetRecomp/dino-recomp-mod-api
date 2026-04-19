#pragma once

#include "modding.h"

typedef int RecompSaveDataBool;

/// Invoked when the game loads a save slot, but before recomp loads its extended save data.
///
/// void recomp_savedata_on_load(long slotno)
#define RECOMP_SAVEDATA_ON_LOAD RECOMP_CALLBACK("*", recomp_savedata_on_load)
/// Invoked after recomp loads its extended save data.
///
/// void recomp_savedata_on_loaded(long slotno)
#define RECOMP_SAVEDATA_ON_LOADED RECOMP_CALLBACK("*", recomp_savedata_on_loaded)

/// Invoked when the game signals to save a save slot, but before recomp saves its extended save data.
///
/// void recomp_savedata_on_save(long slotno)
#define RECOMP_SAVEDATA_ON_SAVE RECOMP_CALLBACK("*", recomp_savedata_on_save)
/// Invoked after recomp saves its extended save data.
///
/// void recomp_savedata_on_saved(long slotno)
#define RECOMP_SAVEDATA_ON_SAVED RECOMP_CALLBACK("*", recomp_savedata_on_saved)

RECOMP_IMPORT("*", void recomp_savedata_set_custom_data(const char *extensionName, void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", RecompSaveDataBool recomp_savedata_get_custom_data(const char *extensionName, void **outData, unsigned long *outSizeBytes));
