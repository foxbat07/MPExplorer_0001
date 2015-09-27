#pragma once

#include "ofMain.h"
#include "ofxSelfOrganizingMap.h"
#include "ofxExif.h"

#include "ImageDataClass.h"


// for a grid of 600 * 600 p , change accordingly

const int numberOfTestImages = 400;


const int imageThumbWidth = 40;
const int imageThumbHeight = 40;


//const int numberOfTestImages = 400;
//const int gridSize = 20;
//
//const int imageThumbWidth = 20;
//const int imageThumbHeight = 20;



const int xMargin = 50;
const int yMargin = 50;


const int fullImageX = 1200;
const int metaBeginY = 750;
const int metaLineHeight = 25;






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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        double minInArray(double passedArray[]);
        double maxInArray(double passedArray[]);
    
        void drawFullImage(int selectedImageNumber);
    
    
    
        // SOM stuff
//        ofxSelfOrganizingMap som;
//        ofImage somImg, sourceImg, sourceImgThumbs[5];
//        string sourcePaths[5];
    
        //image cataloguing stuff
        ofImage imageThumbs[numberOfTestImages];
        ofImage selectedFullImage;
    
        string imagePaths[numberOfTestImages];
        string selectedFullImagePath;
        string exifDataString[numberOfTestImages];
    
        string exifDataString1[numberOfTestImages];
        string exifDataString2[numberOfTestImages];
        string exifDataString3[numberOfTestImages];
    
        double exifDataInt1[numberOfTestImages];
        double exifDataInt2[numberOfTestImages];
        double exifDataInt3[numberOfTestImages];

    
    
    
        int selectedImageNumber = 0;
        int gridSize = sqrt(numberOfTestImages);
            
    
        //pathnames
        string folderName = "mirflickr";
        string imageBaseName = "im";
        string imageExtension = ".jpg";
    
        string exifFolder = "meta/exif";
        string exifBaseName = "exif";
        string exifExtention = ".txt";
    
    
        // check for mouse
        bool mouseInsideGrid = false;
    
    
        //FBO for image grid
        ofFbo fbo;
        ofFbo fbo2;
    
        //SOM
        //ofxSelfOrganizingMap som;

    
    //    ImageDataClass GridImages[numberOfTestImages];
    
        
        vector<ImageDataClass> GridImages;
    
        
    
    
    
		
};
