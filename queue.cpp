#include <iostream>
#include <vector>
using namespace std; 

template <typename T>
struct Queue {
 private:
  vector<T> queue; // declare the queue

 public:
  void Push(const T& val) { queue.push_back(val); } // add an elemnt to the back of queue
  void Pop() { queue.erase(queue.begin()); } // remove elementn at the front 
  T Front() { return queue.front(); } // return the elemnt at front of the queue
  T Back() { return queue.back(); } // return elements at the back of the queue
  int Size() { return queue.size(); } // number of elements in the queue
  bool Empty() { return queue.empty(); } // return true if queue is empty and otherwise
};

int main() {
  Queue<int> q;
  q.Push(9);
  q.Push(7);
  q.Push(5);
  q.Push(2);
    
  
  cout << "Elements in queue: ";
  for (int i = 0; i < q.Size(); i++) {
    
    cout << q.Front() << ":";
    q.Push(q.Front());
    q.Pop();
  }
  
  cout << endl;
  cout << "Size: " << q.Size() << endl; 
  
  
  cout << "Queue is not empty" << endl;

  while (!q.Empty()) {
    cout << "Elements in queue: ";
    cout << q.Front() << ":";
    cout << "\n" << endl;
    q.Pop();
    cout << "Size: " << q.Size() << endl;
  }

  if (q.Empty()) {
    std::cout << "Queue is empty" << std::endl;
  } else {
   
    cout << "Size: " << q.Size() << endl;  
    cout << "Front: " << q.Front() << endl; 
    cout << "Back: " << q.Back() << endl;  
  }

  q.Pop();
  if (q.Empty()) {
    cout << "Queue is empty" << endl;
  } else {
    cout << "Size: " << q.Size() << endl;  
    cout << "Front: " << q.Front() << endl; 
  }

  return 0;
}
/*Add item to queue
pop an item from the queue
return the front of the queue
return the back of the queue
check if full setting <bool var> to 
true otherwise false
check if empty setting <bool var> 
to true otherwise false */
