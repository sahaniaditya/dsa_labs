#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <list>
#include <bits/stdc++.h>
using namespace std;
class Parcel {
public:
    int time_tick;
    std::string parcel_id;
    std::string origin;
    std::string destination;
    int priority;
    bool delivered;
    std::string current_location;

    Parcel() = default;
    Parcel(int time_tick, std::string parcel_id, std::string origin, std::string destination, int priority) {
        this->time_tick = time_tick;
        this->parcel_id = parcel_id;
        this->origin = origin;
        this->destination = destination;
        this->priority = priority;
        this->delivered = false;
        this->current_location = origin;
    }
};

class MaxHeap {
public:
    std::vector<Parcel> heap;
    int size = 0;
public:    
    MaxHeap(){
        heap.push_back(Parcel());
    }
    int parent(int i) {
        // fill in this function
        return i / 2;
    }

    int left(int i) {
        // fill in this function
        return 2*i;
    }

    int right(int i) {
        // fill in this function
        return 2*i + 1;
    }

    Parcel get_max() {
        // fill in this function
        return heap[1];
    }

    Parcel extract_max() {
        // function that returns the max element and removes it from the heap
        Parcel parcel = heap[1];
        return parcel;
    }

    void heapify(int n,int i){
        int largest = i;
        int l = left(i);
        int r = right(i);

        if(l <= n && heap[largest].priority < heap[l].priority)
         largest = l;
        if(r <= n && heap[largest].priority < heap[r].priority)
         largest = r;

        if(largest != i)
        {
            swap(heap[largest],heap[i]);
            heapify(n,largest);
        }  

    }
    void max_heapify(int i) {
        // function that maintains the max heap property
        int n = size;
        for(int i = n / 2;i>0;i--){
            heapify(n,i);
        }

    }

    void insert(Parcel item) {
        // function that inserts item into the heap
        size = size + 1;
        int index = size;
        heap[index] = item;
        while(index > 1){
            int parent_index = parent(index);
            if(heap[index].priority > heap[parent_index].priority){
                swap(heap[index],heap[parent_index]);
                index = parent_index;
            }
            else 
             return;
        }

    }

    bool is_empty() {
        return heap.empty();
    }
};

class FreightCar {
public:
    int max_parcel_capacity;
    std::vector<Parcel> parcels;
    std::string destination_city;
    std::string next_link;
    std::string current_location;
    bool sealed;

    FreightCar(int max_parcel_capacity) {
        this->max_parcel_capacity = max_parcel_capacity;
        // instantiate parcels vector as empty initially
        this->parcels = {};
        this->destination_city = "";
        this->next_link = "";
        this->current_location = "";
        this->sealed = false;
    }

    void load_parcel(Parcel parcel) {
        // load parcel
    }

    bool can_move() {
        // if length of parcels is equal to max_parcel_capacity return true else return false
    }

    void move(std::string destination) {
        // function that moves freight car to destination (link)
    }
};

class Vertex {
public:
    std::string name;
    std::vector<FreightCar> freight_cars;
    std::vector<Vertex*> neighbors;
    // trains_to_move is dict of destination and freight cars 
    std::map<std::string, std::vector<FreightCar>> trains_to_move;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap> parcel_destination_heaps;
    std::vector<FreightCar> sealed_freight_cars;
    std::vector<Parcel> all_parcels;
    Vertex() = default;
    Vertex(std::string name, int min_freight_cars_to_move, int max_parcel_capacity) {
        this->name = name;
        this->freight_cars = {};
        this->neighbors = {};
        this->trains_to_move = {};
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->max_parcel_capacity = max_parcel_capacity;
        this->parcel_destination_heaps = {};
        this->sealed_freight_cars = {};
        this->all_parcels = {};
    }
    string get_name(){
        return this -> name;
    }
    void add_neighbor(Vertex* neighbor) {
        // add neighbor to neighbors vector
        //cout << "have entered add_neighbour" << endl;
        cout << "neighbour name" << endl;
        cout << neighbor -> name << " " << (neighbor -> name).size() << endl;
        (this -> neighbors).push_back(neighbor);
        vector<Vertex*> n = this -> get_neighbors();
        cout << "Printing in add_neighbour : " << n[0] -> name << endl;
    }

