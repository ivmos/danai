#include "php_danai.h"

PHP_FUNCTION(danai_hola_mundo)
{
   php_printf("Hola mundo!\n");
}


PHP_FUNCTION(danai_print_refcount)
{
    zval *arg;
    if (zend_get_parameters(ZEND_NUM_ARGS(), 1, &arg) == FAILURE) {
        RETURN_NULL();
    }
    if (!arg->is_ref) {
        return;
    }

    php_printf("Referenciado %d veces.\n", arg->refcount);
}



PHP_FUNCTION(danai_print_type)
{
   zval *arg;
   if (zend_get_parameters(ZEND_NUM_ARGS(), 1, &arg) == FAILURE) {
      php_error_docref(NULL TSRMLS_CC, E_WARNING, "Falta el parámetro.");
      RETURN_NULL();
   }
   switch (arg->type) {
      case IS_NULL:
         php_printf("Tipo: IS_NULL\n");
         break;
      case IS_BOOL:
         php_printf("Tipo: IS_BOOL\n");
         break;
      case IS_LONG:
         php_printf("Tipo: IS_LONG\n");
         break;
      case IS_DOUBLE:
         php_printf("Tipo : IS_DOUBLE\n");
         break;
      case IS_STRING:
         php_printf("Tipo : IS_STRING\n");
         break;
      case IS_ARRAY:
         php_printf("Tipo : IS_ARRAY\n");
         break;
      case IS_OBJECT:
         php_printf("Tipo : IS_OBJECT\n");
         break;
      case IS_RESOURCE:
         php_printf("Tipo: IS_RESOURCE\n");
         break;
      default:
         php_printf("Otro tipo\n");
   }

}

void php_danai_print_var_hash(HashTable *arrht)
{
    for(zend_hash_internal_pointer_reset(arrht);
    zend_hash_has_more_elements(arrht) == SUCCESS;
    zend_hash_move_forward(arrht)) {
        char *key;
        uint keylen;
        ulong idx;
        int type;
        zval **ppzval, tmpcopy;
        type = zend_hash_get_current_key_ex(arrht, &key, &keylen,
                                                    &idx, 0, NULL);
        if (zend_hash_get_current_data(arrht, (void**)&ppzval) == FAILURE) {
             /* Should never actually fail
              * since the key is known to exist. */
             continue;
        }
        /* Duplicate the zval so that
          * the orignal's contents are not destroyed */
        tmpcopy = **ppzval;
        zval_copy_ctor(&tmpcopy);
        /* Reset refcount & Convert */
        INIT_PZVAL(&tmpcopy);
        convert_to_string(&tmpcopy);
        /* Output */
        php_printf("The value of ");
        if (type == HASH_KEY_IS_STRING) {
             /* String Key / Associative */
             PHPWRITE(key, keylen);
        } else {
             /* Numeric Key */
             php_printf("%ld", idx);
        }
        php_printf(" is: ");
        PHPWRITE(Z_STRVAL(tmpcopy), Z_STRLEN(tmpcopy));
        php_printf("\n");
        /* Toss out old copy */
        zval_dtor(&tmpcopy);
    }
}


PHP_FUNCTION(danai_dump_globalsymtable)
{
      php_printf("Tabla de simbolos global : \n\n");
      php_danai_print_var_hash(&(EG(symbol_table)));
}

PHP_FUNCTION(danai_dump_currentsymtable)
{
      php_printf("Tabla de simbolos actualmente activa : \n\n");
      php_danai_print_var_hash(EG(active_symbol_table));
}

PHP_FUNCTION(danai_dump_symtables)
{

   int i = 0;
   php_printf("El tamaño de la cache es %d\n", SYMTABLE_CACHE_SIZE);

   php_printf("Ahora mismo hay %d tablas de símbolos.\n", EG(symtable_cache_limit));
   while (i <= *(EG(symtable_cache_limit))) {
      php_printf("%d\n",i);
      //php_danai_print_var_hash(EG(symtable_cache[1]));
      i++;
   }


}


   static function_entry php_danai_functions[] = {
      PHP_FE(danai_print_refcount, php_danai_byref_arginfo)
         PHP_FE(danai_print_type, NULL)
         PHP_FE(danai_dump_globalsymtable, NULL)
         PHP_FE(danai_dump_currentsymtable, NULL)
         PHP_FE(danai_dump_symtables, NULL)
         { NULL, NULL, NULL }
   };



zend_module_entry danai_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
   STANDARD_MODULE_HEADER,
#endif
   PHP_DANAI_EXTNAME,
   php_danai_functions, /* Functions */
   NULL, /* MINIT */
   NULL, /* MSHUTDOWN */
   NULL, /* RINIT */
   NULL, /* RSHUTDOWN */
   NULL, /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
   PHP_DANAI_EXTVER,
#endif
   STANDARD_MODULE_PROPERTIES
};
#ifdef COMPILE_DL_DANAI
ZEND_GET_MODULE(danai)
#endif

