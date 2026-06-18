#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    Node* link[26];
    bool flag;

    Node() {
        for (int i = 0; i < 26; i++) {
            link[i] = nullptr;
        }
        flag = false;
    }

    bool present(char ch) {
        return link[ch - 'a'] != nullptr;
    }

    void insert(char ch, Node* node) {
        link[ch - 'a'] = node;
    }

    Node* next(char ch) {
        return link[ch - 'a'];
    }

    void turnflag() {
        flag = true;
    }

    bool giveflag() {
        return flag;
    }
};

class Trie {
public:
    Node* root;

    Trie() {
        root = new Node();
    }

    Node* getroot() {
        return root;
    }

    void insertword(string word) {
        Node* node = root;

        for (char ch : word) {
            if (!node->present(ch)) {
                node->insert(ch, new Node());
            }
            node = node->next(ch);
        }

        node->turnflag();
    }
};

class Solution {
public:
    Trie trie;
    vector<string> ans;

    void dfs(int i, int j, vector<vector<char>>& board, Node* node, string s) {

        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() ||
            board[i][j] == '#')
            return;

        char ch = board[i][j];

        if (!node->present(ch))
            return;

        node = node->next(ch);
        s += ch;

        if (node->giveflag()) {
            ans.push_back(s);
            node->flag = false;      // prevent duplicates
        }

        board[i][j] = '#';

        dfs(i + 1, j, board, node, s);
        dfs(i - 1, j, board, node, s);
        dfs(i, j + 1, board, node, s);
        dfs(i, j - 1, board, node, s);

        board[i][j] = ch;           // backtrack
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

        for (string &word : words) {
            trie.insertword(word);
        }

        Node* root = trie.getroot();

        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dfs(i, j, board, root, "");
            }
        }

        return ans;
    }
};