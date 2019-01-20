#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

#include "memdebug.h"


/** \brief
 *
 * Struct which describes text
 *
 */
typedef struct String
{
      char * m_buffer;  /**< \brief Buffer of text */
      int m_lines;  /**< \brief Number of lines of text */
      int m_curLine;  /**< \brief Current line of text */
      int m_size;  /**< \brief The size of text in bytes */
      int m_curPos;  /**< \brief Actual position in text */
}String;


// file functions

/** \brief
 *
 * This function reads file and stores it in memory
 *
 * \param pString - Ptr on String
 * \param fileName - Path to the file
 * \return Ptr on String
 *
 */
String * readFile(String * pString, const char * fileName);

/** \brief
 *
 * This function initiates writing text to file
 *
 * \param pString - Ptr on String
 * \param fileName - Path to file
 * \return Nothing
 *
 */
void writeFile(String * pString, const char * fileName);

/** \brief
 *
 * This function write text line by line to file. It's recursive function.
 *
 * \param pString - Ptr on String
 * \param pFile - Ptr on FILE
 * \return Nothing
 *
 */
void writeLine(String * pString, FILE * pFile);

/** \brief
 *
 * This function gets file size
 *
 * \param pFile - Ptr on FILE
 * \return Size in bytes
 *
 */
int getFileSize(FILE * pFile);

// string functions

/** \brief
 *
 * This function creates text from given buffer
 *
 * \param pBuffer - Buffer of text as cstring
 * \return Ptr on String
 *
 */
String * createString(const char * pBuffer);

/** \brief
 *
 * This function destroys string
 *
 * \param pString - Ptr on String
 * \return Nothing
 *
 */
void destroyString(String * pString);

/** \brief
 *
 * This function get text from given position to the end of line
 *
 * \param destBuffer - Buffer where will be stored substring
 * \param srcBuffer - Buffer from which to cut substring
 * \param startPos - Start position to cut
 * \param getLineChar - Check if line character will be saved to buffer
 * \return Cut substring
 *
 */
char * getLineFromPos(char * destBuffer, const char * srcBuffer, int startPos, bool getLineChar);

/** \brief
 *
 * This function merge two cstrings into one bigger
 *
 * \param pBuffer1 - Ptr on cstring
 * \param pBuffer2 - Ptr on cstring
 * \return Combined cstring
 *
 */
char * mergeStrings(const char * pBuffer1, const char * pBuffer2);

/** \brief
 *
 * This function returns position of given char in cstring
 *
 * \param pBuffer - Ptr on cstring
 * \param startPos - Start position to search
 * \param c - Character to find
 * \return Position of char
 *
 */
int findChar(const char * pBuffer, int startPos, char c);


#endif // IO_H_INCLUDED
