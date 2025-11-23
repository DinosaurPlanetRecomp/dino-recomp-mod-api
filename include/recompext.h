#ifndef __RECOMPEXT_H__
#define __RECOMPEXT_H__

#include "modding.h"

typedef enum DLLBank {
    // NOTE: Custom engine DLLs are not supported! Consider using the recomp bank instead.
    // 0x0-0x1000
    //DLL_BANK_ENGINE = 0,
    // 0x1000-0x2000
    DLL_BANK_MODGFX = 1,
    // 0x2000-0x4000
    DLL_BANK_PROJGFX = 2,
    // 0x4000-0x8000
    //
    // This bank is unused by the game and has been repurposed for use by misc recomp DLLs.
    // Custom DLLs are *not* required to use this bank, it's just an option!
    DLL_BANK_RECOMP = 3,
    // 0x8000-0xFFFF
    DLL_BANK_OBJECTS = 4
} DLLBank;

struct RecompCustomDLL;

typedef void (*RecompCustomDLLFunc)(struct RecompCustomDLL *self);

typedef struct RecompCustomDLL {
    RecompCustomDLLFunc ctor;
    RecompCustomDLLFunc dtor;
    unsigned short exportCount;
    void *vtblPtr;
} RecompCustomDLL;

// Registers a custom DLL within the specified DLL bank.
// Returns the ID (not tab index!) of the custom DLL.
//
// Notes:
// - Custom engine DLLs are not supported. Consider using the recomp bank instead for those cases.
// - The constructor/destructor functions take a RecompCustomDLL pointer instead of a DLLFile pointer.
RECOMP_IMPORT("*", unsigned short recomp_register_dll(DLLBank bank, unsigned short exportCount, RecompCustomDLLFunc ctor, RecompCustomDLLFunc dtor, void *vtblPtr));
// Registers a custom menu, associated with the specified DLL.
// Returns the ID of the custom menu.
RECOMP_IMPORT("*", long recomp_register_menu(unsigned short dllID));

#endif
