#!/usr/bin/php
<?php

    $lines = file("../data/tableau2.csv");

    $indice = 0;
    $lastNumOr = 0;
    $lastNumAr = 0;
    $lastNumBr = 0;
    $y=[];
    foreach($lines as $num){
        $num = explode(",", $lines[$indice]);

        if($num[3] == $lastNumOr){
            if($num[4] == $lastNumAr){
                if($num[5] == $lastNumBr){
                    $num[0] = "-";
                }
                else{
                    $num[0] = $indice+1;
                }
            }
            else{
                $num[0] = $indice+1;
            }
        }
        else{
            $num[0] = $indice+1;
        }
        // print_r($num);
        // print_r("OR : ".$num[3]." AR : ".$num[4]." BR : ".$num[5]."\n");
        // print_r("OR : ".$lastNumOr." AR : ".$lastNumAr." BR : ".$lastNumBr."\n");
        $lastNumOr = $num[3];
        $lastNumAr = $num[4];
        $lastNumBr = $num[5];
        $indice++;
        $y[$indice] = $num[0].",".$num[1].",".$num[2].",".$num[3].",".$num[4].",".$num[5].",".$num[6];
    }
    file_put_contents("../data/tableau.csv", $y);

?>