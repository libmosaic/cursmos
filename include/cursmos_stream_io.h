/** @file cursmos_stream_io.h
 */

#ifndef CURSMOS_STREAM_IO_H
#define CURSMOS_STREAM_IO_Hy

#include <mosaic/stream_io.h>
#include "cursmos.h"

/**
 * @ref fgetMOSAIC wrapper for CURS_MOS
 */
int fgetCURS_MOS (CURS_MOS *target, FILE *stream);
/// @ref fputFmtMOSAIC wrapper for CURS_MOS
#define fputFmtCURS_MOS(target, fmt, stream) \
		fputFmtMOSAIC ((target->img), (fmt), (stream))
/// @ref fputMOSAIC wrapper for CURS_MOS
#define fputCURS_MOS(target, stream) \
		fputMOSAIC ((target->img), (stream))

/**
 * Loads a @ref CURS_MOS from file.
 *
 * @param[in] target The target CURS_MOS
 * @param[in] file_name The name of the loading file
 *
 * @return 0 if successfully loaded CURS_MOS
 * @return errno on fail
 */
int LoadCURS_MOS (CURS_MOS *target, const char *file_name);

/// @ref SaveFmtMOSAIC wrapper for CURS_MOS
#define SaveFmtCURS_MOS(target, fmt, file_name) \
		SaveFmtMOSAIC ((target->img), (fmt), (file_name))

/// @ref SaveMOSAIC wrapper for CURS_MOS
#define SaveCURS_MOS(target, file_name) \
		SaveMOSAIC ((target->img), (file_name))

/**
 * Load a whole file of MOSAICs into a IMGS list
 *
 * @note This function supposes that the IMGS list is empty
 *
 * @param[out] imgs The IMGS list to be written into
 * @param[in] file_name The name of the loading file
 *
 * @return 0 on success
 * @return ERR on reading first MOSAIC
 * @return _errno_ if error on opening file
 */
int LoadIMGS (IMGS *imgs, const char *file_name);
/**
 * Save a whole bunch of MOSAICs into a file
 *
 * @param[out] imgs The IMGS list to be written in the file
 * @param[in] file_name The name of the saving file
 *
 * @return 0 on success
 * @return ERR on saving MOSAIC
 * @return _errno_ if error on opening file
 */
int SaveIMGS (IMGS *imgs, const char *file_name);



#endif
