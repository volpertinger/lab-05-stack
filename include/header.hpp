// Copyright 2020 Merzlov Nikolay merzlovnik@mail.ru

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <utility>

template <typename T>
class Stack {
 private:
  struct Node {
    T value;
    Node* previous;
  };
  std::size_t size_;
  Node* head_;

 public:
  Stack();
  Stack(Stack const& stack) = delete;
  Stack& operator=(Stack const& stack) = delete;
  Stack(Stack&& stack) noexcept;
  Stack& operator=(Stack&& stack) noexcept;
  ~Stack();

  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;

  template <typename... Args>
  void push_emplace(Args&&... value);

  bool empty();
  size_t size();
};

template <typename T>
Stack<T>::Stack() : size_(0), head_(nullptr) {}

template <typename T>
Stack<T>::~Stack() {
  auto top = head_;
  while (top != nullptr) {
    auto next = top->previous;
    delete top;
    top = next;
  }
}

template <typename T>
Stack<T>::Stack(Stack&& stack) noexcept
    : size_(std::exchange(stack.size_, 0)),
      head_(std::exchange(stack.head_, nullptr)) {}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& stack) noexcept {
  if (&stack != this) {
    std::swap(size_, stack.size_);
    std::swap(head_, stack.head_);
  }
  return *this;
}

template <typename T>
bool Stack<T>::empty() {
  return size_ == 0;
}

template <typename T>
size_t Stack<T>::size() {
  return size_;
}

template <typename T>
const T& Stack<T>::head() const {
  auto const head = head_;
  if (head == nullptr)
    throw ::std::out_of_range("can`t call head(), because stack is empty");
  return head_->value;
}

template <typename T>
void Stack<T>::push(const T& value) {
  static_assert(std::is_copy_constructible<T>::value);
  head_ = new Node{value, head_};
  ++size_;
}

template <typename T>
void Stack<T>::push(T&& value) {
  static_assert(std::is_move_constructible<T>::value);
  head_ = new Node{std::move(value), head_};
  ++size_;
}

template <typename T>
template <typename... Args_T>
void Stack<T>::push_emplace(Args_T&&... value) {
  head_ = new Node{T{std::forward<Args_T>(value)...}, head_};
  ++size_;
}

template <typename T>
void Stack<T>::pop() {
  auto const old_head = head_;
  if (old_head == nullptr) return;

  auto new_head = old_head->previous;
  if (new_head == nullptr) {
    head_ = nullptr;
    size_ = 0;
  } else {
    head_ = new_head;
    --size_;
  }
  delete old_head;
}

#endif  // INCLUDE_HEADER_HPP_
