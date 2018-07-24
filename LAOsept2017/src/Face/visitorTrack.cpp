/*
//  visitorTrack.cpp
//  LAO
//
//  Created by  Sabrina Recoules Quang on 11/08/2017.
//
 
 program to follow the face of the visitor with ofxFacevisitorFace, based on FaceOSC from Kyle McDonald
 extract the half of its face,
 if  visitor found draw a circle shape animation which scale will grow accordingly to the smile 
 check the gaze to decide how the face of the visitor will be drawn 
 if there is no visitor , draw  a flower shape animation -

 manage the visitorCamera , 
 note on camera USB  set up :
 if we have two usb camerasfacetime is always the last after usb cam, visitorCam is the second camera, eyecam is the first
 if we have only facetime and  one usb camera, we set it as the visitorCam, this is is the case where we play a video for the eye,
 
 manage the drawings on the mask , via sending visitor face data to ofApp and controlling irisDraw and shapeSys classes and take information about iris position from irisFinder class
 */


#include "visitorTrack.h"

using namespace ofxCv;
using namespace cv;

//---------------------------------------------------------------------------------------------------------------------------
visitorTrack::visitorTrack()
{
    
    
}


//----------------------------------------------------------------------------------------------------------------------------
void visitorTrack::setup(){

    changeColorShapeSys= true;
    camWidth = 640; // visitor camera size
    camHeight = 480;

        //get back the list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
  
    cout <<"number cameras on is "<< devices.size() <<endl;
    
    if(devices.size()>2){
            visitorCam.setDeviceID(1);// facetime is always the last after usb cam, visitorCam is the second camera, eyecam is the first
    }
    else {
            visitorCam.setDeviceID(0);//number of camera is 2, facetime and   one usb camera, we set it as the visitorCam, this is is the case where we play a video for the eye,
    }

        visitorCam.setDesiredFrameRate( 30);
    
    
        visitorCam.initGrabber(camWidth, camHeight);
    

        setVideoSource(true);
        ofSetVerticalSync(true);
    
    
    //visitor Face tracker setup
    
    visitorFace.setup(); // go to ofxFaceTracker to set what we want to take from the visitor Face, in the function vector<int> ofxFaceTracker::getFeatureIndices(Feature feature)

    bDrawMesh = true;
    
 
    // shape animation when no visitor or face visitor Face not found
    
 setupShapeAnim();
    
   
    
}


//----------------------------------------------------------------------------------------------------------------------------


void visitorTrack::update(){
    rawVector.clear(); // raw data of the face
    poly.clear(); // contour of the face
    visitorCam.update();
    
    if(visitorCam.isFrameNew()) visitorFace.update(toCv(visitorCam));
  
  

}


//----------------------------------------------------------------------------------------------------------------------------


