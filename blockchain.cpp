#include "blockchain.h"
#include "json/json.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

clock_t tStart = clock();

Block *Blockchain::next_block(Block *last_block) {
  int _index = last_block->index + 1;
  string _data = "This is block #" + to_string(_index);
  string _previous_hash = last_block->this_hash;
  Block *new_block = new Block;
  new_block->init(_index, _data, _previous_hash);
  return new_block;
}

Block *Blockchain::build_genesis() {
  Block *block = new Block;
  block->init(0, "HEAD BLOCK", "NO PREVIOUS BLOCK");
  return block;
}

int Blockchain::build(int blockchain_size, bool show_blocks) {
  this->blockchain_size = blockchain_size;
  this->blocks->append(build_genesis());
  if (show_blocks) { this->blocks->get_block(0, this->blocks)->print_block(true); }
  cout << "\033[1;32mHEAD BLOCK";
  cout << "\033[0;32m has been added to the blockchain.\033[0m\n";
  Block *previous_block = this->blocks->get_block(0, this->blocks);
  for (int i = 0; i < blockchain_size; i++) {
    Block *block_to_add = next_block(previous_block);
    this->blocks->append(block_to_add);
    if (show_blocks) { block_to_add->print_block(true); }
    previous_block = block_to_add;
    cout << "\033[1;32mBlock #"<< block_to_add->index;
    cout << "\033[0;32m has been added to the blockchain.\033[0m\n";
  }
  cout << "\n\033[0;32mBlockchain with \033[1;32m" << this->blockchain_size << "\033[0;32m blocks built in ";
  printf("\033[1;32m%.2f seconds.\033[0m\n", (double)(clock() - this->tStart)/CLOCKS_PER_SEC);
  return 0;
}

int Blockchain::export_blockchain(string blockchain_name) {
  json blockchain;
  blockchain["blocks"] = { };
  for (int i = 0; i < this->blockchain_size + 1; i++) {
    blockchain["blocks"][i] = { };
    Block *block = this->blocks->get_block(i, this->blocks);
    blockchain["blocks"][i]["index"] = block->index;
    blockchain["blocks"][i]["timestamp"] = block->timestamp;
    blockchain["blocks"][i]["data"] = block->data;
    blockchain["blocks"][i]["previous_hash"] = block->previous_hash;
    blockchain["blocks"][i]["hash"] = block->this_hash;
  }
  string filename = "blockchains/" + blockchain_name + ".json";
  ofstream o(filename);
  o << setw(4) << blockchain << endl;
  o.close();
  cout << "\033[0;32mCurrent blockchain exported to \033[1;32m" << filename << ".\033[0m" << endl;
  return 0;
}

int Blockchain::check(Block block_1, Block block_2) {
  // 1. Check if indexs match up

  // 3. Check if  block1.hash == hash of block2.previous

  // 2. Hash block1 as HASH. check if HASH == block1.this_block. check if HASH == block2.previous
  return 0;
}

int Blockchain::validate() {
  cout << endl << "Starting validation process." << endl;

  Block *block_1 = new Block;
  for (int i = 0; i < blockchain_size; i++) {

  }
  // validate();
  return 0;
}

int Blockchain::import_blockchain(string blockchain_name, bool show_blocks) {
  string filename = "blockchains/" + blockchain_name + ".json";
  ifstream ifs(filename);
  json blockchain = json::parse(ifs);
  this->blockchain_size = blockchain["blocks"].size();

  for (int i = 0; i < this->blockchain_size; i++) {
    Block *block_to_add = new Block;
    int _index = blockchain["blocks"][i]["index"];
    string _data = blockchain["blocks"][i]["data"];
    string _previous_hash = blockchain["blocks"][i]["previous_hash"];
    string _timestamp = blockchain["blocks"][i]["timestamp"];
    string _this_hash = blockchain["blocks"][i]["hash"];
    block_to_add->init(_index, _data, _previous_hash, true, _timestamp, _this_hash);
    this->blocks->append(block_to_add);

    if (show_blocks) { block_to_add->print_block(true); }
    cout << "\033[1;32mBlock #"<< block_to_add->index;
    cout << "\033[0;32m has been added to the blockchain.\033[0m\n";
  }

  cout << "\n\033[0;32mBlockchain with \033[1;32m" << this->blockchain_size - 1 << "\033[0;32m blocks imported in ";
  printf("\033[1;32m%.2f seconds.\033[0m\n", (double)(clock() - this->tStart)/CLOCKS_PER_SEC);
  validate();
}
