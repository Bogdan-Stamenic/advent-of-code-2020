#ifndef VV_ITERATOR_H
#define VV_ITERATOR_H
#include <iterator>
#include <vector>

template<typename T>
//class vv_iterator : public std::iterator_traits<std::bidirectional_iterator_tag, T>{
class vv_iterator {
public:
  static vv_iterator<T> begin(std::vector<std::vector<T>>& vv) {
    return vv_iterator(&vv, 0, 0);
  }
  static vv_iterator<T> end(std::vector<std::vector<T>>& vv) {
    return vv_iterator(&vv, vv.size(), 0);
  }
  vv_iterator() = default;
  // ++prefix operator
  vv_iterator& operator++() {
    // If we haven't reached the end of this sub-vector.
    if (idxInner + 1 < (*vv)[idxOuter].size()) {
      ++idxInner;// Go to the next element.
    } else {
      // Otherwise skip to the next sub-vector, and keep skipping over empty
      // ones until we reach a non-empty one or the end.
      do {
        ++idxOuter;
      } while (idxOuter < (*vv).size() && (*vv)[idxOuter].empty());
      idxInner = 0;// Go to the start of this vector.
    }
    return *this;
  }
  // --prefix operator
  vv_iterator& operator--() {
    // If we haven't reached the start of this sub-vector.
    if (idxInner > 0) {
      --idxInner;// Go to the previous element.
    } else {
      // Otherwise skip to the previous sub-vector, and keep skipping over empty
      // ones until we reach a non-empty one.
      do {
        --idxOuter;
      } while ((*vv)[idxOuter].empty());
      // Go to the end of this vector.
      idxInner = (*vv)[idxOuter].size() - 1;
    }
    return *this;
  }
  // postfix++ operator
  vv_iterator operator++(int) {
    auto retval = *this;
    ++(*this);
    return retval;
  }
  // postfix-- operator
  vv_iterator operator--(int) {
    auto retval = *this;
    --(*this);
    return retval;
  }
  bool operator==(const vv_iterator& other) const {return other.vv == vv && other.idxOuter == idxOuter && other.idxInner == idxInner;}
  bool operator!=(const vv_iterator &other) const {return !(*this == other);}
  const T& operator*() const {return *this;}
  T& operator*() {return (*vv)[idxOuter][idxInner];}
  const T& operator->() const {return *this;}
  T& operator->() {return *this;}

private:
  vv_iterator(std::vector<std::vector<T>>* _vv,
              std::size_t _idxOuter,
              std::size_t _idxInner)
    : vv(_vv), idxOuter(_idxOuter), idxInner(_idxInner) {}

  std::vector<std::vector<T>>* vv = nullptr;
  std::size_t idxOuter = 0;
  std::size_t idxInner = 0;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = T;
  using pointer = T*;
  using reference = T&;
};

#endif
