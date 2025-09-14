package modele;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.text.Normalizer;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;

public class Liste {
    private static ArrayList<Membre> membres = new ArrayList<>();//1 seule liste nécessaire
    private static String nomF = "svgRechercheRes";
//    private static HashMap<SvgListe,ArrayList<Membre>> svg = Liste.restitue();

    public Liste() {
    }

    public Liste(Membre membre) {
        Liste.membres.add(membre);
    }

    public String afficheS(){
        String s = "Liste de membres : \n";
        for (Membre membre : membres) {
            s+=membre.getNumero()+" : "+membre.getPrenom()+" "+membre.getNom()+"\n";
        }
        return s;

    }

    public void affiche(){
        System.out.println(this.afficheS());
    }


    static private void addMembre(Membre m){
        Liste.membres.add(m);
    }

    private void removeMembre(Membre m){
        Liste.membres.remove(m);
    }

    static public void ajouterMembre(Membre m){
        if (m==null){
            System.out.println("");
        }else if(Liste.membres.contains(m)){
            //System.out.println("Dejà la");
        }else{
            Liste.addMembre(m);
        }
    }

    public void enleverMembre(Membre m){
        if (m==null){
            System.out.println();
        }else if(Liste.membres.contains(m)){
            this.removeMembre(m);
        }else{
            System.out.println();
        }
    }

    public static ArrayList<Membre> aPaye(ArrayList<Membre> aFiltrer){//ne garde que les membres ayant payé
        ArrayList<Membre> aPaye = new ArrayList<>();
        for (Membre i : aFiltrer) {
            if (i.calculMontantPaye()>=0){
                aPaye.add(i);
            }
        }
        return aPaye;
    }

    public static ArrayList<Membre> aPasPaye(ArrayList<Membre> aFiltrer){//ne garde que les membres n'ayant PAS payé
        ArrayList<Membre> aPasPaye = new ArrayList<>();
        for (Membre i : aFiltrer) {
            if (i.calculMontantPaye()<0){
                aPasPaye.add(i);
            }
        }
        return aPasPaye;
    }

    private static ArrayList<Membre> filtrageCours(ArrayList<Membre> aFiltrer,ArrayList<String> filtrageType,ArrayList<Integer> filtrageNiveau){// ne garde que les cours ayant les niveaux ET les types sélectionnés
        ArrayList<Membre> aCoursC = new ArrayList<>();
        for (Membre i : aFiltrer) {
            for (Cours c : i.getCours()){
                if (filtrageType.contains(c.getType()) && filtrageNiveau.contains(c.getNiveau()) && aCoursC.contains(i)==false){
                    aCoursC.add(i);
                }
            }
        }
        return aCoursC;
    }

    private static String inversionAlphabetique(String aInverser){//pour un ordre anti-alphabétique
        aInverser = Normalizer.normalize(aInverser, Normalizer.Form.NFD);//sépare les accents des lettres ; ë -> e+¨
        aInverser = aInverser.toLowerCase(); //transforme les majuscules en minuscule
        String stringInverse = "";
        char stringChar;
        char milieuAlphabetSup = 'n'; //médiane supérieur
        char milieuAlphabetInf = 'm'; //médiane inférieur
        for (int i = 0; i < aInverser.length(); ++i) {
            stringChar = aInverser.charAt(i);
            if (stringChar>='a' && stringChar<+'z'){
                //inversion grâce à la distance à la médiane ; a -> y ; d -> v etc
                if (stringChar>'m'){
                    stringInverse += (char) (stringChar-(stringChar -milieuAlphabetSup)*2);
                }else{
                    stringInverse += (char) (stringChar-(stringChar -milieuAlphabetInf)*2);
                }
            }else if (stringChar=='_' || stringChar=='-' || stringChar==' '){
                //conservation des accents, tirets et espaces mais effacement des accents, cédilles, etc
                stringInverse +=stringChar;
            }
        }
        return stringInverse;
    }

