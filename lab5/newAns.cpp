#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;



// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

//-----------------------------------  MetroStop Class ----------------------------------------------
// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this -> fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

//----------------------------------------- MetroLine Class ----------------------------------------

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this -> node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop -> getStopName() << endl;
        stop = stop -> getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    MetroStop *curr = this -> getNode();
    int c = 0;
    while(curr -> getNextStop() != nullptr)
    {
       c++;
       curr = curr -> getNextStop();
    }
    return c + 1;
}

void MetroLine::populateLine(std::string filename) {
    // Read the file and populate the line
    ifstream inputFile(filename); 

    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    string line;
    while (getline(inputFile, line)){
        //if(line[line.size() - 1] == ',' || line[line.size() - 1] == '\n')
        while(line[line.size() - 1] == ',' || line[line.size() - 1] == '\n'){
          line.erase(line.end() - 1);
        }
         int len = line.size();
         int ind = 0;
        for(int i = len - 1;i>=0;i--){
           if(line[i] == ' ' && line[i + 1] >= '0' && line[i + 1] <= '9'){
            ind = i;
            break;
           }
        } 
        string stopName = line.substr(0,ind);
        int fare = stoi(line.substr(ind + 1,line.size()));
        MetroStop* stop = new MetroStop(stopName,this,fare);

        if(this -> getNode() == nullptr){
            this -> setNode(stop);
        }
        else{
            MetroStop* curr = this -> getNode();
            while(curr -> getNextStop() != nullptr)
             {
                curr = curr -> getNextStop();
             }
             stop -> setPrevStop(curr);
             curr -> setNextStop(stop);
             
        }
    }

    inputFile.close();
}

// ---------------------------------------------- AVLNode Class ----------------------------------------
// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this -> left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this -> right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this -> parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

//------------------------------------------- AVLTree Class --------------------------------------------
// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    void rotateLeft(AVLNode* node);
    void rotateRight(AVLNode* node);
    void balance(AVLNode* node);
    int stringCompare(string s1, string s2);
    void insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this -> root = root;
}

int AVLTree::height(AVLNode* node) {
    if(node == nullptr)
     return 0;
    return 1 + max(height(node -> getLeft()), height(node -> getRight()));
}

int AVLTree::stringCompare(string s1, string s2) {
    //comparing the strings here
    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    if(node == nullptr)
     return 0;
    return height(node -> getLeft())  - height(node -> getRight());
}

void AVLTree::rotateLeft(AVLNode* node) {
     //std::cout << "come L" << endl;
    //inOrderTraversal(node);
    //cout << height(node);
    AVLNode* y = node -> getRight();
    //cout << y -> getStopName() << " ";
    AVLNode* T1 = y -> getLeft();
    //cout << (T1 == nullptr) << " ";
   
    node -> setRight(T1);
    y -> setLeft(node);
    y -> setParent(node -> getParent());
    if(node -> getParent() != nullptr && node -> getParent() -> getRight() == node)
     node -> getParent() -> setRight(y);
    else if(node -> getParent() != nullptr && node -> getParent() -> getLeft() == node) 
     node -> getParent() -> setLeft(y);
    //cout << y -> getLeft() -> getStopName() << " ";
   
    node = y;
   // cout << "apple" << endl;
    this -> setRoot(node);
    //cout << "in L : ";
    //inOrderTraversal(this -> getRoot());
    //cout << "ball" << endl;
    // cout << balanceFactor(node) << endl;
    // inOrderTraversal(y); cout << endl;
}

void AVLTree::rotateRight(AVLNode* node) {
    //std::cout << "come R" << endl;
    AVLNode*  x = node -> getLeft();
    AVLNode* T1 = x -> getRight();
    node -> setLeft(T1);
    x -> setRight(node);
    x -> setParent(node -> getParent());
     if(node -> getParent() != nullptr && node -> getParent() -> getRight() == node)
     node -> getParent() -> setRight(x);
    else if(node -> getParent() != nullptr && node -> getParent() -> getLeft() == node) 
     node -> getParent() -> setLeft(x);
    node = x;
    this -> setRoot(node);
    //cout << "in R : ";
    //inOrderTraversal(this -> getRoot());cout << "| ROOT:" << this -> getRoot() -> getStopName() << endl;
    //cout << "just right" << endl;
    //inOrderTraversal(node);cout << endl;
}

void AVLTree::balance(AVLNode* current) {
           

}


