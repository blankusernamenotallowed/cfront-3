/* Default empty static-ctor/dtor tables, in their OWN object file so the linker
   pulls them ONLY when munch didn't generate a __ctdt.c (i.e. the program has no
   static objects). When munch does provide strong _ctors[]/_dtors[], this member
   is simply not pulled from the archive. PE/COFF-safe (no weak symbols). */
typedef int (*PFV)();
PFV _ctors[] = { 0 };
PFV _dtors[] = { 0 };
