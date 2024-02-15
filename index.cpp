#include "arena.hpp"
#include "stack.hpp"

void arena_example() {
  ArenaAllocator allocator(0x1000);

  int* ptr1 = (int*) allocator.alloc(4);
}

void stack_example() {
  StackAllocator allocator(0x1000);

  int* ptr1 = (int*) allocator.alloc(4);
}

int main() {
  arena_example();
  stack_example();

  return 0;
}
