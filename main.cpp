#include <bits/stdc++.h>

using namespace std;

#define ll long long

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct Node{
    int value;
    Node* next;
    Node(int _value) : value(_value), next(nullptr){}
};

struct List{
    Node* first;
    Node* last;
    int numberOfElements = 0;
    pair<Node*, int>lastPoint = make_pair(nullptr, 0);

    List() : first(nullptr), last(nullptr){}

    bool is_empty(){
        return first == nullptr;
    }

    void add(int value){
        Node* currentElement = new Node(value);
        if(is_empty()){
            first = currentElement;
            last = currentElement;
        }
        currentElement->next = first;
        last->next = currentElement;
        last = currentElement;
        numberOfElements++;
        lastPoint = make_pair(last, numberOfElements - 1);
    }

    void insert(int position, int value){
        Node* insertElement = new Node(value);
        Node* currentElement = first;
        numberOfElements++;
        if(position == 0){
            if(is_empty()){
                last = insertElement;
            }
            last->next = insertElement;
            insertElement->next = first;
            first = insertElement;
            return;
        }
        if(lastPoint.first != nullptr && lastPoint.second <= position - 2){
            currentElement = lastPoint.first;
            for (int i = lastPoint.second; i < position - 2; ++i) {
                currentElement = currentElement->next;
            }
        }
        else{
            for (int i = 0; i < position - 2; ++i) {
                currentElement = currentElement->next;
            }
        }
        lastPoint = make_pair(currentElement, position - 1);
        insertElement->next = currentElement->next;
        currentElement->next = insertElement;
        if(currentElement == last){ last = insertElement; }
    }

    void removeAt(int position){
        Node* currentElement = first;
        numberOfElements--;
        if(position == 1){
            if(first->next == first){
                clear();
                return;
            }
            first = first->next;
            last->next = first;
            delete currentElement;
            return;
        }
        if(lastPoint.first != nullptr && lastPoint.second <= position - 2){
            currentElement = lastPoint.first;
            for (int i = lastPoint.second; i < position - 2; ++i) {
                currentElement = currentElement->next;
            }
        }
        else{
            for (int i = 0; i < position - 2; ++i) {
                currentElement = currentElement->next;
            }
        }
        lastPoint = make_pair(currentElement, position - 1);
        if(currentElement->next == last){ last = currentElement; }
        Node* forDel = currentElement->next;
        currentElement->next = currentElement->next->next;
        delete forDel;
    }

    int elementAt(int position){
        Node* currentElement = first;
        if(lastPoint.first != nullptr && lastPoint.second <= position - 1){
            currentElement = lastPoint.first;
            for (int i = lastPoint.second; i < position - 1; ++i) {
                currentElement = currentElement->next;
            }
        }
        else{
            for (int i = 0; i < position - 1; ++i) {
                currentElement = currentElement->next;
            }
        }
        lastPoint = make_pair(currentElement, position - 1);
        return currentElement->value;
    }

    int count(){
        return numberOfElements;
    }

    void insertBeforeNegative(){
        if(is_empty()){ return; }
        Node* currentElement = last;
        short int cycles = 0;
        while (cycles < 2){
            if(currentElement == last){
                cycles++;
            }
            if(currentElement->next->value < 0){
                numberOfElements++;
                Node* insertElement = new Node(1);
                insertElement->next = currentElement->next;
                currentElement->next = insertElement;
                if(currentElement == last){
                    first = insertElement;
                }
                currentElement = currentElement->next;
            }
            currentElement = currentElement->next;
        }
    }

    void removeNegative(){
        if(is_empty()){ return; }
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
                    currentElement->next = first;
                    last = currentElement;
                }
                else if(currentElement->next == last){
                    currentElement->next = first;
                    last = currentElement;
                }
                else{
                    currentElement->next = currentElement->next->next;
                }
                numberOfElements--;
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
                currentElement = currentElement->next;
                continue;
            }
            if(currentElement->value == value){ valueCounter++; }
            currentElement = currentElement->next;
        }
        return valueCounter;
    }

    void clear(){
        numberOfElements = 0;
        lastPoint = make_pair(nullptr, 0);
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
    List cyclicList;
    while(1){
        string s;
        cin >> s;
        if(s == "add"){
            int currentValue;
            cin >> currentValue;
            cyclicList.add(currentValue);
        }
        else if(s == "insert"){
            int currentValue, position;
            cin >> position >> currentValue;
            cyclicList.insert(position + 1, currentValue);
        }
        else if(s == "removeAt"){
            int position;
            cin >> position;
            cyclicList.removeAt(position + 1);
        }
        else if(s == "elementAt"){
            int position;
            cin >> position;
            cout << cyclicList.elementAt(position + 1) << '\n';
        }
        else if(s == "count_elements"){
            cout << cyclicList.count() << '\n';
        }
        else if(s == "insertBeforeNegative"){
            cyclicList.insertBeforeNegative();
        }
        else if(s == "removeNegative"){
            cyclicList.removeNegative();
        }
        else if(s == "count"){
            int currentValue;
            cin >> currentValue;
            cout << cyclicList.count(currentValue) << '\n';
        }
        else if(s == "clear"){
            cyclicList.clear();
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
