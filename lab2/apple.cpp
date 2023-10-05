#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;


class StudentRecord {
private:
    std::string studentName;
    std::string rollNumber;

public:
    std::string get_studentName() {
        return studentName;
    }
    void set_studentName(std::string Name) {
        studentName = Name;
    }
    std::string get_rollNumber() {
        return rollNumber;
    }
    void set_rollNumber(std::string rollnum) {
        rollNumber = rollnum;
    }
};

class Node {
private:
    Node* next = NULL;
    StudentRecord* element = NULL;

public:
    Node* get_next() {
        return next;
    }
    void set_next(Node* value) {
        next = value;
    }
    StudentRecord* get_element() {
        return element;
    }
    void set_element(StudentRecord* student) {
        element = student;
    }
};

class Entity {
private:
    std::string name;
    Node* iterator;

public:
    std::string get_name() {
        return name;
    }
    void set_name(std::string Name) {
        name = Name;
    }
    Node* get_iterator() {
        return iterator;
    }
    void set_iterator(Node* iter) {
        iterator = iter;
    }
};


class LinkedList : public Entity {
public:
    void add_student(StudentRecord& student) {

     //cout  << student.get_studentName() << endl;   
    Node* it = this -> get_iterator();
    Node* newNode = new Node();
    
    StudentRecord* newStudent = new StudentRecord(student); // Create a copy of the StudentRecord
    newNode -> set_element(newStudent);
    newNode -> set_next(nullptr);
    //cout  << student.get_studentName() << endl;   
    if (it == nullptr) {
        //cout  << "ok" << " ";
        this -> set_iterator(newNode);
    }
    else {
        //cout  << "ok1" << endl;
        while (it -> get_next() != nullptr) {
            it = it -> get_next();
        }
        //cout  << "ok3" << endl;
        it -> set_next(newNode);
        //newNode->set_next(nullptr);
        //cout  << "ok2" << endl;
    }
    //cout  << student.get_studentName() << endl;   
}

    void delete_student(std::string studentName) {
        Node* current = get_iterator();
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->get_element()->get_studentName() == studentName) {
                if (prev != nullptr) {
                    prev->set_next(current->get_next());
                } else {
                    set_iterator(current->get_next());
                }
                delete current;
                break;
            }
            prev = current;
            current = current->get_next();
        }
    }
};

std::vector<StudentRecord> students;
std::vector<LinkedList> EntityArray;

int check_duplicate_entity(std::string dept){
        int j = 0;
        for(j = 0;j<EntityArray.size();j++){
            if(EntityArray[j].get_name() == dept){
                return j;
            }
        }
        return -1;
    }

