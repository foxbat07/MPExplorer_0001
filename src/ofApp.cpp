#include "ofApp.h"
#include <algorithm>



//--------------------------------------------------------------
void ofApp::setup(){
    
    // setting OF diplay parameters
    ofSetVerticalSync( true );
    ofSetFrameRate(60);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableSmoothing();

    // switching to new scheme of things
    
    for (int i = 0, j = 0 ; j  < numberOfTestImages; i++)
         {
             
             ImageDataClass tempClass;
             tempClass.initialize(i);
             if ( tempClass.dAperture != 0 && tempClass.dISOSpeed != 0 && tempClass.dFocalLength > 10 && tempClass.dShutterSpeed != 0 )
             {
                 tempClass.imageNumber = j ;
                 GridImages.push_back(tempClass);
                 j++;
                
             }
             
                 
             imageStack =  i ; 
         }
    
    
    
    
    //find min and max for SOM
//    
//    double minInArray1 =  minInArray( exifDataInt1 );
//    cout<<minInArray1<<endl;
//    
//    double maxInArray1 =  maxInArray( exifDataInt1 );
//    cout<<maxInArray1;
//    
    // WELL THAT WORKS
    

    //creating FBO
    
    fbo.allocate(gridSize * imageThumbWidth, gridSize* imageThumbHeight, GL_RGBA );
    plotsFBO.allocate(plotWidth , 10 * dataCellHeight , GL_RGBA);
    
    //fbo2.allocate(gridSize * imageThumbWidth, gridSize* imageThumbHeight, GL_RGB );
    
    fbo.begin();
    ofClear(255,255,255);
    //ofTranslate(xMargin, yMargin);
    for (int i = 0 ; i < numberOfTestImages; i++)
        {
        //imageThumbs[i].draw( i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight );
        GridImages[i].thumbImage.draw(i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight );
        
            
        }
    fbo.end();
    
    //fbo2 = fbo;
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    //update FBO
    //ofTranslate(xMargin, yMargin);
    updatePlots();
    

}

//--------------------------------------------------------------
void ofApp::draw(){

    
    ofBackground(0);
    
    
    /*
    ofDrawBitmapString("Source image", 30, 20);
    
    sourceImg.draw(20, 30, 480, 480);
    somImg.draw(520, 30, 480, 480);
    
    */
    
     
    //ofDrawBitmapString("Self-organizing map: Iteration " + ofToString(som.getCurrentIteration()) + "/" + ofToString(som.getNumIterations()), 530, 20);
    
    
    fbo.draw(xMargin, yMargin);
    
    
    //if(pickedImagevector.size() >0 )
    plotsFBO.draw(fullImageX , yMargin + 520  );
    
    //fbo2.draw(xMargin + fullImageX- 200, yMargin);
    drawFullImage(selectedImageNumber);
    drawCurrentStateParameters();
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'r')
    {
        refreshFeed();
        
    }
    
    if ( key == 'c')
    {
        clearSelections();
        
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    

    // selected image sholuld be a function of x & y
    
    
    if ( x > xMargin && y > yMargin &&  x <  ( xMargin + gridSize * imageThumbWidth ) &&  y < ( yMargin + gridSize * imageThumbHeight ) )
        {
            mouseInsideGrid = true;
            int xLevel = ( x - xMargin ) / imageThumbWidth;
            int yLevel = ( y - yMargin ) / imageThumbHeight;
            selectedImageNumber = yLevel  + xLevel * gridSize;
        }
    else
        {
            mouseInsideGrid = false;
        }
    

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    //mouse clicks
    
    
    updateSelections(selectedImageNumber);
    
    
    updateGridFbo();
    updatePlots();
    
    if ( pickedImagevector.size() >= convergingMinimum )
    {
        theConvergingFunction();
        converging = true;
    }
    
    

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}





double ofApp::minInArray(double passedArray[])
{
    int minElement;
    minElement = passedArray[0];
    
    for ( int i = 0 ; i< numberOfTestImages ; i++ )
    {
        if (minElement > passedArray[i])
            minElement = passedArray[i];
    }
    
    return minElement;
    
}


double ofApp::maxInArray(double passedArray[])
{
    int maxElement;
    maxElement = passedArray[0];
    
    for ( int i = 0 ; i< numberOfTestImages ; i++ )
    {
        if (maxElement < passedArray[i])
            maxElement = passedArray[i];
    }
    
    return maxElement;
    
}



