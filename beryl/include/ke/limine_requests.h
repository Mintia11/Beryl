#ifndef BERYL_KE_LIMINE_REQUESTS_H
#define BERYL_KE_LIMINE_REQUESTS_H

#include <beryl.h>
#include <limine.h>

#define LIMINE_REQUEST USED SECTION(".requests") static volatile

USED SECTION(".requests_start_marker") static volatile LIMINE_REQUESTS_START_MARKER;
USED SECTION(".requests_end_marker") static volatile LIMINE_REQUESTS_END_MARKER;

LIMINE_REQUEST LIMINE_BASE_REVISION(2);

#endif