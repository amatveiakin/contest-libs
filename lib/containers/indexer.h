// Indexer allows to:
//   - assign numeric indices to values of any type, and
//   - map values to indices and vice versa.

#pragma once

#include <cassert>
#include <vector>
#include <unordered_map>


template<typename ValueT>
class Indexer {
public:
  int size() const {
    return index_to_value_.size();
  }

  std::pair<int, bool> insert(const ValueT& value__) {
    int new_index = int(index_to_value_.size());
    auto res = value_to_index_.insert({value__, new_index});
    if (!res.second)
      return {res.first->second, false};
    index_to_value_.push_back(value__);
    return {new_index, true};
  }

  int insert_new(const ValueT& value__) {
    auto result = insert(value__);
    assert(result.second);
    return result.first;
  }

  bool has_value(const ValueT& value__) const {
    return value_to_index_.count(value__) > 0;
  }

  int index(const ValueT& value__) const {
    return value_to_index_.at(value__);
  }

  const ValueT& value(int index__) const {
    return index_to_value_.at(index__);
  }

private:
  std::vector<ValueT> index_to_value_;
  std::unordered_map<ValueT, int> value_to_index_;
};