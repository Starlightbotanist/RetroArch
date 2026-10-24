#ifndef RETRO_CHECKPOINT_H
#define RETRO_CHECKPOINT_H

#include <stdint.h>
#include <libretro.h>

/* Temporary command IDs pending libretro API approval. */
#define RETRO_ENVIRONMENT_SET_CHECKPOINT_INTERFACE (RETRO_ENVIRONMENT_PRIVATE | 0x5053)
#define RETRO_CHECKPOINT_INTERFACE_VERSION 2
#define RETRO_ENVIRONMENT_GET_CHECKPOINT_SPECULATIVE (RETRO_ENVIRONMENT_PRIVATE | 0x5054)

/* Writes whether prediction/replay is active to a bool. Defer renderer changes
 * while true; the frontend rejects SET_SYSTEM_AV_INFO during these frames. */

/* Register during retro_init/retro_load_game with version and size set. The
 * frontend requires this version and a complete structure, copies known fields
 * and ignores extra fields.
 *
 * The frontend owns handles for one core instance; release before core unload.
 * Never serialize handles. create/save/load/release use retro_run's thread and
 * hardware context; supported/valid only inspect metadata.
 *
 * Failed save preserves previous contents. load never consumes the handle;
 * failure leaves emulation unchanged. Reset, ordinary loads and renderer
 * changes may invalidate contents; valid then returns false. */
struct retro_checkpoint_interface
{
   uint32_t version;
   uint32_t size;
   bool (RETRO_CALLCONV *supported)(void);
   void *(RETRO_CALLCONV *create)(void);
   bool (RETRO_CALLCONV *save)(void *checkpoint);
   bool (RETRO_CALLCONV *load)(const void *checkpoint);
   void (RETRO_CALLCONV *release)(void *checkpoint);
   bool (RETRO_CALLCONV *valid)(const void *checkpoint);
};

#endif
