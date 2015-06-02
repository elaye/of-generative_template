#include "Line.h"

Line::Line(ofParameter<float>& _width){
	width.makeReferenceTo(_width);
	width.addListener(this, &Line::changeWidth);

	shader.load("shaders/line_vert.glsl", "shaders/line_frag.glsl", "shaders/line_geom.glsl");
}

Line::~Line(){
	width.removeListener(this, &Line::changeWidth);
}
//    ______
//    |   /|
//    |1 / |
//    | / 2|
// v0 |/___| v1
//    |   /|
//    |3 / |
//    | / 4|
//    |/___|
//

// void Line::generateMesh(){
// 	mesh.clear();
// 	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
// 	float halfWidth = width / 2.0;

// 	vector<ofPoint> points(getVertices());
// 	// ofLog() << points.size();

// 	ofVec3f v0(points[0]);
// 	ofVec3f n0(getNormalAtIndex(0));
// 	mesh.addVertex(v0);
// 	mesh.addVertex(v0 + halfWidth * n0);
// 	mesh.addVertex(v0 - halfWidth * n0);

// 	for(int i = 1; i < points.size(); ++i){
// 		ofVec3f v0(points[i - 1]);
// 		ofVec3f v1(points[i]);
// 		ofVec3f n1(getNormalAtIndex(i));
// 		// if(n1.dot(ofVec3f(1, 0, 0)) < 0.0){
// 			// n1 = -n1;
// 			// ofLog() << "m";
// 		// }
// 		// ofVec3f n1(getNormalAtIndexInterpolated(float(i)/float(points.size())));
// 		// n1.normalize();

// 		ofVec3f u(v0 - v1);
// 		u.normalize();
// 		ofVec3f v(u.cross(n1));
// 		// float l = halfWidth / v.dot(v);
// 		float l = halfWidth / v.dot(ofVec3f(1, 1, 1));

// 		// mesh.addVertex(v0);
// 		mesh.addVertex(v1);
// 		// mesh.addVertex(v0 + halfWidth * n0);
// 		mesh.addVertex(v1 + l * n1);
// 		// mesh.addVertex(v0 - halfWidth * n0);
// 		mesh.addVertex(v1 - l * n1);

// 		// 1
// 		mesh.addIndex(3 * i - 3);
// 		mesh.addIndex(3 * i - 2);
// 		mesh.addIndex(3 * i + 1);

// 		// 2
// 		mesh.addIndex(3 * i - 3);
// 		mesh.addIndex(3 * i + 1);
// 		mesh.addIndex(3 * i);
	
// 		// 3
// 		mesh.addIndex(3 * i - 3);
// 		mesh.addIndex(3 * i);
// 		mesh.addIndex(3 * i - 1);

// 		// 4
// 		mesh.addIndex(3 * i - 1);
// 		mesh.addIndex(3 * i);
// 		mesh.addIndex(3 * i + 2);
// 	}
// }

void Line::changeWidth(float& w){
	// regenerateMesh();
}

// void Line::regenerateMesh(){
	// mesh.clear();
	// generateMesh();
// }

void Line::setupIndices(){
	indexData.resize(size() * 4);

	indexData[0] = 1;
	indexData[1] = 0;
	indexData[2] = 1;
	indexData[3] = 2;

	for(int i = 1; i < size() - 2; ++i){
		indexData[4 * i] = i - 1;
		indexData[4 * i + 1] = i;
		indexData[4 * i + 2] = i + 1;
		indexData[4 * i + 3] = i + 2;
	}

	indexData[4 * size() - 4] = size() - 3;
	indexData[4 * size() - 3] = size() - 2;
	indexData[4 * size() - 2] = size() - 1;
	indexData[4 * size() - 1] = size() - 2;

	// ofLog() << size();
}

void Line::draw(){
	if(hasChanged()){
		indexData.clear();
		setupIndices();
		vbo.setVertexData(&(getVertices()[0]), size(), GL_DYNAMIC_DRAW);
		vbo.setIndexData(&(indexData[0]), indexData.size(), GL_DYNAMIC_DRAW);
	}
	// mesh.draw();
	// mesh.drawWireframe();
	shader.begin();
		shader.setUniform1f("lineWidth", width);
		// ofPolyline::draw();
		// vertexDataVbo.draw(poly.isClosed()?GL_LINE_LOOP:GL_LINE_STRIP, 0, poly.size());
		vbo.drawElements(GL_LINES_ADJACENCY, indexData.size() * 4);
		// vbo.drawElements(GL_LINE_STRIP_ADJACENCY, size() * 4);
		// vbo.drawElements(GL_LINE_STRIP, 0, size() * 4);
	shader.end();
}
