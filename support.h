#ifndef support_H
#define support_H


#ifndef printDashLine_F
#define printDashLine_F
  static void printDashLine(int nlen) {
      for(int i=0; i<nlen; ++i) {
          printf("-");
      }
      printf("\n");
    return;
  }// stdio.h
#endif /* printDashLine_F */

#ifndef lenof_F
#define lenof_F
  #define lenof(a) ( sizeof(a) / sizeof(a[0]) )
#endif /* lenof_F */


#endif /* support_H */
