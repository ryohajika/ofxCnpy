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
		if(full_dir_path.size() == 0){
			_export_dir_full = ofFilePath::getAbsolutePath("");
		}else{
			if(!ofDirectory::doesDirectoryExist(full_dir_path)){
				bool _b = ofDirectory::createDirectory(full_dir_path, false, true);
				if(!_b){
					ofLogError("ofxCnpy::DirectoryDealer",
							   "got an error during creating directory(ies)");
					return false;
				}
			}else{
				_export_dir_full = full_dir_path;
			}
		}
		
		if(ofDirectory::doesDirectoryExist(_export_dir_full)){
			ofLogNotice("ofxCnpy::DirectoryDealer",
						"directory set to: " + _export_dir_full);
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
			_export_file_name = file_name.substr(0, file_name.find(_export_file_ext) - 1);
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
        if(file_name.find(kNpyExt) != std::string::npos){
            dd_.setExportFilename(file_name.substr(0, file_name.find(kNpyExt)-1),
                                  kNpyExt);
        }else{
            dd_.setExportFilename(file_name, kNpyExt);
        }
        cnpy::npy_save(dd_.getExportFileNameFull(), data.data(), shape, "w");
        return true;
	}
};

struct NpzExporter {
	DirectoryDealer dd_;
	std::vector<size_t>* _base_shape = nullptr;
	size_t _base_frame_elements = 0;
	size_t _frame_count = 0;
	const std::string kNpzExt = "npz";
	bool bFirstData;
	
	inline bool setExportDir(std::string path){
		return dd_.setExportDirectory(path);
	}
	
	bool openNpz(std::vector<size_t>* base_shape,
				 std::string file_name){
		bFirstData = true;
		_base_shape = base_shape;
		_base_frame_elements = 0;
		_frame_count = 0;
		
		_base_frame_elements = _base_shape->at(0);
		for(int i=1; i<_base_shape->size(); i++){
			_base_frame_elements *= _base_shape->at(i);
		}
		
		// check if the directory exists first
		if(file_name.find(kNpzExt) != std::string::npos){
			dd_.setExportFilename(file_name.substr(0, file_name.find(kNpzExt)-1),
								  kNpzExt);
		}else{
			dd_.setExportFilename(file_name, kNpzExt);
		}
		return true;
	}
	bool closeNpz(){
		_base_shape = nullptr;
	}
	
	template<class T>
	bool update(std::vector<T> &data){
 		if(data.size() != _base_frame_elements){
			ofLogError("ofxCnpy::NpzExporter", "frame size invalid, aborted.");
			return false;
		}else{
			if(bFirstData){
				cnpy::npz_save(dd_.getExportFileNameFull(),
							   std::to_string(_frame_count),
							   data.data(),
							   *_base_shape,
							   "w");
				bFirstData = false;
			}else{
				cnpy::npz_save(dd_.getExportFileNameFull(),
							   std::to_string(_frame_count),
							   data.data(),
							   *_base_shape,
							   "a");
			}
			_frame_count += 1;
			return true;
		}
	}
	
	inline size_t getCurrentFrameCount(){
		return _frame_count + 1;
	}
};

};	// namespace ofxCnpy
