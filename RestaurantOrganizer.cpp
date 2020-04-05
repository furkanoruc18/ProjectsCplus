#include "RestaurantOrganizer.h"

using namespace std;
void heapify(int arr[], int n, int index) //working as heapdown just using size (n)
{

    int largest = index; // root is the largest element
    int l = 2*index + 1; // left = 2*root + 1
    int r = 2*index + 2; // right = 2*root + 2

    // If left child is larger than root

    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != index) // if not equal swap it
    {
        swap(arr[index], arr[largest]);
        heapify(arr, n, largest);//recursievly
    }

}
int max_capacity_table(int* tableCapacity, int* tableCurrent,  int numberOfTables){ // find max capacite of tables
    int max_capacity_of_tables=0;
    int j=0;
    for(int i=0;i<numberOfTables;i++){  // all tables
        if(tableCapacity[i]>max_capacity_of_tables) { // if high we assing max
            max_capacity_of_tables = tableCapacity[i];
            j=i; // j index of this capasite update all program time
        }
    }
    tableCurrent[0]=j;  // j assign table current for using this index

    return max_capacity_of_tables; // return max

}

RestaurantOrganizer::RestaurantOrganizer(const vector<int>& tableCapacityInput){
    numberOfTables = tableCapacityInput.size();
    for(int i=0;i<numberOfTables;i++){
        tableCapacity[i] = tableCapacityInput[i];
        heap[i] = i;
        heapUp(i);
    }
}

void RestaurantOrganizer::addNewGroup(int groupSize, ofstream& outFile){

    int table_capacity = max_capacity_table( tableCapacity, tableCurrent,  numberOfTables); // find max capacite of tables

    if (table_capacity >= groupSize) {  //if table capacite higher than group size  we out that table number if not we out -1
        tableCapacity[tableCurrent[0]] = tableCapacity[tableCurrent[0]] - groupSize; // update tablecapacity
        outFile<< tableCurrent[0]<<"\n";
    }
    else
        outFile<< -1<<"\n";

    // IMPLEMENT ME!
}

void RestaurantOrganizer::heapUp(int index){

    while(index > 0)
    {
        int parentIndex = (index-1)/2;
        if(tableCapacity[parentIndex] < tableCapacity[index])
        {
            // swap(heap, parentIndex,index);
            index = parentIndex;
        }
        else
            break;
    }
    // IMPLEMENT ME!
}

void RestaurantOrganizer::heapDown(int index){
    // IMPLEMENT ME!
    int largest = index; // root is the largest element
    int l = 2*index + 1; // left = 2*root + 1
    int r = 2*index + 2; // right = 2*root + 2

    // If left child is larger than root
    if (l < numberOfTables &&tableCapacity[l] >tableCapacity[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < numberOfTables && tableCapacity[r] > tableCapacity[largest])
        largest = r;

    if (largest != index)
    {
        swap(tableCapacity[index], tableCapacity[largest]);
        heapDown(largest);
    }
}

void RestaurantOrganizer::printSorted(ofstream& outFile){
    // IMPLEMENT ME!

    int n = numberOfTables;
    for (int i = n / 2 - 1; i >= 0; i--) // only root index
        heapDown(i);

    for (int i=n-1; i>=0; i--)
    {
        swap(tableCapacity[0], tableCapacity[i]);

        heapify(tableCapacity, i, 0); //heap'fy for reduce size of array working like heapdown
    }
    for(int i= numberOfTables-1;i> -1;i--) //for sorting we need all of index
        outFile<<tableCapacity[i]<<" "; //out of file
}
