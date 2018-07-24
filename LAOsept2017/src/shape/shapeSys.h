//
//  shapeSys.h
//  ZL-Particles
//
//  Created by Sabrina Recoules Quang on 03/04/2017.
//
//

#pragma once

#include"ofMain.h"


#include "shape.h"

class shapeSys{
    
public:
    shapeSys();
//    functions
    void setup(int _numOfshapes,  int radius);//vector<ofPoint> raw,
    void update(vector<ofPoint> raw, int radius);//
    void draw();//vector<ofPoint> raw, int radius
    void colorAnim();
    void addShape(ofPoint a,int radius);
    void clear();
    
//    variables
    int numOfshapes;
    vector<ofPoint> gameRaw;
    int radius, indexColor;
    vector <shape> TargetSys;
      vector<int> maskHexColor;
    
};
