#include <iostream>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

class HybridNode {
public:
    string key;  
    string element;  
    int colour;
    unordered_map<string,int> mpp;
    //1 for colour black
    //0 for colour red
    HybridNode* parent;
    HybridNode* left_child;
    HybridNode* right_child;
    HybridNode* next_node;

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) , colour(-1){}
};

class RedBlackTree {
private:
    HybridNode* root;
    bool ll = false; // LL rotation checker
    bool rr = false; // RR rotation checker
    bool lr = false; // LR rotation checker
    bool rl = false; // RL rotation checker

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;
    }

    void setRoot(HybridNode* node) {
        root = node;
    }

     HybridNode* rotateLeft(HybridNode* node) {
        HybridNode* x = node -> right_child;
        HybridNode* y = x -> left_child;
        x -> left_child = node;
        node -> right_child = y;
        node -> parent = x;
        if (y != nullptr)
            y -> parent = node;
        return x;
    }
 
    // Function to perform Right Rotation
    HybridNode* rotateRight(HybridNode* node) {
        HybridNode* x = node -> left_child;
        HybridNode* y = x -> right_child;
        x -> right_child = node;
        node -> left_child = y;
        node -> parent = x;
        if (y != nullptr)
            y -> parent = node;
        return x;
    }

    //funtion for the insertion
    HybridNode* insertion(HybridNode* root, string key, string element) {
        bool f = false; // Flag to check RED-RED conflict
        //cout << "insert3" << endl; 
        if (root == nullptr){
            //cout << "inside" << endl;
            HybridNode* node = new HybridNode(key, element);
            node -> next_node = nullptr;
            node -> mpp[element]++;
            node -> colour = 0;
            return node;
            
        }
        else if (key.compare(root -> key) < 0) {
            //cout << "good" << endl;
            root -> left_child = insertion(root -> left_child, key, element);
            root -> left_child -> parent = root;
            if (root != this -> getRoot()) {
                if (root -> colour == 0 && root -> left_child -> colour == 0)
                    f = true;
                    //found the double red condition
            }
        } else if(key.compare(root -> key) > 0) {
            //cout << "good2" << endl;
            root -> right_child = insertion(root -> right_child, key, element);
            root -> right_child -> parent = root;
            if (root != this -> getRoot()) {
                if (root -> colour == 0 && root -> right_child -> colour == 0)
                    f = true;
                    //found the double red condition
            }
        }
        else{
            HybridNode* temp = root;
            HybridNode* newNode = new HybridNode(key,element);
            if(root -> element != element){
                while(temp -> next_node != nullptr){
                    temp = temp -> next_node;
                }
                temp -> next_node = newNode;
                root -> mpp[element]++;
            }
            else{
                root -> mpp[root -> element]++;
            }
        }
         //cout << "insert2" << endl;
        // Perform rotations
        if (ll) {
            //cout << "rot1" << endl;
            root = rotateLeft(root);
            root -> colour = 1;
            root -> left_child -> colour = 0;
            ll = false;
        } else if (rr) {
            //cout << "rot2" << endl;
            root = rotateRight(root);
            root -> colour = 1;
            root -> right_child -> colour = 0;
            rr = false;
        } else if (rl) {
            //cout << "rot3" << endl;
            root -> right_child = rotateRight(root -> right_child);
            root -> right_child -> parent = root;
            root = rotateLeft(root);
            root -> colour = 1;
            root -> left_child -> colour = 0;
            rl = false;
        } else if (lr) {
            //cout << "rot4" << endl;
            root -> left_child = rotateLeft(root -> left_child);
            root -> left_child -> parent = root;
            root  = rotateRight(root);
            root -> colour = 1;
            root -> right_child -> colour = 0;
            lr = false;
        }
        //cout << "after rotation" << endl;
        //section for handlin red-red conflicts
        if (f) {
            if (root -> parent -> right_child == root) {
                if (root -> parent -> left_child == nullptr || root->parent->left_child->colour == 1) {
                    if (root -> left_child  && root -> left_child -> colour == 0)
                        rl = true;
                    else if (root -> right_child  && root -> right_child -> colour == 0)
                        ll = true;
                } else {
                    root -> parent -> left_child -> colour = 1;
                    root->colour = 1;
                    if (root -> parent != this -> getRoot())
                        root -> parent -> colour = 0;
                }
            } else {
                if (root -> parent -> right_child == nullptr || root -> parent -> right_child -> colour == 1) {
                    if (root -> left_child  && root->left_child->colour == 0)
                        rr = true;
                    else if (root -> right_child  && root -> right_child -> colour == 0)
                        lr = true;
                } else {
                    root -> parent -> right_child -> colour = 1;
                    root -> colour = 1;
                    if (root->parent != this -> getRoot())
                        root->parent->colour = 0;
                }
            }
            f = false;
        }
        return root;
    }

    HybridNode* insert(string key, string element) {
        if (this -> getRoot() == nullptr) {
            this -> setRoot( new HybridNode(key,element));
            this -> getRoot() -> colour = 1;
        } else{
            //cout << "i am good" << endl;
            this -> setRoot(insertion(this -> getRoot(), key, element));
            //cout << "insert1" << endl;
        }
        
    }

    bool deleteNode(string key) {
        // Implement Red-Black Tree deletion
    }
    int height(HybridNode* root){
        if(root == nullptr)
         return 0;
        return 1 + max(height(root -> left_child), height(root -> right_child)); 
    }
    void traverseUp(HybridNode* node) {
        vector<HybridNode*> store;
        if(node != nullptr){
        while(node -> parent != nullptr){
            store.push_back(node);
            node = node -> parent;
        }
        }
    }

    void traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
        vector<HybridNode*> store;
        for(int i  = 0;i<bit_sequence.size();i++){
            store.push_back(node);
            if(bit_sequence[i] == '1' && node -> left_child){
                node = node -> left_child;
            }
            else if(bit_sequence[i] == '0' && node -> right_child){
                node = node -> right_child;
            }
        }
    }

    vector<string> preOrderTraversal(HybridNode* node, int depth) {
        // Perform in-order traversal staying within specified depth

    }
    HybridNode* search(string key) {
        // Implement Red-Black Tree search
        
    }
    void inorderTraversal(HybridNode* root){
        if(root == nullptr)
         return;
        inorderTraversal(root -> left_child);
        //unordered_map<string, int> mpp = root -> mpp;
        // for(auto it : mpp){
        //     cout << root -> key << " " << it.second;
        // }
        // cout << endl;
        inorderTraversal(root -> right_child);  
    }
    int blackheight(HybridNode* node){
        // Implement blackheight
        if(node == nullptr)
         return 0;
        int h = 0; 
        if(node -> colour == 1)
         h = 1; 
        return h + max(blackheight(node -> left_child), blackheight(node -> right_child));
    }
};

