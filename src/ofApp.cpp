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

    // switching to new scheme of things
    
    for (int i = 0; i < numberOfTestImages; i++)
         {
             
             ImageDataClass tempClass;
             tempClass.initialize(i);
             
             GridImages.push_back(tempClass);
             
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
    
    fbo.allocate(gridSize * imageThumbWidth, gridSize* imageThumbHeight, GL_RGB );
    //fbo2.allocate(gridSize * imageThumbWidth, gridSize* imageThumbHeight, GL_RGB );
    
    fbo.begin();
    ofClear(255,255,255);
    //ofTranslate(xMargin, yMargin);
    for (int i = 0 ; i < numberOfTestImages; i++)
        {
        //imageThumbs[i].draw( i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight );
        GridImages[i].thumbImage.draw(i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight);
        
        
        if( GridImages[selectedImageNumber].isImageSelected )
          {
              ofSetColor( ofColor::blue );
              
              ofRect(i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight, imageThumbWidth, imageThumbHeight);
       
          }
           
            
        }
    fbo.end();
    
    //fbo2 = fbo;
    
    
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

//--------------------------------------------------------------
void ofApp::update(){

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
    
    
    //update FBO
    //ofTranslate(xMargin, yMargin);
    
    
 

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
    //fbo2.draw(xMargin + fullImageX- 200, yMargin);
    drawFullImage(selectedImageNumber);
    
    
    
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
    
    if ( x > xMargin && y > yMargin &&  x <  ( xMargin + gridSize * imageThumbWidth ) &&  y < ( yMargin + gridSize * imageThumbHeight ) )
        {
            mouseInsideGrid = true;
            
            int xLevel = ( x - xMargin ) / imageThumbWidth;
            int yLevel = ( y - yMargin ) / imageThumbHeight;
            
            
            selectedImageNumber = yLevel  + xLevel * gridSize;
            GridImages[selectedImageNumber].isImageSelected = true;
            
        }
    
    
    fbo.begin();
    for (int i = 0 ; i < numberOfTestImages; i++)
    {
        //imageThumbs[i].draw( i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight );
        GridImages[i].thumbImage.draw(i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight);
        
        
        if( GridImages[selectedImageNumber].isImageSelected )
        {
            ofSetColor( ofColor::green  ,200);
            ofNoFill();
            ofRect( i/gridSize * imageThumbWidth , i % gridSize * imageThumbHeight, imageThumbWidth, imageThumbHeight);
            ofSetColor( ofColor::white );

        }
        
        
    }
    fbo.end();

    
    
    
    

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
    selectedFullImagePath = ofToString(folderName) + "/" + ofToString(imageBaseName) + ofToString(selectedImageNumber + 1 ) + ofToString(imageExtension);
    selectedFullImage.loadImage(selectedFullImagePath);
    selectedFullImage.draw(fullImageX , yMargin);
    ofPopMatrix();
    
    
    ofDrawBitmapString("selected image number: " + ofToString(selectedImageNumber), fullImageX, metaBeginY);
    ofDrawBitmapString("image Width  " + ofToString(selectedFullImage.width), fullImageX, metaBeginY + metaLineHeight);
    ofDrawBitmapString("selected image number: " + ofToString(selectedFullImage.height), fullImageX, metaBeginY + 2 * metaLineHeight );
    ofDrawBitmapString("framerate: " + ofToString( int(ofGetFrameRate()) ), fullImageX, metaBeginY + 3 * metaLineHeight);
    ofDrawBitmapString("ISO: " + ofToString( GridImages[selectedImageNumber].dISOSpeed ) + "    Exposure: " + ofToString( GridImages[selectedImageNumber].dShutterSpeed ) + "    Aperture: " + ofToString( GridImages[selectedImageNumber].dAperture ) , fullImageX, metaBeginY + 4 * metaLineHeight);

}


