#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>

class filemanager {
public:
	static std::vector<std::string> getListOfDrives() { // get all drives
		std::vector<std::string> arrayOfDrives;

		char* szDrives = new char[MAX_PATH]();

		if (GetLogicalDriveStringsA(MAX_PATH, szDrives)) {
			for (int i = 0; i < 100; i += 4)
				if (szDrives[i] != (char)0) {
					arrayOfDrives.push_back(std::string{ szDrives[i],szDrives[i + 1],szDrives[i + 2] });
				}
		}

		delete[] szDrives;
		return arrayOfDrives;
	}


	static std::vector<std::wstring> getListOfFiles(std::wstring& path) { // get all files in path
		std::vector<std::wstring> arrayOfFiles = {};

		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		std::wstring spec = path + L"//*";

		hFind = FindFirstFile(spec.c_str(), &ffd);

		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

					arrayOfFiles.push_back(ffd.cFileName);
				}
			} while (FindNextFile(hFind, &ffd) != 0);

			FindClose(hFind);
		}
	
		return arrayOfFiles;
	}

	static std::vector<std::wstring> getListOfFolders(std::wstring& path) { // get all folders in path
		std::vector<std::wstring> arrayOfFolders = {};

		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		std::wstring spec = path + L"//*";

		hFind = FindFirstFile(spec.c_str(), &ffd);

		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

					arrayOfFolders.push_back(ffd.cFileName);
				}
			} while (FindNextFile(hFind, &ffd) != 0);

			FindClose(hFind);
		}

		return arrayOfFolders;
	}
};