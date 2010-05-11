PHP_ARG_ENABLE(danai,
   [Whether to enable the "danai" extension],
   [ enable-danai         Enable "danai" extension support])
if test $PHP_DANAI != "no"; then
   PHP_SUBST(DANAI_SHARED_LIBADD)
   PHP_NEW_EXTENSION(danai, danai.c, $ext_shared)
fi

