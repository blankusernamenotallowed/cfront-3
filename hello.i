# 0 "demo/hello/hello.C"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "demo/hello/hello.C"
# 1 "incl/stream.h" 1
# 20 "incl/stream.h"
# 1 "incl/iostream.h" 1
# 19 "incl/iostream.h"
#pragma lib "ape/libap.a"
#pragma lib "c++/libC.a"

# 1 "incl/memory.h" 1



# 1 "incl/string.h" 1



extern "C" {
    char
 *strcpy(char*, const char*),
 *strncpy(char*, const char*, int),
 *strcat(char*, const char*),
 *strncat(char*, const char*, int),
 *strchr(const char*, char),
 *strrchr(const char*, char),
 *strpbrk(const char*, const char*),
 *strtok(char*, const char*),
 *strdup(const char*);
    int
 strcmp(const char*, const char*),
 strncmp(const char*, const char*, int),
 strlen(const char*),
 strspn(const char*, const char*),
 strcspn(const char*, const char*);
    void
 *memccpy(char *, const char *, int, int),
 *memchr(const char *, int, int),
 *memcpy(char *, const char *, int),
 *memset(void *, int, int);
    int memcmp(const char *, const char *, int);
}
# 5 "incl/memory.h" 2
# 23 "incl/iostream.h" 2
# 49 "incl/iostream.h"
typedef long streampos ;
typedef long streamoff ;

class streambuf ;
class ostream ;


class ios {
public:


 enum io_state { goodbit=0, eofbit=1, failbit=2, badbit=4,
    hardfail=0200};


 enum open_mode { in=1, out=2, ate=4, app=010, trunc=020,
    nocreate=040, noreplace=0100} ;
 enum seek_dir { beg=0, cur=1, end=2 } ;


 enum { skipws=01,

     left=02, right=04, internal=010,

     dec=020, oct=040, hex=0100,

     showbase=0200, showpoint=0400, uppercase=01000,
     showpos=02000,

     scientific=04000, fixed=010000,

     unitbuf=020000, stdio=040000

     } ;
 static const long
   basefield ;
 static const long
   adjustfield ;
 static const long
   floatfield ;
public:
   ios(streambuf*) ;
 virtual ~ios() ;

 long flags() const { return x_flags ; }
 long flags(long f);

 long setf(long setbits, long field);
 long setf(long) ;
 long unsetf(long) ;

 int width() const { return x_width ; }
 int width(int w)
 {
   int i = x_width ; x_width = w ; return i ;
 }

 ostream* tie(ostream* s);
 ostream* tie() { return x_tie ; }
 char fill(char) ;
 char fill() const { return x_fill ; }
 int precision(int) ;
 int precision() const { return x_precision ; }

 int rdstate() const { return state ; }
   operator void*()
    {
    void *retval;
    if (state&(failbit|badbit|hardfail)) retval = 0 ;
    else retval = this ;
    return retval;
    }
   operator const void*() const
    {
    const void *retval;
    if (state&(failbit|badbit|hardfail)) retval = 0 ;
    else retval = this ;
    return retval;
    }

 int operator!() const
    { return state&(failbit|badbit|hardfail); }
 int eof() const { return state&eofbit; }
 int fail() const { return state&(failbit|badbit|hardfail); }
 int bad() const { return state&badbit ; }
 int good() const { return state==0 ; }
 void clear(int i =0)
    {
    state = (i&0377) | (state&hardfail) ;
    ispecial = (ispecial&~0377) | state ;
    ospecial = (ospecial&~0377) | state ;
    }
 streambuf* rdbuf() { return bp ;}

public:
 long & iword(int) ;
 void* & pword(int) ;
 static long bitalloc() ;
 static int xalloc() ;

private:
 static long nextbit ;
 static long nextword ;

 int nuser ;
 union ios_user_union*
   x_user ;
 void uresize(int) ;
public:
 static void sync_with_stdio() ;
protected:
 enum { skipping=01000, tied=02000 } ;

 streambuf* bp;
 void setstate(int b)
   { state |= (b&0377) ;
    ispecial |= b&~skipping ;
    ispecial |= b ;
   }
 int state;
 int ispecial;
 int ospecial;
 int isfx_special;
 int osfx_special;
 int delbuf;
 ostream* x_tie;
 long x_flags;
 short x_precision;
 char x_fill;
 short x_width;

