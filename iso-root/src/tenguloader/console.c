#include "console.h"

static struct limine_terminal_response* term;

void term_set(struct limine_terminal_response* t) {
  term = t;
}

void term_putstr(const char* str) {
  term->write(term->terminals[0], str, strlen(str));
}
