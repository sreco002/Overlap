#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file

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

    #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabberEye;
    #else
		   ofVideoPlayer 		vidPlayer;// video size in relation to screenW and screenH
		#endif
	
        ofxCvColorImage			colorImg;
        ofImage fileImage;
    
        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;

        ofxCvContourFinder 	contourFinder;
    
    // iris
    ofPoint iris;
    ofPoint irisBg; //  iris coordinate from the background
    
    bool right, left; // where do I look 
    bool irisFind ; // is there an iris ?
    int distanceFromtheCenter; // distance between where iris is looking and the calibrated center via gui
    
		//               threshold;
		bool				bLearnBackground; // reset the Background ?
        bool                bLearnIrisBg; // reset the Iris?
    
    // dimension for all the  screens reports
        int                 screenW = 320;
        int                 screenH = 240;
    // position screen position Iris

        int                 screenPosX = 360;
        int                 screenPosY = 540;
    
    // gui panel
    ofxPanel gui;

    ofParameter<int> minArea;
    ofParameter<int> maxArea;
    //ofParameter<int> squareDiff;
    ofParameter<int> freqFrame;
    ofParameter<int> threshold;
    ofParameter<float> toleranceX; // tolerance for calibration 
  
    
    bool bHide;

    
    

};

