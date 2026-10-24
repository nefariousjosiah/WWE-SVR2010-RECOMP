// Guards for game code that crashes here but not on the console (config/default.toml hooks).
//
// Render command 24 (issue #13): the game queues render commands for its render thread, which runs
// them in sub_821E1FA0 (a switch on the command type). Command 24 calls a method of an object the
// command holds (its vtable slot 6). In Road to WrestleMania with a created superstar, after the
// backstage brawl, the object can be destroyed before its command runs: its vtable is then its
// abstract base's, slot 6 is _purecall (sub_826B4E80), and _purecall aborts the game. The call is
// skipped instead, so the command does nothing.

#include <rex/logging.h>
#include <rex/ppc.h>

#include <atomic>
#include <cstdint>

// sub_821E1FA0, command 24, about to call r8 (bctrl at 0x821E2160): true skips the call.
bool SvrDeadObjectCallHook(PPCRegister& r8) {
  constexpr uint32_t kPureCall = 0x826B4E80;  // _purecall: "R6025 pure virtual function call", abort
  if (r8.u32 != kPureCall)
    return false;
  static std::atomic<uint32_t> skipped{0};
  if (skipped.fetch_add(1, std::memory_order_relaxed) < 8)
    REXLOG_WARN("Render command 24 for a destroyed object skipped (pure virtual call)");
  return true;
}
