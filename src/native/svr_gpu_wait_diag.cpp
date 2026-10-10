// Times the game's own wait for the emulated GPU. SvR's D3D (sub_826E6EA8, called each frame
// from sub_826E71E8) spins until the null GPU's command processor has passed a fence from an
// earlier frame. Nothing is drawn by that GPU, but the game still waits for it, so a command
// processor that falls behind costs frame time on the game's thread.

#include <rex/ppc.h>
#include <rex/hook.h>

#include "svr_frame_diag.h"

REX_EXTERN(__imp__sub_826E6EA8);

REX_HOOK_RAW(sub_826E6EA8) {
  bd::gpu::SvrDiagTimer wait(bd::gpu::SvrDiag::kGuestGpuWait);
  __imp__sub_826E6EA8(ctx, base);
}
