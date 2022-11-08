#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
  time_t ahora;
  struct tm *tm_l,*tm_u;
  
  tzset();
  ahora=time(NULL);
  tm_l=localtime(&ahora);
  tm_u=gmtime(&ahora);
  if (tm_l!=NULL) {
    printf("Content-Type: text/html;\n\n");
    printf("%.0f\n",(double)ahora*1000.0);

/*    printf("Local: %02d %02d %04d %02d %02d %02d\n",
      tm_l->tm_mday,tm_l->tm_mon+1,tm_l->tm_year+1900,
      tm_l->tm_hour,tm_l->tm_min,tm_l->tm_sec);
    printf("TZ: %ld\n",tm_l->tm_gmtoff);

    printf("UTC: %02d %02d %04d %02d %02d %02d\n",
      tm_u->tm_mday,tm_u->tm_mon+1,tm_u->tm_year+1900,
      tm_u->tm_hour,tm_u->tm_min,tm_u->tm_sec);
*/
  }
  return 0;
}
