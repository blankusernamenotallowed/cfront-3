typedef void* KEYTYP;
class pnd;
class RECORD {
friend class pnd;
friend int __insert_new_array(KEYTYP addr, int count);
 unsigned long key;
};
