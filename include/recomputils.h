#ifndef __RECOMPUTILS_H__
#define __RECOMPUTILS_H__

#include "modding.h"
#include "stdarg.h"

// N64ModernRuntime

RECOMP_IMPORT("*", void *recomp_alloc(unsigned long size))
RECOMP_IMPORT("*", void recomp_free(void *ptr))

// These functions let you get the return value of a function from within a return hook for that function.
// Calling these outside of a return hook will give an undefined result.
// Calling the function for a return type that doesn't match the function's actual return type also gives an undefined result.
RECOMP_IMPORT("*", long recomphook_get_return_s32(void));
RECOMP_IMPORT("*", unsigned long recomphook_get_return_u32(void));
RECOMP_IMPORT("*", void* recomphook_get_return_ptr(void));
RECOMP_IMPORT("*", short recomphook_get_return_s16(void));
RECOMP_IMPORT("*", unsigned short recomphook_get_return_u16(void));
RECOMP_IMPORT("*", signed char recomphook_get_return_s8(void));
RECOMP_IMPORT("*", unsigned char recomphook_get_return_u8(void));
RECOMP_IMPORT("*", long long recomphook_get_return_s64(void));
RECOMP_IMPORT("*", unsigned long long recomphook_get_return_u64(void));
RECOMP_IMPORT("*", float recomphook_get_return_float(void));
RECOMP_IMPORT("*", double recomphook_get_return_double(void));

typedef enum {
    // The dependency was found and the version requirement was met.
    DEPENDENCY_STATUS_FOUND = 0,
    // The ID given is not a dependency of the mod in question.
    DEPENDENCY_STATUS_INVALID_DEPENDENCY = 1,
    // The dependency was not found.
    DEPENDENCY_STATUS_NOT_FOUND = 2,
    // The dependency was found, but the version requirement was not met.
    DEPENDENCY_STATUS_WRONG_VERSION = 3
} DependencyStatus;

// Checks the status of the provided dependency. This is only relevant for optional dependencies,
// as the game wouldn't have started if a normal dependency wasn't met.
// Use the return value of this to prevent calling imported functions from optional dependencies that are missing.
// Try to avoid calling this function repeatedly, as it may incur some overhead. Instead, call it once at startup
// and store the result into a variable for reading later on.
RECOMP_IMPORT("*", DependencyStatus recomp_is_dependency_met(const char* dependency_id));


// Dino Recomp

typedef enum {
    RECOMP_ASPECT_ORIGINAL,
    RECOMP_ASPECT_EXPAND,
    RECOMP_ASPECT_MANUAL
} RecompAspectRatio;

typedef enum {
    RECOMP_HUD_ORIGINAL,
    RECOMP_HUD_CLAMP16X9,
    RECOMP_HUD_FULL
} RecompHUDRatio;

RECOMP_IMPORT("*", void recomp_get_window_resolution(unsigned long *width, unsigned long *height))
RECOMP_IMPORT("*", RecompAspectRatio recomp_get_aspect_ratio_mode(void))
RECOMP_IMPORT("*", float recomp_get_aspect_ratio(void))
RECOMP_IMPORT("*", RecompHUDRatio recomp_get_hud_ratio_mode(void))
RECOMP_IMPORT("*", int recomp_get_refresh_rate(void))
RECOMP_IMPORT("*", int recomp_get_60fps_enabled(void))

RECOMP_IMPORT("*", void recomp_error_message_box(const char *message))
RECOMP_IMPORT("*", void recomp_exit_with_error(const char *message))
RECOMP_IMPORT("*", void recomp_exit(void))
RECOMP_IMPORT("*", float recomp_powf(float x, float y))
RECOMP_IMPORT("*", unsigned long recomp_time_us(void))

RECOMP_IMPORT("*", int recomp_sprintf(char *s, const char *fmt, ...))
RECOMP_IMPORT("*", int recomp_vsprintf(char *s, const char *fmt, va_list args))

RECOMP_IMPORT("*", int recomp_printf(const char *fmt, ...))
RECOMP_IMPORT("*", int recomp_vprintf(const char *fmt, va_list args))
RECOMP_IMPORT("*", int recomp_eprintf(const char *fmt, ...))
RECOMP_IMPORT("*", int recomp_veprintf(const char *fmt, va_list args))
RECOMP_IMPORT("*", const char *recomp_vsprintf_helper(const char *fmt, va_list args))
RECOMP_IMPORT("*", const char *recomp_sprintf_helper(const char *fmt, ...))


#endif
