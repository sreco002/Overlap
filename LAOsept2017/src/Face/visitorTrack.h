//
//  visitorTrack.hpp
//  LAO
//
//  Created by Main on 11/08/2017.
//
//


#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"
#include "ofxSyphon.h"
#include "shapeSys.h"
#include "irisFinder.h"
#include "irisDraw.h"


//: public ofBaseApp, public FaceOsc
    class visitorTrack  {

public:
    visitorTrack();
    //variables
    //functions
    void setup();
    void update();
    void draw(ofPoint p,int gaze);
        
    void loadSettings();
    void setVideoSource(bool useCamera);
        
        bool bUseCamera, bPaused;
        
        int camWidth, camHeight;
        int movieWidth, movieHeight;
        int sourceWidth, sourceHeight;
        
        ofVideoGrabber visitorCam, vidGrabber;
        ofVideoPlayer movie;
        ofBaseVideoDraws *videoSource;
        
        ofxFaceTracker visitorFace;
        ofMatrix4x4 rotationMatrix;
        
        bool bDrawMesh;
        
        ofxPanel gui;
        bool bGuiVisible;
        
        // vector ofPoints of raw data
        
        vector <ofPoint> rawVector;
        ofPolyline poly;
        ofMesh meshR;
        
        
        // drawing and names feed
        irisDraw irisSmilepaint;
        void drawAnim(ofPoint p, int scale);
        string faceName;
        vector<string> names; // declare an empty vector of names 

        
        // sending to MadMapper with ofxSyphon, based on ofxSyphon example basic
        
        float 	counter;
        bool	bSmooth;
      //  ofFbo fbo;
        ofImage ImageSend;
        ofTexture tex;
        vector<ofPixels> pixVector;
        
        ofxSyphonServer mainOutputSyphonServer;
        ofxSyphonServer individualTextureSyphonServer;
        
        ofxSyphonClient mClient;
        
        
        
        // shapeSys
        
        shapeSys FlowerSys;
        int numFlower, radiusFlower, indexColor;
        vector<ofPoint> seeds;
        vector<int> maskHexColor;
        bool changeColorShapeSys; // toggle the colour change for the background of the animation
        
        
        void setupShapeAnim();
        void updateShapeAnim();
        void drawShapeAnim();
        

        
        
        
        
        
};
