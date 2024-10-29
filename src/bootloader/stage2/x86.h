#pragma once

#include "stdint.h"

void _cdecl x86_div64_32(uint64_t dividend, uint32_t divisor, uint64_t* quotientOut, uint32_t* remainderOut);
void _cdecl x86_video_write_char(char c, uint8_t page);

bool _cdecl x86_disk_reset(uint8_t drive);
bool _cdecl x86_disk_read(uint8_t drive, uint16_t cylinder, uint16_t sector, uint8_t head, uint8_t count, void far* disk_out);
bool _cdecl x86_disk_get_params(uint8_t drive, uint8_t* disk_type_out, uint16_t* cylinders_out, uint16_t* sectors_out, uint16_t* heads_out);
