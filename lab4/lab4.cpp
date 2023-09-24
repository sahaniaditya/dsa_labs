#include<bits/stdc++.h>
using namespace std;

class Vehicle;
class BinaryTreeNode;
BinaryTreeNode* findMin(BinaryTreeNode*);
bool findVehicle(string vechicle);
//--------------------------------------------- Trip ---------------------------------------------------------------

class Trip {
public:
    Trip(Vehicle* vehicle, std::string pick_up_location, std::string drop_location, int departure_time){
        setVehicle(vehicle);
        setPickUpLocation(pick_up_location);
        setDropLocation(drop_location);
        setDepartureTime(departure_time);
        setBookedSeats(0);
        //cout << "here4" << endl;
    }
    

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    std::string getPickUpLocation() const {
        return pick_up_location;
    }

    std::string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(std::string location) {
        pick_up_location = location;
    }

    void setDropLocation(std::string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

private:
    Vehicle* vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

// ---------------------------------  BinaryTreeNode -----------------------------
class BinaryTreeNode {
private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
public:
    
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }
    
};


//----------------------------------------------- TransportService ---------------------------------------------------

class TransportService {
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    BinaryTreeNode* addToBST(BinaryTreeNode* root, BinaryTreeNode* node){
      //cout << "entered" << endl;  
      if (root == nullptr) {
        // If the tree is empty, create a new node and return it as the root.
        //cout << "empty" << endl;
        return node;
    }

    if (node -> getDepartureTime() < root -> getDepartureTime()) {
        
        root -> setLeftPtr(addToBST(root -> getLeftPtr(),node));
    } else if (node -> getDepartureTime() > root -> getDepartureTime()) {
       
        root -> setRightPtr(addToBST(root -> getRightPtr(),node));
    }

    // Return the modified root.
    return root;
    }


    BinaryTreeNode* deleteBST(BinaryTreeNode* root, int key) {
    if (root == nullptr) {
        return root;
    }
    
    if (key < root -> getDepartureTime()) {
        root -> setLeftPtr(deleteBST(root -> getLeftPtr(), key));
    } else if (key > root -> getDepartureTime()) {
        root -> setRightPtr(deleteBST(root -> getRightPtr(), key));
    } else {
        // Node with only one child or no child
        if (root -> getLeftPtr() == nullptr) {
            BinaryTreeNode* temp = root -> getRightPtr();
            delete root;
            return temp;
        } else if (root -> getRightPtr() == nullptr) {
            BinaryTreeNode* temp = root -> getLeftPtr();
            delete root;
            return temp;
        }
        
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        BinaryTreeNode* temp = findMin(root -> getRightPtr());
        
        // Copy the inorder successor's content to this node
        root -> setDepartureTime(temp -> getDepartureTime());
        
        // Delete the inorder successor
        root -> setRightPtr(deleteBST(root -> getRightPtr(), temp -> getDepartureTime()));
    }
    
    return root;
}
    void addTrip(int key, Trip* trip){
        //cout << "here6" << endl;
        BinaryTreeNode* node = new BinaryTreeNode(key,trip,nullptr);
        //cout << node -> getDepartureTime() << endl;
        //cout << "here7" << endl;
        BinaryTreeNode* head = this -> getBSTHead();
        //cout << (head == nullptr) << endl;
        //cout << "here8" << endl;
        BinaryTreeNode* temp = addToBST(head,node); 
        //cout << "here9" << endl;
        setBSTHead(temp);
        //cout << "here5" << endl;
    }

