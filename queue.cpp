#include <iostream>
#include <vector>

template <typename T>
class Queue {
 private:
  std::vector<T> queue;

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
    
  std::cout << "Elements in queue: ";
  for (int i = 0; i < q.Size(); i++) {
    std::cout << q.Front() << ":";
    q.Push(q.Front());
    q.Pop();
  }
  std::cout << std::endl;
   std::cout << "Size: " << q.Size() << std::endl; 
  
  std::cout << "Queue is not empty" << std::endl;

  while (!q.Empty()) {
    std::cout << "Elements in queue: ";
    std::cout << q.Front() << ":";
    std::cout << "\n" << std::endl;
    q.Pop();
    std::cout << "Size: " << q.Size() << std::endl;
  }

  if (q.Empty()) {
    std::cout << "Queue is empty" << std::endl;
  } else {
    std::cout << "Size: " << q.Size() << std::endl;  
    std::cout << "Front: " << q.Front() << std::endl; 
    std::cout << "Back: " << q.Back() << std::endl;  
  }

  q.Pop();
  if (q.Empty()) {
    std::cout << "Queue is empty" << std::endl;
  } else {
    std::cout << "Size: " << q.Size() << std::endl;  
    std::cout << "Front: " << q.Front() << std::endl; 
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
