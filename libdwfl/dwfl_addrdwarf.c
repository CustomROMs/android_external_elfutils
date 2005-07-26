/* Fetch libdw handle from address.
   Copyright (C) 2005 Red Hat, Inc.

   This program is Open Source software; you can redistribute it and/or
   modify it under the terms of the Open Software License version 1.0 as
   published by the Open Source Initiative.

   You should have received a copy of the Open Software License along
   with this program; if not, you may obtain a copy of the Open Software
   License version 1.0 from http://www.opensource.org/licenses/osl.php or
   by writing the Open Source Initiative c/o Lawrence Rosen, Esq.,
   3001 King Ranch Road, Ukiah, CA 95482.   */

#include "libdwflP.h"

Dwarf *
dwfl_addrdwarf (Dwfl *dwfl, Dwarf_Addr address, Dwarf_Addr *bias)
{
  return INTUSE(dwfl_module_getdwarf) (INTUSE(dwfl_addrmodule) (dwfl, address),
				       bias);
}
INTDEF (dwfl_addrdwarf)
