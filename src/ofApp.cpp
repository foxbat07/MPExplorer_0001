#include "ofApp.h"
#include <algorithm>

//--------------------------------------------------------------
void ofApp::setup(){
    
    // setting OF diplay parameters
    //ofSetLogLevel( OF_LOG_VERBOSE );
    ofSetVerticalSync( true );
    ofSetFrameRate(60);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableSmoothing();

    
     for (int i = 0; i < numberOfTestImages; i++)
         {
             
             imagePaths[i] = ofToString(folderName) + "/" + ofToString(imageBaseName) + ofToString(i+1) + ofToString(imageExtension);
             
             ofImage tempImage;
             tempImage.clear();
             tempImage.loadImage(imagePaths[i]);
             
             int aspectDifference = tempImage.width - tempImage.height;
             
             if ( aspectDifference == 0 )
             {
                 // dont crop it is square
             }
             else if ( aspectDifference > 0 )
             {
                 // it is landscape x moves
                 tempImage.crop(aspectDifference/2 , 0 , tempImage.height, tempImage.height);   // height is less, stick with the height;
             }
             else if ( aspectDifference < 0 )
             {
                 // it is portrait y moves
                 tempImage.crop(0 , -aspectDifference/2 , tempImage.width, tempImage.width);   // width is less, stick with width
                 
             }
             
             //tempImage.update();
             tempImage.resize(imageThumbWidth, imageThumbHeight);
             //tempImage.update();
             
             imageThumbs[i].clone(tempImage);
             
             
             //importing the exif data in the same pass
             
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
                             exifDataString1[i].append(buffer.getNextLine() + "  ");
                         if ( exifLine == "-Aperture" )
                             exifDataString2[i].append(buffer.getNextLine() + "  ");
                         if ( exifLine == "-ISO Speed" )
                         {
                             exifDataString3[i].append(buffer.getNextLine() + "  ");
                             break;
                         }
                            
                        }

                   
               }
               // cleaning up to integers for SOM
             //for Exposure
             vector<string> ExposureSplit;
             ExposureSplit =  ofSplitString(exifDataString1[i] , " ");
             exifDataInt1[i] = ofToDouble ( ExposureSplit[0] ) ;
             
             //for Aperture
             vector<string> ApertureSplit;
             ApertureSplit =  ofSplitString(exifDataString2[i] , "f/");
             exifDataInt2[i] = ofToDouble ( ApertureSplit[ApertureSplit.size()-1] );
             
             
             // for ISO speed
             exifDataInt3[i] = ofToDouble ( exifDataString3[i] ) ;
             
             //cout << exifDataString1[i] << exifDataString2[i] << exifDataString3[i] <<endl;
             cout << i <<" + "<< exifDataInt1[i]<<" + "<< exifDataInt2[i] <<" + " <<exifDataInt3[i] << endl;
             cout << i <<" + "<< exifDataString1[i]<<" + "<< exifDataString2[i] <<" + "<<exifDataString3[i] << endl;

             
            
             
             
         }
    //find min and max
    
//    //to find min
//    cout<< std::min_element( exifDataInt1[0], exifDataInt1[numberOfTestImages-1] );
//    //to find max
//    cout<< std::max_element( exifDataInt1[0], exifDataInt1[numberOfTestImages-1] );


    double minInArray1 =  minInArray( exifDataInt1 );
    cout<<minInArray1<<endl;
    
    double maxInArray1 =  maxInArray( exifDataInt1 );
    cout<<maxInArray1;
    
    // WELL THAT WORKS
    
    
    
    
    
    
    
    
    
    
    //creating FBO
    
    fbo.allocate(gridSize * imageThumbWidth, gridSize* imageThumbHeight, GL_RGB );
    fbo2.allocate(gridSize * imageThumbWidth, gridSize* imageThumbHeight, GL_RGB );
    
    fbo.begin();
    ofClear(255,255,255);
    //ofTranslate(xMargin, yMargin);
    for (int i = 0 ; i < numberOfTestImages; i++)
        {
        imageThumbs[i].draw( i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight );
        ofSetColor(ofColor::green);
            
        ofDrawBitmapString(exifDataString1[i] , i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight + 20 );
            
        ofDrawBitmapString(exifDataString2[i]  , i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight + 40 );
            
        ofDrawBitmapString(exifDataString3[i] , i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight + 60 );
            
        ofSetColor(ofColor::white );
        }
    fbo.end();
    
    //fbo2 = fbo;
    
    
    //new SOM stuff
    
    double minInstance[3] = { minInArray( exifDataInt1 ), minInArray( exifDataInt2 ),minInArray( exifDataInt3 ) };
    double maxInstance[3] = { maxInArray( exifDataInt1 ), maxInArray( exifDataInt1 ),maxInArray( exifDataInt1 ) };
    
    som.setFeaturesRange(3, minInstance, maxInstance);
    som.setInitialLearningRate(0.07);
    som.setNumIterations(4000);
    som.setMapSize(gridSize, gridSize);
    som.setup();

    
    
    
    

}

