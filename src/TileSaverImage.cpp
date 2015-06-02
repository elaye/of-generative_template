#include "TileSaverImage.h"

void TileSaverImage::init(int _rows, int _cols, float _colWidth, float _rowHeight){
	rows = _rows;
	cols = _cols;
	colWidth = _colWidth;
	rowHeight = _rowHeight;
			
	width = colWidth * float(rows);
	height = rowHeight * float(cols);
	
	ofFbo::Settings fboSettings;
	fboSettings.width = width;
	fboSettings.height = height;
	fboSettings.internalformat = GL_RGBA;
	// fboSettings.internalformat = GL_RGBA32F;
	fbo.allocate(fboSettings);

	fbo.begin();
		ofClear(255, 255, 255, 0);
	fbo.end();

	post.allocate(fboSettings);

	post.begin();
		ofClear(255, 255, 255, 0);
	post.end();

	// shader.load("shaders/shader_vert.glsl", "shaders/shader_frag.glsl");
}

void TileSaverImage::addPixels(float x, float y, ofTexture& tex){
	// ofLog() << ofGetHeight();
	fbo.begin();
		tex.draw(x * colWidth, y * rowHeight, tex.getWidth(), tex.getHeight());
	fbo.end();

	// save("tex" + ofToString(x) + ofToString(y) + ".tiff", fbo);
}

void TileSaverImage::postProcess(){
	post.begin();
		ofClear(255, 255, 255, 255);
		shader.begin();
			shader.setUniformTexture("imgTex", fbo.getTextureReference(), 0);
			// shader.setUniform1f("saveCoef", rows);
			shader.setUniform1f("saveCoef", 2.0);
			fbo.draw(0, 0);
		shader.end();
	post.end();
}

void TileSaverImage::done(string filename){
	// postProcess();
	// save(filename, post);
	save(filename, fbo);
}

void TileSaverImage::save(string filename, ofFbo& _fbo){
	ofImage img;
	ofPixels pix;
	_fbo.getTextureReference().readToPixels(pix);
	img.setFromPixels(pix);
	img.saveImage(filename);	
}
