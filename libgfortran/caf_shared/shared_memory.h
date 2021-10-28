/* Copyright (C) 2020 Free Software Foundation, Inc.
   Contributed by Nicolas Koenig

This file is part of the GNU Fortran Native Coarray Library (libnca).

Libnca is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

Libnca is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

/* A struct to serve as an opaque shared memory object.  */

struct shared_memory_act;
typedef struct shared_memory_act * shared_memory;

#define SHMPTR_NULL ((shared_mem_ptr) {.p = NULL})
#define SHMPTR_IS_NULL(x) (x.p == NULL)

#define SHMPTR_DEREF(x, s, sm) \
  ((x) = *(__typeof(x) *) s.p)
#define SHMPTR_AS(t, s, sm) ((t) s.p) 
#define SHMPTR_SET(v, s, sm) (v = SHMPTR_AS(__typeof(v), s, sm))
#define SHMPTR_EQUALS(s1, s2) (s1.p == s2.p)

#define SHARED_MEMORY_RAW_ALLOC(mem, t, n) \
  shared_memory_get_mem_with_alignment(mem, sizeof(t)*n, __alignof__(t))

#define SHARED_MEMORY_RAW_ALLOC_PTR(mem, t) \
  SHMPTR_AS (t *, SHARED_MEMORY_RAW_ALLOC (mem, t, 1), mem)

/* A shared-memory pointer is implemented as an offset into the shared
   memory region.  */

typedef struct shared_mem_ptr
{
  void *p;
} shared_mem_ptr;

void shared_memory_init (shared_memory *, size_t);
internal_proto (shared_memory_init);

void shared_memory_prepare (shared_memory *);
internal_proto (shared_memory_prepare);

shared_mem_ptr shared_memory_get_mem_with_alignment (shared_memory *mem,
						     size_t size, size_t align);
internal_proto (shared_memory_get_mem_with_alignment);

#endif
