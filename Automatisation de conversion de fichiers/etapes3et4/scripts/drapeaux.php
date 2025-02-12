#!/usr/bin/php
<?php
    $lines = file("../data/iso.txt");
    $commandes[0]="#!/bin/bash\ncd ../data\n";
    $ligne="";
    foreach($lines as $num){
        $ligne= "wget https://flagcdn.com/80x60/$num.webp ";
        $commandes[$num]=str_replace("\n", "", $ligne);
        $commandes[$num]=$commandes[$num]."\n";
    }
    file_put_contents("../data/commandes", $commandes); //dernière section
?>
