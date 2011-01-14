/*
 *  myIsadoraApp.cpp
 *  IsadoraTest2
 *
 *  Created by say nono on 24.10.10.
 *  Copyright 2010 www.say-nono.com. All rights reserved.
 *
 */

#include "ofxIsadoraApp.h"


#define RECONNECT_TIME 400

ofxIsadoraApp::ofxIsadoraApp(){
}

ofxIsadoraApp::~ofxIsadoraApp(){
}

//--------------------------------------------------------------
void ofxIsadoraApp::setup(){
	connectTime = 0;
	pingTime = 0;
	deltaTime = 0;
	lastFrameTime = 0;
	_inited = false;
	_hasNewFrame = false;

}

//--------------------------------------------------------------
void ofxIsadoraApp::exit(){
	vidGrabber.close();
}

//--------------------------------------------------------------
void ofxIsadoraApp::initStuff(){
	_inited = true;
	camWidth 		= 640;	// try to grab at this size. 
	camHeight 		= 480;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);	
	printf("ofxIsadoraApp::initStuff()\n");
}

//--------------------------------------------------------------
void ofxIsadoraApp::update(){
	
//	printf("ofxIsadoraApp::update()");
	
	if(!_inited) initStuff();
	else{
		vidGrabber.grabFrame();
		
		if (vidGrabber.isFrameNew()){
			_hasNewFrame = true;
			int totalPixels = camWidth*camHeight*3;
			unsigned char * pixels = vidGrabber.getPixels();
			for (int i = 0; i < totalPixels; i++){
				videoInverted[i] = 255 - pixels[i];
			}
			videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
		}
	}
	
}

//--------------------------------------------------------------
void ofxIsadoraApp::draw(){
	printf("myIsadoraApp::draw\n");
	
}

//--------------------------------------------------------------
void ofxIsadoraApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofxIsadoraApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofxIsadoraApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofxIsadoraApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofxIsadoraApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofxIsadoraApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofxIsadoraApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------


bool ofxIsadoraApp::getVideoFrame(UInt32* outData, int w, int h){
	
	if(!_inited || !_hasNewFrame) return false;
	_hasNewFrame = false;
	
	SInt16 red = 250;
	SInt16 green = 78;
	SInt16 blue = 24;
	int outStride = 16;
	
	int cnt = 0;
//	unsigned char* pixels = videoInverted;
	
	int l = w*h;
	for(int i=0;i<l;i++){
		red		= (SInt16)(videoInverted[cnt++]);
		green	= (SInt16)(videoInverted[cnt++]);
		blue	= (SInt16)(videoInverted[cnt++]);
		////			cnt++;
		*(outData) = ARGB_(blue, green, red,255);
		outData++;
		if(cnt%w*3==0) outData = (UInt32*)((char*) outData + outStride);
	}
	return true;
}


void ofxIsadoraApp::ping(){
	printf("new video frame ping\n");
}