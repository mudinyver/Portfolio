#!/usr/bin/php
<?php
    $lines = file("Tableau_des_medailles_v2.csv");
    $nb=0;
    while ($nb< sizeof($lines)-3){ //assigne les valeurs du sous-tab au tab
        $lines[$nb] = $lines[$nb+3]; //ne marche pas sur le titre
        $nb++;
    }
    file_put_contents("depot/Tableau_des_medailles_v2.csv", $lines);
?>