//////////////////////////////////////////////////////////////////////////////////////
//// Name: Ahmad Alkurdy
///  Date: 3/20/2017
///  Class: Algorithm
///  Purpose: a program to generate a set of numbers chosen by the user, and 
//            apply different type of sorting and output the results to individual files.
//            It will pompt the user to a list of options to choose from and the user would 
//            select his option
//    code modified: 1- more comments added to explain each sort
//                   2- merge and quick sort are running and compiling
//                   3- error checking added for the files and the input
//                   4- option to run all the sorts added
//                   5- console interaction modified
/////////////////////////////////////////////////////////////////////////////////////////

//declaring labriries 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include<stdlib.h>
#include<stdio.h>


using namespace std;
//declaring the functions used in the program
void userPrompt();
int generatedInFile(int num);
void InsertionSort();
void mergingSort();
void mergesort(int Array[], int p, int r);
void merge(int *a, int low, int high, int mid);
void selectionSort();
void heapSort();
void heapify(int arr[], int n, int i);
void QuickSort();
void quickSortFunction(int Array[],int l, int h);
int partition (int arr[], int l, int h);



//declaring the main function

int main()
{
	
	int num = 0;
	int numGenerating = 0;
//while loop to prompt the user 	
	while (num != 8)
	{
	//call the function to show the list
	userPrompt();
	cin >> num;
	//a switch statment to call the function chosen by the user
	switch(num)
	{
		//it prompt the user to ask for the number of the generated numbers
	case 1:
		cout << "How many numbers?"<< endl;
		cin >> numGenerating;
		//call the genrating function
		generatedInFile(numGenerating);
		break;
	case 2:
		//call the function for insertion sort
		InsertionSort();
		break;
	case 3:
		//call the function fo quick sort
		QuickSort();
		break;
	case 4:
		//call the funtion for the selection sort
		selectionSort();
		break;
	case 5:
		//call the funtion for the heap sort
		heapSort();
		break;
	case 6:
		//call the function for the merging sort
		mergingSort();
		break;
	case 7:
		InsertionSort();
		QuickSort();
		selectionSort();
		heapSort();
		mergingSort();
		break;

	default:
		//to handle any other numbers inserted
		cout <<"There is no procedure with this number!" << endl;
		cout <<"Enter a number from the list." << endl;
		break;
	}
	
	}
	return 0;
}

//a function to list the options

void userPrompt()
{
	cout << endl;
	cout << endl;
	cout << "Enter a number and I will generate an equal amount of integers in the range" <<
		" of 0 to 9999, and store them in a file called 'Data.txt'" << endl;
	cout << "You will have options to choose what algorithm you want to use to sort them " << 
		", and see the time it took to sort the numbers and be able to compare the different algorithms."
		<< endl;
	cout << "Enter the number of the option you want to be assissted" << endl;
	cout << "1- entring the number to generate the random integres." <<
	 " and write the data generated to the file." << endl;
	cout << "2- Insertion sort." << endl;
	cout << "3-Quick Sort." << endl;
	cout << "4- selection sort." << endl;
	cout << "5- Heap Sort." << endl;
	cout << "6- Merge sort." << endl;
	cout << "7- Run all the sorts" << endl;
	cout << "8- to finish." << endl;
	cout << " --------------------------------------" << endl;

}

int generatedInFile(int num)
{
	//a function to generate the numbers and write them out to Data.txt file
	ofstream output;
	//declaring the output file
	output.open("Data.txt");
	output << num << endl;
	for(int i = 0; i < num; i++)
	{
		//generating the numbers randomly
		output << rand() %1000 << endl;
		
	}
	return 0;
}

