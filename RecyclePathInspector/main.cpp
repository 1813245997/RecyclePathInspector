#include "stdafx.h"
#include "recycle_scanner.h"

std::wstring escape_csv_field(const std::wstring& field) {
	std::wstring escaped = field;
	size_t pos = 0;
	while ((pos = escaped.find(L"\"", pos)) != std::wstring::npos) {
		escaped.insert(pos, L"\"");
		pos += 2;
	}
	return L"\"" + escaped + L"\"";
}

int wmain() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	_setmode(_fileno(stdout), _O_U16TEXT);

	auto files = RecycleScanner::instance().scan_all_recycle_bins();

	// Console output
	for (const auto& f : files) {
		std::wcout << L"\n[File Info]" << std::endl;
		std::wcout << L"  $I Path: " << f.i_file_path << std::endl;
		std::wcout << L"  $R Path: " << f.r_file_path << std::endl;
		std::wcout << L"  Original Path: " << f.original_path << std::endl;
		std::wcout << L"  Deleted Time: " << utils::filetime_to_string(f.delete_time) << std::endl;
	}

	// Write to CSV file
	std::wofstream csv_file(L"recycle_report.csv", std::ios::binary);
	csv_file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

	if (csv_file.is_open()) {
		std::wcout << L"[Info] Writing CSV to: " << std::filesystem::absolute(L"recycle_report.csv") << std::endl;

		// CSV header
		csv_file << L"$I Path,$R Path,Original Path,Deleted Time\n";

		for (const auto& f : files) {
			csv_file
				<< escape_csv_field(f.i_file_path) << L","
				<< escape_csv_field(f.r_file_path) << L","
				<< escape_csv_field(f.original_path) << L","
				<< escape_csv_field(utils::filetime_to_string(f.delete_time)) << L"\n";
		}

		csv_file.close();
		std::wcout << L"\n[Success] CSV report saved to 'recycle_report.csv'" << std::endl;
	}
	else {
		std::wcerr << L"[Error] Failed to open output CSV file." << std::endl;
	}

	system("pause");
	return 0;
}