    // add get neighbors function
    std::vector<Vertex*> get_neighbors() {
        cout << "Neighbours are :" << neighbors.size() << endl;
       cout << "Printing in get_neighbours : " <<  neighbors[0] -> name << endl;
        // for(auto it : neighbors){
        //     cout << it -> name << endl;
        // }
        return neighbors;
    }

    std::vector<Parcel> get_all_current_parcels() {
        // get all parcels from all destination heaps
    }

    void clean_unmoved_freight_cars() {
        // after time tick t, freight cars with parcels < min parcels should be deleted and parcels are to be added to heap
    }

    void loadParcel(Parcel parcel) {
        // load parcel into heap
    }

    void loadFreightCars() {
        // load parcels into freight cars (making sure that each freight car has parcels from only one destination, and # parcels == min_parcel_capacity)
    }

    void print_parcels_in_freight_cars() {
        // for (auto &[destination, heap] : this->parcel_destination_heaps) {
        //     for (auto& parcel : heap.heap) {
        //         std::cout << "Parcel ID: " << parcel.parcel_id << ", Parcel origin: " << parcel.origin << ", Parcel destination: " << parcel.destination << ", Parcel priority: " << parcel.priority << std::endl;
        //     }
        // }
    }
};





class Graph {

public:
    std::vector<Vertex> vertices;
    //std::list<Vertex> vertices;

