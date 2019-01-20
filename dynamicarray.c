#include "dynamicarray.h"

void ** createInternalArray(void ** dynArray, int arraySize)
{
      int i;

      if(!dynArray)
            dynArray = ALLOC(void *, arraySize);
      else
            return dynArray;

      for(i = 0; i < arraySize; i++)
            dynArray[i] = 0;

      return dynArray;
}

DynamicArray * createArray(DynamicArray * pArray, int arraySize)
{
      if(pArray)
            return pArray;

      DynamicArray * tempArray = ALLOC(DynamicArray, 1);

      tempArray->m_arraySize = arraySize;
      tempArray->m_dynArray = NULL;

      tempArray->m_dynArray = createInternalArray(tempArray->m_dynArray, arraySize);

      return tempArray;
}

DynamicArray * insertObject(DynamicArray * pArray, void * pObject)
{
      int i, j;
      bool toSmall;

      i = 0;

      if(i >= pArray->m_arraySize)
            toSmall = true;
      else
            toSmall = false;

      while(!toSmall)
      {
            if(!pArray->m_dynArray[i])
            {
                  pArray->m_dynArray[i] = pObject;
                  break;
            }

            i++;

            if(i >= pArray->m_arraySize)
                  toSmall = true;
      }

      if(toSmall)
      {
            int tempSize = pArray->m_arraySize == 0 ? 1 : pArray->m_arraySize << 1;
            DynamicArray * tempDArray = NULL;
            tempDArray = createArray(tempDArray, tempSize);

            for(i = 0, j = 0; i < pArray->m_arraySize; i++, j++)
                  tempDArray->m_dynArray[j] = pArray->m_dynArray[i];

            for(j; j < tempSize; j++)
                  tempDArray->m_dynArray[j] = NULL;

            tempDArray->m_dynArray[i] = pObject;

            clearArray(pArray, false, NO_ALLEGRO);

            tempDArray->m_arraySize = tempSize;

            return tempDArray;
      }
      return pArray;
}

DynamicArray * removeObject(DynamicArray * pArray, int index, bool deleteObject, ALLEGRO_TYPES allegroStruct)
{
      if(index >= pArray->m_arraySize || index < 0)
            return pArray;

      if(pArray->m_arraySize > 0)
      {
            int i, j;
            int tempSize = pArray->m_arraySize - 1;

            DynamicArray * tempDArray = NULL;
            tempDArray = createArray(tempDArray, tempSize);

            for(i = 0, j = 0; i < pArray->m_arraySize; i++, j++)
            {
                  if(index == i)
                  {
                        j--;
                        continue;
                  }

                  if(!pArray->m_dynArray[i])
                        tempDArray->m_dynArray[j] = NULL;
                  else
                        tempDArray->m_dynArray[j] = pArray->m_dynArray[i];
            }

            if(pArray->m_dynArray[index] && deleteObject)
            {
                  #ifdef USING_ALLEGRO_5
                  {
                        switch(allegroStruct)
                        {
                              case NO_ALLEGRO:
                                    pArray->m_dynArray[index] = NULL;
                                    break;
                              case ALLEGRO5_BITMAP:
                                    al_destroy_bitmap(pArray->m_dynArray[index]);
                                    pArray->m_dynArray[index] = NULL;
                                    break;
                              case ALLEGRO5_SAMPLE:
                                    al_destroy_sample(pArray->m_dynArray[index]);
                                    pArray->m_dynArray[index] = NULL;
                                    break;
                              case ALLEGRO5_SAMPLE_INSTANCE:
                                    al_destroy_sample_instance(pArray->m_dynArray[index]);
                                    pArray->m_dynArray[index] = NULL;
                                    break;
                              case ALLEGRO5_FONT:
                                    al_destroy_font(pArray->m_dynArray[index]);
                                    pArray->m_dynArray[index] = NULL;
                                    break;
                        }
                  }
                  #endif
                  #ifndef USING_ALLEGRO_5
                  {
                        pArray->m_dynArray[index] = NULL;
                  }
                  #endif // ALLEGRO5
            }

            clearArray(pArray, false, NO_ALLEGRO);

            tempDArray->m_arraySize = tempSize;

            return tempDArray;
      }

      return pArray;
}

DynamicArray * clearArray(DynamicArray * pArray, bool deleteObjects, ALLEGRO_TYPES allegroStruct)
{
      int i;

      if(deleteObjects && pArray)
      {
            for(i = 0; i < pArray->m_arraySize; i++)
            {
                  if(pArray->m_dynArray[i])
                  {
                        #ifdef USING_ALLEGRO_5
                        {
                              switch(allegroStruct)
                              {
                                    case NO_ALLEGRO:
                                          pArray->m_dynArray[i] = NULL;
                                          break;
                                    case ALLEGRO5_BITMAP:
                                          al_destroy_bitmap(pArray->m_dynArray[i]);
                                          pArray->m_dynArray[i] = NULL;
                                          break;
                                    case ALLEGRO5_SAMPLE:
                                          al_destroy_sample(pArray->m_dynArray[i]);
                                          pArray->m_dynArray[i] = NULL;
                                          break;
                                    case ALLEGRO5_SAMPLE_INSTANCE:
                                          al_destroy_sample_instance(pArray->m_dynArray[i]);
                                          pArray->m_dynArray[i] = NULL;
                                          break;
                                    case ALLEGRO5_FONT:
                                          al_destroy_font(pArray->m_dynArray[i]);
                                          pArray->m_dynArray[i] = NULL;
                                          break;
                              }
                        }
                        #endif // USING_ALLEGRO_5
                        #ifndef USING_ALLEGRO_5
                        {
                              pArray->m_dynArray[i] = NULL;
                        }
                        #endif
                  }
            }
      }
      if(pArray)
      {
            FREE(pArray->m_dynArray);
            FREE(pArray);
      }

      return NULL;
}

void * getItem(DynamicArray * pArray, int index)
{
      if(pArray->m_dynArray[index])
            return pArray->m_dynArray[index];

      return NULL;
}
