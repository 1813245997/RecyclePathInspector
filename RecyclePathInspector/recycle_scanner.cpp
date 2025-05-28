#include "stdafx.h"
#include "recycle_scanner.h"
RecycleScanner& RecycleScanner::instance() {
	static RecycleScanner singleton;
	return singleton;
}

std::vector<IFileMeta> RecycleScanner::scan_all_recycle_bins() {
 
	std::vector<IFileMeta> results;

	 
	DWORD drive_mask = GetLogicalDrives();
	if (drive_mask == 0) {
		std::wcerr << L"[Error] Failed to retrieve drive information." << std::endl;
		return results;
	}

	for (wchar_t drive = L'A'; drive <= L'Z'; ++drive) {
		if (!(drive_mask & (1 << (drive - L'A')))) continue;

		std::wstring root_path = std::wstring(1, drive) + L":\\";
		std::filesystem::path recycle_root = root_path + L"$Recycle.Bin";

		if (!std::filesystem::exists(recycle_root)) continue;

		try {
			for (const auto& entry : std::filesystem::directory_iterator(recycle_root, std::filesystem::directory_options::skip_permission_denied)) {
				if (!entry.is_directory()) continue;

				const std::filesystem::path& sid_dir = entry.path();
 
				std::unordered_set<std::wstring> r_file_names;
				for (const auto& file : std::filesystem::directory_iterator(sid_dir, std::filesystem::directory_options::skip_permission_denied)) {
					const std::filesystem::path& path = file.path();
					if (path.filename().wstring().starts_with(L"$R")) {
						r_file_names.insert(path.filename().wstring());
					}
				}

			 
				for (const auto& file : std::filesystem::directory_iterator(sid_dir, std::filesystem::directory_options::skip_permission_denied)) {
					const std::filesystem::path& path = file.path();

					if (path.filename().wstring().starts_with(L"$I")) {
						 
						std::wcout << L"[Found $I File] " << path << std::endl;
						IFileMeta meta{};
						if (IFileParser::parse(path, meta)) {
							 
							std::wstring r_file_name = L"$R" + path.filename().wstring().substr(2);
							std::filesystem::path r_file_path = sid_dir / r_file_name;

							if (r_file_names.count(r_file_name) && std::filesystem::exists(r_file_path)) {
								meta.r_file_path = r_file_path.wstring();
							}
							else {
								meta.r_file_path = L"(Corresponding $R file not found)";

							}
							 

							results.push_back(meta);
						}
						else {
							std::wcerr << L"[Failed to parse] " << path << std::endl;
						}
						

						 
					}
				}
			}
		}
		catch (const std::exception& ex) {
			std::wcerr << L"[Exception] Error occurred while processing drive " << root_path << L": " << ex.what() << std::endl;
		}
	}

	return results;
}