    int findPlace(string place){
        // int n = vertices.size();
        // auto start = vertices.begin();
        int i = 0;
        for(auto &it : this -> vertices){
            if(it.name == place){
               return i;
            }
            i++;
        }
        return -1;
    }

    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity) {

        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly
        //cout << "in add_edge" << endl;
        int index1 = findPlace(source);
        int index2 = findPlace(destination);
        cout << index1 << " " << index2 << endl;
        if(index1 != -1 && index2 != -1){
            
            Vertex source_vertex;
            Vertex destination_vertex;
            //list<Vertex>::iterator it;
            // for(auto it = vertices.begin();it != vertices.end();it++){
            //    if((*it).name == source){
            //       source_vertex = *it;
            //    }
            //    if((*it).name == destination){
            //       destination_vertex = *it;
            //    }
            // }
            //cout << "i am here thank you" << endl;
            for(auto &it : this -> vertices){
                if(it.name == source)
                 source_vertex = it;
                if(it.name == destination)
                 destination_vertex = it; 
            }

            source_vertex.add_neighbor(&destination_vertex);
            destination_vertex.add_neighbor(&source_vertex);
            
            //vertices.push_back(source_vertex);
            //vertices.push_back(destination_vertex);
        }

        else if(index1 != -1 && index2 == -1){
            Vertex source_vertex;
            //list<Vertex>::iterator it;
            // for(auto it = vertices.begin();it != vertices.end();it++){
            //    if((*it).name == source){
            //       source_vertex = *it;
            //    }
            // }
            Vertex destination_vertex(destination,min_freight_cars_to_move,max_parcel_capacity);
            for(auto &it : this -> vertices){
                if(it.name == source){
                  
                  destination_vertex.add_neighbor(&it);
                  it.add_neighbor(&destination_vertex);
                  this -> vertices.push_back(destination_vertex);
                  break;
                }
                 //source_vertex = it;
            }

            
            

        }

        else if(index1 == -1 && index2 != -1){
            Vertex destination_vertex;
            //list<Vertex>::iterator it;
            // for(auto it = vertices.begin();it != vertices.end();it++){
            //    if((*it).name == destination){
            //       destination_vertex = *it;
            //    }
            // }
            Vertex source_vertex(source,min_freight_cars_to_move,max_parcel_capacity);
            for(auto &it : this -> vertices){
                if(it.name == destination){
                   source_vertex.add_neighbor(&it);
                   it.add_neighbor(&source_vertex);
                   
                   this -> vertices.push_back(source_vertex);
                   break;
                }
                 //destination_vertex = it;
            }
            
            
        }

        else{
            Vertex source_vertex(source,min_freight_cars_to_move,max_parcel_capacity);
            Vertex destination_vertex(destination,min_freight_cars_to_move,max_parcel_capacity);
            destination_vertex.add_neighbor(&source_vertex);
            source_vertex.add_neighbor(&destination_vertex);
            this -> vertices.push_back(source_vertex);
            this -> vertices.push_back(destination_vertex);
            cout << "hello man" << endl;
            vector<Vertex*> n = source_vertex.get_neighbors();
            cout << n[0] -> name << " "<< (n[0] -> name).size() << endl;
        }
        

    }

    void print_graph() {
        std::cout << "Printing graph, vertices: " << vertices.size() << std::endl;
        for (auto& vertex : this->vertices) {
            std::cout << "Vertex: " << vertex.name << std::endl;
            std::cout << "Neighbors: ";
            for (auto& neighbor : vertex.neighbors) {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::string> bfs(std::string source, std::string destination) {
        // function to return path from source to destination using bfs
        // cout << "entered bfs" << endl;
        // std::unordered_set<string> visited;
        // std::queue<std::vector<string>> q;
        // q.push({source});

        // while (!q.empty()) {
        //     cout << "entered1" << endl;
        //     std::vector<string> path = q.front();
        //     q.pop();
        //     string current = path.back();

        //     if (current == destination) {
        //         return path;
        //     }
            
            
        //     cout << "entered2" << endl;
            
        //     //cout << visited.end() << endl;
        //     cout << this -> vertices.size() << endl;
        //     //cout << (*((vertices[0].get_neighbors())[0])).name << endl;
        //     if (visited.find(current) == visited.end()) {
        //         visited.insert(current);
        //         vector<Vertex*> neighbours;
        //         for(auto list : this -> vertices){
        //             if(list.name == current){
        //                 cout << "Vertex Name : " << list.name << endl;
        //               neighbours = list.get_neighbors();

        //               break;
        //             }
        //         }
        //         cout << "before neighbour" << endl;
        //         //cout << (neighbours[0] -> name) << "City" << endl;
        //         cout << neighbours.size() << endl;
        //         cout << "entered3" << endl;
        //         for (auto adjacent : neighbours) {
        //             cout << "entered4" << endl;
        //             cout << adjacent << endl;
        //             cout << "you can do it" << endl;
        //             if (visited.find(adjacent->name) == visited.end()) {
        //                 cout << "entered here also" << endl;
        //                 std::vector<string> new_path = path;
        //                 new_path.push_back(adjacent -> name);
        //                 q.push(new_path);
        //             }
        //         }
        //     }




        // }

        // //std::cout << "No path found between " << start << " and " << end << "." << std::endl;
        // return {};
        cout << "good man" << endl;
        vector<Vertex*> neigbours = vertices[0].get_neighbors();
        for(auto& it : vertices[0].get_neighbors()){
            cout << "entered loop" << endl;
            //cout << (it -> name) << endl;
        }
        cout << neigbours.size() << endl;
        cout << "leaving here" << endl; 

        return {};
    }

    std::vector<std::vector<string>> dfs(std::string source, std::string destination) {
       // function to return path from source to destination using dfs
       }

    void groupFreightCars() {
        // for every vertex, group freight cars by links
    }

    void moveTrains() {
        // for every vertex, move freight cars to next link
    }



};

class PRC {
public:
    Graph graph;
    std::vector<FreightCar> freight_cars;
    std::map<std::string, Parcel> parcels;
    std::map<int, std::vector<Parcel>> parcels_with_time_tick;
    int max_parcel_capacity;
    int min_freight_cars_to_move;
    int time_tick;
    std::map<std::string, std::string> old_state;
    std::map<std::string, std::string> new_state;
    int max_time_tick;

    PRC(int max_parcel_capacity, int min_freight_cars_to_move) {
        this->max_parcel_capacity = max_parcel_capacity;
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->time_tick = 1;
        this->max_time_tick = 100;
        this->freight_cars = {};
        this->parcels = {};
        this->parcels_with_time_tick = {};
        this->old_state = {};
        this->new_state = {};

    }

    void create_graph(std::string graph_file_name) {
        
        // read graph.txt file and create graph
        std::ifstream inputFile(graph_file_name);

    
        if (!inputFile.is_open()) {
            std::cerr << "Error opening the file!" << std::endl;
            return; 
        }
    
        std::string line;
        while (std::getline(inputFile, line)) {
            istringstream iss(line);
            string word;
            vector<string> words;
            while(iss >> word){
              words.push_back(word);
            }

            this -> graph.add_edge(words[0], words[1], this -> min_freight_cars_to_move, this -> max_parcel_capacity);
            
        }
        cout << "i am here" << endl;
        vector<string> bfs = this -> graph.bfs("a","d");
        cout << "got bfs" << endl;
        cout << bfs.size() << endl;
        inputFile.close();

    }

    int returnIndexOfSpace(string str){
        for(int i = 0;i<str.size();i++){
            if(str[i] == ' ')
             return i;
        }
        return -1;
    }
    void process_parcels(std::string parcels_file_name){
        // read parcels.txt file and create parcels 
        //cout << "i am here" << endl;
        std::ifstream inputFile(parcels_file_name);

    
        if (!inputFile.is_open()) {
            std::cerr << "Error opening the file!" << std::endl;
            return; 
        }
    
        std::string line;
        vector<string> rows;
        while (std::getline(inputFile, line)) {
            rows.push_back(line);
        }
    
        int size_of_rows = rows.size();
        int j = 0;
        int k = 1;
        while(j < size_of_rows){
           for(int i = j;i<size_of_rows;i++){
             string str = rows[i];
             int index_space = returnIndexOfSpace(str);
             int tick_time = stoi(str.substr(0,index_space));
             if(tick_time != k){
                k++;
                j = i--;
                break;
             }
             else{


                istringstream iss(str);
                string word;
                vector<string> words;
                while(iss >> word){
                 words.push_back(word);
                }

                Parcel parcel(tick_time,words[1],words[2],words[3],stoi(words[4]));
                parcels_with_time_tick[tick_time].push_back(parcel);
                this -> parcels[words[1]] = parcel;
             }




           }

           j++;
        }
        inputFile.close();
        
    }

    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel> get_bookings(int time_tick, std::string vertex) {
          vector<Parcel> ans;
          for(auto it : this -> parcels_with_time_tick){
            if(it.first == time_tick){
                for(auto i : it.second){
                    if(i.origin == vertex){
                        ans.push_back(i);
                    }
                }
            }
          }

          return ans;
    }

    std::map<std::string, std::string> get_state() {
        std::map<std::string, std::string> state;
        // from this.parcels
        for (auto& parcel_pair : this->parcels) {
            Parcel& parcel = parcel_pair.second;
            state[parcel.parcel_id] = parcel.current_location;
        }
        return state;
    }

    // run simulation function, takes run_till_time_tick as argument
    // if run_till_time_tick is not provided then run simulation till max_time_tick

    void run_simulation(int run_till_time_tick = -1) {

        // function to run simulation
    }

    bool convergence_check(){
        // function to check convergence between old_state and new_state
    }

    bool all_parcels_delivered() {
        for (auto& parcel_pair : this->parcels) {
            Parcel& parcel = parcel_pair.second;
            if (!parcel.delivered) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> get_stranded_parcels() {
        // return parcel_ids of stranded parcels
    }

    std::vector<std::string> get_delivered_parcels() {
        // return parcel_ids of delivered parcels
    }

    // get status of all parcels at time tick t (status = id, current location, delivered/not delivered)
    std::vector<std::string> get_status_of_all_parcels(int t) {
        //  std::string status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered) + "\n" ;
        // return the status of all parcels at time tick t as a vector of strings (each string formatted as above)
    }

    // get status of parcel_id at time tick t (status = id, current location, delivered/not delivered)
    std::string get_status_of_parcel(std::string parcel_id, int t) {
        // status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered);
        // return status of one parcel at time tick t as a string (formatted as above)
    }

    // get parcels delivered up to time tick t
    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t) {
        // return list of parcel_ids of parcels delivered up to time tick t
    }

};


int main() {

    PRC prc = PRC(2, 2);
    prc.create_graph("graph.txt");
    prc.process_parcels("bookings.txt");
    cout << "i am good" << endl;
    //prc.run_simulation(3);

    return 0;
}
