// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XPAN_H
#define XPAN_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xpan_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XPan_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XPan;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XPan_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XPan_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XPan_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XPan_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XPan_Initialize(XPan *InstancePtr, UINTPTR BaseAddress);
XPan_Config* XPan_LookupConfig(UINTPTR BaseAddress);
#else
int XPan_Initialize(XPan *InstancePtr, u16 DeviceId);
XPan_Config* XPan_LookupConfig(u16 DeviceId);
#endif
int XPan_CfgInitialize(XPan *InstancePtr, XPan_Config *ConfigPtr);
#else
int XPan_Initialize(XPan *InstancePtr, const char* InstanceName);
int XPan_Release(XPan *InstancePtr);
#endif


void XPan_Set_ip(XPan *InstancePtr, u32 Data);
u32 XPan_Get_ip(XPan *InstancePtr);
u32 XPan_Get_ipEnc(XPan *InstancePtr);
u32 XPan_Get_ipEnc_vld(XPan *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
