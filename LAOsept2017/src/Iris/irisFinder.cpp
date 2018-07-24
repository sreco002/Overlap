//
/*  irisFinder.cpp
 LAO

Created by SabrinaRecoulesQuang on 11/08/2017.
based on openFrameworks_0.9.4/examples/addons/opencvExample

 irisFinder  is based on on openFrameworks_0.9.8/examples/addons/opencvExample
using findContour and optical flow technics. 
 user update background (calibration)  and relative position is given after this background

Algorithm to find the iris
loop over the blobs founds and save the iris position from the background image , follow the consecutive movements of the iris
since we have set only one IR led to follow the iris, we are looking only one blob, the brightest one
 if found an iris
 save the centroid coordinates into the iris ofPoint
 save the last iris found into lastIris
 first time we have an iris, we set the irisBg position, then we do not change it anymore until background is reset again
 
irisFinder
 receive calibration and parameters update  from ofApp
 compute the gaze
 send informations about the gaze to ofApp
*/

#include "irisFinder.h"

//---------------------------------------------------------------------------------------------------------------------------
irisFinder::irisFinder()
{
    
    
}


//----------------------------------------------------------------------------------------------------------------------------
void irisFinder::setup( int screenXpos, int screenYpos, int w, int h, int t, float g, float tT, float bR){
    // position and size screen checking, tolerance from center,  ratio Gaze treshold,  time stay long enough, blinkrate
    
    irisFind= false; // no Iris found for now
    bLearnIrisBg = true;
    // Iris position reset
    bleft = false;
    bright = false;
    bstraight = false;
    
    bHide = false; // show the report , if false
    tolerance = t;
    screenX = screenXpos;
    screenY = screenYpos;
    screenW = w;
    screenH = h;
  
    //   in the period of checking timeTresh , if we look at a ratio greater than ratioGazeTresh, this is the direction which will define the drawing

    ratioGazeTresh = g; //ratioGazeTresh, this is the direction which will define the drawing

    timeTresh = tT;// for how long we are checking
    
    
    timeStart = ofGetElapsedTimef();
    countStraight = 0;
    countLeft =0;
    countRight =0;
    countCheck = 0;
    ratioLeft = 0;
    ratioRight = 0;
    ratioStraight = 0;
    
    
}
//-----------------------------------------------------------------------------------------------------------------------------
void irisFinder:: learn(){// reset the reference for the iris 
   bLearnIrisBg= true;
   
}


//----------------------------------------------------------------------------------------------------------------------------



void irisFinder::update( ofxCvGrayscaleImage 	grayDiff,  int minArea, int maxArea){
    
    
    /* find as many contour as we have IRLed, contour should be between the size of minArea
     and maxArea, size the w*h pixels.
     find holes is set to true so we will get interior contours as well....
     we have only 1 led, so only looking for 1 contour*/
  
     contourFinder.findContours(grayDiff, minArea, maxArea, 1,true);	// true to  find holes
    
   
}


// update variables for checking the gaze--------------------------------------------
void irisFinder::updateCheck(){

    
    countStraight = 0;
    countLeft =0;
    countRight =0;
    countCheck = 0;
    timeStart = ofGetElapsedTimef();
}


//------------------------FIND IRIS------------------------------------------------------------------------------------

