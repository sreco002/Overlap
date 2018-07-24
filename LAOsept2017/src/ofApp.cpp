#include "ofApp.h"

/* LAO  is written by Sabrina Recoules Quang for the  Computational Art Master degree show  "Overlap "  7 sept 2017

 
 program for two people sitting in face of each other 
 the visitor , and the mask holder
 a camera is in the mask  checking the iris position of the  mask holder
 another camera is tracking the visitor face
 a projector is sending the visitor face to the mask
 another projector is sending the image of the eye of the  mask holder
 -> usb manangement
 this version is using 4 ports : two usb ports for the camera for following the eye and the camera on the visitor, two thunderbolt ports for video projectors
 
 -> light design is very crucial in this installation, attention is needed for placing the visitor camera and the projectors , for the lights on the visitor and the background to ease the tracking of the face. one projector is used with a mirror to allow short throw projection on the mask
 
 -> calibration of the camera filming the  visitor( visitorcam) and the camera filming the iris of the performer(eyecam)
 align visitorcam to eyecam, so if there is a visitor sit in front of the eyecam holder, the visitor will be in the catch area of the visitorcam
 check distances
 check distance between mask and projector
 check distance between visitorcam and visitor
 -> pseudoCode
 After loading the video taken by the eye camera, we convert the images in grayscale to find the contours of the brightest point in the images. As the eye tracker system is built with only one infra red led, we are looking for only one blob with a small size area. Each time we are running the calibration, we memorize the current background and the current position of the iris found . This position is the new reference from where we will get the information about the gaze of the performer, is he looking straight, on the left or on the right?
 The tracking calibration is helped by a simple GUI slider in which we can choose the size of the blob we are looking for, which level of threshold we use in the background substraction , what is the tolerance we have from the iris reference position, how much we want to correct the blinking effect and reduce data missing from the iris and IR led obturation.
 
-> class and methods
 
 check where the mask holder is looking -> irisFinder class
 track the visitor Face -> visitorTrack class
 irisFinder send iris positions to visitorTrack via ofPoint
 visitorTrack update and draw on visitorFace iris positions
 visitorFace is sent to the projector via MadMapper-Syphon
 irisFinder  is based on on openFrameworks_0.9.4/examples/addons/opencvExample
using findContour and optical flow technics. user update background (calibration)  and relative position is given after this background
animated graphics ->  shape and shapeSys class
 
 -> visitorFace
 use the visitor webcam
 do we have a visitor?
 look for a face in front of the visitor webcam with ofxFaceTracker
 ->irisFinder
 where do I look-> irisFinder.gaze check and gaze return
 ->irisDraw , visitorTrack and shape
 draw graphics if I am not looking straight
 graphics reflecting visitor face movement and responding to his smile
 ->visitorTrack
get the pixels and draw the visitor face if I am looking straight
 
-> ofApp
 manage the gui and its parameters
 manage the available cameras 
 note on camera USB  set up :
 facetime is always the last after usb cam, visitorCam is the second camera, eyecam is the first

 manage the report screens and calibration update instructions
 manage the flow and exchange of variables between visitorTrack, irisFinder and shapeSys classes
 send all drawings and screens to MadMapper via syphon
 using ofxSyphon basic example as a template
 calibration of the projectors is done on MadMapper
 

 */

/*BORROWED CODE
 
 openFrameworks_0.9.8/examples/addons/opencvExample
 Kyle McDonald ofxFaceTracker example empty
 daniel shiffmann Shiffmann //shiffmann tuto https://www.youtube.com/watch?v=OkkjlHTdLGI
 ofxSyphon tutorial

 */



//=======******************************===========*****************=======*********=======****

#include "ofApp.h"

using namespace ofxCv;
using namespace cv;


