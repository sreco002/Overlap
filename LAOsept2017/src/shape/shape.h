//
//  shape.h
//  Particle Game
//
// by Sabrina Recoules Quang for Term2 OF Face Project April 2017 Goldsmiths
//
#pragma once
#include "ofMain.h"

class shape{
public:

//member variables
    ofPoint location;
    int radiusAtt;
  
    
    //functions
void setup( ofPoint a, int radius);
void draw();
};
