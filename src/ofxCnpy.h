#pragma once

#include <unordered_map>
#include "cnpy.h"
#include "ofLog.h"
#include "ofFileUtils.h"
#include "ofUtils.h"

enum CNPY_FILE_TYPE {
	CNPY_NPY = 0,
	CNPY_NPZ = 1
};

namespace ofxCnpy {

struct DirectoryDealer {
	std::string _export_dir_full;
	std::string _export_file_name;
	std::string _export_file_ext;
	
	bool setExportDirectory(std::string full_dir_path){
		if(full_dir_path == ""){
			_export_dir_full = ofFilePath::getAbsolutePath("");
		}else{
			if(!ofDirectory::doesDirectoryExist(full_dir_path)){
				bool _b = ofDirectory::createDirectory(full_dir_path, false, true);
				if(!_b){
					ofLogError("ofxCnpy::DirectoryDealer",
							   "got an error during creating directory(ies)");
					return false;
				}
			}
		}
		
		if(ofDirectory::doesDirectoryExist(full_dir_path)){
			ofLogNotice("ofxCnpy::DirectoryDealer",
						"directory set to: " + full_dir_path);
			_export_dir_full = full_dir_path;
			return true;
		}else{
			ofLogError("ofxCnpy::DirectoryDealer",
					   "came across with some issue while setting exporting directory");
			return false;
		}
	}
	inline std::string getExportDirectoryFullPath(){
		return _export_dir_full;
	}
	
	bool setExportFilename(std::string file_name,
						   std::string extension){
		if(extension.find(".") != std::string::npos){
			_export_file_ext = extension.substr(extension.find(".")+1);
		}else{
			_export_file_ext = extension;
		}
		
		if(file_name.find(_export_file_ext) != std::string::npos){
			_export_file_name = file_name.substr(0, file_name.find(_export_file_ext));
		}else{
			_export_file_name = file_name;
		}
		
		if(ofFile::doesFileExist(_export_dir_full + "/" + _export_file_name + "." + _export_file_ext, false)){
			ofLogError("ofxCnpy::DirectoryDealer",
					   "there's a file in same file name under the specified directory");
			_export_file_name += "_" + std::to_string(ofGetUnixTime());
			ofLogNotice("ofxCnpy::DirectoryDealer",
						"new file name is: " + _export_file_name + "." + _export_file_ext);
		}
		
		ofLogNotice("ofxCnpy::DirectoryDealer",
					"Full path set as: " + _export_dir_full + "/" + _export_file_name + "." + _export_file_ext);
		return true;
	}
	inline std::string getExportFileNameFull(){
		return _export_dir_full + "/" + _export_file_name + "." + _export_file_ext;
	}
	inline std::string getExportFileNameOnly(){
		return _export_file_name;
	}
	inline std::string getExportFileExtensionOnly(){
		return _export_file_ext;
	}
};

struct NpyExporter {
	DirectoryDealer dd_;
	const std::string kNpyExt = "npy";
	
	inline bool setExportDir(std::string path){
		return dd_.setExportDirectory(path);
	}
	
	template<class T>
	bool saveToNpy(std::vector<T> &data,
				   std::vector<size_t> shape,
				   std::string file_name){
		// check if the directory exists first
//		if(!dd_.setExportDirectory(export_path)){
//			ofLogError("ofxCnpy::NpyExporter",
//					   "encountering directory generation issue so about the file saving");
//			return false;
//		}else{
        if(file_name.find(kNpyExt) != std::string::npos){
            dd_.setExportFilename(file_name.substr(0, file_name.find(kNpyExt)),
                                  kNpyExt);
        }else{
            dd_.setExportFilename(file_name, kNpyExt);
        }
        cnpy::npy_save(dd_.getExportFileNameFull(), &data[0], shape, "w");
        return true;
//		}
	}
};

struct NpzExporter {
	DirectoryDealer dd_;
	const std::string kNpzExt = "npz";
};

};	// namespace ofxCnpy
