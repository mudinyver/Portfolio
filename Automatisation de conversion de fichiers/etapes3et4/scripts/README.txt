Le fichier main doit être placé avec les fichiers à convertir. 
Les scripts doivent être dans un dossier scripts, dossier qui doit être placé avec les fichiers à convertir.
Le dossier paysDrapeaux doit être placé dans le dossier parent du dossier contenant les fichiers à convertir au cas où vous êtes à l'IUT. 

Toutes les images docker utilisées doivent être pull manuellement (voir plus bas).

Avertissement : Si vous êtes à l'IUT la commande wget de l'image docker sae103-wget ne fonctionnera pas d'où la nécessité du dossier paysDrapeaux.

Si vous êtes à l'IUT, ouvrez un terminal dans le dossier contenant les fichiers à convertir et faites les commandes suivantes :
docker image pull sae103-excel2csv
docker image pull sae103-imagick
docker image pull sae103-wget
docker image pull sae103-html2pdf
chmod +x mainIUT
./mainIUT

Si vous n'êtes pas à l'IUT, ouvrez un terminal dans le dossier contenant les fichiers à convertir et faites les commandes suivantes :
docker image pull bigpapoo/sae103-excel2csv
docker image pull bigpapoo/sae103-imagick
docker image pull bigpapoo/sae103-wget
docker image pull bigpapoo/sae103-html2pdf
chmod +x mainPasIUT
./mainPasIUT


Dans tous les cas, attendez que le script finisse de s'exécuter.
Tous vos fichiers devraient alors avoir été convertis, ils seraient donc dans le dossier depot. Pour accéder à ce dossier tapez la commande suivante :
cd ../depot