void ofApp::drawFullImage(int selectedImageNumber)
{
    //create selected image
    ofPushMatrix();
    // selectedFullImagePath = ofToString(folderName) + "/" + ofToString(imageBaseName) + ofToString( GridImages[ selectedImageNumber + 1 ].imageNumber ) + ofToString(imageExtension);        // fix original image issue
    selectedFullImagePath = GridImages[selectedImageNumber].imagePath;
    
    selectedFullImage.loadImage(selectedFullImagePath);
    selectedFullImage.draw(fullImageX , yMargin);
    ofPopMatrix();
    
    
                                                                                                  
       
    

}


void ofApp::updateGridFbo()
{
    fbo.begin();
    for (int i = 0 ; i < GridImages.size() ; i++)
    {
        //imageThumbs[i].draw( i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight );
        GridImages[i].thumbImage.draw(i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight);
        
        
        if( GridImages[i].isImageSelected == true  )
        {
            ofSetColor( ofColor::green,100);
            //ofNoFill();
            
            ofRect( i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight, imageThumbWidth, imageThumbHeight );
            ofSetColor( ofColor::white );
            
        }
        
        if( GridImages[i].isImagePersist == false  )
        {
            ofSetColor( ofColor::red,100);

            ofRect( i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight, imageThumbWidth, imageThumbHeight );
            ofSetColor( ofColor::white );
            
        }
        
        
    }
    fbo.end();
    
}



void ofApp::clearSelections()
{
    
    pickedImagevector.clear();
    for ( int  i = 0 ; i < numberOfTestImages ; i ++ )
    {
        GridImages[i].isImageSelected = false;
        
    }
    updateGridFbo();
    
}


    
    
void ofApp::updateSOM ()
{
    
    //    int randomNumber = ofRandom(100);
    //    double instance[3] = { exifDataInt1[randomNumber],exifDataInt2[randomNumber],exifDataInt3[randomNumber] };
    //    som.updateMap(instance);
    
    
    //in update map create quantized movements
    
    //update FBO
    
    
    //    for (int i = 0; i < 256; i++) {
    //        for (int j = 0; j < 256; j++) {
    //            double * c = som.getMapAt(i,j);
    //            ofColor col(c[0], c[1], c[2]);
    //            somImg.setColor(i, j, col);
    //        }
    //    }
    //    somImg.update();
    
    
    
    //    for (int i = 0; i < gridSize; i++) {
    //        for (int j = 0; j < gridSize; j++) {
    //            double * exifData = som.getMapAt(i,j);
    //            for ( int k = 0 ; k < numberOfTestImages ; k++ )
    //                {
    //                if( exifData[0] == exifDataInt1[k] && exifData[1] == exifDataInt2[k] && exifData[2] == exifDataInt3[k])
    //                // create a new table i guess
    //
    //                }
    //            
    //            
    //        }
    //    }
    
    //    fbo2.begin();
    //    ofClear(255,255,255);
    //    for (int i = 0; i < gridSize; i++) {
    //        for (int j = 0; j < gridSize; j++) {
    //
    //            double * exifData = som.getMapAt(i,j);
    //            ofSetColor(ofColor::blue);
    //
    //            ofDrawBitmapString( ofToString( exifData[0] ), i * imageThumbWidth , j * imageThumbHeight + 20 );
    //
    //            ofDrawBitmapString(ofToString( exifData[1] )  , i * imageThumbWidth , j * imageThumbHeight + 40 );
    //
    //            ofDrawBitmapString(ofToString( exifData[2] ) , i * imageThumbWidth , j * imageThumbHeight + 60 );
    //
    //            ofSetColor(ofColor::white );
    //
    //            //imageThumbs[i * gridSize + j ].draw( i * imageThumbWidth , j * imageThumbHeight );
    //            }
    //
    //        }
    //    fbo2.end();

    
    

}
void ofApp::initializeSOM ()
{
    //new SOM stuff
    
    //    double minInstance[3] = { minInArray( exifDataInt1 ), minInArray( exifDataInt2 ),minInArray( exifDataInt3 ) };
    //    double maxInstance[3] = { maxInArray( exifDataInt1 ), maxInArray( exifDataInt1 ),maxInArray( exifDataInt1 ) };
    //
    //    som.setFeaturesRange(3, minInstance, maxInstance);
    //    som.setInitialLearningRate(0.07);
    //    som.setNumIterations(4000);
    //    som.setMapSize(gridSize, gridSize);
    //    som.setup();
    
    
}


