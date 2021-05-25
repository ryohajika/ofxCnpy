meta:
	ADDON_NAME = ofxCnpy
	ADDON_DESCRIPTION = OpenFrameworks wrapper of the cnpy library by @rogersce
	ADDON_AUTHOR = Ryo Hajika
	ADDON_TAGS = "python" "numpy" "ndarray" "utility"
	ADDON_URL = https://github.com/ryohajika/ofxCnpy.git

common:

	ADDON_INCLUDES += lib/cnpy/cnpy.h
	ADDON_SOURCES += lib/cnpy/cnpy.cpp

	ADDON_SOURCES_EXCLUDE += lib/example1.cpp
	ADDON_SOURCES_EXCLUDE += lib/mat2npz
	ADDON_SOURCES_EXCLUDE += lib/npy2mat
	ADDON_SOURCES_EXCLUDE += lib/npz2mat
