#pragma once

#include "ofMain.h"

class Line : public ofPolyline {

	ofParameter<float> width;
	// ofVboMesh mesh;
	ofPath path;

	vector<ofVec3f> normals;
	vector<ofVec3f> points;

	ofVec3f rightVector;

	vector<uint> indexData;

	ofVbo vbo;
	ofShader shader;

	public:
		class Builder;

		Line(ofParameter<float>& _width);

		~Line();

		void setupIndices();
		// void generateMesh();
		// void regenerateMesh();
		// void lineTo(float x, float y, float z = 0.0);
		// void curveTo(float x, float y, float z = 0.0);
		
		void draw();

	private:
		void changeWidth(float& w);
};

class Line::Builder {

	public:
		Builder& setWidth(ofParameter<float>& w) { width.makeReferenceTo(w); return *this; };

		shared_ptr<Line> build(){
			shared_ptr<Line> ptr(new Line{width});
			return ptr;
		}

	private:
		ofParameter<float> width;
};
