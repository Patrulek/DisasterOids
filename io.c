#include "io.h"

// file functions

int getFileSize(FILE * pFile)
{
      int fileSize;

      fseek(pFile, 0, SEEK_END);
      fileSize = ftell(pFile);
      fseek(pFile, 0, SEEK_SET);

      return fileSize;
}

String * readFile(String * pString, const char * fileName)
{
      FILE * pFile = fopen(fileName, "r+");
      int i ;

      if(pString)
            destroyString(pString);

      pString = ALLOC(String, 1);
      pString->m_size = getFileSize(pFile);
      pString->m_curLine = 0;
      pString->m_lines = 0;
      pString->m_curPos = 0;
      pString->m_buffer = ALLOC(char, pString->m_size + 1);

      for(i = 0; !feof(pFile); i++)
      {
            pString->m_buffer[i] = fgetc(pFile);
            pString->m_lines = pString->m_buffer[i] == '\n' ? pString->m_lines + 1 : pString->m_lines;
      }

      fclose(pFile);
      return pString;
}


void writeFile(String * pString, const char * fileName)
{
      FILE * pFile = fopen(fileName, "w+");
      pString->m_curPos = 0;
      pString->m_curLine = 0;

      writeLine(pString, pFile);

      fclose(pFile);
}

void writeLine(String * pString, FILE * pFile)
{
      int i;

      for(i = pString->m_curPos; i < pString->m_size; i++)
      {
            fputc(pString->m_buffer[i], pFile);
            pString->m_curPos++ ;

            if(pString->m_buffer[i] == '\n')
                  break;
      }
      pString->m_curLine++ ;

      if(pString->m_curLine <= pString->m_lines)
            writeLine(pString, pFile);
}


// string functions

void destroyString(String * pString)
{
      if(!pString)
            return;

      FREE(pString->m_buffer);
      FREE(pString);
}

String * createString(const char * pBuffer)
{
      String * tempString = ALLOC(String, 1);

      tempString->m_buffer = NULL;
      tempString->m_curLine = 0;
      tempString->m_curPos = 0;
      tempString->m_size = 0;
      tempString->m_lines = 0;

      int i;
      for(i = 0; ;i++)
      {
            if(pBuffer[i] == '\n')
                  tempString->m_lines++ ;
            if(pBuffer[i] == '\0')
                  break;

            tempString->m_size++ ;
      }

      tempString->m_buffer = ALLOC(char, tempString->m_size + 1);
      strcpy(tempString->m_buffer, pBuffer);

      return tempString;
}

char * getLineFromPos(char * destBuffer, const char * pBuffer, int startPos, bool getLineChar)
{
      int i, j, range;

      for(range = startPos; ; range++)
      {
            if(pBuffer[range] == '\n')
            {
                  range = getLineChar ? range + 1 : range;
                  break;
            }
            if(pBuffer[range] == '\0')
                  break;
      }

      for(j = 0, i = startPos; i < range; i++, j++)
            destBuffer[j] = pBuffer[i];

      destBuffer[j] = '\0';

      return destBuffer;
}


char * mergeStrings(const char * pBuffer1, const char * pBuffer2)
{
      int size1 = strlen(pBuffer1);
      int size2 = strlen(pBuffer2);

      char * tempBuffer = ALLOC(char, size1 + size2 + 1);

      int i, j;

      strcpy(tempBuffer, pBuffer1);
      strcat(tempBuffer, pBuffer2);

      FREE(pBuffer1);

      return tempBuffer;
}

int findChar(const char * pBuffer, int startPos, char c)
{
      int i;

      for(i = startPos; i < strlen(pBuffer); i++)
            if(pBuffer[i] == c)
                  return i;

      return -1;
}