//Insertion sort
void InsertionSort()
{
	//declare the variables
	ifstream input;
	int arraySize = 0;
	int key = 0;
	int j = 0;
	clock_t begin;
	//declare the output file of this specific sorting
	ofstream sortedOutput;
	input.open("Data.txt");

	//if statment to catch an error of the file
	if (!input.is_open())
	{
		cout << "Unable to open file" << endl; 

	}

	else 
	{
		input >> arraySize;
		int *Array = new int [arraySize]; // declare a dyamic array to load the numbers from the data.txt
		for(int i = 0; i < arraySize; i++)
		{
			input >> Array[i];
		}
		 
	begin = clock(); //start the timing


   for (int i = 1; i < arraySize; i++) //outside loop
   {
       key = Array[i];
       j = i-1;
 
     //inside loop in the best case wont be used
       while (j >= 0 && Array[j] > key)
       {
           Array[j+1] = Array[j];
           j = j-1;
       }
       Array[j+1] = key;
   }
    clock_t end = clock(); //end the timing 
	float elapsed_secs = float (end - begin) / CLOCKS_PER_SEC; //divide the diffeence by clocks per sec
	//open the output file and load the results to it
	sortedOutput.open("InsertionSort.txt");
	for(int i = 0; i < arraySize; i++)
	{
	  sortedOutput << Array[i] << endl;

	}

	sortedOutput << "The time: " << elapsed_secs;
	delete [] Array;
	}
	
	//closing the files
	input.close();
	sortedOutput.close();
	


}



void mergingSort()
{
	//declare variables 
	ifstream input;
	int arraySize = 0;
	int key = 0;
	int j = 0;
	clock_t begin;
	//declare the output file
	ofstream sortedOutput;
	input.open("Data.txt");
	//error handling if statment
	if (!input.is_open())
	{
		cout << "Unable to open file" << endl; 

	}

	else 
	{
		input >> arraySize;
		int *Array = new int [arraySize];
		for(int i = 0; i < arraySize; i++)
		{
			input >> Array[i];
		}
		 
	begin = clock();
	//call the mergesort function
	mergesort(Array, 0, arraySize-1);
	
   
   clock_t end = clock();
	float elapsed_secs = float(end - begin) / CLOCKS_PER_SEC;
	//output the rsults to the specific file
	sortedOutput.open("MergingSort.txt");
	
	for(int i = 0; i < arraySize; i++)
	{
	  sortedOutput << Array[i] << endl;

	}

	sortedOutput << "The time: " << elapsed_secs << endl;
	delete [] Array;
	}
	
	
	input.close();
	sortedOutput.close();
	



}

