/* newlib.hpp */
/***********************************************************************************/
/**                                                                                */
/**              RESOURCES AND DEFINITIONS FOR NEWLIB POGRAM                       */
/**                                                                                */
/**--------------------------------------------------------------------------------*/
/**                                                                                */
/**  History: 05/17/2018 - Initial Release, Ryan M. McHale                         */
/**                                                                                */
/***********************************************************************************/

#ifndef _NEWLIB_HPP_
#define _NEWLIB_HPP_

/**
 ****  1 - Configuration And Parameter Constants
 */



/** 1.2 - Error Codes */


/** 1.3 - Internal Error Codes */
#define INT_ERR_No_Args_Provided 100
#define INT_ERR_Invalad_Argument 101


/**
 ****  2 - Prototypes of Public Functions
 */

/** 2.1 - Functions for library creation */
extern int ParseInput(int argc, char **argv);
extern int CreateHeader(void);
extern int CreateSource(void);

#endif /** _NEWLIB_HPP_ */
