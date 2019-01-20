#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "geometry.h"
#include "texturemanager.h"
#include "memdebug.h"

/** \brief
 *
 * Enum for buttons in main menu
 *
 */
typedef enum BUTTONS
{
      PLAY_BTN,
      OPTION_BTN,
      HIGHSCORE_BTN,
      ABOUT_BTN,
      EXIT_BTN
} BUTTONS;

/** \brief
 *
 * Enum for button in options
 *
 */
typedef enum OPTION_BUTTONS
{
      SOUND_BTN,
      SOUND_LEFT_BTN,
      SOUND_RIGHT_BTN,
      MUSIC_BTN,
      MUSIC_LEFT_BTN,
      MUSIC_RIGHT_BTN
} OPTION_BUTTONS;

/** \brief
 *
 * Struct which describe a button
 *
 */
typedef struct Button
{
      char * m_textureID; /**< \brief Key of textures of button when no active or active */
      Point * m_position; /**< \brief Position on a screen */
      int m_height; /**< \brief Height in pixels */
      int m_width; /**< \brief Width in pixels */
      int m_maxFrames; /**< \brief Max different number of textures */
      bool m_active; /**< \brief Check if button is active */

} Button;

/** \brief
 *
 * This function create button
 *
 * \param textureID - Textures of Button
 * \param position - Position on a screen
 * \param height - Height in pixels
 * \param width - Width in pixels
 * \param currentState - State of Button (active or not)
 * \return Ptr on Button
 *
 */
Button * createButton(const char * textureID, Point * position, int height, int width, bool currentState);

/** \brief
 *
 * This function destroy button
 * \param pButton - Ptr on Button
 * \return Nothing
 *
 */
void destroyButton(Button * pButton);

/** \brief
 *
 * This function draws button on screen
 *
 * \param pButton - Ptr on Button
 * \param pTextureManager - Ptr on TextureManager
 * \return Nothing
 *
 */
void drawButton(Button * pButton, TextureManager * pTextureManager);


#endif // BUTTON_H_INCLUDED
