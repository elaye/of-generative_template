#include "ofApp.h"

void ofApp::setup(){
	setupRenderers();
	setupParameters();
	setupFbo();
	setupGui();

	generate();

	shader.load("shaders/shader_vert.glsl", "shaders/shader_frag.glsl");
	saver.setup(4, true);
}

void ofApp::setupRenderers(){
	defaultRenderer = ofGetCurrentRenderer();
	cairoRenderer = ofPtr<ofCairoRenderer>(new ofCairoRenderer);
	cairoRenderer->setupMemoryOnly(ofCairoRenderer::IMAGE, true, false, ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));  
}

void ofApp::setupParameters(){
	parameters.setName("Parameters");
	parameters.add(nbObjects.set("Nb objects", 9, 1, 12));
	parameters.add(scale1.set("Scale 1", 1.0, 0.0, 100.0));
	parameters.add(scale2.set("Scale 2", 1.0, 0.0, 100.0));
	parameters.add(lineWidth.set("Line width", 30.0, 1.0, 100.0));

	nbObjects.addListener(this, &ofApp::changeNbObjects);
}

void ofApp::setupGui(){
	gui.setup(parameters);
}

void ofApp::setupFbo(){
	ofFbo::Settings fboSettings;
	fboSettings.width = ofGetWidth();
	fboSettings.height = ofGetHeight();
	fboSettings.internalformat = GL_RGBA32F;
	fboSettings.numSamples = 16;

	fbo.allocate(fboSettings);
}

void ofApp::generate(){
	for(int i = 0; i < nbObjects; ++i){
		shared_ptr<Object> object = Object::Builder().setParam1(scale1)
								.setParam2(scale2)
								.build();
		objects.push_back(object);
	}

	float r = 200.0;
	// ofPoint p(0, 0);
	ofPoint p(ofGetWidth()/2.0, ofGetHeight()/2.0);
	line.addVertex(r+p.x, p.y);
	int n = 20;
	for(int i = 1; i < n; ++i){
		float a = 2.0 * M_PI * float(i) / float(n);
		line.lineTo(r * cos(a) + p.x, r * sin(a) + p.y);
	}
	line.close();
}

void ofApp::changeNbObjects(int& n){
	regenerate();
}

void ofApp::regenerate(){
	objects.clear();
	generate();
}

void ofApp::update(){

}

void ofApp::draw(){
	ofBackgroundGradient(ofColor(40), ofColor(0), OF_GRADIENT_CIRCULAR);

	ofSetCurrentRenderer(cairoRenderer);
	// cam.begin();
		ofBackground(ofColor::black);
		ofSetColor(ofColor::white);
		ofSetLineWidth(lineWidth);
		line.draw();
	// cam.end();
	ofSetCurrentRenderer(defaultRenderer);

	// cairoRenderer->flush();
	cairoImage.setFromPixels(cairoRenderer->getImageSurfacePixels());

	fbo.begin();
		ofClear(0, 0, 0, 255);
		cam.begin();
			saver.setCameraData( cam.getPosition() + ofVec3f(0,0,1), cam.getPosition(), cam.getUpDir() );
			saver.begin();

				shader.begin();
					shader.setUniform2f("res", ofGetWidth(), ofGetHeight());
					shader.setUniform1f("time", ofGetElapsedTimef());
					drawObjects();	
				shader.end();
		
				// cairoImage.draw(0, 0);
				cairoImage.draw(-ofGetWidth()/2.0, -ofGetHeight()/2.0);

		cam.end();
	fbo.end();

	ofSetColor(ofColor::white);
	fbo.draw(0, 0);
	saver.end();

	gui.draw();
}

void ofApp::drawObjects(){
	for(auto& o : objects){
		o->draw();
	}
}
void ofApp::keyPressed(int key){
	switch(key){
		case 's':
			saver.finish("img.tiff", true);
			break;
	}
}