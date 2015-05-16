#include "ofApp.h"

void ofApp::setup(){
	parameters.setName("Parameters");
	parameters.add(scale.set("Scale", 1.0, 0.0, 100.0));

	shader.load("shaders/shader_vert.glsl", "shaders/shader_frag.glsl");

	gui.setup(parameters);
}

void ofApp::update(){

}

void ofApp::draw(){
	ofBackgroundGradient(ofColor(40), ofColor(0), OF_GRADIENT_CIRCULAR);

	cam.begin();
		shader.begin();
			shader.setUniform2f("res", ofGetWidth(), ofGetHeight());
			shader.setUniform1f("time", ofGetElapsedTimef());
			
		shader.end();
	cam.end();

	gui.draw();
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
