#pragma once

#include <stdint.h>

void _cdecl clear_screen();
void _cdecl putchar(char c);
char _cdecl getchar();
void _cdecl div64_32(uint64_t dividend, uint32_t divisor, uint64_t* quotient_out, uint32_t* remainder_out);
void _cdecl get_registers(uint16_t* ax, uint16_t* bx, uint16_t* cx, uint16_t* dx, uint16_t* si, uint16_t* di, uint16_t* sp, uint16_t* dp);
bool _cdecl disk_reset(uint8_t drive);
bool _cdecl disk_read(uint8_t drive, uint16_t cylinder, uint16_t sector, uint8_t head, uint8_t count, void far* disk_out);
bool _cdecl disk_get_params(uint8_t drive, uint8_t* disk_type_out, uint16_t* cylinders_out, uint16_t* sectors_out, uint16_t* heads_out);
