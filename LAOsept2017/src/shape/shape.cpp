//
//  shape.cpp
//  Particle Game inspired by Daniel Shiffmann
//Shiffmann //shiffmann tuto https://www.youtube.com/watch?v=OkkjlHTdLGI

// by Sabrina Recoules Quang for Overlap Degree Exhibition 2017 Goldsmiths

//
//

#include "shape.h"


//-------------------------------------------------------
void shape::setup(ofPoint _raw,int _radius){
    location = _raw;
    radiusAtt = _radius;
   }


//--------------------------------------------------------------
void shape::draw(){
    // basic shape is composed by two circles with radius dependant of the time elapsed and random circle resolution
    ofPushStyle();
   ofNoFill();
    ofSetLineWidth(2);

    float noiseRad =  ofNoise(ofGetElapsedTimef())*0.65;
    ofSetColor(240,230,noiseRad);// yellow

    ofDrawEllipse(location,radiusAtt,radiusAtt* noiseRad);
    ofSetCircleResolution(ofRandom(1,50));
    ofDrawCircle(location, radiusAtt/4);
    ofPopStyle();
    
}

