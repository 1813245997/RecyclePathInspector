#pragma once
struct IFileMeta {
	std::wstring i_file_path;
	std::wstring r_file_path;
	std::wstring original_path;
	FILETIME delete_time;
};