void AVLTree::insert(AVLNode* node, MetroStop* metroStop) {
      string key = metroStop -> getStopName();
      if(node == nullptr){
        //cout << "god1" << endl;
        node = new AVLNode(key);
        node -> setParent(nullptr);
        node -> addMetroStop(metroStop);
        this -> setRoot(node);
        //cout << "come here" << endl;
        return;
      }

      //AVLNode* newNode = new AVLNode(key);
      AVLNode* curr = node;
      
      //cout << "soup" << endl;
      if(stringCompare(key,curr -> getStopName()) < 0){
        insert(curr -> getLeft(), metroStop);
        if(this -> getRoot() != nullptr)
        curr -> setLeft(this -> getRoot());
        if(this -> getRoot() != nullptr)
         this -> getRoot() -> setParent(curr);
        this -> setRoot(curr);
      }
      else if(stringCompare(key,curr -> getStopName()) > 0){
        insert(curr -> getRight(),metroStop);
        if(this -> getRoot() != nullptr)
         this -> getRoot() -> setParent(curr);
        if(this -> getRoot() != nullptr) 
        curr -> setRight(this -> getRoot());
        this -> setRoot(curr);
      }
      else{
       // cout << "good || " << curr -> getStopName() << endl;
        curr -> addMetroStop(metroStop);
        this -> setRoot(nullptr);
        return;
      }
      


            AVLNode* current = this -> getRoot();
            int balance = balanceFactor(current);
            //cout << current -> getStopName() << " " << balance << endl;
            //cout << balance << " ";
            if(balance < -1  && stringCompare(key,current -> getRight() -> getStopName()) > 0){
               //cout << "1" << endl; 
               rotateLeft(current);
               //cout << "kabri" << endl;
            }  

            //cout << "after1" << endl;
            else if(balance > 1  &&  stringCompare(key,current -> getLeft() -> getStopName()) < 0){
                //cout << "2" << endl; 
               rotateRight(current);
               
            }  
            //cout << "after2" << endl;
            else if(balance < -1  &&  stringCompare(key,current -> getRight() -> getStopName()) < 0){
                //cout << "3" << endl; 
                // cout << "entered3" << endl;
                AVLNode* temp = current -> getRight();
                rotateRight(temp);
                current -> setRight(this -> getRoot());
                rotateLeft(current);
            }
            //cout << "after3" << endl;
            else if(balance > 1  && stringCompare(key,current -> getLeft() -> getStopName()) > 0){
                //cout << "4" << endl; 
                AVLNode* temp = current -> getLeft();
                rotateLeft(temp);
                current -> setLeft(this -> getRoot());
                rotateRight(current);
            }
      
     
}

void AVLTree::populateTree(MetroLine* metroLine) {
    //cout << "come" << endl;
    MetroStop* node = metroLine -> getNode();
    // cout << node -> getStopName() << endl;
    //cout << (this -> getRoot() == nullptr) << endl;
    int c = 0;
    while(node != nullptr){
        //cout << "here2" << endl;
    c++;    
    //cout << c << endl;
    insert(this -> getRoot(), node);
    //cout << this -> getRoot() -> getStopName() << endl;
    //inOrderTraversal(this -> getRoot());cout << "|" << this -> getRoot() -> getStopName() << endl;;
    node = node -> getNextStop();
    }

}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node -> getLeft());
    cout << node -> getStopName() << " ";
    inOrderTraversal(node -> getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node -> getLeft()) + getTotalNodes(node -> getRight());
}

AVLNode* AVLTree::searchStop(string stopName) {
    AVLNode* curr = this -> getRoot();
    while(curr != nullptr){
       if(stringCompare(stopName,curr -> getStopName()) > 0)
        curr = curr -> getRight();
       else if(stringCompare(stopName, curr -> getStopName()) < 0)
        curr = curr -> getLeft();
       else
        return curr;  
    }
    return curr;
}

//---------------------------------------  Trip Class ------------------------------------------------
// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;
    string ptr;
    //vector<Trip*> trips;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    // Getter methods
    MetroStop* getNode() const;
    string getPtr();
    void setPtr(string name);
    Trip* getPrev() const;
    // void setTrip(Trip* trip);
    // vector<Trip*> getTrips();
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}
 string Trip::getPtr(){
    return ptr;
 }
 void Trip::setPtr(string name){
    ptr = name;
 }
MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

vector<Trip*> trips;

// void Trip::setTrip(Trip* trip){
//     trips.push_back(trip);
// }

// vector<Trip*> Trip::getTrips(){
//     return trips;
// }
//--------------------------------------------------- Exploration -------------------------------------
// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}


//------------------------------------------ Path Class -------------------------------------------
class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop -> getStopName() << endl;
    }
}

//------------------------------------------ PathFinder Class ---------------------------------------
// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);
    MetroLine* searchLine(string stopName);
    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() {
  vector<MetroLine*> lines = this -> getLines();
  for(int i  = 0;i<this -> lines.size();i++){
    this -> getTree() -> populateTree(lines[i]);
  }
  
}