 static void (*stdioflush)() ;

 void init(streambuf*) ;

   ios() ;

 int assign_private ;

private:
   ios(ios&) ;
 void operator=(ios&) ;
public:
 int skip(int i) ;
};

class streambuf {
 short alloc;
 short x_unbuf;
 char* x_base;
 char* x_pbase;
 char* x_pptr;
 char* x_epptr;
 char* x_gptr;
 char* x_egptr;
 char* x_eback;
 int x_blen;
    private:
   streambuf(streambuf&);
 void operator=(streambuf&);
    public:
 void dbp();
    protected:
 char* base() { return x_base ; }
 char* pbase() { return x_pbase ; }
 char* pptr() { return x_pptr ; }
 char* epptr() { return x_epptr ; }
 char* gptr() { return x_gptr ; }
 char* egptr() { return x_egptr ; }
 char* eback() { return x_eback ; }
 char* ebuf() { return x_base+x_blen ; }
 int blen() const { return x_blen; }
 void setp(char* p, char* ep)
 {
  x_pbase=x_pptr=p ; x_epptr=ep ;
 }
 void setg(char* eb,char* g, char* eg)
 {
  x_eback=eb; x_gptr=g ; x_egptr=eg ;
 }
 void pbump(int n)
 {
  x_pptr+=n ;
 }

 void gbump(int n)
 {
  x_gptr+=n ;
  }

 void setb(char* b, char* eb, int a = 0 )
 {
  if ( alloc && x_base ) delete x_base ;
  x_base = b ;
  x_blen= (eb>b) ? (eb-b) : 0 ;
  alloc = a ;
  }
 int unbuffered() const { return x_unbuf; }
 void unbuffered(int unb) { x_unbuf = (unb!=0) ; }
 int allocate()
 {
  int retval;
  if ( x_base== 0 && !unbuffered() ) retval = doallocate() ;
  else retval = 0 ;
  return retval;
 }
 virtual int doallocate();
    public :
 virtual int overflow(int c=(-1));
 virtual int underflow();
 virtual int pbackfail(int c);
 virtual int sync();
 virtual streampos
   seekoff(streamoff,ios::seek_dir,int =ios::in|ios::out);
 virtual streampos
   seekpos(streampos, int =ios::in|ios::out) ;
 virtual int xsputn(const char* s,int n);
 virtual int xsgetn(char* s,int n);

 int in_avail()
 {
  return x_gptr<x_egptr ? x_egptr-x_gptr : 0 ;
 }

 int out_waiting()
 {
  int retval;
  if ( x_pptr ) retval = x_pptr-x_pbase ;
  else retval = 0 ;
  return retval;
 }

 int sgetc()
 {

  return (x_gptr>=x_egptr) ? underflow() : ((*x_gptr)&0377);
 }
 int snextc()
 {
  return (++x_gptr>=x_egptr)
    ? x_snextc()
    : ((*x_gptr)&0377);
 }
 int sbumpc()
 {
  return ( x_gptr>=x_egptr && underflow()==(-1) )
    ? (-1)
    : ((*x_gptr++)&0377) ;
 }
 int optim_in_avail()
 {
  return x_gptr<x_egptr ;
 }
 int optim_sbumpc()
 {
  return ((*x_gptr++)&0377) ;
 }
 void stossc()
 {
  if ( x_gptr >= x_egptr ) underflow() ;
  else x_gptr++ ;
 }

 int sputbackc(char c)
 {
  int retval;
  if (x_gptr > x_eback ) {
   if ( *--x_gptr == c ) retval = ((c)&0377) ;
   else retval = ((*x_gptr=c)&0377) ;
  } else {
   retval = pbackfail(c) ;
  }
  return retval;
 }

 int sputc(int c)
 {
  return (x_pptr>=x_epptr) ? overflow(((c)&0377))
          : ((*x_pptr++=c)&0377);
 }
 int sputn(const char* s,int n)
  {
  int retval;
  if ( n <= (x_epptr-x_pptr) ) {
   memcpy(x_pptr,s,n) ;
   pbump(n);
   retval = n ;
  } else {
   retval = xsputn(s,n) ;
  }
  return retval;
 }
 int sgetn(char* s,int n)
 {
  int retval;
  if ( n <= (x_egptr-x_gptr) ) {
   memcpy(s,x_gptr,n) ;
   gbump(n);
   retval = n ;
  } else {
   retval = xsgetn(s,n) ;
  }
  return retval;
 }
 virtual streambuf*
   setbuf(char* p, int len) ;
    streambuf* setbuf(unsigned char* p, int len) ;

