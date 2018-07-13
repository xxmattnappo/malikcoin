#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <string>
using namespace std;

class Block {
private:
  string hash_block();
  string get_timestamp();
public:
  string current_block;
  int block_index;
  string timestamp;
	string data;
  string previous_block;
  int init(int index, string data, string previous_block);
  int print_block(bool spacing);
};

struct Node {
  Block *block;
  Node *next;
};

class List {
public:
  Node *head;
  List();
  ~List();
  void append(Block *block);
  Block *get_block(int index, List *list);
};

class Blockchain {
private:
  clock_t tStart = clock();
  Block *head_block = new Block;
  Block *add_block(Block last_block);
public:
  int blockchain_size;
  List *blocks = new List;
  int build(int blockchain_size, bool show_blocks);
  int export_blockchain(string blockchain_name);
  int import_blockchain(string blockchain_name, bool show_blocks);
};
#endif
