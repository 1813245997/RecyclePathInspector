#pragma once
class RecycleScanner {
public:
	static RecycleScanner& instance();
	std::vector<IFileMeta> scan_all_recycle_bins();

private:
	RecycleScanner() = default;
};