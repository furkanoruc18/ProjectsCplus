#include "HelpStudents.h"
#include <queue>
#include <climits>
#include <map>
#include <list>
#include <utility>

using namespace std;


void swap(long long int *x, long long int *y) { 
    long long int temp = *x; 
    *x = *y; 
    *y = temp; 
} 

void swapint(int *x, int *y) { 
    int temp = *x; 
    *x = *y; 
    *y = temp; 
} 
  
// A class for Min Heap 
class MinHeap 
{ 
public: 
    long long int* harr; // pointer to array of elements in heap 
    int* tag; // Mapping of vertices to their position in the heap
    int* pos; // Mapping of vertices to their position in the heap
    int capacity; // maximum possible size of min heap 
    int heap_size; // Current number of elements in min heap 
    int student_type;

    // Constructor 
    MinHeap(int cap) { 
        heap_size = 0; 
        capacity = cap; 
        harr = new long long int[cap]; 
        pos = new int[cap]; 
        tag = new int[cap]; 
    } 
  
    // to heapify a subtree with the root at given index 
    void MinHeapify(int i) { 
        int l = left(i); 
        int r = right(i); 
        int smallest = i; 

        if (l < heap_size && harr[l] < harr[i]) 
            smallest = l; 
        if (r < heap_size && harr[r] < harr[smallest]) 
            smallest = r; 
        if (smallest != i) { 
            swap(&harr[i], &harr[smallest]); 
            swapint(&tag[i], &tag[smallest]); 
            pos[tag[i]] = i;
            pos[tag[smallest]] = smallest;
            MinHeapify(smallest); 
        } 
    } 
  
    int parent(int i) { return (i-1)/2; } 
  
    // to get index of left child of node at index i 
    int left(int i) { return (2*i + 1); } 
  
    // to get index of right child of node at index i 
    int right(int i) { return (2*i + 2); } 
  
    // to extract the root which is the minimum element 
    pair<int, long long int> extractMin() { 
        if (heap_size <= 0) 
            return make_pair(0, LLONG_MAX); 
    
        // Store the minimum value, and remove it from heap 
        int val = harr[0]; 
        int node = tag[0];
        
        if (heap_size == 1) { 
            heap_size--; 
            return make_pair(node, val);
        } 

        harr[0] = harr[heap_size-1]; 
        tag[0] = tag[heap_size-1]; 
        pos[tag[0]] = 0;
        heap_size--; 
        MinHeapify(0); 
    
        return make_pair(node, val);
    }
  
    // Decreases key value of key at index i to new_val 
    void decreaseKey(int i, long long int new_val) { 
        harr[i] = new_val; 

        while (i != 0 && harr[parent(i)] > harr[i]) { 
            swap(&harr[i], &harr[parent(i)]); 
            swapint(&tag[i], &tag[parent(i)]); 
            pos[tag[i]] = i;
            pos[tag[parent(i)]] = parent(i);
            i = parent(i); 
        } 
    }  
}; 

HelpStudents::HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > ways) {
    this->node_count = N;
    this->edge_count = M;
    this->summit = K;
    this->paths = ways;

    for (auto path : paths) {
        int from = path.first.first;
        int to = path.first.second;
        int cost = path.second;

        if (neighbor.find(from) == neighbor.end()) {
            neighbor[from] = list<pair<int, int>>();
        }

        neighbor[from].push_back(make_pair(to, cost));
    }
}

long long int HelpStudents::firstStudent() {
    // Min-heap for extracting minimum efficiently
    MinHeap heap(node_count);
    heap.heap_size = node_count;

    for (int i = 0; i < node_count; i++) {
        heap.harr[i] = LLONG_MAX;
        heap.pos[i] = i;
        heap.tag[i] = i;
    }

    // Zero the distance to tha camp
    heap.decreaseKey(0, 0);

     // Traverse the graph
    while (heap.heap_size > 0) {
        pair<int, long long int> top = heap.extractMin();
        int node = top.first;
        long long int dist = top.second;

        if (node + 1 == summit) {
            return dist;
        }

        list<pair<int, int>>& nlist = neighbor[node + 1];

        for (auto it = nlist.begin(); it != nlist.end(); it++) {
            long long int alt = dist + it->second;

            if (alt < heap.harr[heap.pos[it->first - 1]]) {
                heap.decreaseKey(heap.pos[it->first - 1], alt);
            }
        }
    }

    return LLONG_MAX;
}

long long int HelpStudents::secondStudent() {
    // Min-heap for extracting minimum efficiently
    MinHeap heap(node_count);
    heap.heap_size = node_count;

    for (int i = 0; i < node_count; i++) {
        heap.harr[i] = LLONG_MAX;
        heap.pos[i] = i;
        heap.tag[i] = i;
    }

    // Zero the distance to tha camp
    heap.decreaseKey(0, 0);

     // Traverse the graph
    while (heap.heap_size > 0) {
        pair<int, long long int> top = heap.extractMin();
        int node = top.first;
        long long int dist = top.second;

        if (node + 1 == summit) {
            return dist;
        }

        list<pair<int, int>>& nlist = neighbor[node + 1];

        for (auto it = nlist.begin(); it != nlist.end(); it++) {
            long long int alt = (dist > it->second) ? dist : it->second;

            if (alt < heap.harr[heap.pos[it->first - 1]]) {
                cout << it->first << " is in " << alt;
                heap.decreaseKey(heap.pos[it->first - 1], alt);
            }
        }
    }

    return LLONG_MAX;
}

long long int HelpStudents::thirdStudent() {
    list<pair<int, int>> q;

    q.push_back(make_pair(1, 0));
    pair<int, int> d;

    do {
        d = q.front();
        q.pop_front();
        list<pair<int, int>>& nlist = neighbor[d.first];
        
        for (auto it = nlist.begin(); it != nlist.end(); it++) {
            q.push_back(make_pair(it->first, d.second + 1));
        }
    } while (d.first != summit);

    return d.second;
}

long long int HelpStudents::fourthStudent() {
    map<int, vector<int>> passed;
    int c = 1;
    int total = 0;

    do {
        list<pair<int, int>>& nlist = neighbor[c];
        int min = INT_MAX;

        for (auto it = nlist.begin(); it != nlist.end(); it++) {
            if (passed.find(c) == passed.end()) {
                passed[c] = vector<int>();
            }

            bool contains = false;
            for (auto v = passed[c].begin() ; v != passed[c].end(); ++v) {
                if (*v == it->first) {
                    contains = true;
                    break;
                }
            }

            if (!contains) {
                if (it->second < min) {
                    min = it->second;
                    c = it->first;
                }
            }
        }

        if (min == INT_MAX) return -1; 

        total += min;

    } while(c != summit);

    return total;
}

long long int HelpStudents::fifthStudent() {
    // IMPLEMENT ME!
}
