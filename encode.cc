#include "encode.h"

void dfs(struct Node* node, string code, unordered_map<int, string> &codes){
    if(node->currChar != '\0'){
        //cout << node->currChar << ":" << code << "\n";
        codes[node->currChar] = code;
        return;
    }
    if(node == NULL){
        return;
    }
    dfs(node->left, code + '0', codes);
    dfs(node->right, code + '1', codes);
}

struct Node* constructTree(priority_queue<struct Node*, vector<struct Node*>, cmp> &heap){
    struct Node* top;
    while(!heap.empty()){
        struct Node* currJoin = new Node(0);
        struct Node* leftNode = heap.top();
        heap.pop();
        cout << leftNode->currVal << ", ";
        struct Node* rightNode = !heap.empty() ? heap.top() : NULL;
        cout << rightNode->currVal << ", ";
        heap.pop();
        currJoin->left = leftNode;
        currJoin->right = rightNode;
        currJoin->currVal += leftNode->currVal;
        if(rightNode != NULL)
            currJoin->currVal += rightNode->currVal;
        if(!heap.empty())
            heap.push(currJoin);
        top = currJoin;
    }
    cout << endl;
    return top;
}

string encode(string toCompress){
    priority_queue<struct Node*, vector<struct Node*>, cmp> heap;
    unordered_map<int, int> charCounts;

    for(char ch : toCompress){
        charCounts[ch]++;
    }
    unordered_map<int, int>:: iterator it;
    for (it = charCounts.begin(); it != charCounts.end(); it++){
        struct Node* curr = new Node(it->second);
        curr->currVal = it->second;
        curr->currChar = it->first;
        heap.push(curr);
    }
    struct Node* eof = new Node(1);
    eof->currChar = PSEUDO_EOF;
    heap.push(eof);
    charCounts[PSEUDO_EOF] = 1;
    struct Node* top = constructTree(heap);
    unordered_map<int, string> codes;
    dfs(top, "", codes);

    string encoded = to_string(charCounts.size() - 1);
    string first = "";
    string second = "";
    for (auto pair : charCounts){
        if(pair.first == PSEUDO_EOF)
            continue;

        first += pair.first;
        second += to_string(pair.second);
        second += ",";
    }
    encoded += first;
    encoded += second;
    for(char ch : toCompress){
        encoded += codes[ch];
    }
    encoded += codes[PSEUDO_EOF];
    return encoded;
}   