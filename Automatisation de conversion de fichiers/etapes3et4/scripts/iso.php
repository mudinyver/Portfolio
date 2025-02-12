#!/usr/bin/php
<?php
    $lines = file("../depot/Tableau_des_medailles_v2.csv");
    $tab=[];
    $nb=0;
    $a=0;
    $ind = 0;
    while ($nb < sizeof($lines)-3){ //assigne les valeurs du sous-tab au tab
        $lines[$nb] = $lines[$nb+3]; //ne marche pas sur le titre
        $nb++;
    }
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
        
        $num[5] = $num[4];
        $num[4] = $num[3];
        $num[3] = $num[2];
        $num[2] = $num[1];
        $num[1] = $num[0];
        $num[0] = "-";

        $num = $num[0].",".$num[1].",".$num[2].",".$num[3].",".$num[4].",".$num[5]."\n";
        $y[$indice]=$num;
        //print_r($sortie);
        
    }
    // $indice = 0;
    for($i = 0; $i <= 91; $i++){
        $sous_tab = explode(",", $y[$i]);
        $placement[$i][0]=$i;
        $placement[$i][1]=$sous_tab[5];
        print_r($placement[$i]);
    }
    echo "\n";
    
    
?>
