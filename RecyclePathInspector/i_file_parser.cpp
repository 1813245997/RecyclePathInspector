#include "stdafx.h"
#include "i_file_parser.h"
 

bool IFileParser::parse(const std::filesystem::path& path, IFileMeta& out_meta) {
	 
	std ::ifstream file(path, std::ios::binary);
	if (!file) return false;

	I_FILE_RECORD_V2 record{};
	file.read(reinterpret_cast<char*>(&record), sizeof(record));

	if (record.header != 2) return false;

	FILETIME ft;
	ft.dwLowDateTime = static_cast<DWORD>(record.delete_time & 0xFFFFFFFF);
	ft.dwHighDateTime = static_cast<DWORD>((record.delete_time >> 32) & 0xFFFFFFFF);

	out_meta.i_file_path = path.wstring();
	out_meta.original_path = std::wstring(record.original_path);
	out_meta.delete_time = ft;

	return true;
}