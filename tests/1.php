<?php
dl('danai.so');
$a = true;
danai_print_type($a);
$a = new stdClass();
$a->attr = 25;
danai_print_type($a);
$a = 4;
danai_print_type($a);
$a = $a * 1000000000;
danai_print_type($a);
