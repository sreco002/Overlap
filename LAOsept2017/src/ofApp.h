#pragma once

#include "ofMain.h"
#include "visitorTrack.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

#include "shapeSys.h"




//#define _USE_LIVE_VIDEO		// comment this to use a video of the eye instead of the live camera




class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //video
    
      ofVideoGrabber vidGrabber;
    
#ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		eyeCam; // connect to eye camera of the mask
    #else
         ofVideoPlayer 	videoEye;// video size in relation to screenW and screenH

#endif
    
 
    
    // gui panel
    ofxPanel gui;
    
    ofParameter<int> minArea;
    ofParameter<int> maxArea;
    //ofParameter<int> squareDiff;
    ofParameter<int> freqFrame;
    ofParameter<int> threshold;
    ofParameter<int> toleranceX; // tolerance for calibration
    ofParameter<float> gazeTresh; // ratio Gaze treshold to decide which direction we are looking
    ofParameter<int> timeGaze; // time period for checking the gaze
    ofParameter <float>blinkRate; // to adjust the counting of the gaze , when looking on the left or right, blinking is count as straight
    
    bool bHide;
    bool bHideTresh;
    bool bLeftMask; // if true, we show the left side of the visitor
    
    //  screens   findContour
    
    
    ofxCvColorImage			colorImg;
    ofImage                          visitorImg;
    
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
   // ofxCvContourFinder 	contourFinder;
    
    ofImage savedIris; // savedIris picture
    
    // dimension for all the  screens reports
    int                 screenW = 320;
    int                 screenH = 240;
    
    // screen position to show  the checking of the Iris
    
    int                 screenCheckX = 360;
    int                 screenCheckY = 20;
    
    // screen position to show  the checking of the Iris
    
    int                 visitorScreenX = 340;
    int                 visitorScreenY = 260;

    
// boolean Calibration reset of the Background for the iris finder
    bool                bLearnBackground; // reset the Background ?
    bool                bLearnIrisBg; // reset the Iris?
    
    
    
    
    //irisFinder declarations
    
    irisFinder irisF;
    
    
    //visitorTrack declarations
    
    visitorTrack visitorT; // visitorT is the face tracking of the visitor
    
    
    
    
    // syphon
    
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonServer individualTextureSyphonServer;
    
    ofxSyphonClient mClient;

 		
};
