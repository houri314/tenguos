#include "limine.h"

#include <stddef.h>
#include <stdint.h>

//Request stuff if tenguloader is disabled.
#ifdef TENGU6_STANDALONE
struct limine_framebuffer_request fb_rq = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};
#endif

//Info struct. tenguloader requests info and pass it to kernel, or the kernel
// gets them itself if required.
typedef struct tengu6_info {
  struct limine_framebuffer_response* framebuffer;
  struct limine_memmap_response* memmap;
} tengu6_info;

#ifdef TENGU6_STANDALONE
void main(tengu6_info tengu6) {
#else
void main(void) {
  tengu6_info tengu6 = {0};
#endif

  //Initializing the machine info struct if tenguloader disabled.
#ifdef TENGU6_STANDALONE
  if (fb_rq.response == NULL || fb_rq.response->framebuffer_count < 1)
    while (1);
  tengu6.framebuffer = fb_rq.response;
#endif

  //Just fill the screen for now. Will add more useful stuff later.
  struct limine_framebuffer* fb = tengu6.framebuffer->framebuffers[0];
  for (size_t x = 0; x < fb->width; x++)
    for (size_t y = 0; y < fb->height; y++) {
      uint32_t* pixel = fb->address;
      pixel[x + fb->pitch/4 * y] = 0xBBBBFF;
    }

  while (1);
}
