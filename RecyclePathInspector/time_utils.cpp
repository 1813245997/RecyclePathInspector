#include "stdafx.h"
#include "time_utils.h"

namespace utils {
	std::wstring filetime_to_string(const FILETIME& ft) {
		SYSTEMTIME stUTC, stLocal;
		FileTimeToSystemTime(&ft, &stUTC);
		SystemTimeToTzSpecificLocalTime(nullptr, &stUTC, &stLocal);

		wchar_t buf[64]{};
		swprintf_s(buf, L"%04d/%02d/%02d %02d:%02d:%02d",
			stLocal.wYear, stLocal.wMonth, stLocal.wDay,
			stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
		return buf;
	}
}
