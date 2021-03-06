/*
 * mcachefs-vops.h
 *
 *  Created on: 21 oct. 2009
 *      Author: francois
 */

#ifndef MCACHEFSVOPS_H_
#define MCACHEFSVOPS_H_

#define MCACHEFS_VOPS_DIR "/.mcachefs"
#define MCACHEFS_VOPS_FILE_PREFIX "/.mcachefs/"


/**
 * *********************** VOPS *******************************
 */

/**
 * VOPS (Virtual files for operations) handling
 */

/**
 * Get the vops file list
 */
const char **mcachefs_vops_get_vops_list();

/**
 * Called at open(), build the content of the vops file
 */
void mcachefs_vops_build(struct mcachefs_file_t *mfile);

/**
 * Called at release() when openned for write, parse that contents we have been sent.
 */
void mcachefs_vops_parse(struct mcachefs_file_t *mfile);

/**
 * Cleanup vops ressources for a given file
 */
void mcachefs_vops_cleanup_vops(struct mcachefs_file_t *mfile);

/**
 * Get the size of the currently openned vops file, or default size if none opened.
 */
off_t mcachefs_vops_getsize(const char *path);

/**
 * VOPS file writer
 */
#define __VOPS_WRITE(__mfile,...) \
  do { if ( __mfile != NULL ) { \
    int wrb = snprintf(&(__mfile->contents[__mfile->contents_size]), __mfile->contents_alloced - __mfile->contents_size, __VA_ARGS__ ); \
    if ( wrb < 0 ) \
      { Bug ( "." ); } \
    if ( wrb < (int) (__mfile->contents_alloced - __mfile->contents_size) ) \
      { __mfile->contents_size += wrb; break; } \
    __mfile->contents_alloced += wrb * 2; \
    __mfile->contents = (char*) realloc ( __mfile->contents, __mfile->contents_alloced ); \
    /* Log("Now mvops content of %s is at %p\n", mvops->path, __mfile->contents); */ \
    if ( __mfile->contents == NULL ) \
      { Bug ( "." ); } \
  } else if (1) { fprintf(stderr, __VA_ARGS__); break; } else { break; } } while(1)

#endif /* MCACHEFSVOPS_H_ */