    private static String inversionNumerique(String aInverser){// pour un ordre antéchronologique
        String stringInverse = "";
        char stringChar;
        char milieuNumerique = (char) ('0'+'9')/2; //médiane
        for (int i = 0; i < aInverser.length(); ++i) {
            stringChar = aInverser.charAt(i);
            stringInverse += (char) (1+stringChar-(stringChar -milieuNumerique)*2);
            //inversion grâce à la distance à la médiane ; 9 -> 0 ; 3 -> 7 etc
        }
        return stringInverse;
    }
    
//    public static void sauvegarder(){
//        try{
//            ObjectOutputStream sortie = new ObjectOutputStream(new FileOutputStream(nomF));
//            sortie.writeObject(Liste.svg);
//            sortie.close();
//        }catch(IOException e){
//            System.out.println("Le fichier n'existe pas. La sauvegarde n'est pas effectuée.");
//        }
//    }
    
//    public static HashMap<SvgListe,ArrayList<Membre>> restitue(){
//        HashMap<SvgListe,ArrayList<Membre>> a = null;
//        try{
//            ObjectInputStream entree = new ObjectInputStream(new FileInputStream(nomF));
//            a = (HashMap<SvgListe,ArrayList<Membre>>) entree.readObject();
//            entree.close();
//        }catch (IOException e) {
//           System.out.println("Erreur à la lecture du fichier. " + e.getMessage());
//        }catch (ClassNotFoundException e) {
//           System.out.println("Fichier introuvable. " + e.getMessage());
//        }
//        return a;
//   }


    public static ArrayList<Membre> svgRecherche(ArrayList<Membre> aTrier,boolean filterSurPaye, ArrayList<String> filtrageType ,ArrayList<Integer> filtrageNiveau,ArrayList<Integer> ordreTriage){
        return Liste.multiTriPrep(aTrier, filterSurPaye, filtrageType , filtrageNiveau, ordreTriage);
        // SvgListe recherche = new SvgListe(aTrier, filterSurPaye, filtrageType , filtrageNiveau, ordreTriage);
        // ArrayList<Membre> aRetourner;
        // if (svg==null){
        //     svg = new HashMap<>();
        // }
        // if(svg.containsKey(recherche)){
        //     aRetourner = svg.get(recherche);
        //     System.out.println("------------");
        // }else{
        //     aRetourner = multiTriPrep(aTrier, filterSurPaye, filtrageType , filtrageNiveau, ordreTriage);
        //     svg.put(recherche,aRetourner);
        //     Liste.sauvegarder();
        // }
        // return aRetourner;
    }



    private static ArrayList<Membre> multiTri(ArrayList<Membre> aTrier){
        Collections.sort(aTrier, new Comparator<Membre>() {
            //tri via l'ordre ASCII des caractères de valTraitementPourListe de chaque membre

            public int compare(Membre m1, Membre m2) {
                return m1.getValTraitementPourListe().compareToIgnoreCase(m2.getValTraitementPourListe());
            }
        });
        return aTrier;
    }

    public static ArrayList<Membre> multiTriPrep(ArrayList<Membre> aTrier,boolean filterSurPaye, ArrayList<String> filtrageType ,ArrayList<Integer> filtrageNiveau, ArrayList<Integer> ordreTriage){
        //System.out.println(aTrier);
        if (filterSurPaye==false){
            aTrier=Liste.aPasPaye(aTrier);
        }else{
            aTrier=Liste.aPaye(aTrier);
        }
        if (filtrageType.size()>0 && filtrageNiveau.size()>0){
            aTrier=Liste.filtrageCours(aTrier,filtrageType,filtrageNiveau);//filtrage sur les types et niveaux sélectionnés
        }
        String[] ordre = new String[aTrier.size()]; //sert à initialiser valTraitementPourListe
        int jndex;
        jndex=0;
        for (Membre m : aTrier) {//initialisation des String
            ordre[jndex]="";
            jndex++;
        }

        for (int index = 0; index < ordreTriage.size(); index++) { 
            //crée l'ordre de priorité des tris et indique si certains sont croissants ou décroissants
            //décroissance obtenue via l'utilisation de fonctions donnant l'inverse de caractères alphabétiques et numériques
            
            
            
            if (ordreTriage.get(index)%2==0){ // tri sur les noms des membres
                jndex=0;
                if (ordreTriage.get(index)>0){ //ordre alphabétique
                    for (Membre m : aTrier) {
                        ordre[jndex]+=m.getNom()+"_"+m.getPrenom()+"_";
                        jndex++;
                    }
                }else{
                    for (Membre m : aTrier) { //ordre anti-alphabétique
                        ordre[jndex]+= Liste.inversionAlphabetique(m.getNom()+"_"+m.getPrenom()+"_");
                        jndex++;
                    }
                }
            }else if (ordreTriage.get(index)%3==0){ //tri sur la date d'inscription d'un membre
                jndex=0;
                if (ordreTriage.get(index)>0){ // ordre chronologique
                    for (Membre m : aTrier) {
                        ordre[jndex]+=m.getSaison().getDebut()+"_";
                        jndex++;
                    }
                }else{
                    for (Membre m : aTrier) { // ordre antéchronologique
                        ordre[jndex]+= Liste.inversionNumerique(m.getSaison().getDebut()+"_");
                        jndex++;
                    }
                }
            }else if (ordreTriage.get(index)%7==0){ // tri sur les des cours
                jndex=0;
                for (Membre m : aTrier) {
                    ArrayList<Cours> cours = m.getCours();
                    Collections.sort(m.getCours(), new Comparator<Cours>() {//range les cours selon leur type, niveau et nom

                    public int compare(Cours c1, Cours c2) {
                        return c1.getValTraitementPourListe().compareToIgnoreCase(c2.getValTraitementPourListe());
                        }
                    });

                    
                    if (ordreTriage.get(index)>0){// ordre alphabétique
                        for (Cours c0 : cours) {
                            ordre[jndex]+=c0.getValTraitementPourListe()+"_";
                        }
                        jndex++;
                    }else{
                        for (Cours c0 : cours) {// ordre anti-alphabétique
                            ordre[jndex]+= Liste.inversionAlphabetique(c0.getType())+Liste.inversionNumerique(String.valueOf(c0.getNiveau()))+Liste.inversionAlphabetique(c0.getIntitule()+"_");
                        }
                        jndex++;
                    }
                }
            }
        }
        int indexVal=0;
        for (Membre m : aTrier) {
            aTrier.get(indexVal).setValTraitementPourListe(ordre[indexVal]);
            System.out.println(aTrier.get(indexVal).getValTraitementPourListe());
            indexVal++;
        }
        return Liste.multiTri(aTrier);
    }

    
    public static ArrayList<Membre> getMembres() {
        return membres;
    }


