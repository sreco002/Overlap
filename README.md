# Overlap
**This is a display of my research for the degree exhibition Overlap**

## What is it?
An installation for people to connect with each other in a playful way


## How does it work?
If two people look at each other, an animation is created.
They have to match each other faces in order to control the animation on the face of each other

## What is the outcome?

Eye contact - make things move


## Diary



***21 june***



Strategy : 
Investigate the problem of **Eye tracking**


Documentation : start github to organise resources
learn how to use github to publish research via a blog?

Crit sessions : Irini Papadimitriou V&A curator for digital works ,( http://www.vam.ac.uk/blog/news-learning-department/digital-futures-e-stitches soft computing)situationist movement, stanza (http://www.stanza.co.uk/sonicity/index.html Stanza)
Atau : investigate more in the gaze proposition in opposition to the journey under the umbrella
my feelings after feedback : focus on the gaze state , more adapted to the degree show and more clear. solve the problem of how to check if people looks at each other. 


Coding : 
**ofxDlib to use faceTracker** for two people at the same time, have to check if it is doing for profiles too or only face
**TravelSales men strategy with genetic algorithm with CodingTrain** , how about using people gazing or not as a mutation factor in this strategy? 

Technical Equipment : 
Organise test for IR camera kinect, webcam, monocular camera to computer


In the bin : 
a journey under the umbrella, maybe for a next exhibition , references to the Situationist movement in opposition of surrealist
Thoughts after feedback : Fail to make it interesting to curators, Too complicate and unclear outcome
*What was it?*
People will navigate under an umbrella , unseen 
*How did it work?*
they will listen to instructions to navigate through the exhibition
instructions from the computer. They will also hear poems when they will be located at certain positions
They will pass the umbrella to another person who will continue the journey
*What was the outcome?*
Me and the other, no Eye contact
Eye contact only when exchanging umbrella




1. one


2. two


***7 June***

Crit sessions : 

What is it?
An installation for people to connect with each other in a playful way

How does it work?
If two people look at each other, an animation is created.
They have to match each other faces in order to control the animation on the face of each other

What is the outcome?
Eye contact - make things move

Feedback from Atau
It is like Marina Abramovich, offering her gaze to people 


**5th July**

have been a part of an experience by a design curating student about Encounter ;)
ideas about the settings and sounds
+ another critical studies reference : Emmnuel Levinas a french philosopher and a book "Totality and Infinity"
will check and put it in the documentation and research

Crit sessions
show my IR eye video and the picture with the hacked on a stick
no need for Calibration if the settings provide enough depth to allow interesting shadows or projections casting

### Level ZERO of Eye contact project
* TWO HUMANS sitting and facing each other , two chairs wearing _eye contact_ devices
* the DISTANCE between them is a constant determined at the launch of the program (via a GUI) / two chairs with a table

* the COMPUTER check GAZE and HEAD positions , to send animations via projector and maybe sounds (LEVEL 1);


HARDWARE / TODO
finalize version with PS3 cam
try a version with wifi cam

SOFTWARE / TODO
check https://webgazer.cs.brown.edu/


** 3rd july
tip about the eyewriter project of Zach Lieberman
very old code , still very helpful to have it to reverse engineering 
will try to use it to use it create a pseudo code and code it 
not quite sure about the addons ....
everything to old
will use the pseudo code and rewrite it

hacking PSE3 webcam 


** 1/2nd july
managed to build a IR webcam , with Sogatel webcam
the wire for the USB link are to tiny and too fragile
ok for testing but not probably for the finished product
put the webcam on a frame 
liked the look of it half robotic

**28th june**
***
thought about Eye gaze , tracking algorithm
**accuracy ?**
two people from a distance , I need to check I am looking in the direction of someone
the camera will check the position of this person.
the projector will draw visuals on this person (if projected on the face, needs to check the luminosity)
Do I need areas of interest instead of precise locations?
the longer the distance, the lower the accuracy has to be .
the project does not need high accuracy. We need to check the gaze at the face of someone in front, in a straight line.
-> calculate the distance and the angle of accuracy

http://www.cl.cam.ac.uk/research/rainbow/projects/eyetab/
 
* approach to build on the model-based “one-circle” algorithm presented in [Wang et al. 2003] which tracks gaze in RGB images
* Gaze estimation from RGB images , Detected eye-pair Coarse eye-ROIs Refined eye-ROIs

* The centre of a circular pattern is defined as the point where the most image gradient vectors intersect

**27th june**
***
Safety glasses cut in shape
Sogatel Camera IR filter replaced by negative film , checked Ok

next to be done : add IR LED in series to the camera
and mount the camera with LED on glasses with wire

try the projector box with magnifying glass and smartphone
next next : test the transmission in OF



**26th june**
***
see MINIMUM SCENARIO

