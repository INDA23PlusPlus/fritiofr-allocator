#include <iostream>

using namespace std;

class StackAllocator {
  void* ptr = nullptr;
  size_t size = 0x0;

  size_t offset_start = 0x0;
  size_t offset_end = 0x0;

  public:
    StackAllocator(size_t size) {
      this->ptr = malloc(size);
      this->size = size;
      this->offset_start = 0;
      this->offset_end = 0;
    }

    ~StackAllocator() {
      free(this->ptr);
    }

    void* alloc(size_t size) {
      if (this->offset_end + size > this->size) {
        return nullptr;
      }

      size_t temp_start = this->offset_start;
      size_t temp_end = this->offset_end;

      this->offset_start = this->offset_end;
      this->offset_end += size + sizeof(size_t) * 2;

      size_t* head = (size_t*) ((size_t) this->ptr + this->offset_start);

      head[0] = temp_start;
      head[1] = temp_end;

      return (size_t*)((size_t)this->ptr + this->offset_start + sizeof(size_t) * 2);
    }

    void free(void* ptr) {
      size_t* head = (size_t*) ((size_t) this->ptr + this->offset_start);

      this->offset_start = head[0];
      this->offset_end = head[1];
    }
};
