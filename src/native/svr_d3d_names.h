// SvR 2010 addresses for the XDK D3D functions that re:Blue's renderer hooks by name.
//
// Force-included into the native renderer sources (cmake/native_renderer.cmake), so
// REX_HOOK(D3DDevice_Clear, ...) overrides SvR's recompiled sub_826E1B90 and
// __imp__D3DDevice_Clear calls its original body. Each entry was matched from SvR 2009's map (2009's
// came from 2008's) and confirmed by behaviour: the device fields it writes and the functions it calls (Present calls this Scissor,
// SetRenderTarget, SynchronizeToPresentationInterval, Swap and Resolve). Functions not listed
// here are either not used by SvR's engine or not identified yet; a hook that names one fails to
// compile on purpose.

#pragma once

// Device / frame
#define D3DDevice_Present                     sub_826DAFC8
#define D3DDevice_Swap                        sub_826DA968
#define D3DDevice_SynchronizeToPresentationInterval sub_826DA538
#define D3DDevice_Resolve                     sub_826E5858
#define D3DDevice_Clear                       sub_826E1B90
#define D3DDevice_SetRenderTarget             sub_826E0288
#define D3DDevice_SetDepthStencilSurface      sub_826E05D8
#define D3DDevice_SetScissorRect              sub_826DF898

// Draws. 2009 links no D3DDevice_DrawVertices (non-indexed draws go through BeginVertices or
// DrawIndexedVertices), so its hook is compiled out (SVR_NO_DRAW_VERTICES).
#define SVR_NO_DRAW_VERTICES 1
#define D3DDevice_BeginVertices               sub_826E47A0
#define D3DDevice_EndVertices                 sub_826E4790
#define D3DDevice_DrawIndexedVertices         sub_826E4C38

// Buffers: the game creates, locks and unlocks its own; the renderer only observes Unlock
// (svr_geometry.cpp). D3DDevice_CreateVertexBuffer sub_826E3730, D3DDevice_CreateIndexBuffer
// sub_826E3808 and D3DVertexBuffer_Lock sub_826E46F8 are matched but deliberately NOT mapped:
// gpu/hooks/resource.cpp's REX_HOOKs would replace them.
#define D3DVertexBuffer_Unlock                sub_826E37F8
#define D3DIndexBuffer_Unlock                 sub_826DB0C8

// Resource creation
#define D3DDevice_CreateVertexDeclaration     sub_826E2D50
#define D3DDevice_CreateVertexShader          sub_826E3218
#define D3DDevice_CreatePixelShader           sub_826E3030

// State
#define D3DDevice_SetTexture                  sub_826DD150
#define D3DDevice_SetVertexShader             sub_826E2A30
#define D3DDevice_SetPixelShader              sub_826E2828
#define D3DDevice_SetVertexDeclaration        sub_826E2C48
#define D3DDevice_SetStreamSource             sub_826DF9E0
#define D3DDevice_SetIndices                  sub_826DFB00

// Original bodies (__imp__ = the recompiled function, for hooks that call through).
#define __imp__D3DDevice_Present              __imp__sub_826DAFC8
#define __imp__D3DDevice_Swap                 __imp__sub_826DA968
#define __imp__D3DDevice_Resolve              __imp__sub_826E5858
#define __imp__D3DDevice_Clear                __imp__sub_826E1B90
#define __imp__D3DDevice_SetTexture           __imp__sub_826DD150
#define __imp__D3DDevice_SetRenderTarget      __imp__sub_826E0288
#define __imp__D3DDevice_SetDepthStencilSurface __imp__sub_826E05D8
#define __imp__D3DDevice_SetScissorRect       __imp__sub_826DF898
#define __imp__D3DDevice_BeginVertices        __imp__sub_826E47A0
#define __imp__D3DDevice_EndVertices          __imp__sub_826E4790
#define __imp__D3DDevice_DrawIndexedVertices  __imp__sub_826E4C38
#define __imp__D3DDevice_CreateVertexDeclaration __imp__sub_826E2D50
#define __imp__D3DDevice_CreateVertexShader   __imp__sub_826E3218
#define __imp__D3DDevice_CreatePixelShader    __imp__sub_826E3030
#define __imp__D3DDevice_SetVertexShader      __imp__sub_826E2A30
#define __imp__D3DDevice_SetPixelShader       __imp__sub_826E2828
#define __imp__D3DDevice_SetVertexDeclaration __imp__sub_826E2C48
#define __imp__D3DDevice_SetStreamSource      __imp__sub_826DF9E0
#define __imp__D3DDevice_SetIndices           __imp__sub_826DFB00
#define __imp__D3DVertexBuffer_Unlock         __imp__sub_826E37F8
#define __imp__D3DIndexBuffer_Unlock          __imp__sub_826DB0C8

// Resource description getters. Their re:Blue hooks are not wired to the game under SvR (the
// names themselves are not mapped), so these only have to link: Surface GetDesc is an exact match
// (sub_826DD028); the two LevelDesc getters are the closest matches, unverified.
#define __imp__D3DSurface_GetDesc             __imp__sub_826DD028
#define __imp__D3DTexture_GetLevelDesc        __imp__sub_826DB2C8
#define __imp__D3DVolumeTexture_GetLevelDesc  __imp__sub_826DC4C8
