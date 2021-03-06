#include <stdio.h>

#define branch(mask,_v1,_v2)                           \
  ({                                                   \
        unsigned char taken;                           \
        unsigned long b1 = _v1;                        \
        unsigned long b2 = _v2;                        \
        asm volatile("     slgr %[b1],%[b2]\n\t"       \
                     "     brc  " #mask " ,1f\n\t"     \
                     "     mvi  %[taken],0\n\t"        \
                     "     j    0f\n\t"                \
                     "1:   mvi  %[taken],1\n\t"        \
                     "0:   bcr 0,0 /* nop */\n\t"      \
             : [taken] "=Q" (taken), [b1] "+d"(b1)     \
             : [b2] "d"(b2)                            \
             : "cc");                                  \
        taken;                                         \
   })


/* cc = (op1 == op2) ? 2
                     : (op1 > op2) ? 3 : 1; */


void
slgr_equal(void)
{
   unsigned long v1, v2;
   int wrong, ok;

   printf("Test #1  op1 == op2\n");

   v1 = v2 = 42;
   wrong = ok = 0;

   if (branch(0,  v1, v2)) ++wrong; else ++ok;
   if (branch(1,  v1, v2)) ++wrong; else ++ok;
   if (branch(2,  v1, v2)) ++ok; else ++wrong;
   if (branch(3,  v1, v2)) ++ok; else ++wrong;
   if (branch(4,  v1, v2)) ++wrong; else ++ok;
   if (branch(5,  v1, v2)) ++wrong; else ++ok;
   if (branch(6,  v1, v2)) ++ok; else ++wrong;
   if (branch(7,  v1, v2)) ++ok; else ++wrong;
   if (branch(8,  v1, v2)) ++wrong; else ++ok;
   if (branch(9,  v1, v2)) ++wrong; else ++ok;
   if (branch(10, v1, v2)) ++ok; else ++wrong;
   if (branch(11, v1, v2)) ++ok; else ++wrong;
   if (branch(12, v1, v2)) ++wrong; else ++ok;
   if (branch(13, v1, v2)) ++wrong; else ++ok;
   if (branch(14, v1, v2)) ++ok; else ++wrong;
   if (branch(15, v1, v2)) ++ok; else ++wrong;

   if (wrong != 0 || ok != 16)
      printf("FAILED\n");
   else
      printf("OK\n");
}

void
slgr_less(void)
{
   unsigned long v1, v2;
   int wrong, ok;

   printf("Test #2  op1 < op2\n");

   v1 = 100;
   v2 = 1000;

   wrong = ok = 0;

   if (branch(0,  v1, v2)) ++wrong; else ++ok;
   if (branch(1,  v1, v2)) ++wrong; else ++ok;
   if (branch(2,  v1, v2)) ++wrong; else ++ok;
   if (branch(3,  v1, v2)) ++wrong; else ++ok;
   if (branch(4,  v1, v2)) ++ok; else ++wrong;
   if (branch(5,  v1, v2)) ++ok; else ++wrong;
   if (branch(6,  v1, v2)) ++ok; else ++wrong;
   if (branch(7,  v1, v2)) ++ok; else ++wrong;
   if (branch(8,  v1, v2)) ++wrong; else ++ok;
   if (branch(9,  v1, v2)) ++wrong; else ++ok;
   if (branch(10, v1, v2)) ++wrong; else ++ok;
   if (branch(11, v1, v2)) ++wrong; else ++ok;
   if (branch(12, v1, v2)) ++ok; else ++wrong;
   if (branch(13, v1, v2)) ++ok; else ++wrong;
   if (branch(14, v1, v2)) ++ok; else ++wrong;
   if (branch(15, v1, v2)) ++ok; else ++wrong;

   if (wrong != 0 /* || ok != 16 */)
      printf("FAILED\n");
   else
      printf("OK\n");
}

void
slgr_greater(void)
{
   unsigned long v1, v2;
   int wrong, ok;

   printf("Test #3  op1 > op2\n");

   v1 = 10000;
   v2 = 1000;

   wrong = ok = 0;

   if (branch(0,  v1, v2)) ++wrong; else ++ok;
   if (branch(1,  v1, v2)) ++ok; else ++wrong;
   if (branch(2,  v1, v2)) ++wrong; else ++ok;
   if (branch(3,  v1, v2)) ++ok; else ++wrong;
   if (branch(4,  v1, v2)) ++wrong; else ++ok;
   if (branch(5,  v1, v2)) ++ok; else ++wrong;
   if (branch(6,  v1, v2)) ++wrong; else ++ok;
   if (branch(7,  v1, v2)) ++ok; else ++wrong;
   if (branch(8,  v1, v2)) ++wrong; else ++ok;
   if (branch(9,  v1, v2)) ++ok; else ++wrong;
   if (branch(10, v1, v2)) ++wrong; else ++ok;
   if (branch(11, v1, v2)) ++ok; else ++wrong;
   if (branch(12, v1, v2)) ++wrong; else ++ok;
   if (branch(13, v1, v2)) ++ok; else ++wrong;
   if (branch(14, v1, v2)) ++wrong; else ++ok;
   if (branch(15, v1, v2)) ++ok; else ++wrong;

   if (wrong != 0 || ok != 16)
      printf("FAILED\n");
   else
      printf("OK\n");
}

int main()
{
   slgr_equal();
   slgr_less();
   slgr_greater();

   return 0;
}
