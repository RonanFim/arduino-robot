#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "Arduino.h"
#include "pair.h"

#define Pointer typename
#define Distance typename
#define InputIterator typename
#define OutputIterator typename
#define ForwardIterator typename
#define RandomAccessIterator typename
#define BidirectionalIterator typename
#define Predicate typename
#define UnaryPredicate typename
#define BinaryPredicate typename
#define Function typename
#define Compare typename

// Applies function fn to each of the elements in the range [first,last)
// that pred returns true.
template <InputIterator I, Predicate P, Function F>
inline
void for_each_if(I first, I last, P pred, F fn) {
  if(first == last) return;

  I ready = find_if(first, last, pred);
  while(ready != last) {
    fn(*ready);
    ready = find_if(ready, last, pred);
  }
}

// Applies function f to each of the elements in the range [first,last).
template <InputIterator I, Function F>
inline
F for_each(I first, I last, F fn) {
  while (first != last) {
    fn(*first);
    ++first;
  }
  return fn;
}

// Returns an iterator to the first element in the range [first,last) that compares equal to val. 
// If no such element is found, the function returns last.
template <InputIterator I, typename T>
inline
I find(I first, I last, const T& value) {
  while (first != last && *first != value) ++first;
  return first;
}

// Returns an iterator to the first element in the range [first,last) for which pred returns true. 
// If no such element is found, the function returns last.
template <InputIterator I, Predicate P>
inline
I find_if(I first, I last, P pred) {
  while (first != last && !pred(*first)) ++first;
  return first;
}

// Returns an iterator to the first element in the range [first,last) for which pred returns false. 
// If no such element is found, the function returns last.
template <InputIterator I, Predicate P>
inline
I find_if_not(I first, I last, P pred) {
  while (first != last && pred(*first)) ++first;
  return first;
}

// Searches the range [first,last) for the first occurrence of two consecutive elements that match, 
// and returns an iterator to the first of these two elements, or last if no such pair is found.
template <ForwardIterator I>
inline
I adjacent_find(I first, I last) {
  if (first == last) return last;

  I next = first;
  while(++next != last) {
    if (*first == *next) return first;
    first = next;
  }
  return last;
}

template <ForwardIterator I, BinaryPredicate P>
inline
I adjacent_find(I first, I last, P binary_pred) {
  if (first == last) return last;
  
  I next = first;
  while(++next != last) {
    if (binary_pred(*first, *next)) return first;
    first = next;
  }
  return last;
}

// Returns the number of elements in the range [first,last) that compare equal to val.
template <InputIterator I, typename T, typename Size>
void count(I first, I last, const T& value, Size& n) {
  while (first != last) 
  if (*first++ == value) ++n;
}

// Returns the number of elements in the range [first,last) for which pred is true.
template <InputIterator I, Predicate P, typename Size>
void count_if(I first, I last, P pred, Size& n) {
  while (first != last)
  if (pred(*first++)) ++n;
}

// Exchanges the values of a and b.
template <typename T>
inline
void swap(T& a, T& b) {
  T c(a); a=b; b=c;
}

// Exchange values of objects pointed by two iterators
template <ForwardIterator I, ForwardIterator J>
inline
void iter_swap(I a, J b) {
  swap(*a, *b);
}

// Exchanges the values of each of the elements in the range [first1,last1) 
// with those of their respective elements in the range beginning at first2.
template <ForwardIterator I, ForwardIterator J>
inline
J swap_ranges(I first1, I last1, J first2) {
  while (first1 != last1) iter_swap(first1++, first2++);
  return first2;
}

// Applies an operation sequentially to the elements of one (1) or two (2) 
// ranges and stores the result in the range that begins at result.
template <InputIterator I, OutputIterator J, typename UnaryOperation>
inline
J transform(I first, I last, J result, UnaryOperation op) {
  while (first != last) *result++ = op(*first++);
  return result;
}

template <InputIterator I, InputIterator J, OutputIterator K, typename BinaryOperation>
inline
K transform(I first1, I last1, J first2, K result, BinaryOperation binary_op) {
  while (first1 != last1) *result++ = binary_op(*first1++, *first2++);
  return result;
}

