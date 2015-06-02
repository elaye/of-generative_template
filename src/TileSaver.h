#pragma once

#include "ofMain.h"

#include "TileSaverImage.h"

// struct FrustumData{
// 	float left, right, bottom, top, near, far;

// 	void set(float _left, float _right, float _bottom, float _top, float _near, float _far){
// 		left = _left;
// 		right = _right;
// 		bottom = _bottom;
// 		top = _top;
// 		near = _near;
// 		far = _far;
// 	}
// };

class TileSaver{

	float ratio, fov, nearZ, farZ;
	float imageWidth, imageHeight;
	float tileHeight, tileWidth;
	int steps, currentRow, currentCol;

	TileSaverImage final;
	// ofImage current;

	// FrustumData curFrustum;

	string fileName;

	bool bGoTiling, bBigImage;
	ofVec3f pos, eye, up;

	ofEasyCam cam;

	public:
		// TileSaver(){}
		//Setup all settings needed
		void setup(int steps, bool bBigImage);

		//setup perspective and Camera, if done, safe Image
		void begin();

		//grab FrameBuffer and ddd it to the Image or save the tile right away
		void end();

		//this starts the saving Process
		void finish(string _fileName, bool _bFlipY);

		//Camera Stuff
		void setPerspectiveData(float _fov, float _ratio, float _nearZ, float _farZ);

		void setCameraData(ofVec3f _pos, ofVec3f _eye, ofVec3f _up);

		void setPerspective();

		void positionCamera();

		//this is the important part, the Frustum gets setup correctly so we can tile perfectly
		void setFrustum(int _row, int _col);
};