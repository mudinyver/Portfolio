#!/usr/bin/php
<?php
    $lines2=[];
    $indice = 0;
    $tab = file("../data/tableau.csv");
    foreach($tab as $num){        
        $num = explode(",", $tab[$indice]);
        $num = str_replace("\n", "", $num);
        $indice ++;
        $lines2[$indice-1][0]=$num[0];
        $lines2[$indice-1][1]=$num[1];
        $lines2[$indice-1][6]=$num[2];
        $lines2[$indice-1][2]=$num[3];
        $lines2[$indice-1][3]=$num[4];
        $lines2[$indice-1][4]=$num[5];
        $lines2[$indice-1][5]=$num[6];
    }
    $iso=file("../data/iso.txt");
    $indiceDrapeau=0;
    $indiceMedailles=0;
    $totalMedailles=0;
    $drapeau=[];
    $drapeau_nom=[];
    $classement=[];
    $nb_medailles_or=[];
    $nb_medailles_argent=[];
    $nb_medailles_bronze=[];
    $pourcentage=[];
    foreach($iso as $unDrapeau){
        $totalMedailles=$totalMedailles+$lines2[$indiceMedailles][5];
        $indiceMedailles++;
    }
    $totalMedailles=$totalMedailles/100;


    foreach($iso as $unDrapeau){
        $drapeau[$indiceDrapeau]="<img src='paysDrapeaux/".$lines2[$indiceDrapeau][6].".webp'>";
        $drapeau_nom[$indiceDrapeau]="<th>".$drapeau[$indiceDrapeau]." ".$lines2[$indiceDrapeau][1]."</th>"."\n";
        $classement[$indiceDrapeau]="<th>".$lines2[$indiceDrapeau][0]."</th>"."\n";
        $nb_medailles_or[$indiceDrapeau]="<th>".$lines2[$indiceDrapeau][2]."</th>"."\n";
        $nb_medailles_argent[$indiceDrapeau]="<th>".$lines2[$indiceDrapeau][3]."</th>"."\n";
        $nb_medailles_bronze[$indiceDrapeau]="<th>".$lines2[$indiceDrapeau][4]."</th>"."\n";
        $pourcentage[$indiceDrapeau]="<th>".round($lines2[$indiceDrapeau][5]/$totalMedailles,2)." %</th>"."\n";
        $indiceDrapeau++;
    }
    $indiceLigne=0;
    $ligne=[];
    while ($indiceLigne < 91){
        $ligne[$indiceLigne]="<tr>".$drapeau_nom[$indiceLigne].$classement[$indiceLigne].$nb_medailles_or[$indiceLigne].$nb_medailles_argent[$indiceLigne].$nb_medailles_bronze[$indiceLigne].$pourcentage[$indiceLigne]."<th> | </th>";
        $indiceLigne++;
        if ($indiceLigne < 91){
            $ligne[$indiceLigne-1]=$ligne[$indiceLigne-1].$drapeau_nom[$indiceLigne].$classement[$indiceLigne].$nb_medailles_or[$indiceLigne].$nb_medailles_argent[$indiceLigne].$nb_medailles_bronze[$indiceLigne].$pourcentage[$indiceLigne]."</tr>";
            $indiceLigne++;
        }
    }
    $ligne=implode("\n",$ligne);
    $txt=
    "<!DOCTYPE html>
    <html xmlns=http://www.w3.org/1999/xhtml xml:lang='fr' lang='fr'>
        <head>
            <meta charset='utf-8'><title id='titre'>Tableau des médailles des JO</title>
            <style>
            *{
                margin:0;
                padding:0;
                font-family: Arial, Helvetica, sans-serif;
            }
            img{
                width:10px;
            }
            th{
                font-size: 10px;
            } 
            table{
                height:35%;
            }
            </style>

            <meta name='author' content='UDIN--YVER Mael'>
        </head>
        <body>
            <main>
                <h4>Tableau des médailles par pays au JO de Paris 2024<img src='logoJO.png'></h4>
                <h5>Sens de lecture : de gauche à droite puis de haut en bas</h5>
                <article>
                    <table>
                        <thead>
                        <tr>
                            <th>Nom</th>
                            <th>Classement</th>
                            <th>Or</th>
                            <th>Argent</th>
                            <th>Bronze</th>
                            <th>Pourcentage</th>
                            <th> | </th>
                            <th>Nom</th>
                            <th>Classement</th>
                            <th>Or</th>
                            <th>Argent</th>
                            <th>Bronze</th>
                            <th>Pourcentage</th>
                        </tr>
                        </thead>
                        <tbody>
                            ".$ligne."
                        </tbody>
                    </table>
                </article>
            </main>
        </body>
    </html>";
    file_put_contents("../data/a.html", $txt);


?>