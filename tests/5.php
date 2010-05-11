<?php

dl('danai.so');
$a = "lala";

danai_dump_globalsymtable();
function prueba() {
   $b = "jaja";
   echo "\n";
   danai_dump_currentsymtable();
}


prueba();
