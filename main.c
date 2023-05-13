/*
  AdrenalineUsbEnabler
  Copyright (C) 2023, Cat
  Copyright (C) 2016-2018, TheFloW

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <taihen.h>
#include <psp2/kernel/modulemgr.h>
#include <psp2/kernel/clib.h>

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp) {
  int res;

  uint32_t module_nid;
  uint32_t data_addr;

  // Tai module info
  tai_module_info_t tai_info;
  tai_info.size = sizeof(tai_module_info_t);
  res = taiGetModuleInfo("ScePspemu", &tai_info);
  if (res < 0)
    return SCE_KERNEL_START_FAILED;

  // Module info
  SceKernelModuleInfo mod_info;
  mod_info.size = sizeof(SceKernelModuleInfo);
  res = sceKernelGetModuleInfo(tai_info.modid, &mod_info);
  if (res < 0)
    return SCE_KERNEL_START_FAILED;

  module_nid = tai_info.module_nid;

  data_addr = (uint32_t)mod_info.segments[1].vaddr;

  uint32_t *unk = NULL;

  sceClibPrintf("patching!\n");

  if (module_nid == 0x2714F07D) { // 3.60 retail
    unk = (uint32_t *)(data_addr + 0x115644c);
  } else if (module_nid == 0x3F75D4D3) { // 3.65/3.67/3.68 retail
    unk = (uint32_t *)(data_addr + 0x115654c);
  } else {
    return SCE_KERNEL_START_FAILED;
  }

  // enable usbpspcm pairing
  unk[0] = 0x10;

  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
  return SCE_KERNEL_STOP_SUCCESS;
}
