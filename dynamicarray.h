#ifndef DYNAMICARRAY_H_INCLUDED
#define DYNAMICARRAY_H_INCLUDED

#define USING_ALLEGRO_5

#ifdef USING_ALLEGRO_5

#include <allegro5/allegro.h>

/** \brief
 *
 * Enum for stored types
 *
 */
typedef enum ALLEGRO_TYPES
{
      NO_ALLEGRO,
      ALLEGRO5_BITMAP,
      ALLEGRO5_SAMPLE,
      ALLEGRO5_SAMPLE_INSTANCE,
      ALLEGRO5_FONT
} ALLEGRO_TYPES;

#endif

#ifndef USING_ALLEGRO5

#define NO_ALLEGRO 0

#endif

#include <stdio.h>
#include <stdbool.h>

#include "memdebug.h"


/** \brief
 *
 * Struct which describes dynamic array
 *
 */
typedef struct DynamicArray
{
      int m_arraySize;  /**< Capacity of array */
      void ** m_dynArray;  /**< Array of objects */

} DynamicArray;

/** \brief
 *
 * This function creates dynamic array
 *
 * \param pArray - Ptr on DynamicArray
 * \param arraySize - Size of array
 * \return Ptr on DynamicArray
 *
 *
 */
DynamicArray * createArray(DynamicArray * pArray, int arraySize);

/** \brief
 *
 * This function clears array
 *
 * \param pArray - Ptr on DynamicArray
 * \param deleteObjects - Check if object have to be deleted
 * \param allegroStruct - Specify if it is allegro struct or not
 * \return NULL
 *
 */
DynamicArray * clearArray(DynamicArray * pArray, bool deleteObjects, ALLEGRO_TYPES allegroStruct);

/** \brief
 *
 * This function creates array of objects in dynamic array struct
 *
 * \param dynArray - Ptr to space where objects will be stored
 * \param arraySize - Number of objects
 * \return Ptr to array of objects
 *
 */
void ** createInternalArray(void ** dynArray, int arraySize);

/** \brief
 *
 * This function insert object to array
 *
 * \param pArray - Ptr on DynamicArray
 * \param pObject - Ptr on object
 * \return Ptr on DynamicArray
 *
 */
DynamicArray * insertObject(DynamicArray * pArray, void * pObject);

/** \brief
 *
 * This function removes object from array
 *
 * \param pArray - Ptr on DynamicArray
 * \param index - Index of object in array
 * \param deleteObject - Check if object has to be deleted
 * \param allegroStruct - Specify if object is allegro struct or not
 * \return Ptr on DynamicArray
 *
 */
DynamicArray * removeObject(DynamicArray * pArray, int index, bool deleteObject, ALLEGRO_TYPES allegroStruct);

/** \brief
 *
 * This function gets item from array
 *
 * \param pArray - Ptr on DynamicArray
 * \param index - Index of object in array
 * \return Ptr on object if exists, NULL otherwise.
 *
 */
void * getItem(DynamicArray * pArray, int index);


#endif // DYNAMICARRAY_H_INCLUDED
