#pragma once

#include "modding.h"

typedef int ReAssetBool;

/* ----- EVENTS ---------------------*/

/// Invoked before any ReAsset stages.
/// IDs and namespaces can be defined here.
#define REASSET_ON_INIT RECOMP_CALLBACK("*", reasset_on_init)

/// Stage 1: Full FST overrides. Redefines what ReAsset considers "base" assets.
/// FST get/set functions are allowed to be called.
#define REASSET_ON_FST_SET RECOMP_CALLBACK("*", reasset_on_fst_set)
#define REASSET_ON_FST_SET_LOW_PRIORITY RECOMP_CALLBACK("*", reasset_on_fst_set_low_priority)

/// Stage 2: Asset additions and replacements.
/// Set and link functions are allowed to be called.
#define REASSET_ON_SET RECOMP_CALLBACK("*", reasset_on_set)
#define REASSET_ON_SET_LOW_PRIORITY RECOMP_CALLBACK("*", reasset_on_set_low_priority)

/// Stage 3: Asset modifications.
/// Set, get, delete, and iterator functions are allowed to be called.
#define REASSET_ON_MODIFY RECOMP_CALLBACK("*", reasset_on_modify)
#define REASSET_ON_MODIFY_LOW_PRIORITY RECOMP_CALLBACK("*", reasset_on_modify_low_priority)

/// Stage 4: Asset ID resolution & final patching.
/// Get, iterator, and resolve map functions are allowed to be called.
#define REASSET_ON_RESOLVE RECOMP_CALLBACK("*", reasset_on_resolve)

/// Stage 5: Rebuilt FST.
/// Only resolve map functions are allowed to be called from this point onward. 
#define REASSET_ON_COMMITTED RECOMP_CALLBACK("*", reasset_on_committed)


/* ----- NAMESPACES ---------------------*/

typedef unsigned long ReAssetNamespace;

#define REASSET_BASE_NAMESPACE 0
#define REASSET_INVALID_NAMESPACE ((ReAssetNamespace)-1)

RECOMP_IMPORT("*", ReAssetNamespace reasset_namespace(const char *name));


/* ----- NAMESPACED IDENTIFIERS ---------------------*/

/// A namespace:identifier pair.
/// If namespace is zero, this represents a base asset.
typedef unsigned long ReAssetID;
typedef long ReAssetLocalID;

RECOMP_IMPORT("*", ReAssetID reasset_id(ReAssetNamespace nmspace, ReAssetLocalID identifier));
RECOMP_IMPORT("*", ReAssetID reasset_base_id(long identifier));
RECOMP_IMPORT("*", ReAssetID reasset_auto_id(ReAssetNamespace nmspace));
RECOMP_IMPORT("*", ReAssetBool reasset_id_lookup(ReAssetID id, ReAssetNamespace *outNamespace, long *outIdentifier));
RECOMP_IMPORT("*", ReAssetBool reasset_id_lookup_name(ReAssetID id, const char **outNamespaceName, long *outIdentifier));


/* ----- ITERATORS ---------------------*/

typedef unsigned long ReAssetIterator;

RECOMP_IMPORT("*", ReAssetBool reasset_iterator_destroy(ReAssetIterator iterator));
RECOMP_IMPORT("*", ReAssetBool reasset_iterator_next(ReAssetIterator iterator, ReAssetID *outID));


/* ----- RESOLVE MAPS ---------------------*/

typedef unsigned long ReAssetResolveMap;

RECOMP_IMPORT("*", long reasset_resolve_map_lookup(ReAssetResolveMap map, ReAssetID id));
RECOMP_IMPORT("*", ReAssetNamespace reasset_resolve_map_owner_of(ReAssetResolveMap map, long resolvedIdentifier));
RECOMP_IMPORT("*", ReAssetBool reasset_resolve_map_id_of(ReAssetResolveMap map, long resolvedIdentifier, ReAssetID *outID));
RECOMP_IMPORT("*", ReAssetIterator reasset_resolve_map_create_iterator(ReAssetResolveMap map));


