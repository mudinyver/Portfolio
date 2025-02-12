#!/usr/bin/php
<?php

    $lines = file("../data/Tableau_des_medailles_v2.csv");
    $iso=file("../data/iso.txt");
    $tab=[];
    $nb=0;
    $a=0;
    $ind = 0;
    $num2=[];
    $y=[];
    // while ($nb < sizeof($lines)-3){ //assigne les valeurs du sous-tab au tab
    //     $lines[$nb] = $lines[$nb+3]; //ne marche pas sur le titre
    //     $nb++;
    // }
    while ($a < sizeof($lines)-3){
        $tab[$a]=$lines[$a];
        $a++;
    }

    //print_r($tab);

    $indice = 0;
    foreach($tab as $num){        
        $num = explode(",", $tab[$indice]);
        $num[4] = $num[1] + $num[2] + $num[3];
        $num = str_replace("\n", "", $num);
        $indice ++;
        
        $num2[6] = $num[4];
        $num2[5] = $num[3];
        $num2[4] = $num[2];
        $num2[3] = $num[1];
        $num2[2] = $iso[$indice-1];
        $num2[1] = $num[0];
        $num2[0] = 0;

        $num2[2] = rtrim($num2[2]);
        $num2[5] = rtrim($num2[5]);
        //print_r($numReassemble);
        $y[$indice] = $num2[0].",".$num2[1].",".$num2[2].",".$num2[3].",".$num2[4].",".$num2[5].",".$num2[6]."\n";
        //print_r($sortie);
        
    }
    file_put_contents("../data/tableau.csv", $y);
    echo "\n";   
?>
