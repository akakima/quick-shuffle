/*
 *  shuffle.c
 *  shuffle file to stdout.
 */

#include <errno.h>
#include <malloc.h>
#include <search.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char **wordtext;
int *wordlen;

char *filename;
char buffer[1024];
FILE *wordfile;

unsigned int wcount;
unsigned int wminlen, wmaxlen;

int ShuffleWords( char *filename )
{
  FILE *wf;
  int nwords;

  wcount = 0;

  wf = fopen( filename, "r" );
  if( wf == NULL )
  {
    fprintf(stderr, "Cant't read file\n");
    return 0;
  }

  while( fgets(buffer, 1024, wf) )
  {
    wcount += 1;
  }

  fclose(wf);

  if( wcount < 1 )
  {
    return 0;
  }

  wordtext = (char**) malloc((sizeof(char*) * (wcount+1)));
  if( wordtext == 0 )
    return 0;
  wordlen  = (int*) malloc( sizeof(int) * (wcount+1) );
  if( wordlen == 0 )
  {
    free(wordtext);
    return 0;
  }

  wf = fopen( filename, "r");
  if( wf == NULL )
  {
    fprintf(stderr, "Cant't open: %s\n", filename);
    return 0;
  }
  nwords = 0;
  while( fgets(buffer, 1024, wf) )
  {
    int wlen;

    if( strstr(buffer, "\n") )
      *( strstr(buffer, "\n") ) = 0x0;
    else
      continue;

    wlen = strlen(buffer);
    if( wlen < 1 )
      continue;
    if( nwords == 0 )
    {
      wminlen = wmaxlen = wlen;
    }
    else
    {
      if( wlen > wmaxlen ) wmaxlen = wlen;
      if( wlen < wminlen ) wminlen = wlen;
    }
    wordtext[nwords] = strdup(buffer);
    wordlen[nwords] = wlen;
    nwords += 1;
  }
  fclose(wf);
  wordtext[nwords] = NULL;
  wordlen[nwords] = 0;
  return nwords;
}

int HaveOption( int argc, char **argv, char *option )
{
  int i;
  for( i=1 ; i < argc ; i++ )
  {
    if( 0 == strcmp(option, argv[i]) ) return 1;
  }
  return 0;
}

int compare( const void *arg1, const void *arg2 )
{
  return _stricmp( * ( char** ) arg1, * ( char** ) arg2 );
}

int cmpshuffle( const void *arg1, const void *arg2 )
{
   double s;
   s = ( rand( )/(double)RAND_MAX ) - 0.5;
   //printf("%f\n", s);
   return (s <= 0.0005) ? 1 : -11;
}


int main( int argc, char **argv )
{
  int nwords;
  int i;

  srand( time(0) );

  nwords = ShuffleWords( "words.txt" );
  //printf("nwords: %d\n", nwords);

  if( HaveOption(argc, argv, "--sort")  )
  {
    qsort( (void *)wordtext, (size_t)nwords, sizeof(char*), compare );
    printf("--- sorted ---\n");
    for(i=0; i < nwords ; i++)
    {
      wordlen[i] = strlen(wordtext[i]);
      printf("%s\n", wordtext[i]);
    }
  }

  if( HaveOption(argc, argv, "--shuffle")  )
  {
    qsort( (void *)wordtext, (size_t)nwords, sizeof(char*), cmpshuffle );
    printf("--- shuffle ---\n");
    for(i=0; i < nwords ; i++)
    {
      wordlen[i] = strlen(wordtext[i]);
      printf("%s\n", wordtext[i]);
    }
  }

  free(wordtext);
  free(wordlen);
  return 0;
}

