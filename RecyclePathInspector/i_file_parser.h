#pragma once
 
class IFileParser {
public:
	static bool parse(const std::filesystem::path& path, IFileMeta& out_meta);
};