void ofApp::updateSelections( int selectedImageNumber )
{
    if ( GridImages[selectedImageNumber].isImageSelected == false )
    {
        GridImages[selectedImageNumber].isImageSelected = true;
        // add it to the picked images vector
        pickedImagevector.push_back(selectedImageNumber);
        
        
    }
    else if ( GridImages[selectedImageNumber].isImageSelected == true)
    {
        
        GridImages[selectedImageNumber].isImageSelected = false;
        
        for ( int i = 0 ; i < pickedImagevector.size() ; i ++ )
        {
            if ( selectedImageNumber == pickedImagevector[i] )
            {
                pickedImagevector.erase(pickedImagevector.begin() + i );
                
            }
        }
        
        
    }
}


void ofApp::theConvergingFunction()
        {
            converging = false;

            dMinFocalLength = GridImages[pickedImagevector[0]].dFocalLength;
            dMaxFocalLength = GridImages[pickedImagevector[0]].dFocalLength;
            dMinISOSpeed = GridImages[pickedImagevector[0]].dISOSpeed;
            dMaxISOSpeed = GridImages[pickedImagevector[0]].dISOSpeed;
            dMinShutterSpeed = GridImages[pickedImagevector[0]].dShutterSpeed;
            dMaxShutterSpeed = GridImages[pickedImagevector[0]].dShutterSpeed;
            dMinAperture = GridImages[pickedImagevector[0]].dAperture;
            dMaxAperture = GridImages[pickedImagevector[0]].dAperture;



            
            
            for ( int i  = 0 ; i < pickedImagevector.size() ; i++ )
                {
                 
                 // get each image check if it is lesser or greater than the current selection
                 //multiplicative factor? lol
                 //fancy statistics charts of current images?
                 
                 //to find min and max within our game
                    
                    
                  //focal length
                  if( dMinFocalLength > GridImages[pickedImagevector[i]].dFocalLength)
                  {
                      dMinFocalLength = GridImages[pickedImagevector[i]].dFocalLength;
                  }
                    
                    
                  if( dMaxFocalLength < GridImages[pickedImagevector[i]].dFocalLength)
                    {
                        dMaxFocalLength = GridImages[pickedImagevector[i]].dFocalLength;
                    }
                   cout<<"FL :  "<<dMinFocalLength<<"   "<< dMaxFocalLength <<endl ;
                    /////////////
                    
                    //ISO speed
                    if( dMinISOSpeed > GridImages[pickedImagevector[i]].dISOSpeed)
                    {
                        dMinISOSpeed = GridImages[pickedImagevector[i]].dISOSpeed;
                    }
                    
                    
                    if( dMaxISOSpeed < GridImages[pickedImagevector[i]].dISOSpeed)
                    {
                        dMaxISOSpeed = GridImages[pickedImagevector[i]].dISOSpeed;
                    }
                    cout<<"ISO:  "<<dMinISOSpeed<<"   "<< dMaxISOSpeed <<endl ;
                    //////////////
                    
                    
                    //Shutter Speed
                    if( dMinShutterSpeed > GridImages[pickedImagevector[i]].dShutterSpeed)
                    {
                        dMinShutterSpeed = GridImages[pickedImagevector[i]].dShutterSpeed;
                    }
                    
                    
                    if( dMaxShutterSpeed < GridImages[pickedImagevector[i]].dShutterSpeed)
                    {
                        dMaxShutterSpeed = GridImages[pickedImagevector[i]].dShutterSpeed;
                    }
                    cout<<"Exposure:  "<<dMinShutterSpeed<<"   "<< dMaxShutterSpeed <<endl ;
                    //////////////
                    
                    
                    //Aperture
                    if( dMinAperture > GridImages[pickedImagevector[i]].dAperture)
                    {
                        dMinAperture = GridImages[pickedImagevector[i]].dAperture;
                    }
                    
                    
                    if( dMaxAperture < GridImages[pickedImagevector[i]].dAperture)
                    {
                        dMaxAperture = GridImages[pickedImagevector[i]].dAperture;
                    }
                    cout<<"Aperture:  "<<dMinAperture<<"   "<< dMaxAperture <<endl ;
                    //////////////
                    cout<<"=========================" <<endl ;
                    
                    
                }
            
            // now for persistance, select the ones that are in range, red the rest
            
            
            for ( int i = 0 ; i< GridImages.size() ; i ++ )
                {
                 // setting up persistance
                    
                 if ( GridImages[i].dFocalLength >= dMinFocalLength &&  GridImages[i].dFocalLength <= dMaxFocalLength )
                     {
                      if ( GridImages[i].dShutterSpeed >= dMinShutterSpeed &&  GridImages[i].dShutterSpeed <= dMaxShutterSpeed )
                         {
                            if ( GridImages[i].dAperture >= dMinAperture &&  GridImages[i].dAperture <= dMaxAperture )
                            {
                             if ( GridImages[i].dISOSpeed >= dMinISOSpeed &&  GridImages[i].dISOSpeed <= dMaxISOSpeed )
                                 {
                                  // if it lies within all four ranges it stays
                                     GridImages[i].isImagePersist = true;
                                     GridImages[i].isImageInRange = true;
                                     
                                 }
                                
                            }
                         }
                             
                     }
                    
                else
                    {
                    GridImages[i].isImagePersist = false;
                    GridImages[i].isImageInRange = false;

                    }
                    
                    //bool back = checkIfImageValid(GridImages[i] )
                    
                    
                }

            theRemovingFunction();
            //injectNewPhotos();
            // replace right then and there?
            
        }


