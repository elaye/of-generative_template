#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	// ofGLWindowSettings settings;
	// settings.setGLVersion(4,3);
	// settings.width = 1024;
	// settings.height = 768;
	// settings.height = 717;
	// settings.windowMode = OF_WINDOW;
	// ofCreateWindow(settings);
//
	ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	// ofSetCurrentRenderer(ofCairoRenderer::TYPE);
	// ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofSetupOpenGL(1024, 717, OF_WINDOW);

	ofRunApp(new ofApp());
}
