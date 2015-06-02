#include "TileSaver.h"

//Setup all settings needed
void TileSaver::setup(int _steps, bool _bBigImage){
	steps = _steps;
	currentRow = 0;
	currentCol = 0;
	tileWidth = ofGetWidth();
	tileHeight = ofGetHeight();

	fov = 60.0f;

	imageWidth = tileWidth * float(steps);
	imageHeight = tileHeight * float(steps);

	bGoTiling = false;
	bBigImage = _bBigImage;

	float halfFov, theTan, screenFov;
	screenFov 		= 60.0f;

	float eyeX 		= float(tileWidth) / 2.0;
	float eyeY 		= float(tileHeight) / 2.0;
	halfFov 		= M_PI * screenFov / 360.0;
	theTan 			= tanf(halfFov);
	float dist 		= eyeY / theTan;
	float nearDist 	= dist / 10.0;	// near / far clip plane
	float farDist 	= dist * 10.0;
	ratio 			= float(tileWidth)/float(tileHeight);

	ofVec3f eyeHolder, posHolder, upHolder;
	posHolder.set(eyeX, eyeY, dist);
	eyeHolder.set(eyeX, eyeY, 0.0);
	upHolder.set(0,1,0);
	setPerspectiveData(screenFov, ratio, nearDist, farDist);
	setCameraData( posHolder, eyeHolder, upHolder);
}

//setup perspective and Camera, if done, safe Image
void TileSaver::begin(){
	if(!bGoTiling){
		return;
	}

    if(currentRow == steps){

		if(bBigImage){
			final.done(fileName);
		}

		setPerspective();
		positionCamera();
		ofSetOrientation(ofGetOrientation(), true);
		bGoTiling = false;
		return;
	}

	ofSetOrientation(ofGetOrientation(), false);
	setFrustum(currentCol, currentRow);
	positionCamera();
}

//grab FrameBuffer and ddd it to the Image or save the tile right away
void TileSaver::end(){
	if(!bGoTiling){
		return;
	}

	ofTexture tex;
	tex.allocate(tileWidth, tileHeight, GL_RGBA32F);
	tex.loadScreenData(0, 0, tileWidth, tileHeight);
	final.addPixels(currentRow, currentCol, tex);

	if(currentCol == steps - 1){
		currentCol = 0;
		++currentRow;
	}
	else{
		++currentCol;
	}
}

//this starts the saving Process
void TileSaver::finish(string _fileName, bool _bFlipY){
	if(bBigImage){
		final.init(steps, steps, tileWidth, tileHeight);
	}
	bGoTiling = true;
	currentCol = 0;
	currentRow = 0;
	fileName = _fileName;
}

//Camera Stuff
void TileSaver::setPerspectiveData(float _fov, float _ratio, float _nearZ, float _farZ){
	fov = _fov;
	ratio = _ratio;
	nearZ = _nearZ;
	farZ = _farZ;
}

void TileSaver::setCameraData(ofVec3f _pos, ofVec3f _eye, ofVec3f _up){
	pos = _pos;
	eye = _eye;
	up = _up;
}

// void TileSaver::setCamera(const ofCamera& _cam){
	// cam = _cam;
// }

void TileSaver::setPerspective(){
	ofSetupScreenPerspective(ofGetWidth(), ofGetHeight(), fov, nearZ, farZ);
}

void TileSaver::positionCamera(){
	ofSetMatrixMode(OF_MATRIX_MODELVIEW);
	ofLoadIdentityMatrix();
	ofMatrix4x4 m;
	m.makeLookAtViewMatrix(pos, eye, up);
	ofLoadMatrix(m);
}

//this is the important part, the Frustum gets setup correctly so we can tile perfectly
void TileSaver::setFrustum(int _row, int _col){
	float Top = nearZ * tanf(fov * M_PI / 360.0);
    float Bottom = -Top;

    float Left = Bottom * ratio;
    float Right = Top * ratio;

	float frustumWidth = (Right - Left) * tileWidth / imageWidth;
	float frustumHeight = (Top - Bottom) * tileHeight / imageHeight;

    float left = Left + float(_col) * frustumWidth;
    float right = left + frustumWidth;

    float bottom = Bottom + float(steps - _row - 1) * frustumHeight;
    float top = bottom + frustumHeight;

    ofSetMatrixMode(OF_MATRIX_PROJECTION);
    ofLoadIdentityMatrix();

	ofMatrix4x4 m;
    m.makeFrustumMatrix(left, right, bottom, top, nearZ, farZ);
    ofLoadMatrix(m);
}



