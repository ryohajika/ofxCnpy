#pragma once

#include "ofMain.h"
#include "ofxCnpy.h"

#define CHANNEL_COUNT 3

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxCnpy::NpyExporter npy;
		ofxCnpy::NpzExporter npz;
		std::vector<size_t> npy_frame_base;
		std::vector<size_t> npz_frame_base;
		std::vector<unsigned int> raw_data_for_npy;
		std::vector<unsigned int> raw_data_for_npz;
		size_t ctr_for_npy;
		bool bRecording;
};