ofPoint irisFinder::find(bool b, int tolerance){ // get the info from ofApp about the report hiding bool b and return informations about iris position
    
    
 bHide = b;
  
    //loop over the blobs founds and save the iris position from the background image , follow the consecutive movements of the iris
   
    for (int i = 0; i < contourFinder.nBlobs; i++){
        
        irisFind = true; // found an iris
        
        //  save the centroid coordinates into the iris ofPoint
        lastIris = iris; // save the last iris found into lastIris
        iris = ofPoint( contourFinder.blobs[i].centroid.x,contourFinder.blobs[i].centroid.y);
        
        // first time we have an iris, we set the irisBg position, then we do not change it anymore until background is reset again
        
        if(  bLearnIrisBg == true )
        {
            
            irisBg = ofPoint( contourFinder.blobs[0].centroid.x,contourFinder.blobs[0].centroid.y);
            bLearnIrisBg = false;
        }
       
        
           if( !bHide){
        // draw the blobs
      contourFinder.blobs[i].draw(screenX,screenY);
        
        // draw over the centroid if the blob is a hole
        ofSetColor(255);
        if(contourFinder.blobs[i].hole){
            ofDrawBitmapString("hole",
                               contourFinder.blobs[i].boundingRect.getCenter().x + screenX,
                               contourFinder.blobs[i].boundingRect.getCenter().y + screenY);
                }
        
           }
        
    }// end looping through nBlobs
    
    
    if( !bHide) {
        // draw lines  of reference around the Iris learned with the Background to check the iris movement
        ofSetColor(255,180);
        ofPushMatrix();
        ofSetLineWidth(0.5);
        ofTranslate(screenX, screenY);
        ofDrawLine(irisBg.x, 0, irisBg.x,0);
        ofDrawLine(0, irisBg.y, screenW,irisBg.y);
        ofDrawCircle(irisBg.x, irisBg.y, 8);
        
        // lines to show tolerance from the Iris learned with the Background to check the iris movement
        ofDrawLine(irisBg.x+tolerance, 0, irisBg.x+tolerance, screenH);
        ofDrawLine(irisBg.x-tolerance, 0, irisBg.x-tolerance, screenH);
        ofPopMatrix();
        
        // finally, a report:
        
        ofSetHexColor(0xffffff);
        stringstream reportStr;
        reportStr << "bg subtraction and blob detection" << endl
        << "press ' ' to capture bg" << endl
        //			<< "threshold " << threshold << " (press: +/-)" << endl
        << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate()<< endl
        <<endl
        << "tolerance "<<tolerance<<endl
        // display the found Iris status and coordinates
        << "Iris found   "<< irisFind<<endl
        << "Iris Bg  "<<irisBg.x <<"/"<< irisBg.y<<endl
        << "Iris last coordinates " << iris.x<<"/"<< iris.y<<endl
        << "distance from the center "<<iris.x-irisBg.x<< endl
        << "looking  "<<bleft <<" L / R "<<bright<< "Straight "<<bstraight<<endl
        ;
        
        ofDrawBitmapString(reportStr.str(), 20, 600);
        
        

    
    
    }// draw reports
    
    
    if (irisFind) {
    checkGaze();
    return iris ; // return iris positions anyway
    }
    
} // end of ofPoint irisFinder::find(bool b, int tolerance)





//---------------------------------------------------------------------------------------------
int irisFinder:: gaze(){ // return the information of the gaze
    // return 0, if looking straight, 1, if looking right, 2, if looking left
    int gaze;
    if(bstraight) gaze =0;
    else if (bright) gaze = 1;
    else if(bleft) gaze= 2;
    
    return gaze;
}


// WHERE is the GAZE--------------------CHECK THE GAZE------------------------------------------------------------------------------

void irisFinder::checkGaze()
// checking the gaze with parameters defined in the GUI : how often we are checking , how much we reduce the impact of blinking when computing the gaze
{
if(ofGetElapsedTimef() -timeStart>timeTresh ){// if time of checking is over, check the gaze ratios  and which one is greater than the others
    
    ratioLeft = blinkRate + countLeft/countCheck; // blinking is count as straight, we add them back
    ratioRight = blinkRate + countRight/countCheck;
    ratioStraight = countStraight/countCheck;
    
    
    // in which direction do we look the most often in the time period ?
          if ((ratioLeft>ratioRight)&&(ratioLeft>ratioStraight))
              
    {
        bstraight= false;
        bleft = true;
        bright = false;
        
    }
        else if  ((ratioRight>ratioLeft)&&(ratioRight>ratioStraight))
            

    {
        bstraight = false;
        bleft = false;
        bright = true;
        
    }
    
    else if  ( ratioStraight > ratioGazeTresh)
    {
        bstraight =true;
        bleft =false;
        bright = false;
        
    }

 
//    cout << "ratioStraight: " << ratioStraight <<" bstraight"<< bstraight<< endl;
//    cout << "ratioLeft:  " << ratioLeft <<" bleft"<< bleft << endl;
//    cout << "ratioRight:  " << ratioRight <<" bright"<< bright<< endl;
//    
    updateCheck();
    
    
    }
    
    
    
    if( ofGetElapsedTimef()-timeStart<timeTresh){ // if time of checking is not over, go on counting number of times we are looking in each direction,
        
        countCheck++; // number of time we check the iris position
        // check over if straight
        // when looking not straight , every blink is count as straight, so we have to give a correction to the countLeft or countRight to neutralise this bias, check delay between the gaze and the drawing, ? try to use the blinkrate to adjust
        
        if (iris.x<irisBg.x- tolerance)
        {
            //        if left, countLeft++
            countLeft++;
            
        }
        else if (iris.x>irisBg.x+ tolerance)
        {
            //        if left, countLeft++
            countRight++;
            
        }
        else // if neither of this two is true, then I am looking straight
            
        {
            countStraight++;
        }
        
        
        
    }
    
    
    }// end -CHECK THE GAZE--