void visitorTrack::draw(ofPoint irispos, int g){
    // take information about iris position, visitor screen and if drawing the face of the visitor is true
   
    int gaze= g;// if 0, we are looking straight, if 1, we are looking on the right, if 2, we are looking on the left
    
    ofNoFill;
   
    if( !visitorFace.getFound()) //  if no visitor found draw the animation
        
    {
        // set a new background for the shapeSys for every visitor or each time we have lost the visitor
  
        if( changeColorShapeSys==true) FlowerSys.colorAnim();
        changeColorShapeSys=false;
        // draw  a flower shape animation
        
        
        FlowerSys.update(seeds, radiusFlower);
        FlowerSys.draw();
        
       // ofSetBackgroundColorHex(0xff0066);
    }
    
    else { // if a visitor is found 
        changeColorShapeSys= true;// we can change the background colour of the animation next time we lost the visitor
       
   
     //   ofSetBackgroundColorHex(0x0a0a10);

        
            /*       create the raw Vector of  getImagePoints selected to fit a Half Left Mask
            8,9,10,11,12,13,14,15,16,26,25,23,23,22,21,27,28,29,30,31,50,49,48,59,58,57 */
        
            rawVector.push_back( visitorFace.getImagePoint(8));
            for (int i = 8; i<16; i++) rawVector.push_back( visitorFace.getImagePoint(i));
            rawVector.push_back( visitorFace.getImagePoint(16));
            rawVector.push_back( visitorFace.getImagePoint(26));
            for (int i = 26; i>21 ; i--) rawVector.push_back( visitorFace.getImagePoint(i));
            rawVector.push_back( visitorFace.getImagePoint(21));
            rawVector.push_back( visitorFace.getImagePoint(27));
            for (int i = 27; i<31 ; i++) rawVector.push_back( visitorFace.getImagePoint(i));
           rawVector.push_back( visitorFace.getImagePoint(31));
            for (int i = 50; i>48 ; i--) rawVector.push_back( visitorFace.getImagePoint(i));
            rawVector.push_back( visitorFace.getImagePoint(49));
            rawVector.push_back( visitorFace.getImagePoint(48));
            for (int i = 59; i>57 ; i--) rawVector.push_back( visitorFace.getImagePoint(i));
            rawVector.push_back( visitorFace.getImagePoint(57));
            rawVector.push_back( visitorFace.getImagePoint(8));
        
        // draw an animation in relation to how big is the visitor Smile
        ofPoint p = visitorFace.getImagePoint(54)- visitorFace.getImagePoint(48);
        float smile = sqrt(p.x * p.x + p.y * p.y); // distance between two extreme of the mouth
        int scale = ofMap (smile,50,100,8,64); // bigger the smile, bigger the drawing animation of the iris
        
        ofSetLineWidth(1);
        ofPushMatrix();
          ofTranslate(camWidth/2,camHeight/2);// half resolution 800x480 projector
            drawAnim(visitorFace.getImagePoint(43),scale); // draw  animated shape on visitor Eye face contour
        ofPopMatrix();
        
        // we have a visitor face, if  we are looking straight too,   then we draw the face of the visitor
        if(gaze ==0){
            //create a polyline with the raw points of the half face of the visitor
            /* go every pixel of the video and check if it is inside the poly
             if yes draw it */
            for (int i = 0; i<rawVector.size();i++) poly.addVertex(rawVector[i]);
            
                for ( int y = 0; y<sourceHeight;y++){
                    for ( int x = 0; x<sourceWidth;x++){
                        ofPoint p (x,y);
                        if (poly.inside(p) )// check the screen, if p is inside the left outlne of the visitor face
                        {
                        ofColor c;
                       c = visitorCam.getPixels().getColor(x, y);
                            ofSetColor(c);
                        ofPushMatrix();
                        ofTranslate(camWidth/2,camHeight/2); // visitor screen
                         ofDrawRectangle(x,y,1,1);// draw pixel size 1x1 one by one inside the poly, we draw only half of the visitorFace
                        ofPopMatrix();
                              }
                    
                    }
                } // end loop the source checking if we are inside the polyMask
            
            }// end of if I am looking straight too
        
      
        else if(gaze ==1){ // i am looking on the right and the visitor Face is found
                ofPushMatrix();
                    ofTranslate(camWidth/2,camHeight/2);// half resolution 800x480 projector
                    visitorFace.getImageMesh().drawWireframe();// draw the wired face to calibrate more easily on MadMapper
                ofPopMatrix();
            }// end of looking on the right
        
        
        else if(gaze ==2){ // i am looking on the left and the visitor Face is found
                ofPushMatrix();
                    ofTranslate(camWidth/2,camHeight/2);// half resolution 800x480 projector
                    visitorFace.draw(); // draw only the contour of the visitor face
                ofPopMatrix();
        }// end of looking on the left
        

        
    }  // end of if visitor Face is found an checking where we are looking
    
    


}





//-------------------------------------------------------------------------------------------------

void visitorTrack::setVideoSource(bool useCamera) {
    

        videoSource = &visitorCam;
        sourceWidth = camWidth;
        sourceHeight = camHeight;
  }




//-----------------------------------------------------------------------------------------------------------------------------------------

void visitorTrack::setupShapeAnim(){
    
    
    radiusFlower= ofRandom(19,65);
    numFlower = ofRandom(36,80);
    FlowerSys.setup(numFlower,radiusFlower);
    for (int i= 0;i<numFlower+1;i++)
    { seeds.push_back(ofPoint(ofRandomWidth(),ofRandomHeight()));
    }
    

    
}






//-------------------------------------------------------------------------------

void visitorTrack::drawAnim(ofPoint p, int scale){
    
    // draw an animation in relation to how big is the visitor Smile
        irisSmilepaint.setup();
        vector<float> drawInfo;
        drawInfo.push_back(p.x);
        drawInfo.push_back(p.y);
    
        irisSmilepaint.update(drawInfo);
        irisSmilepaint.draw(scale);
   
    
}







