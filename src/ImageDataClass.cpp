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



const int imageThumbWidth = 40;
const int imageThumbHeight = 40;

const int gridSize = 20;

// currently 800






void ImageDataClass::initialize(int i)
{
    
    
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
    //// end of getting the image
    
    
    //start of getting exif data
    
    
    string exifFilePath = ofToString(folderName) +"/"+ ofToString(exifFolder) + "/" + ofToString(exifBaseName) + ofToString(i+1) + ofToString(exifExtention);
    
    ofFile file(exifFilePath, ofFile::ReadOnly);
    if( file.isFile())
    {
        ofBuffer buffer = file.readToBuffer();
        //cout << buffer.getText()<<endl ;
        
        
        while(!buffer.isLastLine() )
        {
            string exifLine = buffer.getNextLine();
            
            if ( exifLine == "-Exposure" )
                this->sShutterSpeed.append(buffer.getNextLine() + "  ");
            
            if ( exifLine == "-Aperture" )
                this->sAperture.append(buffer.getNextLine() + "  ");
            
            if ( exifLine == "-ISO Speed" )
            {
                this->sISOSpeed.append(buffer.getNextLine() + "  ");
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
        
        //cout << exifDataString1[i] << exifDataString2[i] << exifDataString3[i] <<endl;
        //cout << i <<" + "<< this->dISOSpeed<<" + "<< this->dAperture <<" + " << this->dShutterSpeed << endl;
        
        
    
        //EXIFInfo exifData;
    
    }
    
    // add if 0 case later
    //string imagePath;
    this->imageNumber = i ; // keeping track of initial numbers

    
    int imageXposition = i%gridSize * imageThumbHeight;
    int imageYposition = i/gridSize * imageThumbWidth;
    
    
    this->isImageSelected = false;
    this->isImagePersist = false ;

    }