 streambuf* setbuf(char* p, int len, int count) ;


   streambuf() ;
   streambuf(char* p, int l) ;

   streambuf(char* p, int l,int c) ;



 virtual ~streambuf() ;
private:
 int x_snextc() ;
};

class istream : virtual public ios {
public:
   istream(streambuf*) ;
 virtual ~istream() ;
public:
 int ipfx(int noskipws=0)
   {
    int retval;
    if ( noskipws?(ispecial&~skipping):ispecial) {
     retval = do_ipfx(noskipws) ;
    } else retval = 1 ;
    return retval;
   }
 void isfx() { }
 istream& seekg(streampos p) ;
 istream& seekg(streamoff o, ios::seek_dir d) ;
    streampos tellg() ;
 istream& operator>> (istream& (*f)(istream&))
   { return (*f)(*this) ; }
 istream& operator>> (ios& (*f)(ios&) ) ;
 istream& operator>>(char*);
 istream& operator>>(unsigned char*);
 istream& operator>>(unsigned char& c)
   {
    istream* retval;
    if ( !ispecial && bp->optim_in_avail() ) {
     c = bp->optim_sbumpc() ;
     retval = this;
    }
    else {
     retval = &(rs_complicated(c));
    }
    return *retval;
   }
 istream& operator>>(char& c)
   {
    istream* retval;
    if ( !ispecial && bp->optim_in_avail() ) {
     c = bp->optim_sbumpc() ;
     retval = this;
    }
    else {
     retval = &(rs_complicated(c));
    }
    return *retval;
   }
 istream& rs_complicated(unsigned char& c);
 istream& rs_complicated(char& c);
 istream& operator>>(short&);
 istream& operator>>(int&);
 istream& operator>>(long&);
 istream& operator>>(unsigned short&);
 istream& operator>>(unsigned int&);
 istream& operator>>(unsigned long&);
 istream& operator>>(float&);
 istream& operator>>(double&);
 istream& operator>>(streambuf*);
 istream& get(char* , int lim, char delim='\n');
 istream& get(unsigned char* b,int lim, char delim='\n') {
    return get((char*)b, lim, delim);
   }
 istream& getline(char* b, int lim, char delim='\n');
 istream& getline(unsigned char* b, int lim, char delim='\n');
 istream& get(streambuf& sb, char delim ='\n');
 istream& get_complicated(unsigned char& c);
 istream& get_complicated(char& c);
 istream& get(unsigned char& c)
   {
    istream* retval;
    if ( !(ispecial & ~skipping) && bp->optim_in_avail() ) {
     x_gcount = 1 ;
     c = bp->sbumpc() ;
     retval = this;
    } else {
     retval = &(get_complicated(c));
    }
    return *retval;
   }
 istream& get(char& c)
   {
    istream* retval;
    if ( !(ispecial & ~skipping) && bp->optim_in_avail() ) {
     x_gcount = 1 ;
     c = bp->sbumpc() ;
     retval = this;
    } else {
     retval = &(get_complicated(c));
    }
    return *retval;
   }
 int get()
   {
    int retval;
    if ( !ipfx(1) ) retval = (-1) ;
    else {
     retval = bp->sbumpc() ;
     if ( retval == (-1) ) setstate(eofbit) ;
     }
    return retval;
   }
 int peek()
   {
    int retval;
    if ( ipfx(-1) ) retval = bp->sgetc() ;
    else retval = (-1) ;
    return retval;
   }
 istream& ignore(int n=1,int delim=(-1)) ;
 istream& read(char* s,int n);
 istream& read(unsigned char* s,int n)
   {
    return read((char*)s,n) ;
   }
 int gcount() ;
 istream& putback(char c);
 int sync() { return bp->sync() ; }
protected:
 int do_ipfx(int noskipws) ;
 void eatwhite() ;
   istream() ;
private:
 int x_gcount ;
 void xget(char* c) ;
public:
   istream(streambuf*, int sk, ostream* t=0) ;


