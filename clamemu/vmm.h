/*
 *  ClamAV bytecode emulator VMM
 *
 *  Copyright (C) 2011 Sourcefire, Inc.
 *
 *  Authors: Török Edvin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 */
#ifndef VMM_H
#define VMM_H

#include "cltypes.h"
struct emu_vmm;
struct cli_exe_section;
struct cli_pe_hook_data;

typedef struct emu_vmm emu_vmm_t;

enum {
    flag_r=0,
    flag_w,
    flag_x
};

enum {
    EMU_ERR_GENERIC=1,
    EMU_ERR_VMM_READ,
    EMU_ERR_VMM_WRITE
};

emu_vmm_t *cli_emu_vmm_new(struct cli_pe_hook_data *pedata, struct cli_exe_section *sections, int fd);
int cli_emu_vmm_read8(emu_vmm_t *v, uint32_t va, uint32_t *value);
int cli_emu_vmm_read16(emu_vmm_t *v, uint32_t va, uint32_t *value);
int cli_emu_vmm_read32(emu_vmm_t *v, uint32_t va, uint32_t *value);
int cli_emu_vmm_read_r(emu_vmm_t *v, uint32_t va, void *value, uint32_t len);
int cli_emu_vmm_read_x(emu_vmm_t *v, uint32_t va, void *value, uint32_t len);
char* cli_emu_vmm_read_string(emu_vmm_t *v, uint32_t va, uint32_t maxlen);

int cli_emu_vmm_write8(emu_vmm_t *v, uint32_t va, uint32_t  value);
int cli_emu_vmm_write16(emu_vmm_t *v, uint32_t va, uint32_t value);
int cli_emu_vmm_write32(emu_vmm_t *v, uint32_t va, uint32_t value);
int cli_emu_vmm_write(emu_vmm_t *v, uint32_t va, const void *value, uint32_t len);

int cli_emu_vmm_alloc(emu_vmm_t *v, uint32_t amount, uint32_t *va);
int cli_emu_vmm_prot_set(emu_vmm_t *v, uint32_t va, uint32_t len, uint8_t rwx);
int cli_emu_vmm_prot_get(emu_vmm_t *v, uint32_t va);

struct cli_emu;
typedef int (*import_handler_t)(struct cli_emu *, const char *desc, unsigned bytes);
struct import_description {
    import_handler_t handler;
    char *description;
    unsigned bytes;
};


struct import_description *cli_emu_vmm_get_import(const emu_vmm_t *v, uint32_t addr);

uint32_t cli_emu_vmm_rva2va(emu_vmm_t *v, uint32_t rva);
int cli_emu_vmm_rebuild(emu_vmm_t *v);
void cli_emu_vmm_free(emu_vmm_t *v);
#define MAPPING_END 0xf0000000
#endif
