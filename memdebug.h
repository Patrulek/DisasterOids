#ifndef MEMDEBUG_H_INCLUDED
#define MEMDEBUG_H_INCLUDED

//#define MEM_DEBUG
#ifdef MEM_DEBUG

      extern mallocCounter;
      extern freeCounter;

      #define ALLOC(t, n) (t *)malloc((n) * sizeof(t)); mallocCounter++
      #define FREE(ptr) if(ptr) {free(ptr); ptr = 0; freeCounter++;}

#endif // MEM_DEBUG
#ifndef MEM_DEBUG

      #define ALLOC(t, n) (t *)malloc((n) * sizeof(t))
      #define FREE(ptr) if(ptr) {free(ptr); ptr = 0;}

#endif // MEM_DEBUG


#endif // MEMDEBUG_H_INCLUDED
