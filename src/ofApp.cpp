#include "ofApp.h"

void ofApp::setup(){
	parameters.setName("Parameters");
	parameters.add(nbObjects.set("Nb objects", 9, 1, 12));
	parameters.add(scale1.set("Scale 1", 1.0, 0.0, 100.0));
	parameters.add(scale2.set("Scale 2", 1.0, 0.0, 100.0));

	nbObjects.addListener(this, &ofApp::changeNbObjects);

	shader.load("shaders/shader_vert.glsl", "shaders/shader_frag.glsl");

	gui.setup(parameters);

	generate();
}

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
	ofBackgroundGradient(ofColor(40), ofColor(0), OF_GRADIENT_CIRCULAR);

	cam.begin();
		shader.begin();
			shader.setUniform2f("res", ofGetWidth(), ofGetHeight());
			shader.setUniform1f("time", ofGetElapsedTimef());
			drawObjects();	
		shader.end();
	cam.end();

	gui.draw();
}

void ofApp::drawObjects(){
	for(auto& o : objects){
		o->draw();
	}
}
void ofApp::keyPressed(int key){

}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
