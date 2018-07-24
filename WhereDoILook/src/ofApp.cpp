#include "ofApp.h"
/*finding iris program for Overlap exhibition sept 2017
based on openFrameworks_0.9.4/examples/addons/opencvExample
 */
 /*
 program only for one visitor , sit in front of the eyecam mask holder
 
 calibrate visitorcam and eyecam
 align visitorcam to eyecam, so if there is a visitor sit in front of the eyecam holder, the visitor will be in the catch area of the visitorcam
 check distances
 distance between mask and projector
 distance between visitorcam and visitor
 
 
 -> visitorFace
 use the visitor webcam
 do we have a visitor?
 look for a face in front of the visitor webcam with faceOSC or Dlib
 take a picture of the face, keep it in a buffer fbo?
once we have a face we can close the videoGrabber of the visitorwebcam , to save performance
after 2 minutes max, we stop drawing the visitor face and check again if there is a visitor
  
 
 check where we are looking -> irisFind class
 
 if we are looking straight,
 draw the face of the visitor on the mask
 if we are not looking straight, draw the red mask
 
 */



/* 13/07/17
 debug
 videoPlay IR test.mov

    background is based on the videoPlay IR test.mov via Photoshop , saved gif format with grayscale 2 colours no dither

 finds the iris as a rectboundingbox square enough
 and there is a blob inside the iris which is a hole,
 the blob is the IR led, only one at the bottom of the iris , no led on the iris, no blob, no iris detection
 finding holes is set to true
 gui added
 we have access to the coordinate of the iris found in ofPoint iris declared as a global variable
 when the iris is in the center , we find it 
 when the iris is off center or the blob is not in the hole, we do not find it
 
 
 14/07
 videoPlay IR test.mov
 code for one Led
 find iris as a IRLed blob
 no more checking rectboundingBox
 checking if looking on the right/ left in relation to reference calibrated via gui
 compute the distance from the center of the videoPlay screen
  checked update the background , code is still working, we see the movement of the IRled from its initial position on the background saved, which is the first image, which is the eye looking straight
 
 toDo : 
 Hardware :work on the mask and the eyecam
 make the mask
 make eyecam with one IR led and one with three IR leds
 prototype the installation with a table , two chairs , one projector and a camera for the visitor
 
 Software
 check lifestream if Irisfind is working Ok
 check access to two cameras from the same computer

 02/08
 lifeVideo feed ok , no slowing
 polish design of the mask , with a stand ot put camera and led together 
 test with eyecam , and IR led
 to do , when snap the calibration, put the iris found in red which is remaining still and put the test lines around it // OK
 
 
 06/08
to do
 add xml files to keep the movement
 maybe drawing something on screen 
 to be projected?
 movement is very fast, check how long is on the right, 
 check what a movement of the head will add to the iris movment
 add accelometer? kinect analysis or little arduino ?
 iphone touchOSC?
 add OSC receiver,
 
 */
//--------------------------------------------------------------
void ofApp::setup(){
       
    //gui setup
    gui.setup();
    gui.setPosition(700, 20);
    gui.setName("Iris Find");
    gui.add(toleranceX.set("toleranceX",1.0,0,10.0));
    gui.add(minArea.set("minArea",  0.5,0.5,40));
    gui.add(maxArea.set("maxArea",  6,3,40));
    gui.add(threshold.set("threshold", 70,30,155));
 
    //initiate the boolean variables
    bHide = false;
    bLearnBackground = true;
    bLearnIrisBg = true;

    // video play or video grabb
	#ifdef _USE_LIVE_VIDEO
    // set up my eye camera
        vidGrabberEye.setVerbose(true);
        vidGrabberEye.setup(screenW,screenH);
	#else
        vidPlayer.load("3mnIris.mov");//IRTest.mov based or 608.mov
        vidPlayer.play();
        vidPlayer.setLoopState(OF_LOOP_NORMAL);
	#endif
    
    colorImg.allocate(screenW,screenH);
	grayImage.allocate(screenW,screenH);
	grayBg.allocate(screenW,screenH);
	grayDiff.allocate(screenW,screenH);

 
}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(100,100,100);
    irisFind= false; // no Iris found for now
    // position reset
    left = false;
    right = false;
    
    bool bNewFrame = false;
   