void mergesort(int Array[], int p, int r)
{
    int q = 0;
	//if statment to handle (Base case: 1 value)
	if (p >= r)
	{
		return;
	}
	else
    {
        q =(r+p)/2; //compute the middle
		//recursive functions to divide and conqure
        mergesort(Array,p,q); //Sort low to mid part of array
        mergesort(Array,q+1,r);//Sort mid+1 to high part of array
		//calling the merge function
        merge(Array,p,r,q);
    }
    return;
}
//same algorithm provided in slides but different coding approach
void merge(int *a, int low, int high, int mid)
{
    int i, j, k;
	//int length = high - low;
	//int *c = new int [length];
	// i tried to allocate the array dynamicly but i always had errors so I hard coded the number
	//while it is not as effecient but it does the job and merging sort will not be effecien for 
	// sorting a lot of numbers i picked 200 as max for the subarray
	int c[200];
    i = low;
    k = low;
    j = mid + 1;
	//while loop to ensure the numbers compared are not higher than the mid and the high
    while (i <= mid && j <= high)
    {
		//if statment will compare the numbers from the a and the smaller will go first to the subarray
		// and increment to compare the next element
        if (a[i] < a[j])
        {
            c[k] = a[i];
            k++;
            i++;
        }
        else
        {
            c[k] = a[j];
            k++;
            j++;
        }
    }
	//while loops to add the numbers left to the subarray
    while (i <= mid)
    {
        c[k] = a[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        c[k] = a[j];
        k++;
        j++;
    }
	//for loop to assign the sorted number to the main array
    for (i = low; i < k; i++)
    {
        a[i] = c[i];
    }
}

void selectionSort()
{
	//declaring variables
	ifstream input;
	int arraySize = 0;
	int min = 0;
	clock_t begin;
	ofstream sortedOutput;
	input.open("Data.txt");
	//error handling if statment
	if (!input.is_open())
	{
		cout << "Unable to open file" << endl; 

	}

	else 
	{
		input >> arraySize;
		int *Array = new int [arraySize];
		for(int i = 0; i < arraySize; i++)
		{
			input >> Array[i];
		}
		 
	begin = clock();

	for (int i = 0; i < arraySize -1 ; ++i)
	{
    //Find minimum element in the unsorted array
    //Assume it's the first element
    min = i;
 
    //Loop through the array to find it
    for (int j = i + 1; j < arraySize; ++j)
    {
      if (Array[j] < Array[min])
      {
        //Found new minimum position
        min = j;
      }
    }
 
    //Swap the values
    swap (Array[i], Array[min]);
  }	

  
   clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	sortedOutput.open("SelectionSort.txt");
	//for loop to output the numbers to selectionSort file
	for(int i = 0; i < arraySize; i++)
	{
	  sortedOutput << Array[i] << endl;

	}
	//output the time
	sortedOutput << "The time: " << elapsed_secs << endl;
	delete [] Array;
	}
	
	
	input.close();
	sortedOutput.close();
	

}
void heapSort()
{
	//declaring the variables
	
	ifstream input;
	int arraySize = 0;
	int key = 0;
	int j = 0;
	clock_t begin;
	ofstream sortedOutput;
	input.open("Data.txt"); //openning the file to get the numbers from
	// error handling if statments
	if (!input.is_open())
	{
		cout << "Unable to open file" << endl; 

	}

	else 
	{
		input >> arraySize;
		int *Array = new int [arraySize]; //declaring a dynamic array
		//for loop to input the numbers from the input file into the dynamic array
		for(int i = 0; i < arraySize; i++)
		{
			input >> Array[i];
		}
		begin = clock();
		for (int i = arraySize / 2 - 1; i >= 0; i--)
        heapify(Array, arraySize, i);
 
    // One by one extract an element from heap
    for (int i=arraySize-1; i>=0; i--)
    {
        // Move current root to end
        swap(Array[0], Array[i]);
 
        // call heapify on the reduced heap
        heapify(Array, i, 0);
    }
	  clock_t end = clock();
	  //calculate the time
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	//openning the output file fir this sort
	sortedOutput.open("HeapSort.txt");
	//for loop to out put the numbers in the array to the output file
	for(int i = 0; i < arraySize; i++)
	{
	  sortedOutput << Array[i] << endl;

	}

	sortedOutput << "The time: " << elapsed_secs << endl;
	//delete the array 
	delete [] Array;
	}
	
	
	input.close();
	sortedOutput.close();
	

}
void heapify(int Array[], int arraySize, int i)
{
    int largest = i;  
    int l = 2*i + 1;  // left 
    int r = 2*i + 2;  // right
 
    // If left child is larger than root
    if (l < arraySize && Array[l] > Array[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < arraySize && Array[r] > Array[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i)
    {
		//swap the elements in the array
        swap(Array[i], Array[largest]);
        heapify(Array, arraySize, largest);
    }
}
void QuickSort()
{
	//declar variables
	ifstream input;
	int arraySize = 0;
	int key = 0;
	int j = 0;
	clock_t begin;
	ofstream sortedOutput;
	//open the input file
	input.open("Data.txt");
	//error handling if statment
	if (!input.is_open())
	{
		cout << "Unable to open file" << endl; 

	}

	else 
	{
		input >> arraySize;
		int *Array = new int [arraySize];
		for(int i = 0; i < arraySize; i++)
		{
			input >> Array[i];
		}
		 
	begin = clock();
	//calling the function quicksort 
	quickSortFunction(Array, 0, arraySize-1);
	
   
   clock_t end = clock();
   //calculating the time
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	//openning the quicksort file
	sortedOutput.open("QuickgSort.txt");
	//output the sorted array into quicksort file
	for(int i = 0; i < arraySize; i++)
	{
	  sortedOutput << Array[i] << endl;

	}

	sortedOutput << "The time: " << elapsed_secs << endl;
	delete [] Array;
	}
	
	
	input.close();
	sortedOutput.close();
	
}
void quickSortFunction(int Array[], int p, int r)
{
	//If there is more than 1 element
    //Call Partition; assign return value to q
   //Pass left partition to Quicksort
   //Pass right partition to Quicksort
    if (p < r)
    {        
        int q = partition(Array, p, r); 
        quickSortFunction(Array, p, q - 1);  
        quickSortFunction(Array, q + 1, r);
    }
}
int partition (int Array[], int p, int r)
{
    int x = Array[r]; //Set last value in array to pivot

    int i = (p - 1);//Set partition to be before first value
 /*if the value in A[j] is less than the pivot
move the partition wall (very important – i starts out negative)
swap the values in Array[i] and Array[j]
*/
    for (int j = p; j <= r- 1; j++)
    {
        if (Array[j] <= x)
        {
            i++;
             swap(Array[i], Array[j]);
        }
    }
     swap(Array[i + 1], Array[r]);
    return (i + 1);
}