//--------------------------------------------------------------
void ofApp::setup(){
    
/*
  setup gui
 list of video grabber devices
 set up irisFinder
 setup visitorTrack
 setup Syphon

 */
    
    
    
    /* set up irisFinder======================================

*/
//    ofSetBackgroundColor(130,0,0);
    
    ofSetCircleResolution(50);
    //gui setup
    gui.setup();
    gui.setPosition(700, 20);
    gui.setName("Iris Find and Gaze check");
    gui.add(toleranceX.set("toleranceX",8.0,0,20.0));
    gui.add(minArea.set("minArea",  0.5,0.5,40));
    gui.add(maxArea.set("maxArea",  6,3,40));
    gui.add(threshold.set("threshold", 70,30,155));
    gui.add( gazeTresh .set("gazeTresh",0.65,0.50,1));
    gui.add(timeGaze.set("checkGaze in sec", 5,1,10));
    gui.add(blinkRate.set("blink Rate", 0.17, 0.00,0.50));
    
    bHide = true; // show the reports and the gui
    bHideTresh = false; // show the treshold screen to check
    
    
    
    
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    
    
    // video play or video grabb for the iris
#ifdef _USE_LIVE_VIDEO
    // set up my eye camera
    eyeCam.setDeviceID(0);
    eyeCam.setVerbose(true);
    eyeCam.initGrabber(screenW,screenH);
    eyeCam.setDesiredFrameRate( 30);
    
#else
    videoEye.load("3mnIris.mov");
    videoEye.play();
    videoEye.setLoopState(OF_LOOP_NORMAL);
    
    
#endif
    
    
    
    
    
    
    //initiate the boolean variable for calibration of the background
    bLearnBackground = true;
    bLearnIrisBg = true;
    
    colorImg.allocate(screenW,screenH);
    grayImage.allocate(screenW,screenH);
    grayBg.allocate(screenW,screenH);
    grayDiff.allocate(screenW,screenH);
    
  
        // give informations about positions of the screen where to show the results of irisFinder
  
    irisF.setup(screenCheckX,screenCheckY, screenW, screenH, toleranceX,gazeTresh,timeGaze, blinkRate );
    
    // position and size screen checking, tolerance from center,  ratio Gaze treshold,  time stay long enough, blinkrate

    
    
    // setup for the visitor Face tracking======================================
    visitorT.setup();
   
 // setup Syphon for sending data to MadMapper
    ofSetWindowTitle("LAO Syphon");
    mainOutputSyphonServer.setName("Screen Output");
//    individualTextureSyphonServer.setName("Texture Output");
    mClient.setup();
    //using Syphon app Simple Server, found at http://syphon.v002.info/
    mClient.set("","Simple Server");
    
    
    
   
    
}




//--------------------------------------------------------------
void ofApp::update(){
/*
 update videos
 update the screens
 update irisFinder
 update visitorTrack
 update Syphon*/
    
    
  
    /*
     update videos
     videos are loaded at 320 x 240 @ 25.000000 fps
 */
    bool bNewFrame = false;
    
#ifdef _USE_LIVE_VIDEO
      eyeCam.update();
	   bNewFrame = eyeCam.isFrameNew();
#else
    videoEye.update();
    bNewFrame = videoEye.isFrameNew();
#endif
    
    
    visitorT.update(); //  update visitorFace
    

    
    /*
     update the screens
     */
    
    if (bNewFrame){ // update ofxCvimages and the iris findings
        
    #ifdef _USE_LIVE_VIDEO
         colorImg.setFromPixels(eyeCam.getPixels());
    #else
        colorImg.setFromPixels(videoEye.getPixels());
    #endif
        
        grayImage = colorImg;
        
        if (bLearnBackground == true){
            grayBg = grayImage; //send the info to irisFinder that we have to learn the bg again
            irisF.learn(); // set bLearnIris  to true
           
            savedIris.setFromPixels(videoEye.getPixels());
            
            bLearnBackground = false;
        }
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
   
         /* send informations updated  to irisFinder to run find contours on the treshold screen; */
        
        irisF.update( grayDiff,minArea,maxArea); //update irisFinder
        
    } // end if bNewFrame
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofSetColor(255);
/*
 draw the screens
 draw irisFinder to check if we have an iris
 draw visitorTrack  to check if we have a visitor
 draw into Syphon send the drawings to the projectors
 */
    
    
    /*
     draw the screens*/
    if( !bHide )
    {
        gui.draw();
        grayBg.draw(20,280); // draw the background
        grayDiff.draw(360,280); //show the grayDiff will hide the visitorFace
    }
    // draw the incoming
    ofSetHexColor(0xffffff);
    colorImg.draw(20,20);
    

    // get the information about the iris position with irisFinder
   
    ofPoint irisMove;
    irisMove =  irisF.find(bHide,toleranceX); // positions of the iris kept to be used in visitor Face drawing
    

   // send information about the iris position, to check where we are looking with  irisF.gaze() to decide if the visitor will be drawn or not and how.
    
    visitorT.draw(irisMove, irisF.gaze());
  
   //syphon send information to MadMapper

    mClient.draw(50, 50);
    mainOutputSyphonServer.publishScreen();

    
  
}// END DRAW


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    switch (key){
        case ' ':
            bLearnBackground = true; // learn another background
            irisF.learn(); // reset the reference for the iris too
           
            break;
            
        case '+':
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
    }
    

    if( key == 'h' ){
        bHide = !bHide; // hide or reveal the gui , the report , the grayDiff and the background screen
    }
    if(key == 's') {
        gui.saveToFile("settingsIris.xml");
        
    }
    if(key == 'l') {
        gui.loadFromFile("settingsIris.xml");
    }
    
    if(key == 'r') {
        gui.loadFromFile("irisSave.png");
    }
    
    if(key == 'x') {
        
        visitorImg.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        visitorImg.save("screenshot.png");
    }
//    if(key == 'c') {
//        
//    visitorT.setupShapeAnim();
//    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
