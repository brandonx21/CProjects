/* Header Comment
    Brandon Williams, 804679951 bwilli21
*/
#include "cachelab.h"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <strings.h>
#include <limits.h>







typedef struct
{
   int s;
   int b;
   int E;
   int S;
   int B;
} cache_param_t;



// For cmd line, use something like ./csim -s 1 -E 1 -b 1 -t traces/<whatever trace>
void printUsage(char *argv[])
{
   printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
   printf("Options:\n");
   printf("  -h         Print this help message.\n" );
   printf("  -v         Optional verbose flag.\n" );
   printf("  -s <num>   Number of set index bits.\n" );
   printf("  -E <num>   Number of lines per set.\n" );
   printf("  -b <num>   Number of block offset bits.\n" );
   printf("  -t <file>  Trace file.\n" );
   exit(0);
}

int verbose;
typedef unsigned long long int mem_addr_t;
//void printSummary(int hit_count,int miss_count,int eviction_count)
/*
{
   printf( "hits: %d   misses: %d   evictions: %d\n", hit_count, miss_count, eviction_count );
}
*/

int main(int argc, char **argv)
{
   cache_param_t par;
    int hit_count = 0;
   int miss_count = 0;
   int eviction_count = 0;
   char *trace_file;
   char cases;

   while ((cases = getopt(argc,argv,"s:E:b:t:v:h")) != -1)
                    {
        switch (cases)
      {
         case 's':
            par.s = atoi(optarg);
            break;
         case 'E':
            par.E = atoi(optarg);
            break;
         case 'b':
            par.b = atoi(optarg);
            break;
         case 't':
            trace_file = optarg;
            break;
         case 'v':
            verbose = 1;
            break;
         case 'h':
            printUsage(argv);
            exit(0);
         default:
            printUsage(argv);
            exit(1);
      }
   }

                        // checking for missing cmd line arguments.
   if ( par.s == 0 || par.E == 0 || par.b == 0 || trace_file == NULL )
   {
      printf( "%s: Arguments are invalid.", argv[0] );
      printUsage(argv);
      exit(1);
   }



   //this computes s^b as needed for the lab
   par.S = ( 1 << par.s );
   par.B = ( 1 << par.b );

   // Struct for how file is structuredd.
   typedef struct
   {
      int valid;
      mem_addr_t tag;
      int timestamp;
   } line_st;

   typedef struct
   {
      line_st *lines;
   } cache_set;

   typedef struct
   {
      cache_set *sets;
   } cache_t;

   // Using cache_t struct
   cache_t cache;

                    // Allocate size of struct
   cache.sets = malloc(par.S *sizeof(cache_set));
   for (int i = 0; i < par.S; i++)
   {
      cache.sets[i].lines = malloc(sizeof(line_st) * par.E);
   }





   char LSM;
   int size;
   int TSTAMP = 0;
   int empty = -1;
   int H = 0;
   int E = 0;
   mem_addr_t addr;


   FILE *trace = fopen(trace_file, "r" );

   if (trace != NULL)
                {
      while (fscanf(trace," %c %llx,%d", &LSM, &addr, &size) == 3 )
      {
         int toEvict = 0;             // eviction?
         if ( LSM != 'I' )
         {
                        //calculating address tag, not sure if this is correct.
            mem_addr_t addr_tag = addr >> ( par.s + par.b );
                        // 64 bit
            int tag_size = ( 64 - ( par.s + par.b ) );
            unsigned long long temp = addr << (tag_size);
            unsigned long long setid = temp >> (tag_size + par.b);
            cache_set set = cache.sets[setid];
            int low = INT_MAX;

                        // Check here first for error. Not sure if itll get what i want
            for ( int e = 0; e < par.E; e++ ) {
               if ( set.lines[e].valid == 1 ) {

                  if (set.lines[e].tag == addr_tag) {
                     hit_count++;
                     H = 1;
                     set.lines[e].timestamp = TSTAMP;
                     TSTAMP++;
                  }

                  else if ( set.lines[e].timestamp < low ) {
                     low = set.lines[e].timestamp;
                     toEvict = e;
                  }
               }

               else if( empty == -1 ) {
                  empty = e;
               }
            }


            if ( H != 1 )
            {
               miss_count++;

               if ( empty > -1 )
               {
                  set.lines[empty].valid = 1;
                  set.lines[empty].tag = addr_tag;
                  set.lines[empty].timestamp = TSTAMP;
                  TSTAMP++;
               }

               else if ( empty < 0 )
               {
                  E = 1;
                  set.lines[toEvict].tag = addr_tag;
                  set.lines[toEvict].timestamp = TSTAMP;
                  TSTAMP++;
                  eviction_count++;
               }
            }

            if ( LSM == 'M' )
            {
               hit_count++;
            }

            if ( verbose == 1 )
            {
               printf( "%c ", LSM );
               printf( "%llx,%d", addr, size );
               if ( H == 1 )
               {
                  printf("Hit ");
               }
               else if (H != 1)
               {
                printf( "Miss ");
               }
               if (E == 1)
               {
                printf( "Eviction " );
               }

               printf( "\n" );
            }
            empty = -1;
            H = 0;
            E = 0;
         }
      }
   }

  //printSummary(hit_count, miss_count, eviction_count);
  printSummary(printf( "hits: %d   misses: %d   evictions: %d\n", hit_count, miss_count, eviction_count ));
   //fclose(trace);
   return 0;
}