    void deleteTrip(int key, Trip* trip){
       BinaryTreeNode* head = this -> getBSTHead();
       BinaryTreeNode* temp = deleteBST(head,key);
       setBSTHead(temp);
    }

private:
    std::string name;
    BinaryTreeNode* BSThead;
};


//------------------------------------------- Vehicle Class ---------------------------------------------------------

class Vehicle {
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    vector<Trip*> getTrips(){
        return trips;
    }
    void deleteTrip(int key){
       trips.erase(trips.begin() + key);
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip*> trips;
};

//----------------------------------------------------- Location ---------------------------------------------

class Location {
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    TransportService* getServicePtr(std::string droplocation) const {
      for(int i  = 0;i < serviceptrs.size();i++){
        if(serviceptrs[i] -> getName() == droplocation)
         return serviceptrs[i];
       }
       return nullptr;
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }

    TransportService* setServicePtr(std::string droplocation) {
        TransportService* service = new TransportService("");
        service -> setName(droplocation);
        service -> setBSTHead(nullptr);
        serviceptrs.push_back(service);
        return service;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }
    void deleteTrip(int key){
        trips.erase(trips.begin() + key);
    }
    vector<TransportService*> returnServices(){
        return serviceptrs;
    }

private:
    std::string name;
    std::vector<TransportService*> serviceptrs;
    std::vector<Trip*> trips;
};

//--------------------------------------------------------- BinaryTree ----------------------------------------------------
int height(BinaryTreeNode* node){
  if(node == nullptr)
   return 0;
  return max(1 + height(node -> getLeftPtr()), 1 + height(node -> getRightPtr()));
}
int numberOfNodes(BinaryTreeNode* node){
    if(node == nullptr)
     return 0;
    return 1 + numberOfNodes(node -> getLeftPtr()) + numberOfNodes(node -> getRightPtr());
}

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const {
        // Implement this function to return the height of the tree
        if(this -> root == nullptr)
         return 0;
        return height(this -> root); 
         
    }

    int getNumberOfNodes() const {
        // Implement this function to return the number of nodes in the tree
        if(this -> root == nullptr)
         return 0;
        return numberOfNodes(this -> root); // Placeholder
    }
};

BinaryTreeNode* minKey(BinaryTreeNode* root){
     if(root -> getLeftPtr() == nullptr)
      return root;
    return minKey(root -> getLeftPtr());
}
BinaryTreeNode* maxKey(BinaryTreeNode* root){
    if(root -> getRightPtr() == nullptr)
     return root;
    return maxKey(root -> getRightPtr()); 
}
BinaryTreeNode* searchNode(BinaryTreeNode* root,int key){
    if(root == nullptr){
        return nullptr;
    }
    if(key < root -> getDepartureTime())
       return searchNode(root -> getLeftPtr(),key);
    else if(key > root -> getDepartureTime()) 
       return searchNode(root -> getRightPtr(),key);
    else
       return root;
}

BinaryTreeNode* findMin(BinaryTreeNode* root) {
    while (root->getLeftPtr() != nullptr) {
        root = root->getLeftPtr();
    }
    return root;
}

// Function to find the successor of a node in a BST
BinaryTreeNode* findSuccessor(BinaryTreeNode* root, int target) {
    BinaryTreeNode* successor = nullptr;

    while (root != nullptr) {
        if (root -> getDepartureTime() == target) {
            
            if (root -> getRightPtr() != nullptr) {
                successor = findMin(root -> getRightPtr());
            }
            break;
        } else if (root -> getDepartureTime() < target) {
            
            root = root -> getRightPtr();
        } else {
            
            successor = root;
            root = root -> getLeftPtr();
        }
    }

    return successor;
}

BinaryTreeNode* findSuccessorWithNode(BinaryTreeNode* root, BinaryTreeNode* node) {
    BinaryTreeNode* successor = nullptr;

    while (root != nullptr) {
        if (root->getDepartureTime() == node -> getDepartureTime()) {
            
            if (root->getRightPtr() != nullptr) {
                successor = findMin(root->getRightPtr());
            }
            break;
        } else if (root->getDepartureTime() < node -> getDepartureTime()) {
            
            root = root->getRightPtr();
        } else {
            
            successor = root;
            root = root->getLeftPtr();
        }
    }

    return successor;
}

BinaryTreeNode* findMax(BinaryTreeNode* root) {
    while (root->getRightPtr() != nullptr) {
        root = root->getRightPtr();
    }
    return root;
}

// Function to find the predecessor of a node in a BST
BinaryTreeNode* findPredecessor(BinaryTreeNode* root, int target) {
    BinaryTreeNode* predecessor = nullptr;
    
    while (root != nullptr) {
        if (root->getDepartureTime() == target) {
            
            if (root->getLeftPtr() != nullptr) {
                predecessor = findMax(root->getLeftPtr());
            }
            break;
        } else if (root->getDepartureTime() > target) {
            
            root = root->getLeftPtr();
        } else {
            
            predecessor = root;
            root = root->getRightPtr();
        }
    }
    
    return predecessor;
}

BinaryTreeNode* findPredecessorWithNode(BinaryTreeNode* root, BinaryTreeNode* node){
     BinaryTreeNode* predecessor = nullptr;
    
    while (root != nullptr) {
        if (root->getDepartureTime() == node -> getDepartureTime()) {
            
            if (root->getLeftPtr() != nullptr) {
                predecessor = findMax(root->getLeftPtr());
            }
            break;
        } else if (root->getDepartureTime() > node -> getDepartureTime()) {
            
            root = root->getLeftPtr();
        } else {
            predecessor = root;
            root = root->getRightPtr();
        }
    }
    
    return predecessor;
}

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

