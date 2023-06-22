#pragma once
#include "limine.h"

#include <stddef.h>
#include <stdint.h>
#include "string.h"

void term_set(struct limine_terminal_response*);
void term_putstr(const char*);