MetroLine* PathFinder::searchLine(string stopName){
    vector<MetroLine*> lines = this -> getLines();
    for(int i = 0;i<lines.size();i++){
        MetroStop* root = lines[i] -> getNode();
        while(root != nullptr){
            if(root -> getStopName() == stopName){
                return lines[i];
            }
            root = root -> getNextStop();
        }
    }

    return nullptr;
}

MetroStop* getStopOnLine(string stopName, MetroLine* line){
     MetroStop* stop = line -> getNode();
     while(stop != nullptr){
        if(stop -> getStopName() == stopName)
         return stop;
        stop = stop -> getNextStop(); 
     }
     return nullptr;
}

bool findStop(Path* path,string stopName){
   vector<MetroStop*> stops = path -> getStops();
   for(int  i = 0;i<stops.size();i++){
    if(stops[i] -> getStopName() == stopName)
     return true;
   }
   return false;
}

bool findTrip(MetroStop* stop){
   for(int i  = 0;i < trips.size();i++){
    if(trips[i] -> getNode() -> getStopName() == stop -> getStopName())
     return true;
   }
   return false;
}

Path* PathFinder::findPath(std::string origin, std::string destination) {
    //cout << "come entered" << endl;
    AVLTree* root = this -> getTree();
    //cout << this -> getLines().size() << endl;
    //AVLNode* stop = root -> searchStop(origin);
    MetroLine* line = searchLine(origin);
    //cout << (line == nullptr) << endl;
    //cout << "here2" << endl;
    MetroStop* stop = getStopOnLine(origin,line);
    //cout << "here1" << endl;
    AVLNode* avlNode = root -> searchStop(origin);
    vector<MetroStop*> stops = avlNode -> getStops();
    Exploration* explore = new Exploration();
    for(int i  = 0;i<stops.size();i++){
        Trip* trip1 = new Trip(stop, nullptr);
        trip1 -> setPtr("prev");
        Trip* trip2 = new Trip(stop,nullptr);
        trips.push_back(trip1);
        trips.push_back(trip2);
        trip2 -> setPtr("next");
        explore -> enqueue(trip1);
        explore -> enqueue(trip2);
    }
    //cout << "entered2" << endl;
    while(!explore -> isEmpty()){
         Trip* currTrip = (explore -> getTrips()).front();
         explore -> dequeue();
         MetroStop* forNode = currTrip -> getNode();
         string traversalMode = currTrip -> getPtr();
         int flag = -1;
         if(traversalMode == "prev")
          flag = 0;
         else 
          flag = 1; 
         //MetroStop* backNode = currTrip -> getNode();
         //cout << "entered3" << endl;


         while(forNode != nullptr){
            //cout << "i am here" << endl;
            //when destination is found
             if(forNode -> getStopName() == destination){
                MetroStop* travNode = getStopOnLine(forNode -> getStopName(),forNode -> getLine());
                int fareNode = travNode -> getLine() -> getNode() -> getFare();
                Path* path = new Path();
                
                  while(currTrip  != nullptr){
                    int flagInner = -1;
                    string travMode = currTrip -> getPtr();
                    if(travMode == "prev")
                     flagInner = 1;
                    else 
                     flagInner = 0; 
                    travNode = getStopOnLine(travNode -> getStopName(),currTrip -> getNode() -> getLine());
                    MetroStop* node1 = currTrip -> getNode();
                    path -> setTotalFare(path -> getTotalFare() + abs(travNode -> getFare() - node1 -> getFare()));
                     while(travNode != node1){
                        if(findStop(path,travNode -> getStopName()) == false)
                         path -> addStop(travNode);
                         //path -> setTotalFare(path -> getTotalFare() + abs(travNode -> getFare() - fareNode));
                        if(flagInner)
                         travNode = travNode -> getNextStop();
                        else 
                         travNode = travNode -> getPrevStop(); 
                     }
                     path -> addStop(travNode);
                     //path -> setTotalFare(path -> getTotalFare() + abs(travNode -> getFare() - fareNode));
                     currTrip = currTrip -> getPrev();
                 }
                return path;
             }

             //if stop is a junction

             AVLNode* junStop = root -> searchStop(forNode -> getStopName());
             vector<MetroStop*> juncVec = junStop -> getStops();
             if(juncVec.size() >  1){
             for(int i  = 0;i<juncVec.size();i++){
                if(findTrip(juncVec[i]) == false){
                if(juncVec[i] -> getLine() != forNode -> getLine()){
                  
                Trip* juncTrip1 = new Trip(juncVec[i],currTrip);
                 juncTrip1 -> setPtr("prev");
                Trip* juncTrip2 = new Trip(juncVec[i],currTrip);
                juncTrip2 -> setPtr("next");
                explore -> enqueue(juncTrip1);
                explore -> enqueue(juncTrip2);
                
                 }
                }


               }

            }

             if(flag)
              forNode = forNode -> getNextStop();
             else
              forNode = forNode -> getPrevStop();
         }

        //cout << "entered4" << endl; 
        //   while(backNode != nullptr){
        //     cout << "i am here2" << endl;
        //      if(backNode -> getStopName() == destination){
        //         MetroStop* travNode = getStopOnLine(backNode -> getStopName(),backNode -> getLine());
        //         int fareNode = travNode -> getLine() -> getNode() -> getFare();
        //         Path* path = new Path();
        //         cout << "entered5" << endl;
        //         int c = 0;
        //         while(currTrip  != nullptr){
        //             cout << "entered6" << endl;
        //             cout << "|" << currTrip -> getNode() -> getLine() -> getLineName() << endl;
        //             travNode = getStopOnLine(travNode -> getStopName(),currTrip -> getNode() -> getLine());
        //             MetroStop* node1 = currTrip -> getNode();
        //              while(travNode != node1){
        //                 path -> addStop(travNode);
        //                 path -> setTotalFare(path -> getTotalFare() + abs(travNode -> getFare() - fareNode));
        //                 cout << travNode -> getStopName() << endl;
        //                 if(c == 0)
        //                  travNode = travNode -> getNextStop();
        //                 else
        //                  travNode = travNode -> getPrevStop();
                         
        //                 //cout << "loop" << endl;
        //              }
        //              c++;
        //              cout << "trav:" << travNode -> getStopName() << endl;
        //              path -> addStop(travNode);
        //              path -> setTotalFare(path -> getTotalFare() + abs(travNode -> getFare() - fareNode));
        //              currTrip = currTrip -> getPrev();
                     
        //          }
        //          cout << "good" << endl;
        //          return path;
        //      }


        //      AVLNode* junStop = root -> searchStop(backNode -> getStopName());
        //      vector<MetroStop*> juncVec = junStop -> getStops();
        //       if(juncVec.size() >  1){
        //      for(int i  = 0;i<juncVec.size();i++){
        //         if(juncVec[i] -> getLine() != backNode -> getLine()){
        //         Trip* juncTrip = new Trip(juncVec[i],currTrip);
        //         explore -> enqueue(juncTrip);
        //         }
        //      }
        //      }
        //      backNode = backNode -> getPrevStop();
        //  }
       

    }
    //cout << "count on you" << endl;
    return nullptr;

}






