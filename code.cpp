#include<iostream>
using namespace std;

class Queue{
    public:
     int size;
     int front;
     int rear;
     int *arr;

     Queue(int size){
        this -> size = size;
        front = 0;
        rear = 0;
        arr = new int[size];
     }

     void push(int element){
        if(front == rear)
         front = rear = 0;

        if(rear == size){
            cout << "Queue is full" << endl;
            return;
        } 

        else{
            arr[rear] = element;
            rear++;
        }
     }

     void pop(){
        if(rear == 0){
            cout << "Queue is empty" << endl;
            return;
        }
        else{
            arr[front] = 0;
            front++;
        }
        
     }

     void print(){
        for(int i = front;i<rear;i++){
            cout << arr[i] << " ";
        }
        cout << endl;
     }
};

int main(){
    Queue ob(5);
    ob.push(1);
    ob.push(2);
    ob.print();
    ob.pop();
    ob.print();
}
