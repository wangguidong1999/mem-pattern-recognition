//Author: Lixiang

#ifndef TRACE_LIST_H
#define TRACE_LIST_H

#include <assert.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>

#include "instruction.h"
#include "pattern.h"
#include "pc_meta.h"

// #define DEBUG_HISTORY
#define ENABLE_TIMER

#ifdef ENABLE_TIMER
#include <chrono>
#endif

class TraceList {
  struct TraceNode {  // Single Memory Access
    unsigned long long int pc;
    unsigned long long int addr;
    unsigned long long int value;
    bool isWrite;
    unsigned long long int id;
    TraceNode() {}
    TraceNode(unsigned long long int _p, unsigned long long int _a,
              unsigned long long int _v, bool _i, unsigned long long int _id)
        : pc(_p), addr(_a), value(_v), isWrite(_i), id(_id) {}
    void __debug() { std::cerr << std::hex << (pc << 1) << std::endl; }
  };

  std::unordered_map<unsigned long long int, std::deque<TraceNode>> value2trace;
  std::deque<TraceNode> traceHistory;

  unsigned long long int pattern_count[PATTERN_NUM];
  std::unordered_map<unsigned long long int, PCmeta> pc2meta;
#ifdef ENABLE_TIMER
  unsigned long long int total_time;
#endif
  std::unordered_map<unsigned long long int, unsigned long long int> region_cnt;
#ifndef ENABLE_HOTREGION_V1
  std::unordered_map<unsigned long long int, unsigned long long int> region_ht;
  std::set<unsigned long long int> hot_region_list;
#endif
  bool enable_hotregion_;
  unsigned long long hot_region_size;

  std::ofstream out;

  void erase_before(std::deque<TraceNode> &L, const unsigned long long int &id);
  void add_next(std::deque<TraceNode> &L, TraceNode tn);

  bool check_static_pattern(
      std::unordered_map<unsigned long long int, PCmeta>::iterator &it_meta,
      unsigned long long int &addr, unsigned long long int &value);
  bool check_stride_pattern(
      std::unordered_map<unsigned long long int, PCmeta>::iterator &it_meta,
      unsigned long long int &addr);
  bool check_pointer_pattern(
      std::unordered_map<unsigned long long int, PCmeta>::iterator &it_meta,
      std::unordered_map<unsigned long long int,
                         std::deque<TraceNode>>::iterator &it_val);
  bool check_pointerA_pattern(
      std::unordered_map<unsigned long long int, PCmeta>::iterator &it_meta,
      unsigned long long int &addr, unsigned long long int &value,
      bool &isWrite);
  bool check_pointerB_pattern(
      std::unordered_map<unsigned long long int, PCmeta>::iterator &it_meta);
  bool check_indirect_pattern(
      std::unordered_map<unsigned long long int, PCmeta>::iterator &it_meta,
      unsigned long long int &addr);
  bool check_struct_pointer_pattern(
      std::unordered_map<unsigned long long int, PCmeta>::iterator &it_meta,
      unsigned long long int &addr);
  bool check_locality_pattern(
      std::unordered_map<unsigned long long int, PCmeta>::iterator &it_meta,
      unsigned long long int &addr);
  bool check_random_pattern(
      std::unordered_map<unsigned long long int, PCmeta>::iterator &it_meta,
      unsigned long long int &addr);
  void check_hot_region(unsigned long long int &region_id,
                        const unsigned long long &inst_id);

 public:
  TraceList(unsigned long long hr_size = 0, bool enable_hotregion = false) {
    for (int i = 0; i < PATTERN_NUM; i++) pattern_count[i] = 0;
#ifdef ENABLE_TIMER
    total_time = 0;
#endif
    enable_hotregion_ = enable_hotregion;
    hot_region_size = hr_size;
  }
  TraceList(const char filename[], unsigned long long hr_size = 0,
            bool enable_hotregion = false) {
    std::ifstream in(filename);
    unsigned long long pc;
    pc2meta = std::unordered_map<unsigned long long, PCmeta>();
    while (in >> std::hex >> pc) {
      pc2meta[pc] = PCmeta();
      pc2meta[pc].input(in);
    }
    TraceList(hr_size, enable_hotregion);
  }
  void add_outfile(const char filename[]) {
    out.open(filename);
    assert(out);
  }
  void add_trace(unsigned long long int pc, unsigned long long int addr,
                 unsigned long long int value, bool isWrite,
                 unsigned long long int &id, const unsigned long long inst_id);
  void printStats(unsigned long long totalCnt, const char filename[],
                  const char hot_region_file[] = "");

  void merge(std::string input_dir, std::string id,
             unsigned long long &inst_id);
};

void add_trace(TraceList &traceList, unsigned long long &id,
               unsigned long long int ip, MemRecord &r, bool isWrite,
               const int inst_id);

#endif