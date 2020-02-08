#ifndef __CKSUM_H__
#define __CKSUM_H__

#include <stdio.h>
#include <inttypes.h>

uint32_t cksum(FILE *fp, const char *filename);

#endif