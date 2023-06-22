#include "limine.h"

#include <stdint.h>
#include <stddef.h>

#include "string.h"
#include "console.h"

struct limine_terminal_request term_rq = {
  .id = LIMINE_TERMINAL_REQUEST,
  .revision = 0
};

struct limine_kernel_file_request k_rq = {
  .id = LIMINE_KERNEL_FILE_REQUEST,
  .revision = 0
};

void main(void) {
  struct limine_terminal_response* term = term_rq.response;
  if (term == NULL || term->terminal_count < 1)
    while (1);

  term_set(term);

  term_putstr("TenguOS Kernel Loader\n");
  while (1);
}
