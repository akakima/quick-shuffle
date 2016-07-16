/*
 *  enumperm.c
 *
 *  EnumPermutations( )
 *  EnumCombinations( )
 */

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int mcount = 0;
unsigned int mlevel = 0;
unsigned int mlen   = 0;

unsigned char values [26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
unsigned char current[26] = {0};

void PrintCurrent( int pos )
{
  #if 0
  fprintf(stderr,"%06d: ", count);
  for( int i=0 ; i < pos ; i++ )
    fprintf( stderr, "%c", current[i] );
  fprintf( stderr, "\n" );
  #endif
  for( int i=0 ; i < pos ; i++ )
    printf("%c", current[i]);
  printf("\n");
}

int EnumPermutations( int pos, int n, unsigned char *values)
{
  #if 0
  fprintf(stderr, "EnumPermutations( pos:%02d, n:%d, [", pos, n);
  for( int jj=0; jj<n; jj++ )
  {
    //if( values[jj] != '.' )
    fprintf(stderr, "%c", values[jj]);
  }
  fprintf(stderr, "])\n");
  #endif

  if( pos < n )
  {
    unsigned char *vp;

    //fprintf(stderr, "-- malloc (level = %04u)\n", mlevel);
    //for( int j=0 ; j<n; j++ ) vp[j] = values[j];

    mcount += 1;
    mlevel += 1;
    mlen += n;
    fprintf(stderr, "%10d %10d %10d\n", mcount, mlevel, mlen);
    vp = (unsigned char *) malloc(n);
    memcpy(vp, values, n);

    for( int i=0 ; i < n ; i++ )
    {
      if( values[i] == '.' ) continue;
      current[pos] = values[i];
      vp[i] = '.';
      EnumPermutations(pos+1, n, vp);
      vp[i] = values[i];
    }

    free(vp);
    mlevel -= 1;
    mlen -= n;
    fprintf(stderr, "%10d %10d %10d\n", mcount, mlevel, mlen);
    return 0;
  }

  PrintCurrent( pos );
  return 0;
}


int EnumCombinations( int pos, int n, unsigned char *values)
{
  #if 0
  fprintf(stderr, "EnumCombinaisons( pos:%02d, n:%d, [", pos, n);
  for( int jj=0; jj<n; jj++ )
  {
    //if( values[jj] != '.' )
    fprintf(stderr, "%c", values[jj]);
  }
  fprintf(stderr, "])\n");
  #endif

  if( pos < n )
  {
    unsigned char *vp;

    mcount += 1;
    mlevel += 1;
    mlen += n;
    fprintf(stderr, "%10d %10d %10d\n", mcount, mlevel, mlen);
    vp = (unsigned char *) malloc(n);
    memcpy(vp, values, n);

    for( int i=0 ; i < n ; i++ )
    {
      //if( values[i] == '.' ) continue;
      current[pos] = values[i];
      //vp[i] = '.';
      EnumCombinations(pos+1, n, vp);
      //vp[i] = values[i];
    }

    free(vp);
    mlevel -= 1;
    mlen -= n;
    fprintf(stderr, "%10d %10d %10d\n", mcount, mlevel, mlen);
    return 0;
  }

  PrintCurrent( pos );
  return 0;
}

int main( int argc, char **argv )
{
  int i;
  int k;

  fprintf(stderr, "VALUES: ");
  for( i=0 ; i < sizeof(values) ; i++ )
    fprintf(stderr, "%c", values[i]);
  fprintf(stderr, "\n");

  mcount = 0;
  mlevel = 0;

  k = (argc > 1) ? atoi(argv[1]) : 5;
  if( k < 0 || k > 26 )
    k=5;
  EnumPermutations(0, k, values);
  printf("----\n");
  EnumCombinations(0, k, values);


  fprintf(stderr, "mcount: %d\n", mcount);
  return 0;
}
