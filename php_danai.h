#ifndef PHP_DANAI_H
/* Prevent double inclusion */
#define PHP_DANAI_H
/* Define Extension Properties */
#define PHP_DANAI_EXTNAME     "danai"
#define PHP_DANAI_EXTVER    "1.0"
/* Import configure options
    when building outside of
    the PHP source tree */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
/* Include PHP Standard Header */
#include "php.h"
/* Define the entry point symbol
 * Zend will use when loading this module
 */
extern zend_module_entry danai_module_entry;
#define phpext_danai_ptr &danai_module_entry
#endif /* PHP_DANAI_H */


/* Esto es para la ultima */
#if (PHP_MAJOR_VERSION > 5) || (PHP_MAJOR_VERSION == 5 && \
                                PHP_MINOR_VERSION > 0)
static
    ZEND_BEGIN_ARG_INFO_EX(php_danai_retref_arginfo, 0, 1, 0)
       ZEND_END_ARG_INFO ()
#endif /* PHP >= 5.1.0 */

#ifdef ZEND_ENGINE_2
   static
       ZEND_BEGIN_ARG_INFO(php_danai_byref_arginfo, 0)
           ZEND_ARG_PASS_INFO(1)
       ZEND_END_ARG_INFO()
#else /* ZE 1 */
   static unsigned char php_danai_byref_arginfo[] =
                                   { 1, BYREF_FORCE };
#endif

