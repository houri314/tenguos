#include <boot/limine.h>

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

struct limine_bootloader_info_request bl_rq = {
  .id = LIMINE_BOOTLOADER_INFO_REQUEST,
  .revision = 0
};

void main(void) {
  struct limine_terminal_response* term = term_rq.response;
  if (term == NULL || term->terminal_count < 1)
    while (1);

  struct limine_file* kern = k_rq.response->kernel_file;
  if (term == NULL || term->terminal_count < 1)
    while (1);

  term_set(term);

  char tmp[50];
  strcpy(tmp, "File: ");
  strcpy(tmp, kern->path);
  term_putstr(tmp);
  term_putstr("\n");

  strcpy(tmp, "Params: ");
  strcat(tmp, kern->cmdline);
  term_putstr(tmp);
  term_putstr("\n");

  while (1);
}
