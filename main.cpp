#include <bits/stdc++.h>

using namespace std;

#define ll long long

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct Node{
    int value;
    Node* next;
    Node(int _value) : value(_value), next(nullptr){}
};

struct CyclicList{
    Node* first;
    Node* last;

    CyclicList() : first(nullptr), last(nullptr){}

    bool is_empty(){
        return first == nullptr;
    }

    void add(int value){
        Node* currentElement = new Node(value);
        if(is_empty()){
            first = currentElement;
        }
        currentElement->next = first;
        last->next = currentElement;
        last = currentElement;
    }

    void insert(int position, int value){
        Node* insertElement = new Node(value);
        Node* currentElement = first;
        if(position == 0){
            if(is_empty()){
                last = insertElement;
            }
            last->next = insertElement;
            insertElement->next = first;
            first = insertElement;
            return;
        }
        for (int i = 0; i < position - 1; ++i) {
            currentElement = currentElement->next;
        }
        insertElement->next = currentElement->next;
        currentElement->next = insertElement;
        if(currentElement == last){ last = insertElement; }
    }

    void removeAt(int position){
        Node* currentElement = first;
        if(position == 0){
            if(first->next == first){
                clear();
                return;
            }
            first = first->next;
            last->next = first;
            delete currentElement;
            return;
        }
        for (int i = 0; i < position - 1; ++i) {
            currentElement = currentElement->next;
        }
        if(currentElement->next == last){ last = currentElement; }
        Node* forDel = currentElement->next;
        currentElement->next = currentElement->next->next;
        delete forDel;
    }

    int elementAt(int position){
        Node* currentElement = first;
        for (int i = 0; i < position; ++i) {
            currentElement = currentElement->next;
        }
        return currentElement->value;
    }

    void insertBeforeNegative(){
        Node* currentElement = last;
        short int cycles = 0;
        while (cycles < 2){
            if(currentElement->next->value < 0){
                Node* insertElement = new Node(1);
                insertElement->next = currentElement->next->next;
                currentElement->next = insertElement;
                if(currentElement == last){
                    last = insertElement;
                }
            }
            if(currentElement == last){
                cycles++;
            }
            currentElement = currentElement->next;
        }
    }

    void removeNegative(){
        Node* currentElement = last;
        short int cycles = 0;
        while (cycles < 2){
            if(currentElement->next->value < 0){
                Node* forDel = currentElement->next;
                if(currentElement->next == first){
                    if(first->next == first){
                        clear();
                        return;
                    }
                    first = first->next;
                    last->next = first;
                }
                else if(currentElement->next == last){
                    last = currentElement;
                    currentElement->next = first;

                }
                else{
                    currentElement->next = currentElement->next->next;
                }
                delete forDel;
            }
            currentElement = currentElement->next;
            if(currentElement == last){
                cycles++;
            }
        }
    }

    int count(int value){
        if(is_empty()){
            return 0;
        }
        int valueCounter = 0;
        Node* currentElement = first;
        short int cycles = 0;
        if(first->value == value){ valueCounter++; }
        while (cycles < 2){
            if(currentElement == first){
                cycles++;
                continue;
            }
            if(currentElement->value == value){ valueCounter++; }
            currentElement = currentElement->next;
        }
        return valueCounter;
    }

    void clear(){
        if(is_empty()){
            return;
        }
        Node* currentElement = first;
        while(currentElement != last){
            Node* forDel = currentElement;
            currentElement = currentElement->next;
            delete forDel;
        }
        delete currentElement;
        first = nullptr;
        last = nullptr;
    }
};

int main(int argc, char *argv[]){
    //ios_base::sync_with_stdio(0);
    //cin.tie(0); cout.tie(0);
    CyclicList list;
    while(1){
        string s;
        cin >> s;
        if(s == "add"){
            int currentValue;
            cin >> currentValue;
            list.add(currentValue);
        }
        else if(s == "insert"){
            int currentValue, position;
            cin >> position >> currentValue;
            list.insert(position, currentValue);
        }
        else if(s == "removeAt"){
            int position;
            cin >> position;
            list.removeAt(position);
        }
        else if(s == "elementAt"){
            int position;
            cin >> position;
            list.elementAt(position);
        }
        else if(s == "insertBeforeNegative"){
            list.insertBeforeNegative();
        }
        else if(s == "removeNegative"){
            list.removeNegative();
        }
        else if(s == "count"){
            int currentValue;
            cin >> currentValue;
            cout << list.count(currentValue) << '\n';
        }
        else if(s == "clear"){
            list.clear();
        }
        else if(s == "stop"){
            break;
        }
        else{
            cout << "unknown command\n";
        }
    }
    return 0;
}
