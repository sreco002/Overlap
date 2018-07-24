//
//  irisFinder.hpp
//  LAO
//
//  Created by Sabrina Recoules Quang on 11/08/2017.
//
//

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
//#include "irisDraw.h"


class irisFinder{
public:
    irisFinder();
    //variables
    //functions
    void setup( int  screenX, int screenY, int w, int h, int t, float g, float tT, float b);// position and size screen checking, tolerance from center,  ratio Gaze treshold,  time stay long enough, blinkrate
    void update( ofxCvGrayscaleImage 	grayDiff,  int m, int M);
   

    
    
    void updateCheck();
    ofPoint find(bool b, int tolerance);
    void drawAnim(int  screenX, int screenY);
    void learn();
    int gaze(); // return 0, if looking straight, 1, if looking right, 2, if looking left
    float blinkRate; // use to adjust the gaze computing
    void checkGaze();
    
    
    
    
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
   
    //contourFinder
    
     ofxCvContourFinder 	contourFinder;
    
    // iris
    
    ofPoint iris;
    ofPoint lastIris;
    ofPoint irisBg; //  iris coordinate from the background
    
    
    
    bool   bstraight, bright, bleft; // where do I look
    bool irisFind ; // is there an iris ?
    bool  bLearnIrisBg;
    
    // screen variables to draw results of the findings
    
    int screenX, screenY, screenW, screenH;
    int tolerance;
    
    // report hiding or not
    bool bHide;
    
    
    
    
  // gaze probablilty schecking over the period of timeTresh starting at  timeStart
    float timeStart;// when do we start to count
    float timeTresh;//  long enough time
    float ratioGazeTresh; // stayed at the same gaze long enough
    float ratioGaze ; // checking if this ratio is greater than the ratio GazeTresh to tell which direction we are looking at
    
    float countStraight, countCheck;
    float ratioStraight;
    bool bStraightLongEnough; // i was looking straigth long enough, reset the timeStart
    
    // same checking with left and right
    
    float countLeft;
    float ratioLeft;
    
  //  bool bLeftLongEnough; // i was looking straigth long enough, reset the timeStart
    
    float countRight;
    float ratioRight;
  //  bool bRightLongEnough; // i was looking straigth long enough, reset the timeStart
    
    // draw different position, if the position has not changed for long enough, do not change the position of the iris
    
    bool isLongEnough;
    
    
    
    
    
    
};
