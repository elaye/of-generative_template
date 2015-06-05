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
	ofPolyline line;

	ofPtr<ofBaseRenderer> defaultRenderer;
	ofPtr<ofCairoRenderer> cairoRenderer;

	ofImage cairoImage;
	
	public:
		void setup();
		void setupRenderers();
		void setupParameters();
		void setupGui();
		void setupFbo();

		void update();
		void draw();

		void keyPressed(int key);
		
	private:
		void generate();
		void regenerate();
		void changeNbObjects(int& n);
		void drawObjects();
};
