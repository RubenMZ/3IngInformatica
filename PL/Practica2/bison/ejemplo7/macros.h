#ifndef _MACROS_H_
#define _MACROS_H_

#define LUGAR(x,y)   printf("\033[%d;%dH",x,y)
#define BORRAR       printf("\33[2J") 
#define PARPADEO     printf("%c[5m",27)
#define APAGA        printf("%c[0m",27)
#define INVERSO      printf("%c[7m",27)
#define SUBRAYA      printf("%c[4m",27)
#define INTENSIDAD   printf("%c[1m",27)


#endif
