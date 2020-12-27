#include "stdlib.h"
#include "LinkedList.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>
#include "time.h"

using namespace cv;
using namespace std;

 typedef struct Data {

    size_t i;
    size_t j;

 }Data;

 void initializeData(Data*, size_t, size_t);

 /*------------------------------ Thinning Algorithm Function Prototype---------------------*/
 void thiningAlgo(Mat*); 
 /*------------------------------ Thinning Algorithm Function Prototype---------------------*/

 
int main(int argc, char* argv[])
{
    
    char PCBImage[20];
    cout<<"Please enter the file name of PCB layout image:";
    cin>>PCBImage;
    
    Mat src = imread(PCBImage, IMREAD_GRAYSCALE); // Read the PCB Layout Image
    

    if (src.empty())
    {
        cout << "Fail to Read Image!" << endl;
        return -1;
    }

    /* Transfer the source image to the binary image */
    threshold(src, src, 200, 255, THRESH_BINARY);


    

    // iterate over all pixels of the image
    
    for (int r = 0; r < src.rows; r++) {
        // obtain a pointer to the beginning of row r
        uchar* ptr = src.ptr<uchar>(r);

        for (int c = 0; c < src.cols; c++) {
            // invert the values of the pixel
            ptr[c] = 255- ptr[c];
            
        }
    }
    
 
   
    /* Image Thinning */
    
    Mat dst;
    src.copyTo(dst);
    
    clock_t start_time, end_time;
    float total_time = 0;

    start_time = clock(); /* mircosecond */
    
    thiningAlgo(&dst);

    end_time = clock();


    /* reverse the black and white */


    // iterate over all pixels of the image

    for (int r = 0; r < dst.rows; r++) {
        // obtain a pointer to the beginning of row r
        uchar* ptr = dst.ptr<uchar>(r);

        for (int c = 0; c < dst.cols; c++) {
            // invert the values of the pixel
            ptr[c] = 255 - ptr[c];

        }
    }

    /*Execution Time*/
    total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
    cout<<"Execution Time:"<<total_time<<"(sec)"<<endl;

    /* Show the Image */
    namedWindow("src1", CV_WINDOW_AUTOSIZE);
    namedWindow("dst1", CV_WINDOW_AUTOSIZE);


    imshow("src1", src);
    imshow("dst1", dst);

    imwrite("dst.jpg", dst);
    waitKey(0);
}



void initializeData(Data* d, size_t i, size_t j){
  d->i = i;
  d->j = j;
}