   istream(int size ,char*,int sk=1) ;

   istream(int fd,int sk=1, ostream* t=0) ;

};

class ostream : virtual public ios {
public:
   ostream(streambuf*) ;
 virtual ~ostream();
public:
 int opfx()
   {
    int retval;
    if ( ospecial ) retval = do_opfx() ;
    else retval = 1 ;
    return retval;
   }
 void osfx()
   { if ( osfx_special ) do_osfx() ; }

 ostream& flush() ;
 ostream& seekp(streampos p) ;
 ostream& seekp(streamoff o, ios::seek_dir d) ;
  streampos tellp() ;
 ostream& put(char c)
 {
  ostream* retval;
  if (ospecial || osfx_special) {
   retval = &complicated_put(c);
  }
  else {
   if ( bp->sputc(c) == (-1) ) {
    setstate(eofbit|failbit) ;
   }
   retval = this ;
  }
  return *retval;
 }
 ostream& complicated_put(char c);
 ostream& operator<<(char c)
 {
  ostream* retval;
  if (ospecial || osfx_special) {
   retval = &ls_complicated(c);
  }
  else {
   if ( bp->sputc(c) == (-1) ) {
    setstate(eofbit|failbit) ;
   }
   retval = this ;
  }
  return *retval;
 }

 ostream& operator<<(unsigned char c)
 {
  ostream* retval;
  if (ospecial || osfx_special) {
   retval = &ls_complicated(c);
  }
  else {
   if ( bp->sputc(c) == (-1) ) {
    setstate(eofbit|failbit) ;
   }
   retval = this ;
  }
  return *retval;
 }
 ostream& ls_complicated(char);
 ostream& ls_complicated(unsigned char);

 ostream& operator<<(const char*);
 ostream& operator<<(int a);
 ostream& operator<<(long);
 ostream& operator<<(double);
 ostream& operator<<(float);
 ostream& operator<<(unsigned int a);
 ostream& operator<<(unsigned long);
 ostream& operator<<(void*);

 ostream& operator<<(streambuf*);
 ostream& operator<<(short i) { return *this << (int)i ; }
 ostream& operator<<(unsigned short i)
   { return *this << (int)i ; }

 ostream& operator<< (ostream& (*f)(ostream&))
   { return (*f)(*this) ; }
 ostream& operator<< (ios& (*f)(ios&) ) ;

 ostream& write(const char* s,int n)
 {
  if ( !state ) {
   if ( bp->sputn(s,n) != n ) setstate(eofbit|failbit);
   }
  return *this ;
 }
 ostream& write(const unsigned char* s, int n)
 {
  return write((const char*)s,n);
 }
protected:
 int do_opfx() ;
 void do_osfx() ;
   ostream() ;

public:
   ostream(int fd) ;

   ostream(int size ,char*) ;

} ;

class iostream : public istream, public ostream {
public:
   iostream(streambuf*) ;
 virtual ~iostream() ;
protected:
   iostream() ;
 } ;

class istream_withassign : public istream {
public:
   istream_withassign() ;
 virtual ~istream_withassign() ;
 istream_withassign& operator=(istream&) ;
 istream_withassign& operator=(streambuf*) ;
} ;

class ostream_withassign : public ostream {
public:
   ostream_withassign() ;
 virtual ~ostream_withassign() ;
 ostream_withassign& operator=(ostream&) ;
 ostream_withassign& operator=(streambuf*) ;
} ;

class iostream_withassign : public iostream {
public:
   iostream_withassign() ;
 virtual ~iostream_withassign() ;
 iostream_withassign& operator=(ios&) ;
 iostream_withassign& operator=(streambuf*) ;
} ;

extern istream_withassign cin ;
extern ostream_withassign cout ;
extern ostream_withassign cerr ;
extern ostream_withassign clog ;

ios& dec(ios&) ;
ostream& endl(ostream& i) ;
ostream& ends(ostream& i) ;
ostream& flush(ostream&) ;
ios& hex(ios&) ;
ios& oct(ios&) ;
istream& ws(istream&) ;

