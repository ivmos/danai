<?php
dl('danai.so');
$a = 5;
$b = &$a;
$c = &$a;
danai_print_refcount($a);
danai_print_type($a);
