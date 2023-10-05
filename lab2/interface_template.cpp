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
    void add_student(StudentRecord &ele){
        
        Node* ob = new Node();
        ob -> set_element(&ele); 
        ob -> set_next(nullptr);
         
        if(get_iterator() == nullptr){
            
           set_iterator(ob);
            
        }
        else{
            
             Node* ite = get_iterator();
            
             while(ite -> get_next() != nullptr){
               
                ite = ite -> get_next();
             }
             ite -> set_next(ob);
             
        }
       
    }
    void delete_student(string name){
        Node* current = get_iterator();

        
        if (current && current->get_element()->get_studentName() == name) {
            this -> set_iterator(current->get_next());
            delete current;
            return;
        }

        
        Node* prev = nullptr;
        while (current && current->get_element()->get_studentName() != name) {
            prev = current;
            current = current->get_next();
        }

        
        if (current == nullptr) {
            return;
        }

        
        prev->set_next(current -> get_next());
        delete current;
       
    }

};



vector<StudentRecord> students;
vector<LinkedList> EntityArray;
void read_input_file(string file_path){
    //file reading starts
    ifstream file;
    file.open(file_path);
    string line;
    
    vector<vector<string>> row;
    while (getline(file, line)) {
        vector<string> str;
        line = line + ',';
        string word = "";
        for(int i  = 0;i<line.size();i++){
            if(line[i] == '['){
                string s = "";
                while(line[i] != ']'){
                  s = s + line[i];
                  i++;
                }
                s = s + line[i];
                str.push_back(s);
                continue;
            }
            if(line[i] == ','){
                str.push_back(word);
                word = "";
            }
            else{
              word = word + line[i];
            }
        }
        row.push_back(str);
    }

  
    file.close();

    
   vector<string> st;

   for(int i  = 0;i<row.size();i++){
        for(int j = 2;j<row[0].size();j++){
            
            if(row[i][j][0] == '['){
               string s = row[i][j];
               s.erase(s.begin());
               s.erase(s.end() - 1);
               s = s + ',';
               string word = "";
               for(int k = 0;k<s.size();k++){
                  if(s[k] == ','){
                    if(find(st.begin(),st.end(),word) == st.end()){
                     st.push_back(word);
                     word = "";
                    }
                  }
                  else{
                    word = word + s[k];
                  }
               }
            }
            else{
                if(find(st.begin(),st.end(),row[i][j]) == st.end()){
                     st.push_back(row[i][j]);
                    }
                
            }
        }
    }

    for(auto it = st.begin();it != st.end();it++){
        if(*it == "\n" || *it == "" || *it == " ")
         st.erase(it);
    }
    //entity code ends

    //storing students record

    for(int i  = 0;i<row.size();i++){
        StudentRecord obj;
        for(int j = 0;j<2;j++){
            if(j == 0){
                obj.set_studentName(row[i][j]);
            }
            else{
                obj.set_rollNumber(row[i][j]);
            }
        }

        students.push_back(obj);
    }
    
    

    //students record ends

    //creating the entity

    for(auto it = st.begin();it != st.end();it++){
        LinkedList ob;
        ob.set_name(*it);
        ob.set_iterator(nullptr);
        EntityArray.push_back(ob);

    }
 

    //done creating entity array

    //adding students to different linkedlist
    int studentPointer = 0;
    for(int i  = 0;i<row.size();i++){
      
        for(int j = 2;j<row[0].size();j++){
            
            if(row[i][j][0] == '['){
               string s = row[i][j];
               s.erase(s.begin());
               s.erase(s.end() - 1);
               s = s + ',';
               string word = "";
               for(int k = 0;k<s.size();k++){
                  if(s[k] == ','){
                    string name = word;
                    for (LinkedList  &entity : EntityArray) {
                                if (entity.get_name() == name) {
                                    entity.add_student(students[studentPointer]);
                                }
                            }
                    word = "";
                  }
                  else{
                    word = word + s[k];
                  }
               }
            }
            else{
                for (LinkedList &entity : EntityArray) {
                                string name = row[i][j];
                                if (entity.get_name() == name) {
                                    entity.add_student(students[studentPointer]);
                                }
                            }
                 
            }
        }

        studentPointer = studentPointer + 1;
    }

}