/* ----- FST ---------------------*/

RECOMP_IMPORT("*", void reasset_fst_set(long fileID, const void *data, unsigned long size));
/// Does not make a copy of data.
RECOMP_IMPORT("*", void reasset_fst_set_static(long fileID, const void *data, unsigned long size));
RECOMP_IMPORT("*", unsigned long reasset_fst_get_file_size(long fileID));
RECOMP_IMPORT("*", void reasset_fst_read_from_file(long fileID, void *dst, unsigned long offset, unsigned long size));


/* ----- ASSET - ANIMS ---------------------*/

RECOMP_IMPORT("*", void reasset_anims_set(ReAssetID id, ReAssetNamespace owner, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_anims_get(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", ReAssetIterator reasset_anims_create_iterator(void));
RECOMP_IMPORT("*", void reasset_anims_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_anims_get_resolve_map(void));


/* ----- ASSET - ANIM CURVES ---------------------*/

RECOMP_IMPORT("*", void reasset_anim_curves_set(ReAssetID id, long eventCount, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_anim_curves_get(ReAssetID id, long *outEventCount, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", ReAssetIterator reasset_anim_curves_create_iterator(void));
RECOMP_IMPORT("*", void reasset_anim_curves_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_anim_curves_get_resolve_map(void));


/* ----- ASSET - BITS ---------------------*/

typedef enum BitSaveType {
    BITSAVETYPE_NEVER = 0,
    BITSAVETYPE_CHECKPOINT = 1,
    BITSAVETYPE_ALWAYS = 2,
    BITSAVETYPE_MAP = 3
} BitSaveType;

RECOMP_IMPORT("*", void reasset_bits_add(ReAssetID id, long length, BitSaveType saveType));
RECOMP_IMPORT("*", void reasset_bits_add_task(ReAssetID id, long length, BitSaveType saveType, long task));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_bits_get_resolve_map(void));


/* ----- ASSET - BLOCKS ---------------------*/

RECOMP_IMPORT("*", void reasset_blocks_set(ReAssetID trkblkID, ReAssetID id, ReAssetNamespace owner, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_blocks_get(ReAssetID trkblkID, ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", ReAssetIterator reasset_blocks_create_iterator(ReAssetID trkblkID));
RECOMP_IMPORT("*", void reasset_blocks_link(ReAssetID trkblkID, ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_blocks_get_resolve_map(ReAssetID trkblkID));


/* ----- ASSET - HITS ---------------------*/

RECOMP_IMPORT("*", void reasset_hits_set(ReAssetID trkblkID, ReAssetID blockID, ReAssetID id, ReAssetNamespace owner, const void *data));
RECOMP_IMPORT("*", void reasset_hits_set_bulk(ReAssetID trkblkID, ReAssetID blockID, ReAssetNamespace owner, ReAssetID *idArray, const void **dataArray, long count));
RECOMP_IMPORT("*", void* reasset_hits_get(ReAssetID trkblkID, ReAssetID blockID, ReAssetID id));
RECOMP_IMPORT("*", void reasset_hits_delete(ReAssetID trkblkID, ReAssetID blockID, ReAssetID id));
RECOMP_IMPORT("*", ReAssetIterator reasset_hits_create_iterator(ReAssetID trkblkID, ReAssetID blockID));
RECOMP_IMPORT("*", void reasset_hits_link(ReAssetID trkblkID, ReAssetID blockID, ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_hits_get_resolve_map(ReAssetID trkblkID, ReAssetID blockID));


/* ----- ASSET - MODELS ---------------------*/

RECOMP_IMPORT("*", void reasset_models_set(ReAssetID id, ReAssetNamespace owner, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void reasset_models_set_modanims(ReAssetID id, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void reasset_models_set_amap(ReAssetID id, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_models_get(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", void* reasset_models_get_modanims(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", void* reasset_models_get_amap(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", ReAssetIterator reasset_models_create_iterator(void));
RECOMP_IMPORT("*", void reasset_models_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_models_get_resolve_map(void));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_models_get_modanims_resolve_map(void));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_models_get_amap_resolve_map(void));

RECOMP_IMPORT("*", void reasset_model_indices_set(ReAssetID id, ReAssetID modelID));
RECOMP_IMPORT("*", ReAssetBool reasset_model_indices_get(ReAssetID id, ReAssetID *outModelID));
RECOMP_IMPORT("*", ReAssetIterator reasset_model_indices_create_iterator(void));
RECOMP_IMPORT("*", void reasset_model_indices_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_model_indices_get_resolve_map(void));


/* ----- ASSET - MAPS ---------------------*/

RECOMP_IMPORT("*", void reasset_maps_set_header(ReAssetID id, const void *data));
RECOMP_IMPORT("*", void* reasset_maps_get_header(ReAssetID id));
RECOMP_IMPORT("*", void reasset_maps_set_blocks(ReAssetID id, ReAssetNamespace owner, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_maps_get_blocks(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", void reasset_maps_set_grid_a1(ReAssetID id, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_maps_get_grid_a1(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", void reasset_maps_set_grid_a2(ReAssetID id, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_maps_get_grid_a2(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", void reasset_maps_set_grid_b1(ReAssetID id, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_maps_get_grid_b1(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", void reasset_maps_set_grid_b2(ReAssetID id, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_maps_get_grid_b2(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", ReAssetIterator reasset_maps_create_iterator(void));
RECOMP_IMPORT("*", void reasset_maps_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_maps_get_resolve_map(void));


/* ----- ASSET - MAP OBJECTS ---------------------*/

RECOMP_IMPORT("*", void reasset_map_objects_set(ReAssetID mapID, ReAssetID id, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_map_objects_get(ReAssetID mapID, ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", void reasset_map_objects_delete(ReAssetID mapID, ReAssetID id));
RECOMP_IMPORT("*", ReAssetIterator reasset_map_objects_create_iterator(ReAssetID mapID));
RECOMP_IMPORT("*", void reasset_map_objects_link(ReAssetID mapID, ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_map_objects_get_resolve_map(ReAssetID mapID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_map_objects_get_global_resolve_map(void));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_map_objects_get_curve_resolve_map(void));


/* ----- ASSET - MPEG ---------------------*/

RECOMP_IMPORT("*", void reasset_mpeg_set(ReAssetID id, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_mpeg_get(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", ReAssetIterator reasset_mpeg_create_iterator(void));
RECOMP_IMPORT("*", void reasset_mpeg_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_mpeg_get_resolve_map(void));


/* ----- ASSET - MUSIC ACTIONS ---------------------*/

RECOMP_IMPORT("*", void reasset_music_actions_set(ReAssetID id, ReAssetNamespace owner, const void *data));
RECOMP_IMPORT("*", void* reasset_music_actions_get(ReAssetID id));
RECOMP_IMPORT("*", ReAssetIterator reasset_music_actions_create_iterator(void));
RECOMP_IMPORT("*", void reasset_music_actions_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_music_actions_get_resolve_map(void));


/* ----- ASSET - OBJECTS ---------------------*/

RECOMP_IMPORT("*", void reasset_objects_set(ReAssetID id, ReAssetNamespace owner, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_objects_get(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", ReAssetIterator reasset_objects_create_iterator(void));
RECOMP_IMPORT("*", void reasset_objects_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_objects_get_resolve_map(void));

RECOMP_IMPORT("*", void reasset_object_indices_set(ReAssetID id, ReAssetID objID));
RECOMP_IMPORT("*", ReAssetBool reasset_object_indices_get(ReAssetID id, ReAssetID *outObjID));
RECOMP_IMPORT("*", ReAssetIterator reasset_object_indices_create_iterator(void));
RECOMP_IMPORT("*", void reasset_object_indices_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_object_indices_get_resolve_map(void));


/* ----- ASSET - OBJECT SEQUENCES ---------------------*/

RECOMP_IMPORT("*", void reasset_object_sequences_set(ReAssetID id, ReAssetNamespace owner, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void reasset_object_sequences_set_ex(ReAssetID id, ReAssetNamespace owner, ReAssetID map, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_object_sequences_get(ReAssetID id, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", void reasset_object_sequences_set_curve(ReAssetID id, long actor, long eventCount, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_object_sequences_get_curve(ReAssetID id, long actor, long *outEventCount, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", ReAssetIterator reasset_object_sequences_create_iterator(void));
RECOMP_IMPORT("*", void reasset_object_sequences_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_object_sequences_get_resolve_map(void));


/* ----- ASSET - TEXTURES ---------------------*/

typedef enum TextureBank {
    /// TEX0
    TEX_BANK_0,
    /// TEX1
    TEX_BANK_1
} TextureBank;

RECOMP_IMPORT("*", void reasset_textures_set(TextureBank bank, ReAssetID id, long numFrames, const void *data, unsigned long sizeBytes));
RECOMP_IMPORT("*", void* reasset_textures_get(TextureBank bank, ReAssetID id, long *outNumFrames, unsigned long *outSizeBytes));
RECOMP_IMPORT("*", ReAssetIterator reasset_textures_create_iterator(TextureBank bank));
RECOMP_IMPORT("*", void reasset_textures_link(TextureBank bank, ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_textures_get_resolve_map(TextureBank bank));

RECOMP_IMPORT("*", void reasset_texture_table_set(ReAssetID id, TextureBank bank, ReAssetID texID));
RECOMP_IMPORT("*", ReAssetBool reasset_texture_table_get(ReAssetID id, TextureBank *outBank, ReAssetID *outTexID));
RECOMP_IMPORT("*", ReAssetIterator reasset_texture_table_create_iterator(void));
RECOMP_IMPORT("*", void reasset_texture_table_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_texture_table_get_resolve_map(void));


/* ----- ASSET - TRKBLK ---------------------*/

RECOMP_IMPORT("*", ReAssetIterator reasset_trkblk_create_iterator(void));
RECOMP_IMPORT("*", void reasset_trkblk_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", ReAssetResolveMap reasset_trkblk_get_resolve_map(void));


/* ----- SPECIAL ASSET - DLLS ---------------------*/

typedef enum DLLBank {
    /// 0x1000-0x2000
    DLL_BANK_MODGFX = 1,
    /// 0x2000-0x4000
    DLL_BANK_PROJGFX = 2,
    /// 0x4000-0x8000
    ///
    /// This bank is unused by the game and has been repurposed for use by misc recomp DLLs.
    /// Custom DLLs are *not* required to use this bank, it's just an option!
    DLL_BANK_RECOMP = 3,
    /// 0x8000-0xFFFF
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

/// Registers a custom DLL within the specified DLL bank.
///
/// Notes:
/// - Custom engine DLLs are not supported. Consider using the recomp bank instead for those cases.
/// - The constructor/destructor functions take a RecompCustomDLL pointer instead of a DLLFile pointer.
RECOMP_IMPORT("*", void reasset_dlls_set(ReAssetID id, DLLBank bank, unsigned short exportCount, 
    RecompCustomDLLFunc ctor, RecompCustomDLLFunc dtor, void *vtblPtr));
RECOMP_IMPORT("*", void reasset_dlls_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", long reasset_dlls_lookup(ReAssetID id));


/* ----- SPECIAL ASSET - MENUS ---------------------*/

RECOMP_IMPORT("*", void reasset_menus_set(ReAssetID id, ReAssetID dll));
RECOMP_IMPORT("*", void reasset_menus_link(ReAssetID id, ReAssetID externID));
RECOMP_IMPORT("*", long reasset_menus_lookup(ReAssetID id));