//--------------------------------------------------------------
void ofApp::update(){

    int randomNumber = ofRandom(100);
    double instance[3] = { exifDataInt1[randomNumber],exifDataInt2[randomNumber],exifDataInt3[randomNumber] };
    som.updateMap(instance);
    
    
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
    
    
    fbo2.begin();
    ofClear(255,255,255);
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            
            double * exifData = som.getMapAt(i,j);
            ofSetColor(ofColor::blue);
            
            ofDrawBitmapString( ofToString( exifData[0] ), i * imageThumbWidth , j * imageThumbHeight + 20 );
            
            ofDrawBitmapString(ofToString( exifData[1] )  , i * imageThumbWidth , j * imageThumbHeight + 40 );
            
            ofDrawBitmapString(ofToString( exifData[2] ) , i * imageThumbWidth , j * imageThumbHeight + 60 );
            
            ofSetColor(ofColor::white );

            //imageThumbs[i * gridSize + j ].draw( i * imageThumbWidth , j * imageThumbHeight );
            }

        }
    fbo2.end();
    
    
    
    
    
    //update FBO
    
    
    
    

    
    
    
    
    

    
    
    

}

//--------------------------------------------------------------
void ofApp::draw(){

    
    ofBackground(0);
    
    /*
    ofDrawBitmapString("Source image", 30, 20);
    
    sourceImg.draw(20, 30, 480, 480);
    somImg.draw(520, 30, 480, 480);
    
    // draw thumbnails
    ofDrawBitmapString("Click one of the thumbnails or drag another image file into the application to change the source", 120, 540);
    for (int i = 0; i < 5; i++)
        sourceImgThumbs[i].draw(25 + 195*i, 550, 185, 185);
     */
    
    ofDrawBitmapString("Self-organizing map: Iteration " + ofToString(som.getCurrentIteration()) + "/" + ofToString(som.getNumIterations()), 530, 20);
    
    
    fbo.draw(xMargin, yMargin);
    //fbo2.draw(xMargin + fullImageX- 200, yMargin);

    //create selected image
    ofPushMatrix();
    selectedFullImagePath = ofToString(folderName) + "/" + ofToString(imageBaseName) + ofToString(selectedImageNumber + 1 ) + ofToString(imageExtension);
    selectedFullImage.loadImage(selectedFullImagePath);
    selectedFullImage.draw(fullImageX , yMargin);
    ofPopMatrix();
    
    ofDrawBitmapString("selected image number: " + ofToString(selectedImageNumber), fullImageX, metaBeginY);
    ofDrawBitmapString("image Width  " + ofToString(selectedFullImage.width), fullImageX, metaBeginY + metaLineHeight);
    ofDrawBitmapString("selected image number: " + ofToString(selectedFullImage.height), fullImageX, metaBeginY + 2 * metaLineHeight );
    ofDrawBitmapString("framerate: " + ofToString( int(ofGetFrameRate()) ), fullImageX, metaBeginY + 3 * metaLineHeight);
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
        
//        if (selectedImageNumber < 0 || selectedImageNumber > 100)
//            selectedImageNumber = 5;
        
        
        
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