class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;  // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val) {
        word = word_val;
    }

    string getWord() {
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {
        return chapter_word_counts;
    }

    void addOccurrence(string chapter, int word_count) {
        // Add a chapter's word count for this word
        // vector<pair<string, int>> ob = this -> getChapterWordCounts();
        // for(int i = 0;i<ob.size();i++){
        //     auto it = ob[i].first;
        //     if(it == chapter){
        //         pair<string,int> pr = make_pair(chapter, word_count);
        //     }
        // }
        // pair<string, int> pr = make_pair(chapter , word_count);
        // this -> setChapterWordCounts();
        pair<string, int> pr = make_pair(chapter, word_count);
        this -> chapter_word_counts.push_back(pr);

    }

    string toString() {
        // Return a string representation of the IndexEntry
        // Modify the implementation as needed for specific use cases
        return "";
    }
};

class Lexicon {
private:
    RedBlackTree red_black_tree;

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree() {
        return red_black_tree;
    }

    void readChapter(string chapter_name, vector<string> words) {
        // Process words from a chapter and update the Red-Black Tree
        vector<string> chapWords = processFile(chapter_name);
        cout << chapWords.size() << endl;
        RedBlackTree root = this -> getRedBlackTree();
        //Lexicon *lex = new Lexicon();
        for(int i = 0;i<chapWords.size();i++){
            root.insert(chapWords[i], chapter_name);
            
        }
        //root.inorderTraversal(root.getRoot());
        this -> setRedBlackTree(root);
        //cout << lex 
    }

