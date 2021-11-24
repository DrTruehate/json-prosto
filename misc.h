/*
 * misc.h
 *
 *  Created on: 08 июня 2021 г.
 *      Author: Eugene Frantsuzov
 */
#ifndef MISC_H_
#define MISC_H_

#define PTR_SIZEOF(type, obj) (type *)&obj, sizeof(obj)
#define BZERO(array)          bzero( array, sizeof(array) )
#define TZERO(obj)            bzero( &obj, sizeof(obj) )

#define PROGNAME(str) \
  ( ( str = strrchr(argv[0], '/') ) != NULL ) ? str++ : (str = argv[0])

#define ERROR(message, ...) \
  do { \
    fprintf(stderr, "Line: %d  Function: %s()  " message, \
            __LINE__, __FUNCTION__, ##__VA_ARGS__); \
    exit(EXIT_FAILURE); \
  } while(0)

#define ERR_RET(message, ...) \
  do { \
    fprintf(stderr, message, ##__VA_ARGS__); \
    return EXIT_FAILURE; \
  } while(0)

#endif // MISC_H_