void ofApp::theRemovingFunction()
        {
            // removing all imagepersisted
            // check if criterion matched
            // if it does, replace
            // have an option to flush out and expand
            
            // evolving 3D vis with 2D scatter plots etc
            imagesRemoved.clear();
            for ( int i = 0 ; i< GridImages.size() ; i ++ )
            {
                if ( GridImages[i].isImagePersist == false )
                    {
                     //GridImages.erase(GridImages.begin() + i );
                     imagesRemoved.push_back(i);
                     //check if new image is any good
                    bool newImageFound = false;
                        
                    while( newImageFound == false )
                        {
                         ImageDataClass tempImage;
                         tempImage.initialize(++imageStack);
                            
                         bool isValid =  checkIfImageValid(tempImage);
                        
                         if (isValid)
                            {
                                GridImages[i] = tempImage;   //swap it for the new one, although its position will be wierd
                                GridImages[i].imageNumber = i; // resetting i. else it be in wierd places
                                newImageFound = true;
                                break;
                                
                            }
                          else
                          {
                              newImageFound = false;
                              continue;
                              
                          }
                        
                        }
                        
                     // image should be swapped at this point
                        
                     // add function to set number and position
                        
                    }
            
            }
            
         // remove photos
            
        }


void ofApp::injectNewPhotos()
{
    for ( int i = 0 ,  j = 0 ; i < imagesRemoved.size() ; i++, j++ )
    {
        //loop through next set of images
        
        //create new grid
        ImageDataClass testImageData;
        testImageData.initialize(imageStack + j );
        
        GridImages.push_back(testImageData);
        
        
    }
    
    
    updateGridFbo();
    
}



bool  ofApp::checkIfImageValid ( ImageDataClass tempImage)
{
    
    if ( tempImage.dFocalLength >= dMinFocalLength &&  tempImage.dFocalLength <= dMaxFocalLength )
    {
        if ( tempImage.dShutterSpeed >= dMinShutterSpeed &&  tempImage.dShutterSpeed <= dMaxShutterSpeed )
        {
            if ( tempImage.dAperture >= dMinAperture &&  tempImage.dAperture <= dMaxAperture )
            {
                if ( tempImage.dISOSpeed >= dMinISOSpeed &&  tempImage.dISOSpeed <= dMaxISOSpeed )
                {
                    // if it lies within all four ranges it stays
                    tempImage.isImagePersist = true;
                    tempImage.isImageInRange = true;
                    return true;
                    
                }
                
            }
        }
        
    }
    
    else
    {
        tempImage.isImagePersist = false;
        tempImage.isImageInRange = false;
        return false;
        
        
    }
    
   
    
}
                                                                                                  

                                                                                                  
void ofApp::drawCurrentStateParameters()
  {
      ofSetColor(ofColor::blueSteel);
      
      ofDrawBitmapString("selected image number: " + ofToString(selectedImageNumber), fullImageX, metaBeginY);
      ofDrawBitmapString("image Width  " + ofToString(selectedFullImage.width), fullImageX, metaBeginY + metaLineHeight);
      ofDrawBitmapString("selected image number: " + ofToString(selectedFullImage.height), fullImageX, metaBeginY + 2 * metaLineHeight );
      ofDrawBitmapString("framerate: " + ofToString( int(ofGetFrameRate()) ), fullImageX, metaBeginY + 3 * metaLineHeight);
      ofDrawBitmapString("ISO: " + ofToString( GridImages[selectedImageNumber].dISOSpeed ) + "    Exposure: " + ofToString( GridImages[selectedImageNumber].dShutterSpeed ) + "    Aperture: " + ofToString( GridImages[selectedImageNumber].dAperture)  + "    Focal length: " + ofToString( GridImages[selectedImageNumber].dFocalLength)  , fullImageX, metaBeginY + 4 * metaLineHeight);
      
      ofDrawBitmapString("image selections: " + ofToString( pickedImagevector ), fullImageX, metaBeginY + 5 * metaLineHeight);
      ofDrawBitmapString("image selection size: " + ofToString( pickedImagevector.size() ), fullImageX, metaBeginY + 6 * metaLineHeight);
      
      ofDrawBitmapString("converging: " + ofToString( converging ), fullImageX, metaBeginY + 7 * metaLineHeight);
      
      ofDrawBitmapString("Stack Number : " + ofToString( imageStack  ), fullImageX, metaBeginY + 8 * metaLineHeight);
      ofDrawBitmapString("Images Deleted: " + ofToString( imagesRemoved.size()  ), fullImageX, metaBeginY + 9 * metaLineHeight);
      
      ofSetColor(ofColor::white);

  }


