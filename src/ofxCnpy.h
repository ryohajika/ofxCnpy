#pragma once

#include <unordered_map>
#include "cnpy.h"
#include "ofFileUtils.h"

enum CNPY_FILE_TYPE {
	CNPY_NPY = 0,
	CNPY_NPZ = 1
};

namespace ofxCnpy {

struct DirectoryDealer {
	bool setExportDirectory(std::string full_dir_path){
		
	}
};

struct NpyExporter {
	DirectoryDealer dd_;
};

struct NpzExporter {
	
};

};	// namespace ofxCnpy

class ofxCnpy {
	public:
		ofxCnpy(){
			_data_dim.clear();
			_export_path = ofFilePath::getAbsolutePath("");
		}
		~ofxCnpy(){
			
		}
	
		void init(std::vector<size_t> &shape,
				  std::string full_dir_path,
				  std::string file_name){
			_export_path = full_dir_path;
			this->init(shape, file_name);
		}
		
		void init(std::vector<size_t> &shape,
				  std::string file_name){
			_b_initial_data = true;
			_data_dim = shape;
			
			if(file_name.find_last_of(".npy") != std::string::npos){
				_file_type = CNPY_NPY;
			}
			else if(file_name.find_last_of(".npz") != std::string::npos){
				_file_type = CNPY_NPZ;
			}else{
				// error: file ext specified is not suitable
			}
		}
		void setShape(std::vector<size_t> &shape){
			_data_dim = shape;
		}
		inline std::vector<size_t>* getShape(){
			return &_data_dim;
		}
	
		CNPY_FILE_TYPE getFileType(){
			
		}
		inline std::string getFileTypeExt(){
			
		}
	
		void setExportDir(std::string full_dir_path){
			_export_path = full_dir_path;
		}
		inline std::string getExportDir(){
			return _export_path;
		}
	
	
	private:
		CNPY_FILE_TYPE _file_type;
		const std::unordered_map<short int, std::string> CNPY_EXT_PAIR = {
			{0, ".npy"},
			{1, ".npz"}
		};
		std::vector<size_t> _data_dim;
		bool _b_initial_data;

		std::string _export_path;
		std::string _export_name;
};
