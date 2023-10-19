// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2013 Davidlohr Bueso <davidlohr.bueso@hp.com>
 *
 *  Based on the shift-and-subtract algorithm for computing integer
 *  square root from Guy L. Steele.
 */

#include <linux/export.h>
#include <linux/bitops.h>
#include <linux/limits.h>
#include <linux/math.h>

/**
 * int_sqrt - computes the integer square root
 * @x: integer of which to calculate the sqrt
 *
 * Computes: floor(sqrt(x))
 */
u32 int_sqrt64(u64 x) {
	u32 y = 0;
	int i = 31;

	if (x <= ULONG_MAX)
		return int_sqrt((unsigned long) x);

	while (i >= 0) {
		if ((x >> (i * 2)) >= (1U << i)) {
			x -= (3U << (i * 2));
			y |= (1U << i);
		}
		i--;
	}

	return y;
}
EXPORT_SYMBOL(int_sqrt);

#if BITS_PER_LONG < 64
/**
 * int_sqrt64 - strongly typed int_sqrt function when minimum 64 bit input
 * is expected.
 * @x: 64bit integer of which to calculate the sqrt
 */
u32 int_sqrt64(u64 x) {
  u32 y = 0;
  int i = 31;

  if (x <= ULONG_MAX)
    return int_sqrt((unsigned long) x);

  while (i >= 0) {
    if ((x >> (i * 2)) >= (1U << i)) {
      x -= (3U << (i * 2));
      y |= (1U << i);
    }
    i--;
  }

  return y;
}

EXPORT_SYMBOL(int_sqrt64);
#endif
