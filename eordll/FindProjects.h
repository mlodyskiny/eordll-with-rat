#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "filemanager.h"

class FindProjects {
public:
	struct Project {
		std::wstring name;
		std::wstring path;
	};

	static std::vector<Project> SearchForProjects() {
		
		std::vector<Project> Projects;
		
		std::vector<std::wstring> wDrives;
		for (auto drive : filemanager::getListOfDrives()) {
			wDrives.push_back(std::wstring(drive.begin(), drive.end()));
		}
		
		for (auto& drive : wDrives) {
			Search(drive, Projects);
		}
		
		return Projects;
	}

private:
	static void Search(std::wstring path, std::vector<Project>& Projects) {
		bool skipFolder = false;
		static std::wstring LastFolder;
		static int i = 0;
		
		for (auto& file : filemanager::getListOfFiles(path)) {
			if (file == L"UE4.sln") {
				skipFolder = true;
				return;
			}
			if (file.find(L".sln") != std::wstring::npos) {
				Project p;
				p.path = path;
				p.name = LastFolder + std::to_wstring(i);
				Projects.push_back(p);
				i++;
			}
		}
		
		if (skipFolder) {
			skipFolder = false;
			return;
		}

		for (auto& folder : filemanager::getListOfFolders(path)) {
			if (folder != L"." && folder != L".." && folder != L"osu!" && folder != L"Windows") {
				LastFolder = folder;
				Search(path + folder + L"\\", Projects);
			}
		}
	}
};