// int main(){
//     MetroLine ob("green");
//     ob.populateLine("green.txt");
//     MetroLine ob1("orange");
//     ob1.populateLine("orange.txt");
//     MetroLine ob2("magenta");
//     ob2.populateLine("magenta.txt");
//     MetroLine ob3("violet");
//     ob3.populateLine("violet.txt");
//     MetroLine ob4("blue");
//     ob4.populateLine("blue.txt");
//     MetroLine ob5("yellow");
//     ob5.populateLine("yellow.txt");
//     MetroLine ob6("red");
//     ob6.populateLine("red.txt");
//     MetroStop* node = ob.getNode();
//     AVLTree tree;
//     tree.setRoot(nullptr);
//     lines.push_back(&ob);
//     lines.push_back(&ob1);
//     lines.push_back(&ob2);
//     lines.push_back(&ob3);
//     lines.push_back(&ob4);
//     lines.push_back(&ob5);
//     lines.push_back(&ob6);
//     cout << "come" << endl;
//     testFindPath();
//     //cout << "here2" << endl;
//     //tree.populateTree(&ob);
//     //tree.inOrderTraversal(tree.getRoot());
//     //cout << tree.getRoot() -> getStopName();
//     //cout << tree.getTotalNodes(tree.getRoot()) << endl;
//     //tree.populateTree(&ob1);
//     //cout << tree.getTotalNodes(tree.getRoot()) << endl;
//     //tree.populateTree(&ob2);
//     // cout << tree.getTotalNodes(tree.getRoot()) << endl;
//     //tree.populateTree(&ob3);
//     // cout << tree.getTotalNodes(tree.getRoot()) << endl;
//     //tree.populateTree(&ob4);
//     // cout << tree.getTotalNodes(tree.getRoot()) << endl;
//     //tree.populateTree(&ob5);
//     // cout << tree.getTotalNodes(tree.getRoot()) << endl;
//     //tree.populateTree(&ob6);
//     // cout << tree.getTotalNodes(tree.getRoot()) << endl;
//     //cout << "comeon" <<endl;
//     //cout << tree.getTotalNodes(tree.getRoot()) << endl;
//     //cout << tree.height(tree.getRoot()) << endl;
//     //tree.inOrderTraversal(tree.getRoot());
//     //cout << isBalanced(tree.getRoot()) << endl;
//     //cout << tree.getRoot() -> getStopName() << endl;
//     return 0;
// }