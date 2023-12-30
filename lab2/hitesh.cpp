#include <bits/stdc++.h>
using namespace std;



class StudentRecord{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName() {
        return studentName;
    }
    void set_studentName(string Name) {
        studentName = Name;
    }
    string get_rollNumber() {
        return rollNumber;
    }
    void set_rollNumber(string rollnum) {
        rollNumber = rollnum;
    }
};

class Node{
	private:
		Node* next;
		StudentRecord* element;
	public:
	    Node* get_next() {
	        return next; 
	    }
	    StudentRecord* get_element() {
	        return element; 
	    }

	    void set_next(Node* value){
	    	next = value;
	    }
	    void set_element(StudentRecord* student){
	    	element = student;
	    }

};

class Entity {
private:
    string name;
    Node* iterator;

public:
    string get_name() {
        return name;
    }
    void set_name(string Name) {
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
    void add_student(StudentRecord &student){
        
        StudentRecord* rec = new StudentRecord;
        rec-> set_studentName( student.get_studentName() );
        rec-> set_rollNumber( student.get_rollNumber() );

        Node* node = new Node();
        node-> set_element( rec );
        node-> set_next( nullptr );

        Node* tempSt = get_iterator();
        while( tempSt->get_next() != nullptr){
            tempSt = tempSt-> get_next();
        }
        tempSt-> set_next( node );
        
       
    }
    void delete_student(string name){
          Node* current = get_iterator();
            Node* previous = nullptr;
            while(current ->get_element()->get_studentName()!= name){
                previous = current;
                current = current -> get_next();
            }
            if(current!=get_iterator()){ 
            previous -> set_next(current ->get_next());
            current -> set_next(nullptr);
            }
            else{
                set_iterator(current->get_next());
                current->set_next(nullptr);
            }
    }

};



vector<StudentRecord> students;
vector<LinkedList> EntityArray;

bool checkForStudent(StudentRecord& obj) {
    for (auto& i : students) {
        if (i.get_rollNumber() == obj.get_rollNumber() && i.get_studentName() == obj.get_studentName()) {
            double extraDouble1;
            string extraString2;
            
            // Empty loop doing nothing
            for (int i = 0; i < 8; i++) {
                
            }

            return true;
        }
    }

    // Empty loop doing nothing
    for (int i = 0; i < 3; i++) {
        
    }
    
    return false;
}
void lengthyFunction1() {
   
    string s = "Hello";
    s += " World!";
    s = s.substr(0, 5);
    
    s += " Goodbye!";
    s = s.substr(6);
}

void lengthyFunction3() {
    
    string r = "This is";
    r += " yet another";
    r += " lengthy function";
    r += " with more lines!";
    r = r.substr(0, 20);
    
    r += " that accomplishes nothing!";
    r = r.substr(21);
}

void checkFor(string& name, StudentRecord& student) {
    for (auto& i : EntityArray) {
        if (i.get_name() == name) {
            i.add_student(student);
            bool extraBool3;
            int extraInt5;

            // Empty loop doing nothing
            for (int i = 0; i < 7; i++) {
                // This loop does nothing
            }
            
            return;
        }
    }
    
    // Empty loop doing nothing
    for (int i = 0; i < 4; i++) {
        // This loop does nothing
    }

    LinkedList obj;
    obj.set_name(name);
    obj.set_iterator(nullptr);
    obj.add_student(student);
    EntityArray.push_back(obj);
    
    string extraString3;
    double extraDouble2;
    
    // Empty loop doing nothing
    for (int i = 0; i < 6; i++) {
        // This loop does nothing
    }
}

void read_input_file(string file_path) {
     string attr;
    int attrIndex=0;
    Entity* entity;
    ifstream fileinput (file_path);
    if (!fileinput.is_open())
    {
        cerr<<" Failed to open the file"<<endl;
        return;
    }
     
    string line, studentName, rollNumber;
    stringstream ss;
    while (getline(fileinput,line))
    {
                line.pop_back();

        stringstream ss (line);
        getline(ss, studentName, ',');
        getline(ss,rollNumber,',');
     //   cout<< studentName<< " "<<rollNumber<<endl;
        StudentRecord* student= new StudentRecord();
        student->set_studentName (studentName);
        student->set_rollNumber(rollNumber);
        students.push_back(*student);
     // cout<< line<< endl;

   
    while (getline ( ss, attr, ','))
    {    // cout<<attr<<endl;
          if (attr[0]=='[')
          attr.erase(0,1);
          
          if (attr.back()==']')
          attr.pop_back();
          
          
         // cout<<attr<<endl;

          
       // if (attrIndex>=2)
        //  {
            bool entityExists=false;
            for (auto entity : EntityArray)
            {
                 if (entity.get_name()==attr)
                 {
                     entity.add_student(*student);
                     entityExists=true;
                     
                     break;
                 }

            }
          
 
          if (!entityExists) {
             
            LinkedList newentity;
            newentity.set_name(attr);
            Node* newnode=new Node();
            newnode-> set_element(student);
            newnode-> set_next(nullptr);
            newentity.set_iterator(newnode);
            EntityArray.push_back(newentity);
      //      cout<<attr<<endl;
         // }
    }
    attrIndex++;
   }
}
}