#include "Msequence.h"

// M Sequence Signal
char mseq(){
  // Shift Register
  static unsigned char Xn = 1;
  static unsigned int cnt = MSEQ_WIDTH;
  unsigned ret;

  cnt--;
  ret = ((Xn & 64) >> 6) ^ (Xn & 1);
  if (cnt == 0){
    Xn = (Xn << 1) + ret;
    cnt = MSEQ_WIDTH;
  }

  return ret;
}