static class Iostream_init {
 static int stdstatus ;
 static int initcount ;
 friend class ios ;
public:
 Iostream_init() ;
 ~Iostream_init() ;
} iostream_init ;
# 21 "incl/stream.h" 2
# 1 "incl/iomanip.h" 1
# 20 "incl/iomanip.h"
#pragma lib "ape/libap.a"
#pragma lib "c++/libC.a"

# 1 "incl/generic.h" 1


#pragma lib "ape/libap.a"
#pragma lib "c++/libC.a"
# 19 "incl/generic.h"
extern int genericerror(int,char*);
typedef int (*GPT)(int,char*);
# 24 "incl/iomanip.h" 2
# 112 "incl/iomanip.h"
class smanip_int { ios& (*fct)(ios&,int) ; int arg ; public: smanip_int(ios& (*f)(ios&, int), int a) : fct(f), arg(a) { } friend istream& operator>>(istream& i, const smanip_int& m) { ios* s = &i ; (*m.fct)(*s,m.arg) ; return i ; } friend ostream& operator<<(ostream& o, const smanip_int& m) { ios* s = &o ; (*m.fct)(*s,m.arg) ; return o ; } } ; class sapply_int { ios& (*fct)(ios&, int) ; public: sapply_int(ios& (*f)(ios&,int)) : fct(f) { } smanip_int operator()(int a) { return smanip_int(fct,a) ; } } ; class imanip_int { istream& (*fct)(istream&,int) ; int arg ; public: imanip_int(istream& (*f)(istream&, int), int a ) : fct(f), arg(a) { } friend istream& operator>>(istream& s, const imanip_int& m) { return(*m.fct)(s,m.arg) ; } } ; class iapply_int { istream& (*fct)(istream&, int) ; public: iapply_int(istream& (*f)(istream&,int)) : fct(f) { } imanip_int operator()(int a) { return imanip_int(fct,a) ; } } ; class omanip_int { ostream& (*fct)(ostream&,int) ; int arg ; public: omanip_int(ostream& (*f)(ostream&, int), int a ) : fct(f), arg(a) { } friend ostream& operator<<(ostream& s, const omanip_int& m) { return(*m.fct)(s,m.arg) ; } } ; class oapply_int { ostream& (*fct)(ostream&, int) ; public: oapply_int(ostream& (*f)(ostream&,int)) : fct(f) { } omanip_int operator()(int a) { return omanip_int(fct,a) ; } } ; class iomanip_int { iostream& (*fct)(iostream&,int) ; int arg ; public: iomanip_int(iostream& (*f)(iostream&, int), int a ) : fct(f), arg(a) { } friend istream& operator>>(iostream& s, const iomanip_int& m) { return(*m.fct)(s,m.arg) ; } friend ostream& operator<<(iostream& s, const iomanip_int& m) { return(*m.fct)(s,m.arg) ; } } ; class ioapply_int { iostream& (*fct)(iostream&, int) ; public: ioapply_int(iostream& (*f)(iostream&,int)) : fct(f) { } iomanip_int operator()(int a) { return iomanip_int(fct,a) ; } } ;
class smanip_long { ios& (*fct)(ios&,long) ; long arg ; public: smanip_long(ios& (*f)(ios&, long), long a) : fct(f), arg(a) { } friend istream& operator>>(istream& i, const smanip_long& m) { ios* s = &i ; (*m.fct)(*s,m.arg) ; return i ; } friend ostream& operator<<(ostream& o, const smanip_long& m) { ios* s = &o ; (*m.fct)(*s,m.arg) ; return o ; } } ; class sapply_long { ios& (*fct)(ios&, long) ; public: sapply_long(ios& (*f)(ios&,long)) : fct(f) { } smanip_long operator()(long a) { return smanip_long(fct,a) ; } } ; class imanip_long { istream& (*fct)(istream&,long) ; long arg ; public: imanip_long(istream& (*f)(istream&, long), long a ) : fct(f), arg(a) { } friend istream& operator>>(istream& s, const imanip_long& m) { return(*m.fct)(s,m.arg) ; } } ; class iapply_long { istream& (*fct)(istream&, long) ; public: iapply_long(istream& (*f)(istream&,long)) : fct(f) { } imanip_long operator()(long a) { return imanip_long(fct,a) ; } } ; class omanip_long { ostream& (*fct)(ostream&,long) ; long arg ; public: omanip_long(ostream& (*f)(ostream&, long), long a ) : fct(f), arg(a) { } friend ostream& operator<<(ostream& s, const omanip_long& m) { return(*m.fct)(s,m.arg) ; } } ; class oapply_long { ostream& (*fct)(ostream&, long) ; public: oapply_long(ostream& (*f)(ostream&,long)) : fct(f) { } omanip_long operator()(long a) { return omanip_long(fct,a) ; } } ; class iomanip_long { iostream& (*fct)(iostream&,long) ; long arg ; public: iomanip_long(iostream& (*f)(iostream&, long), long a ) : fct(f), arg(a) { } friend istream& operator>>(iostream& s, const iomanip_long& m) { return(*m.fct)(s,m.arg) ; } friend ostream& operator<<(iostream& s, const iomanip_long& m) { return(*m.fct)(s,m.arg) ; } } ; class ioapply_long { iostream& (*fct)(iostream&, long) ; public: ioapply_long(iostream& (*f)(iostream&,long)) : fct(f) { } iomanip_long operator()(long a) { return iomanip_long(fct,a) ; } } ;

