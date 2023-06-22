#include "limine.h"

#include <stddef.h>
#include <stdint.h>

struct limine_framebuffer_request fb_rq = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};

void main(void) {
  struct limine_framebuffer_response* fb_res = fb_rq.response;
  if (fb_res == NULL || fb_res->framebuffer_count < 1)
    while (1);

  //Just fill the screen for now. Will add more useful stuff later.
  struct limine_framebuffer* fb = fb_res->framebuffers[0];
  for (size_t x = 0; x < fb->width; x++)
    for (size_t y = 0; y < fb->height; y++) {
      uint32_t* pixel = fb->address;
      pixel[x + fb->pitch/4 * y] = 0xBBBBFF;
    }

  while (1);
}