    BinaryTreeNode* getElementWithMinimumKey() const {
        // Implement this function to return the element with the minimum key
        BinaryTreeNode* node = minKey(this -> root);
        return node; // Placeholder
    }

    BinaryTreeNode* getElementWithMaximumKey() const {
        // Implement this function to return the element with the maximum key
        BinaryTreeNode* node = maxKey(this -> root);
        return node; // Placeholder
    }

    BinaryTreeNode* searchNodeWithKey(int key) const {
        // Implement this function to search for a node with the given key or the next larger key
        BinaryTreeNode* node = searchNode(this -> root,key);
        return node; // Placeholder
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the successor node of the given node
        BinaryTreeNode* ansnode = findSuccessorWithNode(this -> root,node);
        return ansnode; // Placeholder
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        // Implement this function to return the successor node by key
        BinaryTreeNode* ansnode = findSuccessor(this -> root,key);
        return ansnode; // Placeholder
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
        // Implement this function to return the predecessor node of the given node
        BinaryTreeNode *ansnode = findPredecessorWithNode(this -> root , node);
        return nullptr;
        // Placeholder
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
        // Implement this function to return the predecessor node by key
         BinaryTreeNode* ansnode = findPredecessor(this -> root,key);
         return ansnode; // Placeholder
    }
};

