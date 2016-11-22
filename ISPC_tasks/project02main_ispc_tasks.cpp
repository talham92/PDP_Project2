///Thinh Nguyen and Talha Mahmood
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string.h>
#include <chrono>
#include "sqrtFunction_ispc_tasks_ispc.h"
#include <cmath>
using namespace ispc;
using namespace std;
typedef std::chrono::high_resolution_clock Clock;
//---------------------------SIZE OF THE ARRAY---------------------------
int size=30000000;

//--------------------------Array Randomizing function---------------------
void randomizingArray(float* array1,float* array2)
{
	// Declare range for array elements.
	int min =0.0;
	int max =5.0;
	float div=(RAND_MAX/(max-min));
	
	// Assign random values within the range to the array.
	for (int i=0;i<=size-1;++i)
	{
		//array1[i]=(float)(rand() %(max + 1 - min)) + min; //array with INTEGERS.
		array1[i]=(float)(rand() /div)+min;	//array with REAL numbers.
		array2[i]=array1[i];	// Dublicate array1.
	}
}

//------------------------Array Display Function-----------------------------
void displayArray(float* array)
{
	for(int i=0;i<=size-1;++i)
	{
		std::cout<<" "<<array[i];
	}
		std::cout<<endl;
}		
//-----------------------Square Root Sequential function-------------------------------
void squareroot(float array[],int end)
{
	for (int i=0;i<=end;++i)
		{
			float k=1.0;		// k hold value of the next approximation.
			float N=array[i];

			while(fabs(k-sqrt(N))>0.0001)
			{
				k=(k+(N/k))/2;		
			}
			array[i]=k;
		}
}

////////////////////////////////-----Main-----/////////////////////////////////
int main()
{
	// Create array of the 15 million random numbers ranging 0 to 5.
		 float *array1=new float[size];	//make an empty array of 30 million.
		 float *array2=new float[size];	// "new" operator is to 
									// reserve memory for our array.
		randomizingArray(array1,array2);	//randomizing the empty array.
		
		long seq, tasktime;
	// Finding the Square Root of array SEQUENTIALY----------------------------.
		//displayArray(array1);			// display array.
		//t1s = clock();
		std::cout<<"//---------------------SEQUENTIAL-------------------//"<<endl;
		auto t3 = Clock::now();
		squareroot(array1,size-1);		//calling the squareroot fucntion.
		auto t4 = Clock::now();
		//t1s = clock() - t1s;
		//displayArray(array1);			// display array.
		std::cout<<"Time taken:"<<std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count()<<" seconds"<<endl;
		seq = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
	// Finding the Square Root of array with ISPC-----------------------------.
		//displayArray(array2);			// display array.
		std::cout<<"//--------------------ISPC COMPILER-----------------//"<<endl;
		for(int i = 2;i<=64; i*=2)
		{
			//t2 = clock();
			auto t1 = Clock::now();
			squareroot_ispc_tasks(array2,size,i);		//calling the squareroot fucntion.
			auto t2 = Clock::now();
			   		
    			std::cout<<"Time taken:"<<std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()<<" seconds"<<endl;
    			tasktime = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
std::cout<<"        "<<seq/tasktime<<"x SPEED UP FROM ISPC"<<endl;
    			
			
		}
		//displayArray(array2);			// display array.
		
		delete[]array1;		//"delete" operator is to restore the arrays memory.
		delete[]array2;
		
		
return 0;
}	


