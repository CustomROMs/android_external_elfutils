/* Return offset of DIE.
   Copyright (C) 2003, 2005 Red Hat, Inc.
   Written by Ulrich Drepper <drepper@redhat.com>, 2003.

   This program is Open Source software; you can redistribute it and/or
   modify it under the terms of the Open Software License version 1.0 as
   published by the Open Source Initiative.

   You should have received a copy of the Open Software License along
   with this program; if not, you may obtain a copy of the Open Software
   License version 1.0 from http://www.opensource.org/licenses/osl.php or
   by writing the Open Source Initiative c/o Lawrence Rosen, Esq.,
   3001 King Ranch Road, Ukiah, CA 95482.   */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <dwarf.h>
#include "libdwP.h"


Dwarf_Off
dwarf_dieoffset (die)
     Dwarf_Die *die;
{
  return (die == NULL
	  ? ~0ul
	  : (Dwarf_Off) (die->addr
			 - die->cu->dbg->sectiondata[IDX_debug_info]->d_buf));
}
INTDEF(dwarf_dieoffset)
