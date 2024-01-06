#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include "zip/zip.h"
#include "FindProjects.h"
#include "filemanager.h"

class Zip {
public:
	struct ZipFile {
		std::wstring name;
		std::wstring path;
	};
	
	static std::vector<ZipFile> ZipProjects(std::vector<FindProjects::Project> projects) {
		
		std::vector<ZipFile> ZipFiles;
		
		// Get temp folder path
		std::string tempFolderPath = getenv("TEMP") + (std::string)"\\" + "BlwicSNSgj1QfW8Auq1p";
		std::wstring tempFolderPathW = std::wstring(tempFolderPath.begin(), tempFolderPath.end());
		
		
        for(auto& project : projects) {		
			char ctemppath[MAX_PATH];
			
			std::wstring zippath = tempFolderPathW + L"\\" + project.name + L".zip";
			
			wcstombs(ctemppath, zippath.c_str(), MAX_PATH);
			
			if (!std::filesystem::is_directory(tempFolderPathW) || !std::filesystem::exists(tempFolderPathW)) {
				std::filesystem::create_directory(tempFolderPathW);
			}
			
			struct zip_t* zip = zip_open(ctemppath, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w'); {
				ZipFolder(zip, project.path, project.path, project.name);
			}
			
			zip_close(zip);

			ZipFile f;
			f.path = zippath;
			f.name = project.name;
			
			ZipFiles.push_back(f);
			
		}
		
		
		return ZipFiles;
	}

	static void RemoveTempFolder() {
		std::filesystem::remove_all(getenv("TEMP") + (std::string)"\\" + "BlwicSNSgj1QfW8Auq1p");
	}

private:
	static void ZipFolder(struct zip_t* zip, std::wstring path, const std::wstring startpath, const std::wstring projectname) {;	
		for (auto& file : filemanager::getListOfFiles(path)) {
			std::wstring currentzippath = path;
			currentzippath.erase(0, startpath.length());
			currentzippath = projectname + L"\\" + currentzippath;
			currentzippath += file;
			
			char cfile[MAX_PATH];
			char ccurrentzippath[MAX_PATH];
			
			std::wstring filepath = path + file;
			
			wcstombs(cfile, filepath.c_str(), MAX_PATH);
			wcstombs(ccurrentzippath, currentzippath.c_str(), MAX_PATH);
			
			zip_entry_open(zip, ccurrentzippath);
			zip_entry_fwrite(zip, cfile);
			zip_entry_close(zip);
		}

		for (auto& folder : filemanager::getListOfFolders(path)) {
			if(folder != L"." && folder != L".." && folder != L".vs") {
				ZipFolder(zip, path + folder + L"\\", startpath, projectname);
			}
		}
	}
};