//
//  ImageDataClass.h
//  MPExplorer_001
//
//  Created by Mohit Hingorani on 9/20/15.
//
//

#ifndef __MPExplorer_001__ImageDataClass__
#define __MPExplorer_001__ImageDataClass__

#include "ofxExif.h"



#endif /* defined(__MPExplorer_001__ImageDataClass__) */



class ImageDataClass
    {
    public:
        
    ofImage fullImage;
    ofImage thumbImage;
        
    EXIFInfo exifData;
    //ofxThreadedImageLoader loader;

    string imagePath;
    string thumbPath;
    
    int imageNumber;

    string sFocalLength;
    string sISOSpeed;
    string sShutterSpeed;
    string sAperture;

    string sExifDataString;

    double dFocalLength;
    double dISOSpeed;
    double dShutterSpeed;
    double dAperture;

    int imageXposition;
    int imageYposition;
    
    bool isImageSelected;
    bool isImagePersist;
    bool isImageInRange;
        
        
    
    bool imageWidth;
    bool imageheight;
        
    vector <string> tagwords;
    string tagString;


    void initialize(int i);
    //void update();
        
        
        
    
    
        
         
    };