class TravelDesk {
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        // Implement this function to add a trip
           //cout << "here3" << endl;
           Vehicle* vehicle = returnVehicle(vehicle_number);
           if(vehicle == nullptr){
            //cout << "i am apple";
            vehicle = new Vehicle(vehicle_number,seating_capacity);
           }
           Trip *trip = new Trip(vehicle,pick_up_location,drop_location,departure_time);
           vehicle -> addTrip(trip);
           vehicles.push_back(vehicle);
           if(getLocation(pick_up_location) != nullptr){
               //cout << "here10" << endl;
               Location* temp = getLocation(pick_up_location);
               if(temp -> getServicePtr(drop_location) != nullptr){
                    //cout << "i am here" << endl;
                    TransportService *service = temp -> getServicePtr(drop_location);
                    service -> addTrip(departure_time,trip);
               }
               else{
                  //cout << "i am here2" << endl;
                  TransportService *service = temp -> setServicePtr(drop_location);
                  service -> addTrip(departure_time,trip);
               }
               
           }
           else{
           //cout << "here11" << endl; 
           Location *location = new Location("");
           location -> setName(pick_up_location);
           location -> addTrip(trip);
           locations.push_back(location);
           TransportService *service = location -> setServicePtr(drop_location);
           service -> addTrip(departure_time,trip);
           }
        // }
    }

    std::vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
        // Implement this function to retrieve trips within a specified time range
        Location* location = getLocation(pick_up_location);
        vector<TransportService*> services = location -> returnServices();
        //cout << services.size();
        vector<Trip*> finalans;
        int len = services.size();
        for(int i = 0;i<len;i++){
            vector<Trip*> ans = showTripsbydestination(pick_up_location,services[i] -> getName(),after_time,before_time);
            for(int j = 0;j<ans.size();j++){
                finalans.push_back(ans[j]);
            }
        }
        return finalans; // Placeholder
    }
     void inorder(BinaryTreeNode* root,vector<Trip*> &ans,int after_time,int before_time){
           if(root == nullptr)
            return;
            inorder(root -> getLeftPtr(),ans,after_time,before_time);
           if(root -> getDepartureTime() >= after_time && root -> getDepartureTime() < before_time)
            {
                ans.push_back(root -> getTripNodePtr());
            } 
            inorder(root -> getRightPtr(),ans,after_time,before_time);
     }

     std::vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time) {	
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin	
        if(before_time < after_time)
         swap(after_time,before_time);
        vector<Trip*> ans;
        vector<Trip*> anotherans;
        Location *location = getLocation(pick_up_location);
        TransportService* service = location -> getServicePtr(destination);
        BinaryTreeNode* node = service -> getBSTHead();
        inorder(node,anotherans,after_time,before_time);
        //BinaryTreeNode* ob = new BinaryTreeNode()
        int value = after_time - 1;
        while(findSuccessor(node,value) != nullptr){
            //cout << "entered" << endl;
            BinaryTreeNode* ob = findSuccessor(node, value);
            if(ob -> getDepartureTime() < before_time){
              ans.push_back(ob -> getTripNodePtr());
            //   node = ob;
              value = ob -> getDepartureTime();
            }
            else{
                break;
            }
        }
        if(anotherans.size() == ans.size())
         return ans;
        else 
         return anotherans;  // Placeholder	
    }	

    Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        // Implement this function to book a trip
        //vector<Trip*> trips = showTripsbydestination(pick_up_location,drop_location,)
        Vehicle* vehicle = returnVehicle(vehicle_number);
        Location *location = getLocation(pick_up_location);
        TransportService* service = location -> getServicePtr(drop_location);
        BinaryTreeNode* head = service -> getBSTHead();
        if(vehicle != nullptr){
            vector<Trip*> trips = vehicle -> getTrips();
            for(int i = 0;i<trips.size();i++){
                if(trips[i] -> getDepartureTime() == departure_time && trips[i] -> getPickUpLocation() == pick_up_location
                && trips[i] -> getDropLocation() == drop_location)
                 {

                    trips[i] -> setBookedSeats(trips[i] -> getBookedSeats() + 1);
                    if(trips[i] -> getBookedSeats() == vehicle -> getSeatingCapacity()){
                        service -> deleteTrip(departure_time,trips[i]);
                        vehicle -> deleteTrip(i);
                        location -> deleteTrip(i);
                    }
                    return trips[i];
                 }

            }
        }
        return nullptr; // Placeholder
    }
    Location* getLocation(std::string location){
        for(int i = 0;i < locations.size();i++){
        if(locations[i] -> getName() == location)
         return locations[i];
       }
       return nullptr;
    }
    bool findVehicle(string vehicle){
       for(int i  = 0;i<vehicles.size();i++){
        if(vehicles[i] -> getVehicleNumber() == vehicle)
         return true;
       }
       return false;
    }
    Vehicle* returnVehicle(string vehicle){
         for(int i = 0;i<vehicles.size();i++){
            if(vehicle == vehicles[i] -> getVehicleNumber()){
                return vehicles[i];
            }
         }
         return nullptr;
    }
private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};


