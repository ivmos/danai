<?php

dl('danai.so');
$a = "lala";

function patata() {
   $c = "kakla";

}

function prueba() {
   patata();
   $b = "jaja";
   echo "antes";
   danai_dump_symtables();
   echo "despues";
}


prueba();