void ofApp::updatePlots()
{
    //cout<<"updating plots" << endl ;

    
    vector<double> dISOList;
    vector<double> dFocalLengthList;
    vector<double> dShutterSpeedList;
    vector<double> dApertureList;
    
    for ( int  i = 0 ; i < pickedImagevector.size() ; i++ )
    {
        // create ISO chart
        dISOList.push_back(GridImages[pickedImagevector[i]].dISOSpeed);
        dFocalLengthList.push_back(GridImages[pickedImagevector[i]].dFocalLength);
        
        dShutterSpeedList.push_back(GridImages[pickedImagevector[i]].dShutterSpeed);
        dApertureList.push_back(GridImages[pickedImagevector[i]].dAperture);
        
    }   //aggregated list
    
    
    // drawing
    plotsFBO.begin();
    ofBackground(0);
       //ofTranslate(fullImageX, metaBeginY );
    
    for ( int i = 0 ; i < pickedImagevector.size() ; i++ )
    {
        
        ofSetColor(ofColor::blueSteel);
        ofFill();
        
        ofDrawBitmapString("ISO Speed:  ", 0, heightDifference -4);
         ofDrawBitmapString("Focal Length:  ", 0, 3 * heightDifference  -4);
        ofDrawBitmapString("Shutter Speed:  ", 0, 5 * heightDifference -4 );
        ofDrawBitmapString("Aperture :  ", 0, 7 * heightDifference -4  );
        ofSetColor(ofColor::blueSteel , 70 );
        
        ofRect( ( dISOList[i] - dMinISOSpeed )/ ( dMaxISOSpeed - dMinISOSpeed ) * plotWidth, heightDifference, dataCellWidth, dataCellHeight);
        
       
        
        ofRect( ( dFocalLengthList[i] - dMinFocalLength )/ ( dMaxFocalLength - dMinFocalLength )  * plotWidth, 3 * heightDifference , dataCellWidth, dataCellHeight);
        
        
        
        
        ofRect( ( dShutterSpeedList[i] - dMinShutterSpeed )/ ( dMaxShutterSpeed - dMinShutterSpeed )  * plotWidth, 5 * heightDifference , dataCellWidth, dataCellHeight);

        
        ofRect( ( dApertureList[i] - dMinAperture )/ ( dMaxAperture - dMinAperture ) * plotWidth , 7 * heightDifference , dataCellWidth, dataCellHeight);
        
        
        ofSetColor( ofColor::white);

        
    }
       plotsFBO.end();
    
    
    
    
}

void ofApp::refreshFeed()
{
    
    for ( int  i  = 0 ; i < GridImages.size() ; i++ )
    {
        
        
        if ( !GridImages[i].isImageSelected)
        {
            //remove photo and replace
            
            
            //GridImages.erase(GridImages.begin() + i );
            imagesRemoved.push_back(i);
            //check if new image is any good
            bool newImageFound = false;
            
            while( newImageFound == false )
            {
                ImageDataClass tempImage;
                tempImage.initialize(++imageStack);
                
                bool isValid =  checkIfImageValid(tempImage);
                
                if (isValid)
                {
                    GridImages[i] = tempImage;   //swap it for the new one, although its position will be wierd
                    GridImages[i].imageNumber = i; // resetting i. else it be in wierd places
                    newImageFound = true;
                    break;
                    
                }
                else
                {
                    newImageFound = false;
                    continue;
                    
                }
                
            }
            
            // image should be swapped at this point
            
            // add function to set number and position
            

            
            
        }
    }
    updateGridFbo();
    
}



