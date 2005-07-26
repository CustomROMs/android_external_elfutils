/* Helper functions for form handling.
   Copyright (C) 2000, 2002 Red Hat, Inc.
   Written by Ulrich Drepper <drepper@redhat.com>, 2000.

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
#include <string.h>

#include <libdwarfP.h>


int
internal_function
__libdwarf_form_val_len (Dwarf_Debug dbg, Dwarf_CU_Info cu, Dwarf_Word form,
			 Dwarf_Small *valp, size_t *len, Dwarf_Error *error)
{
  Dwarf_Small *saved;
  Dwarf_Word u128;

  switch (form)
    {
    case DW_FORM_addr:
    case DW_FORM_strp:
    case DW_FORM_ref_addr:
      *len = cu->address_size;
      break;

    case DW_FORM_block1:
      *len = *valp + 1;
      break;

    case DW_FORM_block2:
      *len = read_2ubyte_unaligned (dbg, valp) + 2;
      break;

    case DW_FORM_block4:
      *len = read_4ubyte_unaligned (dbg, valp) + 4;
      break;

    case DW_FORM_block:
      saved = valp;
      get_uleb128 (u128, valp);
      *len = u128 + (valp - saved);
      break;

    case DW_FORM_ref1:
    case DW_FORM_data1:
    case DW_FORM_flag:
      *len = 1;
      break;

    case DW_FORM_data2:
    case DW_FORM_ref2:
      *len = 2;
      break;

    case DW_FORM_data4:
    case DW_FORM_ref4:
      *len = 4;
      break;

    case DW_FORM_data8:
    case DW_FORM_ref8:
      *len = 8;
      break;

    case DW_FORM_string:
      *len = strlen ((char *) valp) + 1;
      break;

    case DW_FORM_sdata:
    case DW_FORM_udata:
    case DW_FORM_ref_udata:
      saved = valp;
      get_uleb128 (u128, valp);
      *len = valp - saved;
      break;

    case DW_FORM_indirect:
      saved = valp;
      get_uleb128 (u128, valp);
      if (__libdwarf_form_val_len (dbg, cu, u128, valp, len, error)
	  != DW_DLV_OK)
	return DW_DLV_ERROR;
      *len += valp - saved;
      break;

    default:
      __libdwarf_error (dbg, error, DW_E_INVALID_DWARF);
      return DW_DLV_ERROR;
    }

  return DW_DLV_OK;
}
