#pragma once
#include <iostream>
#include <Windows.h>

#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4129)

class Registry {
private:

	LPCWSTR DisableTaskMgr = L"DisableTaskMgr";
	HKEY hKey = HKEY_CURRENT_USER;
	LPCWSTR TMGR_PATH = (L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System\\");
	DWORD val_disable = 1;
	DWORD val_enable = 0;

public:
	void EnableT_MGR();
};

void Registry::EnableT_MGR()
{
	RegOpenKeyExW(hKey, TMGR_PATH, 0, KEY_ALL_ACCESS, &hKey);

	if (RegQueryValueExW(hKey, DisableTaskMgr, NULL, NULL, NULL, NULL) == ERROR_FILE_NOT_FOUND)
	{

		if (RegSetValueExW(hKey, DisableTaskMgr, 0, REG_DWORD, (const BYTE*)&val_enable, sizeof(val_enable)) != ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			exit(0);
			return;
		}
		else
		{
			RegCloseKey(hKey);
		}
	}
	else
	{
		RegSetValueExW(hKey, DisableTaskMgr, 0, REG_DWORD, (const BYTE*)&val_enable, sizeof(val_enable));
		RegCloseKey(hKey);
		return;
	}

	return;
}