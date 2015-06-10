#pragma once

#include "ofMain.h"

#include "ofxGui.h"

// #include "TileSaver.h"

#include "Object.h"

class ofApp : public ofBaseApp{

	ofParameter<int> nbObjects;

	ofParameter<float> scale1;
	ofParameter<float> scale2;

	ofParameter<float> lineWidth;
	
	ofParameterGroup parameters; 

	ofxPanel gui;

	// ofFbo fbo;
	// ofShader shader;
	// ofEasyCam cam;

	// TileSaver saver;

	vector<shared_ptr<Object>> objects;

	ofPtr<ofBaseRenderer> defaultRenderer;
	ofPtr<ofCairoRenderer> cairoRenderer;
	ofPtr<ofCairoRenderer> cairoSaveRenderer;
	cairo_t* cr;

	ofImage cairoImage;
	
	bool bHasChanged, bParameters, bSave;
	int scale;
	
	public:
		void setup();
		void setupRenderers();
		void setupParameters();
		void setupGui();
		// void setupFbo();

		void update();
		void draw();

		void keyPressed(int key);
		
	private:
		void generate();
		void regenerate();
		void changeNbObjects(int& n);
		void drawObjects();
};