    //function to trim the extra spaces from back and front of the line
    string trim(string str) {

    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
    }
     
    bool isAlphaNumeric(char s){
        if((s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z') || (s >= '0' && s <= '9'))
         return true;
        return false; 
    } 
    //function to process the file
    vector<string>  processFile(string chapter_name){
        string filename = chapter_name; 
        ifstream inputFile(filename);
    
        if (!inputFile.is_open()) {
            std::cerr << "Failed to open the file: " << filename << endl;
        }
        
        string line;
        vector<string> words;
        while (getline(inputFile, line)) {
           if(line[line.size() - 1] == '\n')
            line.erase(line.end() - 1);
           
           string str = trim(line);
           //cout << str << " " << str.size() << endl;
           str = str + " ";
           int len = str.size();
           string final_string = "";
           //cout << str << endl;
           for(int i = 0;i<len;i++){
            if(isAlphaNumeric(str[i]) != true){
                if((int)str[i] != 39)
                 final_string = final_string + ' ';
                else
                 final_string = final_string + str[i]; 
                //cout << "enter" << endl;
            }
            else{
               final_string = final_string + str[i];
               //cout << "good" << endl;
            }
           }
           //cout << final_string << "|" << endl;
           string word = "";
           for(int i = 0;i<len;i++){
              if(final_string[i] == ' ')
               {
                if(word != "")
                 words.push_back(word);
                word = "";
               }
               else{
                word = word + final_string[i];
               }
           }

        }
        // for(int i = 0;i<words.size();i++){
        //     cout << words[i] << "|" << endl;
        // }
        return words;
        inputFile.close();
    }

    void pruneRedBlackTree() {
        // Prune the Red-Black Tree by deleting common words
    }
    void inorder(HybridNode* root, vector<IndexEntry> &indexes){
        if(root == nullptr)
         return;
        inorder(root -> left_child, indexes);
        unordered_map<string, int> mpp = root -> mpp;
        // for(auto it : mpp){
        //     cout << root -> key << " " << it.second;
        // }
        // cout << endl;
        IndexEntry *ob = new IndexEntry(root -> key);
        for(auto it : mpp){
            ob -> addOccurrence(it.first, it.second);
        }
        indexes.push_back(*ob);
        inorder(root -> right_child, indexes);  
    }
    vector<IndexEntry> buildIndex() {
        RedBlackTree root = this -> getRedBlackTree();
        HybridNode* node = root.getRoot();
        vector<IndexEntry> indexes;
        inorder(node, indexes);
        return indexes;
    }
};
int main(){
    // RedBlackTree* ob = new RedBlackTree();
    // cout << "i am here1" << endl;
    // ob -> insert("a","apple");
    // ob -> inorderTraversal(ob -> getRoot());
    // cout << "i am here2" << endl;
    // ob -> insert("b","ball");
    // cout << "i am here3" << endl;
    // ob -> insert("c","cat");
    // cout << "i am here" << endl;
    // ob -> insert("d","cat");
    // ob -> insert("e","cat");
    // ob -> insert("f","fish");
    // //ob -> insert("g","good");
    // ob -> inorderTraversal(ob -> getRoot());
    // cout << ob -> height(ob -> getRoot());
    // cout << "-------------" << endl;
    // cout << ob -> getRoot() -> key;
    // cout << ob -> blackheight(ob -> getRoot()) << endl;
    Lexicon *ob = new Lexicon();
    ob -> processFile("abc.txt");
    vector<string> words;
    ob -> readChapter("Chapter1.txt", words);
    ob -> readChapter("Chapter2.txt", words);
    //ob -> readChapter("")
    cout << "good" << endl;
    cout << (ob -> getRedBlackTree().getRoot() == nullptr);
    //ob -> getRedBlackTree().inorderTraversal(ob -> getRedBlackTree().getRoot(), );
    vector<IndexEntry> vec = ob -> buildIndex();
    cout << endl;
    for(auto it : vec){
       vector<pair<string, int>> v = it.getChapterWordCounts();
       cout << it.getWord() << "|";
       for(auto ite : v){
        cout << ite.first << " " << ite.second << ":";
       }
       cout << endl;
    }
    cout << "apple" << endl;
   

}
extern Lexicon lexicon;