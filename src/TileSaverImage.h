#pragma once

#include "ofMain.h"

class TileSaverImage {

	int rows, cols;
	float colWidth, rowHeight;
	float width, height;

	ofFbo fbo, post;
	ofShader shader;

	public:
		void init(int rows, int cols, float colWidth, float rowHeight);
		void addPixels(float x, float y, ofTexture& tex);

		void done(string filename);

	private:
		void postProcess();
		void save(string filename, ofFbo& _fbo);
};