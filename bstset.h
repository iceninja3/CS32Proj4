#ifndef bstset_h
#define bstset_h
#include <iostream>
using namespace std;
//clang++ -std=c++17 testBST.cpp -o main && ./main


//remove below
#include <ctime>
#include <sstream>
#include <iomanip>
std::string forma_time(int unix_time)
{
    std::time_t time = unix_time;
    std::tm* tm_ptr = std::gmtime(&time);
    std::ostringstream oss;
    oss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M UTC (") << unix_time << ")";
    return oss.str();
} // TODO REMOVE

template <typename T>
class BSTSet{
    private:
    
        struct Node{
            T data;
            Node* left;
            Node* right;
            Node* parent;
            Node (const T& value) : data(value), left(nullptr), right(nullptr), parent(nullptr){}
        };
        Node* root;

        // void print_tree_recursive(Node* node, int depth) const {
        //     if (node == nullptr) {
        //         return;
        //     }
            
        //     // Print right subtree
        //     print_tree_recursive(node->right, depth + 1);
            
        //     // Print current node with indentation
        //     for (int i = 0; i < depth; i++) {
        //         cout << "    ";
        //     }
            
        //     // Print node data
        //     const FlightSegment* flight = static_cast<const FlightSegment*>(&node->data);
        //     cout << flight->airline << " " << flight->flight_no 
        //          << " from " << flight->source_airport << " to " << flight->destination_airport
        //          << " (Departure: " << forma_time(flight->departure_time) << ")" << endl;
            
        //     // Print left subtree
        //     print_tree_recursive(node->left, depth + 1);
        // } // TODO REMOVE CERR 

        

        Node* insert(Node* node, const T& value) {
            //size++; //TODO: REMOVE
            // Helper function to insert a value into the BST
            if (node==nullptr) {
                //cerr << "Inserting " << node->data << endl; // TODO REMOVE
                return new Node(value);
            }

            if (value < node->data) {
                //cerr << "node inserted on left" <<endl;
                //cerr << "Going left from " << node->data << " for " << value << endl; //TODO REMOVE
                Node* leftChild = insert(node->left, value);
                node->left = leftChild;
                leftChild->parent = node;
            } else if (value > node->data) {
                //cerr << "node inserted on right" <<endl;
                //cerr << "Going right from " << node->data << " for " << value << endl; // TODO REMOVE
                Node* rightChild = insert(node->right, value);
                node->right = rightChild;
                rightChild->parent = node;
            } else {
                //cerr << "previous node found " <<endl;
                //return node; //delete this we need to replace the node if equal
                
                node->data = value;


                // Node* newNode = new Node(value);
                // newNode->left = node->left;
                // newNode->right = node->right;
                // newNode->parent = node->parent;

                
                // // // Update children's parent pointers
                // if (newNode->left) newNode->left->parent = newNode;
                // if (newNode->right) newNode->right->parent = newNode;
                
                // // Update parent's child pointer
                // if (newNode->parent) {
                //     if (newNode->parent->left == node) {
                //         newNode->parent->left = newNode;
                //     } else {
                //         newNode->parent->right = newNode;
                //     }
                // }
                
                // delete node;
                // return newNode;
            }

            //cerr << node->data;
            return node;
        }

        Node* find(Node* node, const T& value) const{
            if(node==nullptr){
                return nullptr;
            }

            if(value < node->data){
                return find(node->left, value);
            }
            else if(value > node->data){
                return find(node->right, value);
            }
            else{ //value = node->value
                return node;
            }
        } //end helper function to find node

        Node* find_first_not_smaller(Node* node, const T& value) const{ //i think this is right?
            //finding smallest node larger than node
            //we're basically going right till we find a value larger than value and then left to the end of the tree

            Node* result = nullptr;
    
            while (node != nullptr) {
                if (value < node->data || value == node->data) {
                    // Current node is >= value, it's a candidate
                    result = node;
                    node = node->left; // Look for a smaller candidate
                } else {
                    // Current node is < value, look for larger values
                    node = node->right;
                }
            }
            
            return result;



            // Node* nodeToReturn = nullptr;
            // while(node!=nullptr){
            //     if(node->data<value){ //if current node is less than value
            //         node=node->right; //go right
            //         if(node==nullptr){
            //             cerr << "right was null" <<endl;
            //         }
            //     }
            //     else{ //if current node greater than or equal to value
            //         nodeToReturn = node;
            //         node=node->left;
            //         if(node==nullptr){
            //             cerr << "left was null" <<endl;
            //         }
            //     }
            // }
            // return nodeToReturn;
        }

        void deleteTree(Node* rootNode){
            if(rootNode == nullptr)
                return;
            deleteTree(rootNode->left);
            deleteTree(rootNode->right);
            delete rootNode;
        }




public:

// void print_tree() const {
//     cout << "Printing BST contents:" << endl;
//     print_tree_recursive(root, 0);
//     cout << "End of BST" << endl;
// } // TODO REMOVE CERR

    BSTSet() : root(nullptr) {}   //initialize empty BST Set
    ~BSTSet(){
        deleteTree(root);
        root = nullptr;
        //release internal sources
    }

    void insert(const T& value){
       root = insert(root, value); //TODO FIX ERROR BAD
    }


    class SetIterator{    
        public:
            SetIterator(Node* node) : current(node){};
            //add some sort of constructor
            //add some sort of destructor

            const T* get_and_advance() {
                // if(current == nullptr)
                //     return nullptr;
                    
                // T* temp = &(current->data);
                // if(current->right != nullptr)
                // {
                //     current = current->right;
                //     while(current->left != nullptr)
                //         current = current->left;
                //     return temp;
                // }
                
                // while(current->parent != nullptr && current->parent->right != nullptr && current->parent->right == current)
                // {
                //     current = current->parent;
                // }
                // if(current->parent == nullptr)
                // {
                //     current = nullptr;
                //     return temp;
                // }
                // current = current->parent;
                // return temp;
                    //old---new
                if (current==nullptr){
                    cerr << "returning a nullptr because there's nothing here!" <<endl;
                    return nullptr;
                } 
               
                const T* value = &current->data;
                current = successor(current);
                // if(current==nullptr){
                //     cerr << "current is nullptr" <<endl;
                // }
                return value;
            } // TODO ERROR BAD
        
            private:
            Node* current;


            Node* successor(Node* node) {
                if(node == nullptr){
                    return nullptr;
                } //added this in TODO

                if (node->right != nullptr) {
                    return min_node(node->right);
                }

                Node* parent = node->parent;
                while (parent && node == parent->right){
                    node = parent;
                    parent = parent->parent;
                }
                return parent;
            }

            Node* min_node(Node* node) { //finding minimum node in tree by going left repeatedly until nullptr reached
                while ((node != nullptr) && (node->left != nullptr)) {
                    node = node->left;
                }
                return node;
            }

    }; //end SetIterator class


    SetIterator find(const T& value) const{
        return(SetIterator(find(root, value)));
    }

    SetIterator find_first_not_smaller(const T& value) const{
        return SetIterator(find_first_not_smaller(root, value));
    }
};


#endif
