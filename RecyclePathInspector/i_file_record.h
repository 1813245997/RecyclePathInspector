#pragma once
 

#pragma pack(push, 1)
struct I_FILE_RECORD_V2 {
	uint64_t header;                      // 0x00: Version indicator (1 or 2)
	uint64_t file_size;                   // 0x08: Original file size
	uint64_t delete_time;                 // 0x10: Deletion time (in Windows FILETIME format)
	uint32_t reserved;                    // 0x18: Unknown / reserved (commonly zero)
	wchar_t original_path[MAX_PATH];      // 0x18: Original file path (UTF-16 null-terminated string)
};
#pragma pack(pop)