**TECHNOLOGY** : it is difficult to actually write or draw with the eye, because the eye is not doing smooth movements.
the installation needs to **check only where the watcher is looking,** and not what , avoid need for too much precision
we can say it will be someone : the "performer"
( https://www.newscientist.com/article/dn22112-gaze-tracking-illusion-lets-you-draw-with-your-eyes/), 

Help from the scenario : to make the watcher follow something,
the wider the movement , the best it is 

HOW TO FORCE THE WATCHER 's EYE TO MAKE BIG MOVEMENT?

**STRATEGY**

* Watcher is the one with eye tracking system 
* Performer is followed by the eye of the watcher
* the different gazes will be taken as references for "drawing" on the performer
* Performer will move his/ her face only like in AEIO
* Drawings are planned in large scale , the Performer will catch the drawings projected. The Performer will be in front of a screen/ wall where the remaining drawings will be projected
* possibilty of displaying the different parts , the eye tracker is looking at ? on 5 different screens? https://uk.pinterest.com/pin/774408098396475619/


**PLAN**

* -> make eye tracker glasses
* -> check the feed back from the tracker
* -> check the relation between distance ( watcher/performer) and efficiency of the tracking( noticeable difference between feedbacks)
* -> create a 3D staging mock up
* -> use camera and AEIO to have data from the face of the "watcher"
* -> combine feed back from the tracker and from FaceOSc on the watcher to draw on the face of the viewer


**23th june**
***


make an installation 
one person is equipped with eye tracker glasses
looking at someone
trying to DRAW ON the person you are looking at 
manage distance to help drawing not accurately but aesthetically pleasant
maybe having an automate between them which will be activated if they look at each other

plan 
-> make eye tracker glasses
-> check the feed back from the tracker
-> create an animation with the information from the feed back



28 07
safety issue on IRLED for my eye
-> time IRLED not always on, triggered by presence of a visitor, sensor on the chair of the visitor (take a cushion and put sensor in it : put two sensor , )
when triggered , look for my iris , is it straight?
if it is straight , stop IR
if there is no one or if it is over 2 mn, check again

29/07
— verifier pourquoi calibration sur PI ne marche pas : example-ofxCvPiCam-calibration
et en se mettant en face si face follow marche
- tester camera USB sur PI
verifier compilation sur ordi via smba?
changer la longueur du connecteur a camera
checker camera IR led sur PI

alimentation indépendante des IR Led lies a sensor coussin,
envoyer information des sensors via OSC?  prise en main Xbee 

 30/07
tried XBee connection , for a cushion sensor
set up Xbee ok
communication through Mac ok
no communication to pi


test solid clay on silicone
nice pictures


30/07
Xbee s2d mesh digi set up 
a lot of unplug plug close to be able to work out the settings!!!!
Xbee serial mesh networking OK ;)
every Xbee is to be plugged to serial port of a computer

XBee + Raspberry?
The console used to diagnose transmitted data is integrated in XCTU, and it is only available when the module connected to the PC is running in API mode. Therefore, it makes sense to operate the endpoint in AT mode and the coordinator in API mode.

31/07
leave Xbee pressure sensor for now
solid clay not possible to take off without breaking it

to do 

cast another half mask in plaster /Ok


draw the schematic of the installation to see the picture /ok


IR led position and number

set up for the projector
set up hardware with the table


http://users.ntua.gr/bnakos/Eye_Tracking_Eng.html
for the position and number of Led
just one The infrared LED, which is located under the observer's eye, illuminates the eyeball while its image is being capturing by the camera that is placed next to the infrared LED. another one
http://www.jasonbabcock.com/eyetracking.html


//install 7 inch HDMI LCD screen to raspberry pi
http://www.waveshare.com/wiki/7inch_HDMI_LCD_(B)#Working_with_Raspberry_Pi

sudo nano /boot/config.txt

follow instructions
declare HDMI 
careful size screen set adequately

worked but not the touch screen


// screen 7 inch connected  - plug ethernet cable on Pi 
control from computer is then possible again

 need s screen to startup the PI
then remote control is possible
//screen 3.5 
no 


1 Aout still to do as of 2 August



/Software
// connection OF et Arduino , via Firmata

http://www.instructables.com/id/Arduino-Installing-Standard-Firmata/

use Firmata example in OF/ examples/ communication 

Firmata is working only with Uno

run on Raspberry

http://www.instructables.com/id/Arduino-On-Pi/


Installation must also run without Raspberry , in case of Raspberry failing !


Hardware
// Projector 

Add Mirror to projector 
http://www.physchim.info/webphy/optique/colorimetrie/video_proj_RVB/video_proj_RVB.html
create a stand for the mirror
https://www.youtube.com/watch?v=7Cijm_W71_w


Order wood for table top , to install Hardware under

Holographic effect
https://www.youtube.com/watch?v=1PfTBLUKbLo


Mask making again
attach camera IR Led for demonstration
used soft textile technique to fit the mask
create a switch textile to turn off and on the IR led

search for safety IR led on eye

worked on the logistic moving in and back , fit in a suitcase ;)

2 aout

try to avoid using screen PI to connect remotely without screen and mouse 

https://www.raspberrypi.org/documentation/remote-access/ssh/passwordless.md


nope

try to use the noIR camera
compel videoGrabber example on PI, had error like 
https://forum.openframeworks.cc/t/ofgstvideoutils-not-loaded-error-opencvexample/13760/10

input solution
and reboot
make Clean to clean previous compiling 

videoPlayer example works
videoGrabber does not work

need special RPi Grabber
https://github.com/jvcleave/ofxRPiCameraVideoGrabber

try to run example_pixels

will back up the Pi too 
https://www.raspberrypi.org/magpi/back-up-raspberry-pi
OK

test the projector

avoid the nose, problem of mapping
flat the nose
or change the mesh



