/** @file cursmos.h
 * Curses wrapper for @ref MOSAIC
 */

#ifndef CURSMOS_H
#define CURSMOS_H

#include <curses.h>
#include <panel.h>

#include <mosaic/mosaic.h>

/**
 * Curses Mosaic: wraps the MOSAIC; list and curses interface
 * 
 * The MOSAIC structured as a double linked list, for sequencial matters ["video",
 * as we like to call it] and Curses interface.
 */
typedef struct curs_mos_t {
	MOSAIC *img;	///< the asc art itself
	int y,		///< the Y coordinate of the piece of @ref img showed at the pad
		x;		///< the X coordinate of the piece of @ref img showed at the pad
	struct curs_mos_t *prev,	///< previous CURS_MOS
					  *next;	///< next CURS_MOS
	WINDOW *win;	///< window for showing the MOSAIC
	PANEL *pan;		///< panel for showing the window
} CURS_MOS;


/// Whole images circular double linked list and it's size
typedef struct {
	CURS_MOS *list;	///< the first image
	unsigned int size;	///< the array size
} IMGS;


/// Initializes the IMGS
void InitIMGS (IMGS *everyone);
/// Puts the first CURS_MOS in imgs, making it a circular list with itself
void CircularIMGS (IMGS *imgs, CURS_MOS *mos);
/** 
 * Create a new @ref CURS_MOS, allocating the necessary memory
 * 
 * @param[in] new_height New MOSAIC's height
 * @param[in] new_width New MOSAIC's width
 * 
 * @return New @ref CURS_MOS, clean and unlinked
 * @return __NULL__ if allocation failed
 */
CURS_MOS * NewCURS_MOS (int new_height, int new_width);

/**
 * Gets a CURS_MOS inside a CURS_MOS: CURS_MOSception!
 *
 * @note SubCURS_MOS shares memory with it's relative CURS_MOS, so
 * changes affecting one will affect the other.
 *
 * @warning Freeing a SubCURS_MOS must be done before it's relative, as curses'
 * subWINDOWs must be freed before it's relatives. This is different from 
 * SubMOSAICs, which are used here.
 *
 * @param[in] parent	The outter CURS_MOS
 * @param[in] begin_y 	The upper-left Y coordinate, where inner CURS_MOS begins
 * @param[in] begin_x 	The upper-left X coordinate, where inner CURS_MOS begins
 * @param[in] height	Inner CURS_MOS' height
 * @param[in] width		Inner CURS_MOS' width
 *
 * @return SubCURS_MOS
 * @return NULL on allocation errors, or if coordinates get out of bounds
 */
CURS_MOS * SubCURS_MOS (CURS_MOS *parent, int height, int width, int begin_y, int begin_x);
/**
 * Rewrite target's WINDOW from scratch
 *
 * @note This function doesn't refresh the WINDOW
 *
 * @param[in] target CURS_MOS to have it's WINDOW rewritten
 */
void RewriteCURS_MOS (CURS_MOS *target);
/**
 * Resize a @ref CURS_MOS, resizing the MOSAIC inside and it's WINDOW
 * @sa ResizeCURS_MOS_WINDOW
 * 
 * @param[in] target the target CURS_MOS
 * @param[in] new_height CURS_MOS' new height
 * @param[in] new_width CURS_MOS' new width
 * 
 * @return 0 if successfully resized @ref CURS_MOS
 * @return ERR if allocation failed
 */
int ResizeCURS_MOS (CURS_MOS *target, int new_height, int new_width);
/**
 * Resize a @ref CURS_MOS' WINDOW
 * @sa ResizeCURS_MOS
 *
 * @note This function just resizes the WINDOW, without caring about erasing or
 * showing it on the screen
 *
 * @param[in] target the target CURS_MOS
 * @param[in] new_height CURS_MOS' new height
 * @param[in] new_width CURS_MOS' new width
 */
void ResizeCURS_MOS_WINDOW (CURS_MOS *target, int new_height, int new_width);
/**
 * @ref TrimMOSAIC wrapper for CURS_MOS
 *
 * @param[in] target Target CURS_MOS
 * @param[in] resize Bool: sould we resize the mosaic?
 *
 * @return The return from TrimMOSAIC
 */
int TrimCURS_MOS (CURS_MOS *target, char resize);
/**
 * Only to say if you want to link the img before or after the other in LinkMOSAIC
 */
enum direction {after = 0, before};
/**
 * Link an image to another, before or after it
 * 
 * @param[in] dest Image linked to
 * @param[in] src Image to link to dest
 * @param[in] dir Link src before or after dest
 */
void LinkCURS_MOS (CURS_MOS *dest, CURS_MOS *src, enum direction dir);

/**
 * Add a char to the CURS_MOS at position y/x and print it in it's WINDOW.
 * 
 * @note It doesn't refresh the WINDOW, so do it yourself whenever you feel ready
 * 
 * @return 0 on success
 * @return ERR on error
 */
int curs_mosSetCh (CURS_MOS *image, int y, int x, int c);
/// Just a nice definition for getting the mos_char
#define curs_mosGetCh(i, y, x)		(mosGetCh (i->img, y, x))
/// Another nice definition for mos_char, without boundaries checking
#define _curs_mosGetCh(i, y, x)		(_mosGetCh (i->img, y, x))

/**
 * Set a char's attr at position y/x and update it's WINDOW.
 *
 * @note It doesn't refresh the WINDOW, so do it yourself whenever you feel ready
 * 
 * @return 0 on success
 * @return ERR on error
 */
int curs_mosSetAttr (CURS_MOS *image, int y, int x, mos_attr a);
/// Just a nice definition for getting the mos_attr
#define curs_mosGetAttr(i, y, x)	(mosGetAttr (i->img, y, x))
/// Another nice definition for mos_attr, without boundaries checking
#define _curs_mosGetAttr(i, y, x)		(_mosGetAttr (i->img, y, x))
/**
 * Displays current CURS_MOS in the stdscr
 * 
 * @param[in] current CURS_MOS
 */
void DisplayCurrentMOSAIC (CURS_MOS *current);

/**
 * Destroy a CURS_MOS, deallocating the used memory
 */
void FreeCURS_MOS (CURS_MOS *image);
/**
 * Destroy and free memory from the images list
 * 
 * @warning This function should be called before exiting a program
 * with a IMGS struct, unless you know what you're doing...
 */
void DestroyIMGS (IMGS *everyone);

#endif
