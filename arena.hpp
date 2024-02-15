#include <iostream>

using namespace std;

class ArenaAllocator {
  void* ptr = nullptr;
  size_t size = 0x0;
  size_t offset = 0x0;

  public:
    ArenaAllocator(size_t size) {
      this->ptr = malloc(size);
      this->size = size;
      this->offset = 0;
    }

    ~ArenaAllocator() {
      free(this->ptr);
    }

    void* alloc(size_t size) {
      if (this->offset + size > this->size) {
        return nullptr;
      }

      void* result = (void*)((size_t)this->ptr + this->offset);
      this->offset += size;
      return result;
    }

    void free(void* ptr) {
      // Do nothing
    }
};
