#include "limine.h"

#include <stdint.h>
#include <stddef.h>

struct limine_terminal_request term_rq = {
  .id = LIMINE_TERMINAL_REQUEST,
  .revision = 0
};

void main(void) {
  struct limine_terminal_response* term = term_rq.response;
  if (term == NULL || term->terminal_count < 1)
    while (1);

  term->write(term->terminals[0], "hello world", 11);
  while (1);
}
