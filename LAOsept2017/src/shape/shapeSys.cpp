//
//  shapeSys.cpp based on
// Shiffmann //shiffmann tuto https://www.youtube.com/watch?v=OkkjlHTdLGI

//
//  Created by Sabrina Recoules Quang on 29/08/2017, //
//

#include "shapeSys.h"

//-------------------------------------------------------
shapeSys::shapeSys()
{
    
}

//--------------------------------------------------------------
void shapeSys::setup(int _numRaw,  int _radius){//vector<ofPoint> _raw,
  
    numOfshapes = _numRaw;
    radius = _radius;
    
   
    
    //initiate shape system with numRaw elements
    for (int i=0; i<numOfshapes ; i++)
    {
        shape t;
        TargetSys.push_back(t);
      

    }
}
//--------------------------------------------------------------

void shapeSys::colorAnim(){ // change colour of the background for the shape animation
    maskHexColor.push_back(0xff0066);
    maskHexColor.push_back(0x33cccc);
    maskHexColor.push_back(0x660033);
    maskHexColor.push_back(0x000033);
    maskHexColor.push_back(0x4d1919);
    maskHexColor.push_back(0x660066);
    maskHexColor.push_back(0x003366);
    maskHexColor.push_back(0x336600);
    maskHexColor.push_back(0xacb58c);
    maskHexColor.push_back(0x2b3c48);
    maskHexColor.push_back(0xfb3c48);
    maskHexColor.push_back(0xfb4334);
    
    indexColor = ofRandom(0,12);
    cout <<"indexColor "<<indexColor<<endl;
    ofSetBackgroundColorHex(maskHexColor[indexColor]);
    
}
//--------------------------------------------------------------
void shapeSys::update(vector<ofPoint> points, int _radius){//
    // system of shapes is determined by number of shapes we want to draw  and  their radius, the shapes positions are dependant of an attractor which position varies with the elapsed time
    radius = _radius;
    gameRaw = points;
 
    
    TargetSys.clear();
    gameRaw.clear();
    /*update shapes - give movement for shapes*/
    for (int i =0;i<numOfshapes;i++){
        ofPoint r;
        
        
        float angle = ofMap(ofGetElapsedTimef(),0,4*60,0,20)/3.965;
        
        float k =  ofMap(sin(angle),-1,1,8,0);
        float amp = 6;// how far from the first position
        float a = 1+amp*cos(k*i);
        float rad= a* radius ;
        
        r.x = ofGetWidth()/2+ rad * cos(i);// position of the center of the flower shape
        r.y = ofGetHeight()-200+ rad * sin(i);
       
        
        gameRaw.push_back(r);
    }
    
    for (int i=0; i<numOfshapes; i++)
    {
        shape t;
        t.setup( gameRaw[i], radius);
        TargetSys.push_back(t);
    }
    
}
//--------------------------------------------------------------
void  shapeSys::draw(){
    
    for (int i=0; i<numOfshapes; i++)
    {
        TargetSys[i].draw( );
        
    }
    
}


//--------------------------------------------------------------
void shapeSys::addShape(ofPoint  p, int radius){
    shape t;
    t.setup(p, radius);
    TargetSys.push_back(t);
}



//--------------------------------------------------------------
void shapeSys::clear()
{
    TargetSys.clear();
    
}
