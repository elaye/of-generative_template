#include "ofApp.h"

void ofApp::setup(){
	setupRenderers();
	setupParameters();
	// setupFbo();
	setupGui();

	generate();

	// shader.load("shaders/shader_vert.glsl", "shaders/shader_frag.glsl");
	// saver.setup(4, true);

	bHasChanged = true;
	bParameters = true;
	bSave = false;

	scale = 8;
}

void ofApp::setupRenderers(){
	defaultRenderer = ofGetCurrentRenderer();
	cairoRenderer = ofPtr<ofCairoRenderer>(new ofCairoRenderer);
	cairoRenderer->setupMemoryOnly(ofCairoRenderer::IMAGE, false, true, ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));  

	cairoSaveRenderer = ofPtr<ofCairoRenderer>(new ofCairoRenderer);
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

// void ofApp::setupFbo(){
// 	ofFbo::Settings fboSettings;
// 	fboSettings.width = ofGetWidth();
// 	fboSettings.height = ofGetHeight();
// 	fboSettings.internalformat = GL_RGBA32F;
// 	fboSettings.numSamples = 16;

// 	fbo.allocate(fboSettings);
// }

void ofApp::generate(){
	for(int i = 0; i < nbObjects; ++i){
		shared_ptr<Object> object = Object::Builder().setParam1(scale1)
								.setParam2(scale2)
								.build();
		objects.push_back(object);
	}
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
	ofBackground(ofColor::white);

	if(bHasChanged || bSave){
		if(bSave){
			ofSetCurrentRenderer(cairoSaveRenderer);
			cr = cairoSaveRenderer->getCairoContext();
		}
		else{
			ofSetCurrentRenderer(cairoRenderer);
			cr = cairoRenderer->getCairoContext();
		}
			ofBackground(ofColor::white);
			ofSetLineWidth(lineWidth);
			cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
			cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
			if(bSave){
				cairo_scale(cr, scale, scale);
			}
			drawObjects();

		ofSetCurrentRenderer(defaultRenderer);

		if(bSave){
			cairoSaveRenderer->close();
			bSave = false;
		}
		else{
			cairoRenderer->flush();
			cairoImage.setFromPixels(cairoRenderer->getImageSurfacePixels());
			bHasChanged = false;
		}
	}

	ofSetColor(ofColor::white);
	cairoImage.draw(0, 0, ofGetWidth(), ofGetHeight());

	// fbo.begin();
	// 	ofClear(0, 0, 0, 255);
	// 	cam.begin();
	// 		saver.setCameraData( cam.getPosition() + ofVec3f(0,0,1), cam.getPosition(), cam.getUpDir() );
	// 		saver.begin();

	// 			shader.begin();
	// 				shader.setUniform2f("res", ofGetWidth(), ofGetHeight());
	// 				shader.setUniform1f("time", ofGetElapsedTimef());
	// 				drawObjects();	
	// 			shader.end();
		
	// 			// cairoImage.draw(0, 0);
	// 			cairoImage.draw(-ofGetWidth()/2.0, -ofGetHeight()/2.0);

	// 	cam.end();
	// fbo.end();

	// ofSetColor(ofColor::white);
	// fbo.draw(0, 0);
	// saver.end();

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
			// saver.finish("img.tiff", true);
			bSave = true;
			cairoSaveRenderer->setup("output.tiff", ofCairoRenderer::IMAGE, false, true, ofRectangle(0, 0, scale*ofGetWidth(), scale*ofGetHeight()));
			break;
	}
}