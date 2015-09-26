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



class ImageDataClass{
                    public:
                    ofImage fullImage;
                    ofImage thumbImage;
                    EXIFInfo exifData;
    
                    string imagePath;
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
                    bool isImageGood;
                    bool isImageBad;
                    
                    bool imageWidth;
                    bool imageheight;
    
    
    
};