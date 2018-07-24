//
//  Face.hpp
//  Term2Face
//
//  Created by Main on 27/03/2017.
//
//



#pragma once
#include "ofMain.h"



class irisDraw{
    
public:
   irisDraw();
      //variables
    ofPoint origine,center,iris;
    int screenDisplayX, screenDisplayY;
    float eyebrowLeft,distance,orientation,sizeBody;

 //   float goldRatio =1.6180339887498948420 ;
    float noiseSeed,  angle,transparency;
//
        
    //functions
   
    void setup();
    void update(vector<float>drawInfo);
    void draw(int scale);
    void eyeM(float x, float y, float radius1, float radius2, int npoints);
    void creatureM (ofPoint c, float scale, int size);
    void bodyM(ofPoint origine,float sizeBody, float shoulder);
    
    
    
    
    
    
    
    
};