#ifdef _USE_LIVE_VIDEO
       vidGrabberEye.update();
	   bNewFrame = vidGrabberEye.isFrameNew();
    #else
        vidPlayer.update();
        bNewFrame = vidPlayer.isFrameNew();
	#endif
    
	if (bNewFrame){

		#ifdef _USE_LIVE_VIDEO
            colorImg.setFromPixels(vidGrabberEye.getPixels());
    #else
            colorImg.setFromPixels(vidPlayer.getPixels());
    #endif
            grayImage = colorImg;
    
  		if (bLearnBackground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBackground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        
		/* find as many contour as we have IRLed, contour should be between the size of minArea
         and maxArea, size the w*h pixels.
		  find holes is set to true so we will get interior contours as well....
      we have only 1 led, so only looking for 1 contour*/
        contourFinder.findContours(grayDiff, minArea, maxArea, 1,true);	// true to  find holes
	}
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if( !bHide ){
        gui.draw();
    }
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
	colorImg.draw(20,20);
	grayImage.draw(360,20);
	grayBg.draw(20,280);
	grayDiff.draw(360,280);

	// then draw the screen for displaying the blobs:

	ofFill();
	ofSetHexColor(0x333333);
	ofDrawRectangle(360,540,320,240);
    
	// we could draw the whole contour finder
    //	contourFinder.draw(360,540);
 
//    for (int i = 0; i < contourFinder.nBlobs &&
//         contourFinder.blobs[i].boundingRect.width >contourFinder.blobs[i].boundingRect.height-squareDiff
//         &&       contourFinder.blobs[i].boundingRect.width <squareDiff+contourFinder.blobs[i].boundingRect.height
//         ; i++)
//    {

        for (int i = 0; i < contourFinder.nBlobs; i++){
        
        irisFind = true; // found an iris
        //  save the centroid coordinates into the iris ofPoint
        iris = ofPoint( contourFinder.blobs[i].centroid.x,contourFinder.blobs[i].centroid.y);
        
            // first time we have an iris, we set the irisBg position, then we do not change it anymore until background is reset again
     
            if( bLearnIrisBg== true)
           {
            irisBg = ofPoint( contourFinder.blobs[0].centroid.x,contourFinder.blobs[0].centroid.y);
            bLearnIrisBg = false;
           }

        // draw the blobs
        contourFinder.blobs[i].draw(360,540);
		// draw over the centroid if the blob is a hole
                ofSetColor(255);
                if(contourFinder.blobs[i].hole){
                ofDrawBitmapString("hole",
                contourFinder.blobs[i].boundingRect.getCenter().x + 360,
				contourFinder.blobs[i].boundingRect.getCenter().y + 540);
                          }
        }// end looping through nBlobs
    
    //}// end looping condittional to boundingRect square enough
	
    // lines Reference around the Iris learned with the Background to check the iris movement
    ofSetColor(255,180);
    ofPushMatrix();
    ofSetLineWidth(0.5);
        ofTranslate(screenPosX, screenPosY);
        ofDrawLine(irisBg.x, 0, irisBg.x,0);
        ofDrawLine(0, irisBg.y, screenW,irisBg.y);
        ofDrawCircle(irisBg.x, irisBg.y, 8);
  
    // lines to show tolerance from the Iris learned with the Background to check the iris movement
        ofDrawLine(irisBg.x+toleranceX, 0, irisBg.x+toleranceX, screenH);
        ofDrawLine(irisBg.x-toleranceX, 0, irisBg.x-toleranceX, screenH);
   
    // where do I look?
    if (iris.x<irisBg.x- toleranceX)
    {
        left = true; // is the iris on the left?
        right = false;
    }
    else if (iris.x>irisBg.x+ toleranceX)
    {
        right = true; // is the iris on the right?
        left =false;
    }
    // if neither of this two is true, then I am looking straight
    ofPopMatrix();
    
        // finally, a report:
    ofSetHexColor(0xffffff);
	stringstream reportStr;
	reportStr << "bg subtraction and blob detection" << endl
			  << "press ' ' to capture bg" << endl
//			<< "threshold " << threshold << " (press: +/-)" << endl
			  << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate()<< endl
             <<endl
            // display the found Iris status and coordinates
            << "Iris found   "<< irisFind<<endl
            << "Iris Bg  "<<irisBg.x <<"/"<< irisBg.y<<endl
            << "Iris last coordinates " << iris.x<<"/"<< iris.y<<endl
            << "distance from the center "<<iris.x-irisBg.x+screenPosX<< endl
            << "looking  "<<left <<"L / R"<<right<< endl
        ;
	
    ofDrawBitmapString(reportStr.str(), 20, 600);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key){
		case ' ':
			bLearnBackground = true; // learn another background
            bLearnIrisBg = true; // learn another Iris from background
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
    
    if( key == 'h' ){// show menu or not
        bHide = !bHide;
    }
    if(key == 's') {
        gui.saveToFile("settings.xml");
    }
    if(key == 'l') {
        gui.loadFromFile("settings.xml"); //load settings menu
    }
    
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
