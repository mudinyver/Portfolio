#!/usr/bin/php
<?php
    $lines = file("Sports_emblematiques.data");
    $cmpt=2;
    $num="";
    $indice=0;
    $convertir=0;
    foreach($lines as $num){
        if ($num==="SECTION_".$cmpt."\n"){ //si on a fini la section $cmpt-1
            file_put_contents("depot/Sports_emblematiques".($cmpt-1).".data", $parFic);
            $parFic[0]="";
            $parFic[1]="";
            $parFic[2]="";
            $cmpt++;
            $indice=0;
        }
        $parFic[$indice]=$num;
        $indice++;
    }
    file_put_contents("depot/Sports_emblematiques".($cmpt-1).".data", $parFic); //dernière section

    while ($cmpt!=1){
        $lines = file("depot/Sports_emblematiques".($cmpt-1).".data");
        $lines[0] = explode("TITRE=", $lines[1]); //enlever TITRE=
        $lines[0] = $lines[0][1];
        $lines[1] = explode("PARAGRAPHES=", $lines[2]); //enlever PARAGRAPHES=
        $lines[1] = explode("|", $lines[1][1]); //créer un sous-tableau
        $lines[2] = "";
        $convertir = sizeof($lines[1])-1;
        while ($convertir!=-1){ //assigne les valeurs du sous-tab au tab
            $lines[$convertir+1] = $lines[1][$convertir]; //ne marche pas sur le titre
            $convertir--;
        }
        file_put_contents("depot/Sports_emblematiques".($cmpt-1).".data", $lines);
        $cmpt--;
    }
?>
