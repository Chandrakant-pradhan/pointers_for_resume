#include <iostream>
#ifndef MARKET_H
#define MARKET_H
#include<vector>
struct broker1{
    std::string name;
    int sells;
    int buys;
    int transfer;
};

struct order
{
    int time_s = 0;
    int time_e = 0;
    std::string broker;
    std::vector<std::pair<std::string, int>> lab_quant;
    int price = 0;
    int quantity = 0;
	std::string mode = 0;
    int broker_index;

	bool operator<( order& other)  {
        // Compare price first

        if (price < other.price){
            return (mode == "BUY");
        } else if (price > other.price) {
            return (mode == "SELL");
        }

        // If price is equal, compare time
        if (time_s > other.time_s) {
            return true;
        } else if (time_s < other.time_s) {
            return false;
        }

        // If both price and time are equal, compare names
        return broker > other.broker;
    }
	bool operator>( order& other)  {
       return ! (*this < other);
    }
};


class pq {
public:
    std::vector<order> heap;
    // Helper function to heapify up (used in push)
    void heapifyUp() {
        int index = heap.size() - 1;
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] > heap[parentIndex]) {
                std::swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

   // used to decrement quantity from the top element's quantity property 
   void dec(int quantity){
        heap[0].quantity -= quantity;
   }
    // Helper function to heapify down (used in pop)
    void heapifyDown(int index = 0) {
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;

            if (leftChild < heap.size() && heap[leftChild] > heap[smallest]) {
                smallest = leftChild;
            }

            if (rightChild < heap.size() && heap[rightChild] > heap[smallest]) {
                smallest = rightChild;
            }

            if (smallest != index) {
                std::swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }
    // Push an element onto the priority queue
    void push(order value) {
        heap.push_back(value);
        heapifyUp();
    }

    // Pop the highest-priority element from the priority queue
    void pop() {
        // Move the last element to the root and heapify down
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown();
    }

	void removeExp(int time){
		int i = 0;
		while(i < heap.size()){
			if(heap[i].time_e < time){
				std::swap(heap[i], heap[heap.size() - 1]);
				heap.pop_back();
			}
			i++;
		}
		for (int i = heap.size() / 2 - 1; i >= 0; --i) {
            heapifyDown(i);
        }
	}
    
    void updater(int index){
        if(index >= heap.size()){
            return;
        }
        removeExp(index);
        updater(2*index);
        updater(2*index + 1 );

    }

    // Get the highest-priority element without removing it
    order top()  {
        return heap[0];
    
    }

    // Check if the priority queue is empty
    bool empty()  {
        return heap.empty();
    }

    // Get the size of the priority queue
    size_t size()  {
        return heap.size();
    }
};

class market
{
public:
	market(int argc, char** argv);
	void start();
    std::vector<std::pair<pq,pq>> arr;
    void remove(int time){
        for (int i =0; i<arr.size();i++){
            arr[i].first.removeExp(time);
            arr[i].second.removeExp(time);
        }
        return;
    }
    std::vector<broker1> broker_list;
    int tot_transfer = 0;
    int comp_trades  = 0;
    int tot_shares = 0;
	 
};
#endif