/* ----------------------------------------thinning algorithm--------------------------------------*/
void thiningAlgo(Mat* dst_ptr) {

    size_t numofRows = (size_t)dst_ptr->rows;
    size_t numofCols = (size_t)dst_ptr->cols;

    int counter = 0;
    int A = 0;
    int B = 0;
    int first_c = 0;
    int first_d = 0;
    int second_c = 0;
    int second_d = 0;


    node* deleteList = NULL; // the linked list to store the points to be deleted
    
    
    do {

        counter = 0;

        /*  Traverse IT to search M */
        /*  First Subiteration */
        for (size_t r = 1; r < numofRows - 2; r++) {
            // obtain a pointer to the beginning of row r


            uchar* ptr_north = (dst_ptr)->ptr<uchar>(r - 1);
            uchar* ptr = (dst_ptr)->ptr<uchar>(r);
            uchar* ptr_south = (dst_ptr)->ptr<uchar>(r + 1);

            for (size_t c = 1; c < numofCols - 2; c++) {

                if (ptr[c] == 255) {



                    /*  Compute B(P1) */
                    B = (ptr_north[c - 1] + ptr_north[c] + ptr_north[c + 1] + ptr[c - 1] + ptr[c + 1] + ptr_south[c - 1] + ptr_south[c] + ptr_south[c + 1]) / 255; // B(P1)

                    if(B >= 2 && B <= 6){
                    
                    	/*  Compute Condition(c) and (d)  */

                    	first_c = ptr_north[c] * ptr[c + 1] * ptr_south[c];   // P2*P4*P6
                    	first_d = ptr[c + 1] * ptr_south[c] * ptr[c - 1];      // P4*P6*P8
                    	
                    	if(first_c == 0 && first_d == 0){
                    	
                    	  /*  Compute A(P1) */
                   	  int* check = new int[9]();

                    	  *check = ptr_north[c] / 255;
                     	  *(check + 1) = ptr_north[c + 1] / 255;
                         *(check + 2) = ptr[c + 1] / 255;
                         *(check + 3) = ptr_south[c + 1] / 255;
                         *(check + 4) = ptr_south[c] / 255;
                         *(check + 5) = ptr_south[c - 1] / 255;
                         *(check + 6) = ptr[c - 1] / 255;
                         *(check + 7) = ptr_north[c - 1] / 255;
                         *(check + 8) = ptr_north[c] / 255;

                   	  for (int i = 0; i < 8; i++) {
                        	if ((check[i + 1] - check[i]) == 1)
                           	    A++;
                    	  }


                         delete[] check;
                    	
                    	  if(A == 1){
                    	    
                    	    /*  delete the point */
                    	    Data* d = (Data*)malloc(sizeof(Data)); // Note: must to be released to avoid memory leakage problem
                           initializeData(d,r,c);
                           deleteList = push_front(deleteList, (void*)d);
                           counter = counter + 1;
                    	  
                    	  }
                    	
                    	}
                    	
                    }
                    
                              
                    A = 0;
                    B = 0;
                    first_c = 0;
                    first_d = 0;
                }
            }




        }







        size_t size = counter; // Obtain size of the deleteList
      
        
      
        for (size_t k = 0; k < size; k++) {

            Data* d = (Data*)front(deleteList);

            
            
            deleteList = pop_front(deleteList);

            (dst_ptr)->ptr<uchar>(d->i)[d->j] = 0;
            
            free(d); // avoid the memory leakeage problem

        }

      


        counter = 0;
        
       
        /*  Traverse IT to search M */
        /*  Second Subiteration */


        for (size_t r = 1; r < numofRows - 2; r++) {
            // We obtain a pointer to the beginning of row r


            uchar* ptr_north = (dst_ptr)->ptr<uchar>(r - 1);
            uchar* ptr = (dst_ptr)->ptr<uchar>(r);
            uchar* ptr_south = (dst_ptr)->ptr<uchar>(r + 1);

            for (size_t c = 1; c < numofCols - 2; c++) {

                if (ptr[c] == 255) {

                    /*  Compute B(P1) */
                    B = (ptr_north[c - 1] + ptr_north[c] + ptr_north[c + 1] + ptr[c - 1] + ptr[c + 1] + ptr_south[c - 1] + ptr_south[c] + ptr_south[c + 1]) / 255; // B(P1)

                    if(B >= 2 && B <= 6){
                    
                    	/*  Compute Condition(c) and (d)  */
                       second_c = ptr_north[c] * ptr[c + 1] * ptr[c - 1];   // P2*P4*P8
                    	second_d = ptr_north[c] * ptr_south[c] * ptr[c - 1];   // P2*P6*P8
                    	
                    	if(second_c == 0 && second_d == 0){
                    	
                    	  /*  Compute A(P1) */
                   	  int* check = new int[9]();

                    	  *check = ptr_north[c] / 255;
                     	  *(check + 1) = ptr_north[c + 1] / 255;
                         *(check + 2) = ptr[c + 1] / 255;
                         *(check + 3) = ptr_south[c + 1] / 255;
                         *(check + 4) = ptr_south[c] / 255;
                         *(check + 5) = ptr_south[c - 1] / 255;
                         *(check + 6) = ptr[c - 1] / 255;
                         *(check + 7) = ptr_north[c - 1] / 255;
                         *(check + 8) = ptr_north[c] / 255;

                   	  for (int i = 0; i < 8; i++) {
                        	if ((check[i + 1] - check[i]) == 1)
                           	    A++;
                    	  }


                         delete[] check;
                    	
                    	  if(A == 1){
                    	    
                    	    /*  delete the point */
                    	    Data* d = (Data*)malloc(sizeof(Data)); // Note: must to be released to avoid memory leakage problem
                           initializeData(d,r,c);
                           deleteList = push_front(deleteList, (void*)d);
                           counter = counter + 1;
                    	  
                    	  }
                    	
                    	}
                    	
                    }

                    A = 0;
                    B = 0;
                    second_c = 0;
                    second_d = 0;

                }
            }




        }

        size = counter; // Obtain size of the deleteList
        
        for (size_t k = 0; k < size; k++) {

            Data* d = (Data*)front(deleteList);
            
            deleteList = pop_front(deleteList);

            dst_ptr->ptr<uchar>(d->i)[d->j] = 0;
            
            free(d); // avoid the memory leakeage problem

        }

 
    }while (counter != 0);
       

        
    
}

/*----------------------------------------------thinning algorithm-----------------------------------*/





