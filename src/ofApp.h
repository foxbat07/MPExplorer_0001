#pragma once

#include "ofMain.h"
#include "ofxSelfOrganizingMap.h"
#include "ofxExif.h"
#include "ImageDataClass.h"
#include "ofxThreadedImageLoader.h"



// for a grid of 600 * 600 p , change accordingly

const int numberOfTestImages = 144;


const int imageThumbWidth = 75;
const int imageThumbHeight = 75;


//const int numberOfTestImages = 400;
//const int gridSize = 20;
//
//const int imageThumbWidth = 20;
//const int imageThumbHeight = 20;



const int xMargin = 50;
const int yMargin = 50;


const int fullImageX = 1200;
const int metaBeginY = 800;
const int metaLineHeight = 25;
const int convergingMinimum = 6;


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
        void updateGridFbo ();
        void updateSOM ();
        void initializeSOM ();
        void clearSelections();
        void updateSelections( int selectedImageNumber );
        void theConvergingFunction();
        void theRemovingFunction();
        void getNewImages();
        void injectNewPhotos();
        bool checkIfImageValid ( ImageDataClass tempImage);
        void drawCurrentStateParameters();
        void updatePlots();
    
        void refreshFeed();
    
        void setExifExtreme();
    
    
    
    
    
    
        // SOM stuff
        ofxSelfOrganizingMap som;
    
//        ofImage somImg, sourceImg, sourceImgThumbs[5];
//        string sourcePaths[5];
    
        //image cataloguing stuff
        ofImage imageThumbs[numberOfTestImages];
        ofImage selectedFullImage;

        string selectedFullImagePath;
    
    
        int selectedImageNumber = 0;
        int gridSize = sqrt(numberOfTestImages);
    
        bool converging = false;
    
        // check for mouse
        bool mouseInsideGrid = false;
    
    
        //FBO for image grid
        ofFbo fbo;
        ofFbo fbo2;
        ofFbo plotsFBO;
    
        //SOM
        //ofxSelfOrganizingMap som;
    
    //   ImageDataClass GridImages[numberOfTestImages];
        
        vector<ImageDataClass> GridImages;
        vector<int> pickedImagevector;
        vector<int> imagesRemoved;

        string folderName = "mirflickr";
        string imageBaseName = "im";
        string imageExtension = ".jpg";
        
        string exifFolder = "meta/exif";
        string exifBaseName = "exif";
        string exifExtention = ".txt";
    
    
        double dMinFocalLength = 1000;
        double dMinISOSpeed = 10000 ;
        double dMinShutterSpeed = 100 ;
        double dMinAperture = 100 ;
        
        double dMaxFocalLength = 0;
        double dMaxISOSpeed = 0;
        double dMaxShutterSpeed = 0;
        double dMaxAperture = 0;
    
        // make sure they are doubles
    
        int imageStack = numberOfTestImages;
    
        int dataCellWidth = 10 ;
        int dataCellHeight = 20 ;
        int heightDifference = 20;
    
        double plotWidth = 400;
    
            
    
		
};
