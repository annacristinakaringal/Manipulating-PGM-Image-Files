/*
 MANIPULATING PGM IMAGE FILES
 by Anna Cristina Karingal
 CSCI 135 Assignment 2
 
 Reads an image "image_in.pgm" and:
 
 1. Creates and saves a copy of the image
 2. Inverts the image and saves the new image to a new file
 3. Sets all pixels to a specified brightness and saves the new image to a new file
 
 Creates an image with: 
 
 1. A filled box inside
 2. An outlined box inside
 3. A blurred copy of the image with an outlined box.
 
 Last edited: April 21, 2014
 */


#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class image {
    
private:
    int img[100][100];

public:
    
    // RETURNS COPY OF IMAGE
    image copy(){
        image imgcopy;
        
        for (int i=0; i<100; i++){
            for (int j=0; j<100; j++){
                imgcopy.img [i][j] = img [i][j]; // Writes contents of original image into imgcopy
            }
        }
        
        return imgcopy;
    }
    
    
    // SETS ALL PIXELS IN IMAGE TO BRIGHTNESS b
    void fill (int b){
        int i, j;
        for (i=0; i <100; i++){
            for (j=0; j<100; j++){
                img [i][j]=b;
            }
        }
    }
    
    
    // INVERTS IMAGE
    void invert(){
        int b, i, j;
        for (i=0; i <100; i++){
            for (j=0; j<100; j++){
                b = img [i][j];
                img [i][j] = 100-b;
            }
        }
    }
    
    
    // DRAWS BOX WITH OUTLINE OF BRIGHTNESS b
    void box_outline (int b, int r, int c, int width, int height){
        int i, j;
        
        for (i=0; i<r; i++){ //Fills pixels until row r with white
            for (j=0; j<100; j++){
                img [i][j] = 100;
            }
        }

        for (i=r; i<(r+1); i++) { //Draws top outline
        
            for (j=0; j<c; j++){
                img [i][j] = 100;
            }
            
            for (j=c; j<(c+width+1); j++){
                img [i][j] = b;
            }
            for (j=(c+width+1); j<100; j++){
                img [i][j] = 100;
            }
        }
        
        for (i=(r+1); i < (r+height); i++){ //Draws side outlines
            
            for (j=0; j<c; j++){
                img [i][j] = 100;
            }
            
            for (j=c; j<(c+1); j++){
                img[i][j] = b;
            }
            
            for (j=(c+1); j<(c+width); j++){
                img [i][j] = 100;
            }
            
            for (j=(c+width); j<(c+width+1); j++){
                img [i][j] = b;
            }
            
            
            for (j=(c+width+1); j<100; j++) {
                img [i][j] = 100;            }
        }
        
        for (i=(r+height); i<(r+height+1) ;i++){ // Draws bottom outline
            
            for (j=0; j<c; j++){
                img [i][j] = 100;
            }
            
            for (j=c; j<(c+width+1); j++){
                img [i][j] = b;
            }
            for (j=(c+width+1); j<100; j++){
                img [i][j] = 100;
            }
            
        }
        
        for (i=(r+height+1); i<100; i++){ // Fills pixels from bottom outline to end of image with white
            for (j=0; j<100; j++){
                img [i][j] = 100;
            }
        }
        
        
    }
    
    // DRAWS FILLED BOX WITH BRIGHTNESS B
    void box_filled (int b, int r, int c, int width, int height){
        int i, j;
        
        for (i=0; i<r; i++){ //Fills in rows 0 to r with white
            for (j=0; j<100; j++){
                img [i][j] = 100;
            }
        }
        
        for (int i=r; i < (r+height); i++){ // Fills in box with brightness b
            for (j=0; j<c; j++){
                img [i][j] = 100;
            }
            for (j=c; j < (c+width); j++){
                img [i][j] = b;
            }
            for (j = (c+width); j<100; j++){
                img [i][j] = 100;
            }
        }
        
        for (i=(r+height); i<100; i++){ // fills in rest of rows with white
            for (j=0; j<100; j++){
                img [i][j] = 100;
            }
        }
        
    }
    
    
    // BLURS IMAGE
    void blur (){
        int i, j;
        image c = copy(); //Creates copy of image
        
        for (i=0; i<1; i++){ // Averages (blurs) first row
            for (j=0; j<1; j++){
                img [i][j] = (c.img[i][j] + c.img[i][j+1] +
                              c.img[i+1][j] + c.img[i+1][j+1]) / 4;
            }
            
            for (j=1; j<99; j++){
                img [i][j] = (c.img[i][j-1] + c.img[i][j] + c.img[i][j+1] +
                              c.img[i+1][j-1] + c.img[i+1][j] + c.img[i+1][j+1]) / 6;
            }
            
            for(j=99; j<100; j++){
                img [i][j] = (c.img[i][j-1] + c.img[i][j] +
                              c.img[i+1][j-1] + c.img[i+1][j]) / 4;
            }
        }
        
        for (i=1; i<99; i++){ // Averages (blurs) image except first and last rows
            for (j=0; j<1; j++){
                img [i][j] = (c.img[i-1][j] + c.img[i-1][j+1] +
                              c.img[i][j] + c.img[i][j+1] +
                              c.img[i+1][j] + c.img[i+1][j+1]) / 6;
            }
            
            for (j=1; j<99; j++){
                img [i][j] = (c.img[i-1][j-1] + c.img[i-1][j] + c.img[i-1][j+1] +
                              c.img[i][j-1] + c.img[i][j] + c.img[i][j+1] +
                              c.img[i+1][j-1] + c.img[i+1][j] + c.img[i+1][j+1]) / 9;
            }
            
            for(j=99; j<100; j++){
                img [i][j] = (c.img[i-1][j-1] + c.img[i-1][j] +
                              c.img[i][j-1] + c.img[i][j] +
                              c.img[i+1][j-1] + c.img[i+1][j]) / 6;
            }
            
        }
        
        for (i=99; i<100; i++){ //Blurs last row
            for (j=0; j<1; j++){
                img [i][j] = (c.img[i-1][j] + c.img[i-1][j+1] +
                              c.img[i][j] + c.img[i][j+1]) / 4;
            }
            
            for (j=1; j<99; j++){
                img [i][j] = (c.img[i-1][j-1] + c.img[i-1][j] + c.img[i-1][j+1] +
                              c.img[i][j-1] + c.img[i][j] + c.img[i][j+1]) / 6;
            }
            
            for(j=99; j<100; j++){
                img [i][j] = (c.img[i-1][j-1] + c.img[i-1][j] +
                              c.img[i][j-1] + c.img[i][j]) / 4;
            }
            
        }
        
    }
    
    
    // READS IMAGE FROM FILE
    void read(){
        ifstream ins;
        ins.open("image_in.pgm");
        
        string type;
        ins >> type; // Gets file type
        
        // Checks to see if file is PGM format
        if (type == "P2") {
            int height, width, max;
            ins >> height >> width >> max; // Gets other metadata from file
            
            int val, i, j;
            for (i=0; i<width; i++){
                for (j=0; j<height; j++){
                    ins >> val;
                    img [i][j] = val; // Reads image from file into array
                }
            }
        }
        
        else {
            cout << "ERROR: Unreadable file." << endl;
        }
        
        
        ins.close();
    }
    
    
    // WRITES IMAGE TO FILE
    void write(string name){
        ofstream ons;
        ons.open (name.c_str());
        
        string type = "P2";
        int height = 100;
        int width = 100;
        int max = 100;
        
        // Writes metadata to file
        ons << type << endl << height << endl << width << endl << max << endl;
        
        for (int i=0; i<width; i++){
            for (int j=0; j<height; j++){
                ons << img [i][j] << endl; // Writes image to file
            }
        }
        
        ons.close();
    }
    
};


//DEMONSTRATING MEMBER FUNCTIONS

int main () {
    
    image white;
    
    white.read(); // Reads contents of image_in.pgm (an all white image) and saves to array
    
    //Copies image_in.pgm and saves as new file
    image whitecopy = white.copy();
    whitecopy.write("image_copy.pgm");
    
    //Sets all pixels to brightness 10 and saves as new file
    white.fill(50);
    white.write("img_0.pgm");
    
    //Inverts original image and saves as new file
    white.read();
    white.invert();
    white.write("img_invert.pgm");
    
    //Creates & saves new image file with filled black 50x50 box in the middle of the image
    image box1;
    box1.box_filled(0, 25, 25, 50, 50);
    box1.write("img_boxfilled.pgm");
    
    //Creates & saves new image file with white 50x50 box outlined in black in the middle of the image
    image box2;
    box2.box_outline(0, 25, 25,50,50);
    box2.write("boxoutline.pgm");
    
    //Blurs outlined box image and saves as new file
    box2.blur();
    box2.write("boxoutline_blur.pgm");
    
    
    
    
    
    return 0;
}