smanip_int setbase(int b) ;
smanip_long resetiosflags(long b) ;
smanip_long setiosflags(long b) ;
smanip_int setfill(int f);
smanip_int setprecision(int p);
smanip_int setw(int w) ;
# 22 "incl/stream.h" 2
# 1 "incl/stdiostream.h" 1
# 20 "incl/stdiostream.h"
# 1 "incl/stdio.h" 1



extern "C" {





    typedef char *va_list;
# 43 "incl/stdio.h"
extern int _flsbuf(unsigned,struct _iobuf*);
extern int _filbuf(struct _iobuf*);
# 59 "incl/stdio.h"
extern struct _iobuf* fopen(const char*, const char*);
extern struct _iobuf* fdopen(int, const char*);
extern struct _iobuf* freopen(const char*, const char*, struct _iobuf*);
extern long ftell(const struct _iobuf*);
extern char* fgets(char*, int, struct _iobuf*);






extern char* gets(char*);
extern int puts(const char *s);
extern int fputs(const char *s, struct _iobuf *stream);
extern int printf(const char* ...);
extern int fprintf(struct _iobuf*, const char* ...);
extern int sprintf(char*, const char* ...);
extern int scanf(const char* ...);
extern int fscanf(struct _iobuf*, const char* ...);
extern int sscanf(char*, const char* ...);
extern int fread(char*, int, int, struct _iobuf*);
extern int fwrite(const char*, int, int, struct _iobuf*);
extern int fclose(struct _iobuf*);
extern int fflush(struct _iobuf *stream);
extern void clearerr (struct _iobuf *__stream);
extern int fseek(struct _iobuf*, long, int);
extern void rewind(struct _iobuf*);
extern int getw(struct _iobuf*);
extern int fgetc(struct _iobuf*);
extern struct _iobuf* popen(const char*, const char*);
extern int pclose(struct _iobuf*);
extern int putw(int, struct _iobuf*);
extern int fputc(int, struct _iobuf*);
extern void setbuf(struct _iobuf *stream, char *buf);
extern int ungetc(int, struct _iobuf*);

extern void exit(int);
extern void abort(void);

extern int atoi(const char*);
extern double atof(const char*);
extern long atol(const char*);




extern struct _iobuf *tmpfile ();
extern char *ctermid(char*),
                *cuserid(char*),
                *tempnam(char*, char*),
                *tmpnam(char*);
extern int vprintf(char*, va_list),
                vfprintf(struct _iobuf*, char*, va_list),
                vsprintf(char*, char*, va_list),
  setvbuf(struct _iobuf*, char*, int, int);

extern void perror (const char*);


extern char* sys_errlist[];
extern int sys_nerr;
extern unsigned char *_bufendtab[];

int feof(struct _iobuf *p);
int ferror(struct _iobuf *p);
int fileno(struct _iobuf *p);
char* strerror(int);


extern struct _iobuf* _get_stdin();
extern struct _iobuf* _get_stdout();
extern struct _iobuf* _get_stderr();
# 141 "incl/stdio.h"
void _main();

}
# 21 "incl/stdiostream.h" 2

