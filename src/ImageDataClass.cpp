//
//  ImageDataClass.cpp
//  MPExplorer_001
//
//  Created by Mohit Hingorani on 9/20/15.
//
//

#include "ImageDataClass.h"

//pathnames

string folderName = "mirflickr";
string imageBaseName = "im";
string imageExtension = ".jpg";

string exifFolder = "meta/exif";
string exifBaseName = "exif";
string exifExtention = ".txt";

string tagFolder = "meta/tags";
string tagName = "tags";
string tagExtention = ".txt";

string thumbnailFolder = "thumb";
string thumbnailName = "im";
string thumbnailExtention = ".jpg";



const int imageThumbWidth = 100;
const int imageThumbHeight = 100;

const int gridSize = 10;

// currently 800






void ImageDataClass::initialize(int i)
{
    ///start of getting image
    
    
    this->imagePath = ofToString(folderName) + "/" + ofToString(imageBaseName) + ofToString(i+1) + ofToString(imageExtension);
    
    
    
    
    this->thumbImage.loadImage(this->imagePath);
    
    int aspectDifference = this->fullImage.width - this->fullImage.height;
    
    if ( aspectDifference == 0 )
    {
        // dont crop it is square
    }
    else if ( aspectDifference > 0 )
    {
        // it is landscape x moves
        this->fullImage.crop(aspectDifference/2 , 0 , this->fullImage.height, this->fullImage.height);   // height is less, stick with the height;
    }
    else if ( aspectDifference < 0 )
    {
        // it is portrait y moves
        this->fullImage.crop(0 , -aspectDifference/2 , this->fullImage.width, this->fullImage.width);   // width is less, stick with width
        
    }
    
    
    this->thumbImage.resize( imageThumbWidth, imageThumbHeight);
    
    
    //saving out the image
    
//    string thumbnailImagePath = ofToString(thumbnailFolder) + "/" + ofToString(thumbnailName) + ofToString(i+1) +".png";
//    
//    this->thumbImage.saveImage(thumbnailImagePath);
    

    
    
    //// end of getting the image

    
    //start of getting exif data
    
    
    string exifFilePath = ofToString(folderName) +"/"+ ofToString(exifFolder) + "/" + ofToString(exifBaseName) + ofToString(i+1) + ofToString(exifExtention);
    
    ofFile file(exifFilePath, ofFile::ReadOnly);
    if( file.isFile())
    {
        ofBuffer buffer = file.readToBuffer();
        //cout << buffer.getText()<<endl ;
        
        int eCounter = 0 ;
        int ACounter = 0 ;
        
        
        
        while(!buffer.isLastLine() )
        {
            string exifLine = buffer.getNextLine();
            
            if ( exifLine == "-Exposure" )
                this->sShutterSpeed.append(buffer.getNextLine() + "  ");
            
            if ( exifLine == "-Aperture" && ACounter == 0 )
            {
                this->sAperture.append(buffer.getNextLine() + "  ");
                ACounter++;
            }
            
            
            if ( exifLine == "-ISO Speed" )
            {
                this->sISOSpeed.append(buffer.getNextLine() + "  ");
                
            }
            
            if ( exifLine == "-Focal Length" )
            {
                this->sFocalLength.append(buffer.getNextLine() + "  ");
                break;

            }
            
        }
                
        
        // cleaning up to integers for SOM
        //for Exposure
        vector<string> ExposureSplit;
        ExposureSplit =  ofSplitString( this->sShutterSpeed , " ");
        this->dShutterSpeed = ofToDouble ( ExposureSplit[0] ) ;
        
        //for Aperture
        vector<string> ApertureSplit;
        ApertureSplit =  ofSplitString(this->sAperture , "f/");
        this->dAperture = ofToDouble ( ApertureSplit[ApertureSplit.size()-1] );
        
        
        // for ISO speed
        this->dISOSpeed = ofToDouble ( this->sISOSpeed ) ;
        
        // focal length split
        vector<string> FocalLengthSplit;
        FocalLengthSplit =  ofSplitString( this->sFocalLength , " ");
        this->dFocalLength = ofToDouble ( FocalLengthSplit[0] ) ;

        
        
        //cout << exifDataString1[i] << exifDataString2[i] << exifDataString3[i] <<endl;
        //cout << i <<" + "<< this->dISOSpeed<<" + "<< this->dAperture <<" + " << this->dShutterSpeed << endl;
        
        
    
        //EXIFInfo exifData;
    
    }
    
    
    
//    ///getting tag data
//    string tagPath = ofToString(folderName) +"/"+ ofToString(tagFolder) + "/" + ofToString(tagName) + ofToString(i+1) + ofToString(tagExtention);
//    
//    ofFile tagFile(tagPath, ofFile::ReadOnly);
//    if( tagFile.isFile())
//    {
//        ofBuffer buffer = tagFile.readToBuffer();
//        //string tagString;
//        
//        while(!buffer.isLastLine() )
//             {
//                 string tag = buffer.getNextLine();
//
//                 tagString.append(tag);
//                 tagString.append(" ");
//             }
//        // should have a string by now
//
//    }
    
    
        
        
        
    
    
    
    
     //add if 0 case later
    string imagePath;
    this->imageNumber = i ; // keeping track of initial numbers

    
    int imageXposition = i%gridSize * imageThumbHeight;
    int imageYposition = i/gridSize * imageThumbWidth;
    
    
    this->isImageSelected = false;
    this->isImagePersist = true  ;
    this->isImageInRange = true ;

    }