// Print elements on the range
template <ForwardIterator I, typename StreamObject>
inline
void print_range(I first, I last, StreamObject out) {
  while (first != last) {
    out.print(*first);
    out.print(" ");
    ++first;
  }
  out.print("\n");
}

// Assigns new_value to all the elements in the range [first,last) that compare equal to old_value.
template <ForwardIterator I, typename T>
inline
void replace(I first, I last, const T& old_value, const T& new_value) {
  while (first != last) {
    if (*first == old_value) *first = new_value;
    ++first;
  }
}

// Assigns new_value to all the elements in the range [first,last) for which pred returns true.
template <ForwardIterator I, Predicate P, typename T>
inline
void replace_if(I first, I last, P pred, const T& new_value) {
  while (first != last) {
  if (pred(*first)) *first = new_value;
    ++first;
  }
}

// Rearranges the elements from the range [first,last), in such a way that all the elements 
// for which pred returns true precede all those for which it returns false. 
// The iterator returned points to the first element of the second group.
template <BidirectionalIterator I, UnaryPredicate P>
inline
I partition(I first, I last, P p) {
  while (1) {
	  while ((first != last) && p(*first)) {
	    ++first;
	  }
	  if (first == last--) break;
	  while ((first != last) && !p(*last)) {
	    --last;
	  }
	  if (first == last) break;
	  iter_swap(first++, last);
  }
  return first;
}

// Rotates the order of the elements in the range [first,last), in such a way that the 
// element pointed by middle becomes the new first element.
template <ForwardIterator I>
inline
void rotate(I first, I middle, I last)
{
  I next = middle;
  while (first!=next)
  {
    swap(*first++,*next++);
    if (next==last) next=middle;
    else if (first==middle) middle=next;
  }
}

template <RandomAccessIterator I>
inline
void slide(I first, I last, I position) {
  if (position < first) rotate(position,first,last);
  if (last < position) rotate(first,last,position);
}

// Returns an iterator pointing to the element with the largest value in the range [first,last).
template <ForwardIterator I>
I max_element(I first, I last) {
  if (first == last) return first;

  I result = first;
  while (++first != last) 
    if (*result < *first) result = first;
  return result;
}

// Returns an iterator pointing to the element with the largest value in the range [first,last).
template <ForwardIterator I, Compare Cmp>
I max_element(I first, I last, Cmp comp) {
  if (first == last) return first;
  
  I result = first;
  while (++first != last) 
    if (comp(*result, *first)) result = first;
  return result;
}

// Returns an iterator pointing to the element with the smallest value in the range [first,last).
template <ForwardIterator I>
I min_element(I first, I last) {
  if (first == last) return first;
  
  I result = first;
  while (++first != last) 
    if (*first < *result) result = first;
  return result;
}

// Returns an iterator pointing to the element with the smallest value in the range [first,last).
template <ForwardIterator I, Compare Cmp>
I min_element(I first, I last, Cmp comp) {
  if (first == last) return first;
  
  I result = first;
  while (++first != last) 
    if (comp(*first, *result)) result = first;
  return result;
}

// Returns the result of accumulating all the values in the range [first,last) to init.
template <InputIterator I, typename T>
T accumulate(I first, I last, T init) {
  while (first != last) init = init + *first++;
  return init;
}

// Returns the result of accumulating init with the inner products of the pairs formed 
// by the elements of two ranges starting at first1 and first2.
template <InputIterator I, InputIterator J, typename T>
T inner_product(I first1, I last1, J first2, T init) {
  while (first1 != last1) init = init + (*first1++ * *first2++);
  return init;
}

// Store increasing sequence
// Assigns to every element in the range [first,last) successive values of val, 
// as if incremented with ++val after each element is written.
template <ForwardIterator I, typename T>
void iota(I first, I last, T value) {
  while (first != last) *first++ = value++;
}

template <Pointer I>
I adjacent3_find(I first, I last) {

}

#endif