//
//  Face.cpp
//  Drawing animation projected on the mask
//graphics based on circles and lines rotating in a noised angle , this method take the informations about the scale, the size and the center of the circles

//  Created by Sabrina Recoules Quang on 04/04/2017. for the term2Project MA computational Arts 2016 2017 and modified for the Overlap degree show sept 2017

// //
#include "irisDraw.h"

//---------------------------------------------------------------------------------------------------------------------------
irisDraw::irisDraw()
{
    
    
}

    
//----------------------------------------------------------------------------------------------------------------------------
    void irisDraw::setup(){
        noiseSeed = 0;
        angle = 0;
        
        
        
    }



//------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------

void irisDraw::update(vector<float>drawInfo ){
    // update informations about where to draw the graphics and their  rotation
    noiseSeed += 0.0013;
    angle = angle+noiseSeed;
    origine.x = drawInfo[0];
    origine.y = drawInfo[1] ;
    screenDisplayX = drawInfo [2];
    screenDisplayY = drawInfo[3];

  
   }




//----------------------------------------------------------------------------------------------------------------------------
void irisDraw::draw(int scale){
      // transfer information of scale to draw the graphics
    creatureM(origine,scale, 3);

  }
//-------------------------------------------------------------------------------------
void irisDraw::creatureM(ofPoint origine,float scale, int size){
   //graphics based on circles and lines rotating in a noised angle , this method take the informations about the scale, the size and the center of the circles
    int sizeCircle= scale;
    ofSetColor(ofRandom(180,185),ofRandom(190,200),ofRandom(190,230));

    ofPushMatrix();
    ofTranslate(screenDisplayX,screenDisplayY);
    ofSetColor(ofRandom(180,255),ofRandom(190,200),ofRandom(0,20));

    ofDrawCircle(origine,sizeCircle*2*scale/100);
    ofDrawCircle(origine,sizeCircle);
    ofTranslate(origine.x,origine.y);
    ofScale(size, size);
    int numRad= 12;
    
    for (int i = 0;i<numRad;i++){
       ofDrawCircle(0,0,scale/4);
        ofRotate(angle);
         ofSetColor(255,0,0);
      
         ofDrawCircle(scale,scale,0.5);
          ofSetColor(80, 140, 220);
        ofRotate(30);
        ofDrawLine(0,0,0,scale*1.2);

        }
    ofPopMatrix();

}
