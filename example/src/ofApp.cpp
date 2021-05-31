#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	npy.setExportDir("");	// give an empty string to export file
							// to the data directory of the project
	npz.setExportDir("/Users/ryohajika/Desktop");
							// or specify full path for the export directory
	// in this example, we make three channels of Fbos
	// so that we can demonstrate multiple frames export
	npy_frame_base = {0, CHANNEL_COUNT, 512, 512};
							// in NPY, put total frame count to the first
							// element at the end of the recording
	npz_frame_base = {CHANNEL_COUNT, 512, 512};
							// in the case of NPZ, we only define
							// the basic frame size so that the
							// frame count will be updated by
							// the NpzExporter itself
	bRecording = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	for(int i=0; i<20; i++){
		unsigned r = ofRandom(0,3);
		switch(r){
			case 0:
				ofSetColor(ofColor::red);
				break;
			case 1:
				ofSetColor(ofColor::green);
				break;
			case 2:
				ofSetColor(ofColor::blue);
				break;
			default:
				ofSetColor(ofColor::white);
				break;
		}
		ofDrawCircle(ofRandom(0, 512), ofRandom(0, 512), ofRandom(-200, 200),
					 50);
	}
	ofDisableBlendMode();
	
	ofImage img;
	img.grabScreen(0, 0, 512, 512);
	
	// processing for NPY/NPZ recording
	if(bRecording){
		ctr_for_npy += 1;
		for(int i=0; i<CHANNEL_COUNT; i++){
			// NPY
			// stuck frame data up to a vector
			// https://stackoverflow.com/questions/7278347/c-pointer-array-to-vector/15203325
			unsigned char *ptr = img.getPixels().getChannel(i).getData();
			std::vector<unsigned char> p(ptr, ptr + 512 * 512);
			raw_data_for_npy.insert(raw_data_for_npy.end(),
									p.begin(), p.end());
			
			// NPZ
			// put all the data to a buffer
			raw_data_for_npz.insert(raw_data_for_npz.end(),
									p.begin(), p.end());
		}
		// NPZ
		// update the elements
		npz.update(raw_data_for_npz);
		raw_data_for_npz.clear();
	}
	
	ofSetColor(ofColor::white);
	if(bRecording){
		ofDrawBitmapString("Recording....", 20, 20);
	}else{
		ofDrawBitmapString("Not recording", 20, 20);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	// here is initializing/saving demo of NPY/NPZ
	if(key == ' '){
		bRecording = !bRecording;
		
		if(bRecording == false){	// stop recording
			// NPY
			// update frame size vector first then we can export data
			npy_frame_base[0] = ctr_for_npy + 1;
			npy.saveToNpy(raw_data_for_npy,
						  npy_frame_base,
						  std::to_string(ofGetUnixTime())+".npy");
			// NPZ
			// close the file
			npz.closeNpz();
			
			// maybe clean up the data buffer?
			// https://stackoverflow.com/questions/35514909/how-to-clear-vector-in-c-from-memory
			if(raw_data_for_npy.size())
				std::vector<unsigned int>().swap(raw_data_for_npy);
			if(raw_data_for_npz.size())
				std::vector<unsigned int>().swap(raw_data_for_npz);
		}else{						// start recording
			// NPY
			// only initializing buffer vector is required
			// all the data needs to be kept in a buffer
			// then export all at the end of recording
			// also counter variable needs to be prepared
			ctr_for_npy = 0;
			npy_frame_base[0] = 0;
			if(raw_data_for_npy.size())
				std::vector<unsigned int>().swap(raw_data_for_npy);
			// NPZ
			// initialization is required
			// whenever we get a new frame, we can export
			// it to NPZ accordingly
			// no counter variable is required
			if(raw_data_for_npz.size())
				std::vector<unsigned int>().swap(raw_data_for_npz);
			npz.openNpz(&npz_frame_base,
						std::to_string(ofGetUnixTime())+".npz");
			
			bRecording = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