void read_input_file(string file_path){
    

    ifstream data(file_path);
    
    if(data.is_open()){


        // char bom[3];
        // data.read(bom, 3);

        // if (data) {
        //     // Check for UTF-8 BOM (Byte Order Mark) and skip it if present
        //     if (bom[0] == (char)0xEF && bom[1] == (char)0xBB && bom[2] == (char)0xBF) {
        //         int s;
        //     } else {
        //         // If there's no BOM, reset the file pointer to the beginning
        //         data.seekg(0);
        //     }
        // }
        string line;
        while (getline(data, line)) {
            int flag = 0;
            StudentRecord temp;
            std::string name;
            std::string roll;
            int a =0;
            for (int  i = 0; i < line.length(); i++) {
                char c = line[i];
                if (c == ',') {
                    break;
                    
                } else {
                    name += c;
                    a++;
                }
            }
            for(int i =0;i<students.size();i++){
                if(students[i].get_studentName()==name){
                    flag = 1;
                    break;
                }
            }
            if(flag){
                continue;
            }
            else{
            temp.set_studentName(name);
            }
            
            for ( int i = a+1 ; i < line.length();i++) {
                char c = line[i];
                if (c == ',') {
                    break;
                } else {
                    roll += c;
                    a++;
                }
            }
            temp.set_rollNumber(roll);
            
            students.push_back(temp);
            std::string dept;
            a =a+2;
            for ( int i = a; i < line.length(); i++) {
                char c = line[i];
                if (c == ',') {
                    break;
                    
                } else {
                    dept += c;
                    a++;
                }
            }
            //cout  << dept << " ";
            a= a+2;

            int dept_duplicate = check_duplicate_entity(dept);
             if(dept_duplicate == -1){
                LinkedList newLinkedList; // Create a new LinkedList
                newLinkedList.set_name(dept);
                newLinkedList.set_iterator(nullptr);
                EntityArray.push_back(newLinkedList);
                //cout  << "come here 2" << " ";
                EntityArray.back().add_student(students.back()); // Add the student record
                
             }
             else{
                EntityArray[dept_duplicate].add_student(students.back());
            }
            //cout  << "i am here" << " ";
            
            std::string course;
            vector<string> courses;
            for (int  i = a ; i < line.length(); ++i) {
                char c = line[i];
                if (c == ']'){ 
                    courses.push_back(course);
                    
                    course.clear();
                    break;
                    
                }
                else if(c == ',') {
                    a++;
                    courses.push_back(course);
                    
                    course.clear();
                    continue;
                }
                else {
                    course += c;
                    a++;
                }
            }  

            // cout  << "come" << " ";
             ////cout  << courses.size() << " ";
             //cout  << "good" << " ";
            a = a+2;
            for(int k =0;k<courses.size();k++){
                int course_duplicate = check_duplicate_entity(courses[k]);
                if(course_duplicate != -1){
                    EntityArray[course_duplicate].add_student(temp);
                }
                else{
                    LinkedList newLinkedList; // Create a new LinkedList
                    newLinkedList.set_name(courses[k]);
                    newLinkedList.set_iterator(nullptr);
                    EntityArray.push_back(newLinkedList);
                    EntityArray.back().add_student(students.back()); // Add the student record
                    
                }
                
            }
            


            std::string hostel;
            for (int  i = a ; i < line.length(); ++i) {
                char c = line[i];
                if (c == ',') {
                    break;
                
                } else {
                    hostel += c;
                    a++;
                }
            }
            //cout  << hostel << " ";
            a = a + 2;
            
            int hostel_duplicate = check_duplicate_entity(hostel);
            if( hostel_duplicate != -1){
                //cout  << "come3" << " ";
                EntityArray[hostel_duplicate].add_student(temp);
            }
            else{
                //cout  << "hostel" << " ";
                LinkedList newLinkedList; // Create a new LinkedList
                newLinkedList.set_name(hostel);
                newLinkedList.set_iterator(nullptr);
                EntityArray.push_back(newLinkedList);
                //cout  << EntityArray.size() << " ";
                int index = check_duplicate_entity(hostel);
                //cout  << index << " ";
                ////cout  << EntityArray.back().get_name() << " ";
                EntityArray.back().add_student(students.back());
                //cout  << "hostel2" << " "; // Add the student record
                
            }

            //cout  << "good2" << " ";
            std::string club;
            vector<string> clubs;
            for ( int i = a ; i < line.length(); ++i) {
                char c = line[i];
                if (c == ']') {
                    clubs.push_back(club);
                    club.clear();
                    break;
                 }
                 else if(c == ',') {
                     a++;
                    clubs.push_back(club);
                    club.clear();
                     continue;
                 }
                 else {
                     club += c;
                     a++;
                }
            }
            //cout  << "i am here2" << " ";
            //cout  << clubs.size() << endl;

            for(int k =0;k<clubs.size();k++){
                 int club_duplicate = check_duplicate_entity(clubs[k]);
                 if(club_duplicate != -1){
                     EntityArray[club_duplicate].add_student(temp);
                }
                 else{
                      LinkedList newLinkedList; // Create a new LinkedList
                     newLinkedList.set_name(clubs[k]);
                     newLinkedList.set_iterator(nullptr);
                     EntityArray.push_back(newLinkedList);
                     EntityArray.back().add_student(students.back()); // Add the student record
                    
                 }
            }

            //cout  << endl;
        }
        data.close();
    }
    else{
        std::cout <<"Cannot be opened";
    }

    // string name = "DSA";
    // cout << " i am god" << endl;
    // for(int i  = 0;i<EntityArray.size();i++){
    //     if(EntityArray[i].get_name() == name){
    //         Node* it = EntityArray[i].get_iterator();
    //         while(it != nullptr){
    //             cout << it -> get_element() -> get_studentName() << endl;
    //             it = it -> get_next();
    //         }
    //     }
    // }

}

// int main(){
//     read_input_file("Details.txt");


// }