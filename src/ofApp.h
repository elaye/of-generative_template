#pragma once

#include "ofMain.h"

#include "ofxGui.h"

#include "TileSaver.h"

#include "Object.h"
#include "Line.h"

class ofApp : public ofBaseApp{

	ofParameter<int> nbObjects;

	ofParameter<float> scale1;
	ofParameter<float> scale2;

	ofParameter<float> lineWidth;
	
	ofParameterGroup parameters; 

	ofxPanel gui;

	ofFbo fbo;
	ofShader shader;
	ofEasyCam cam;

	TileSaver saver;

	vector<shared_ptr<Object>> objects;
	shared_ptr<Line> line;

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
	private:
		void generate();
		void regenerate();
		void changeNbObjects(int& n);
		void drawObjects();
};