    public static void main(String[] args) {
//    	Membre a = new Membre("DELERUE","Maël","6 rue Jean Pillard",30.0,new Saison("2023", "2024"));
//        Membre b = new Membre("UDIN--YVER","Mael","6 rue Jean Pillard",30.0,new Saison("1984", "2024"));
//        Membre c = new Membre("LEFRANÇOIS","Julien","6 rue Jean Pillard",30.0,new Saison("2007", "2022"));
//        Membre e = new Membre("DELERUE","Maël","6 rue Jean Pillard",30.0,new Saison("2003", "2004"));
//        Membre f = new Membre("UDIN--YVER","Ethan","6 rue Jean Pillard",30.0,new Saison("1984", "2024"));
//        Membre g = new Membre("LEFRANÇOIS","Jules","6 rue Jean Pillard",30.0,new Saison("2007", "2022"));
//        a.ajouterCours(new Cours("AM", "1h00","Dance classique",1));
//        a.ajouterCours(new Cours("Bac",  "1h45","Dance latine",2));
//        a.ajouterCours(new Cours("Colis",  "1h30","Dance classique",3));
//        b.ajouterCours(new Cours("Allo",  "0h45","Dance latine",1));
//        f.ajouterCours(new Cours("Allo",  "1h00","Dance rock",1));
//        c.ajouterCours(new Cours("Ayo",  "2h00","Dance rock",3));
//        c.ajouterCours(new Cours("Ayo",  "3h00","Dance latine",2));
//        g.ajouterCours(new Cours("Ayo",  "4h00","Dance classique",2));
//
//        Liste l = new Liste();
//        l.ajouterMembre(a);
//        l.ajouterMembre(b);
//        l.ajouterMembre(c);
//        l.ajouterMembre(e);
//        l.ajouterMembre(f);
//        l.ajouterMembre(g);
//        //System.out.println(Liste.triageAlphabetique(l.getMembres(), 1));
//        ArrayList<Integer> ordre = new ArrayList<>();
//
//        //choix ordre tri
//        // 2 pour nom ; 3 pour saison ; 7 pour cours
//        ordre.add(-7);
//        ordre.add(2);
//        ArrayList<Membre> li = new ArrayList<>();
//        ArrayList<String> lTypeCours = new ArrayList<>();
//        ArrayList<Integer> lNiveauCours = new ArrayList<>();
//        li = Liste.multiTriPrep(Liste.membres, false, lTypeCours, lNiveauCours, ordre);
//        for (Membre m : li) {
//            m.afficheTestsTri();
//        }
    }

    

    
}