class stdiobuf : public streambuf {

public:
 virtual int overflow(int=(-1));
 virtual int underflow();
 virtual int sync() ;
 virtual streampos
   seekoff(streamoff,ios::seek_dir,int) ;
 virtual int pbackfail(int c);
public:
   stdiobuf(struct _iobuf* f) ;
 struct _iobuf* stdiofile() { return fp ; }
 virtual ~stdiobuf() ;
private:
 struct _iobuf* fp ;
 int last_op ;
 char buf[2];
};

class stdiostream : public ios {
public:
   stdiostream(struct _iobuf*) ;
   ~stdiostream() ;
 stdiobuf* rdbuf() ;
private:
 stdiobuf buf ;
};
# 23 "incl/stream.h" 2
# 1 "incl/fstream.h" 1
# 21 "incl/fstream.h"
class filebuf : public streambuf {
public:
 static const int openprot ;
public:
   filebuf() ;
   filebuf(int fd);
   filebuf(int fd, char* p, int l) ;

 int is_open() { return opened ; }
 int fd() { return xfd ; }
 filebuf* open(const char *name, int om, int prot=openprot);
 filebuf* attach(int fd) ;
 int detach() ;
 filebuf* close() ;
   ~filebuf() ;
public:
 virtual int overflow(int=(-1));
 virtual int underflow();
 virtual int sync() ;
 virtual streampos
   seekoff(streamoff,ios::seek_dir,int) ;
 virtual streambuf*
   setbuf(char* p, int len) ;
protected:
 int xfd;
 int mode ;
 char opened;
 streampos last_seek ;
 char* in_start;
 int last_op();
 char lahead[2] ;
};

class fstreambase : virtual public ios {
public:
   fstreambase() ;

   fstreambase(const char* name,
     int mode,
     int prot=filebuf::openprot) ;
   fstreambase(int fd) ;
   fstreambase(int fd, char* p, int l) ;
   ~fstreambase() ;
 void open(const char* name, int mode,
     int prot=filebuf::openprot) ;
 void attach(int fd);
 int detach();
 void close() ;
 void setbuf(char* p, int l) ;
 filebuf* rdbuf() { return &buf ; }
private:
 filebuf buf ;
protected:
 void verify(int) ;
} ;

class ifstream : public fstreambase, public istream {
public:
   ifstream() ;
   ifstream(const char* name,
     int mode=ios::in,
     int prot=filebuf::openprot) ;
   ifstream(int fd) ;
   ifstream(int fd, char* p, int l) ;
   ~ifstream() ;

 filebuf* rdbuf() { return fstreambase::rdbuf(); }
 void open(const char* name, int mode=ios::in,
     int prot=filebuf::openprot) ;
} ;

class ofstream : public fstreambase, public ostream {
public:
   ofstream() ;
   ofstream(const char* name,
     int mode=ios::out,
     int prot=filebuf::openprot) ;
   ofstream(int fd) ;
   ofstream(int fd, char* p, int l) ;
   ~ofstream() ;

 filebuf* rdbuf() { return fstreambase::rdbuf(); }
 void open(const char* name, int mode=ios::out,
     int prot=filebuf::openprot) ;
} ;

class fstream : public fstreambase, public iostream {
public:
   fstream() ;

   fstream(const char* name,
     int mode,
     int prot=filebuf::openprot) ;
   fstream(int fd) ;
   fstream(int fd, char* p, int l) ;
   ~fstream() ;
 filebuf* rdbuf() { return fstreambase::rdbuf(); }
 void open(const char* name, int mode,
    int prot=filebuf::openprot) ;
} ;
# 24 "incl/stream.h" 2






extern char* oct(long, int =0);
extern char* dec(long, int =0);
extern char* hex(long, int =0);

extern char* chr(int, int =0);
extern char* str(const char*, int =0);
extern char* form(const char* ...);
# 50 "incl/stream.h"
extern istream& WS(istream&) ;
extern void eatwhite(istream&) ;

static const int input = (ios::in) ;
static const int output = (ios::out) ;
static const int append = (ios::app) ;
static const int atend = (ios::ate) ;
static const int _good = (ios::goodbit) ;
static const int _bad = (ios::badbit) ;
static const int _fail = (ios::failbit) ;
static const int _eof = (ios::eofbit) ;

typedef ios::io_state state_value ;
# 2 "demo/hello/hello.C" 2

main()
{
    cout << "Hello, World!\n";
}
