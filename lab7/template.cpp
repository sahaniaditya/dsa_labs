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
#include <list>

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
    std::vector<Parcel*> heap;

    int parent(int i) {
        // fill in this function
    }

    int left(int i) {
        // fill in this function
    }

    int right(int i) {
        // fill in this function
    }

    Parcel* get_max() {
        // fill in this function
    }

    Parcel* extract_max() {
        // function that returns the max element and removes it from the heap
    }

    void max_heapify(int i) {
        // function that maintains the max heap property
    }

    void insert(Parcel item) {
        // function that inserts item into the heap
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

    void add_neighbor(Vertex* neighbor) {
        // add neighbor to neighbors vector
    }

    // add get neighbors function
    std::vector<Vertex*> get_neighbors() {
        return this->neighbors;
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
        for (auto& [destination, heap] : this->parcel_destination_heaps) {
            for (auto& parcel : heap.heap) {
                std::cout << "Parcel ID: " << parcel.parcel_id << ", Parcel origin: " << parcel.origin << ", Parcel destination: " << parcel.destination << ", Parcel priority: " << parcel.priority << std::endl;
            }
        }
    }
};

class Graph {

public:
    std::list<Vertex> vertices;
    std::vector<std::pair<Vertex*, Vertex*>> edges;

    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity) {

        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly

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
        }

    std::vector<std::vector<std::string>> dfs(std::string source, std::string destination) {
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

    }

    void process_parcels(std::string parcels_file_name){
        // read parcels.txt file and create parcels 
    }

    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel> get_bookings(int time_tick, std::string vertex) {
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
    prc.create_graph();
    prc.process_parcels();
    prc.run_simulation(3);

    return 0;
}
