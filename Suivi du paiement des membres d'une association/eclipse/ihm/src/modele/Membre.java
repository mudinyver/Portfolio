package modele;

import java.io.Serializable;
import java.util.ArrayList;
public class Membre implements Serializable{
    static private int id = 0;
    static private Liste l = new Liste();
    private int numero;
    private String nom;
    private String prenom;
    private String coordonnees;
    private double montantDu;
    private double montantPaye;
    private String tarifApplique;
    private String valTraitementPourListe; //Ne pas modifier
    private String typeCoursAvecNiveau;
    private ArrayList<String> lTypeCours;
    private int compteJour;
    private ArrayList<DocsGeneres> docsGeneres;
    private ArrayList<Paiement> paiements;
    private ArrayList<Cours> cours;
    private Saison saisonInscription;

    static final int NB_JOUR_DESINSCRIPTION_COURS = 20;

    public Membre(String nom, String prenom, String coordonnees, /*double montantDu,*/ double montantPaye, Saison saisonInscription) {
        this.nom = nom;
        this.prenom = prenom;
        this.coordonnees = coordonnees;
        this.montantDu = 0.0;
        this.montantPaye = 0.0;
        this.saisonInscription=saisonInscription;

        this.compteJour=0;
        this.tarifApplique="Plein tarif";
        this.valTraitementPourListe="";
        this.docsGeneres = new ArrayList<>();
        this.paiements = new ArrayList<>();
        this.cours = new ArrayList<>();
        this.lTypeCours = new ArrayList<>();
        this.typeCoursAvecNiveau = "";
        this.numero = id++;

        l.ajouterMembre(this);
    }

    public Membre(String tarifApplique, String nom, String prenom, String coordonnees, /*double montantDu,*/ double montantPaye, Saison saisonInscription) {
        this.nom = nom;
        this.prenom = prenom;
        this.coordonnees = coordonnees;
        this.montantDu = 0.0;
        this.montantPaye = 0.0;
        this.saisonInscription=saisonInscription;
        this.tarifApplique=tarifApplique;

        this.compteJour=0;
        this.valTraitementPourListe="";
        this.docsGeneres = new ArrayList<>();
        this.paiements = new ArrayList<>();
        this.cours = new ArrayList<>();
        this.lTypeCours = new ArrayList<>();
        this.typeCoursAvecNiveau = "";
        this.numero = id++;

        l.ajouterMembre(this);
    }

    public Membre(String nom, String prenom, String coordonnees, /*double montantDu,*/ double montantPaye) {
        this.nom = nom;
        this.prenom = prenom;
        this.coordonnees = coordonnees;
        //this.montantDu = montantDu;
        this.montantPaye = 0.0;

        this.saisonInscription= new Saison("2024", "2025" );
        this.compteJour=0;
        this.tarifApplique="Plein tarif";
        this.valTraitementPourListe="";
        this.docsGeneres = new ArrayList<>();
        this.paiements = new ArrayList<>();
        this.cours = new ArrayList<>();
        this.lTypeCours = new ArrayList<>();
        this.typeCoursAvecNiveau = "";
        this.numero = id++;

        l.ajouterMembre(this);
    }

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Affichage %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

    public String affiche(){
        return nom + " " + prenom + "\n" +"coordonnées : " + coordonnees + "\n" + "Reste à payer : " + this.calculMontantDu() + " - " + montantPaye + " = " + calculMontantPaye();
    }

    @Override
    public String toString() {
        return "Membre [numero=" + numero + ", nom=" + nom + ", prenom=" + prenom + ", coordonnees=" + coordonnees + ", montantDu=" + this.calculMontantDu() + ", montantPaye=" + montantPaye + "]\n";
    }

    public void afficheTestsTri() {
        System.out.println(nom + " " + prenom + " | " + this.saisonInscription.getDebut() + " | "+this.cours + "\n");
    }

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Méthode %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

    public void envoieMail(){
        new Mail(this);
    }

    public double calculMontantPaye(){
       return this.calculMontantDu()-this.montantPaye;
    }
    
    public double calculMontantTotPaiements(){
        double aRetourner=0.0;
        if (this.paiements.size()>0){
            for (Paiement p : this.paiements){
                aRetourner+=p.getMontant();
            }
        }
        this.montantPaye=aRetourner;
        return aRetourner;
    }

    public double calculMontantDu(){
        double aRetourner=0.0;
        if (this.getCours().size()>0){
            for (Cours c : this.cours){
                aRetourner+=c.calculPrix(this.tarifApplique);
            }
        }
        this.montantDu=aRetourner;
        return aRetourner;
    }

    public boolean desinscription(Membre m){
        boolean boo=false;
        /*if(compteJour >= NB_JOUR_DESINSCRIPTION_COURS){*/
        if(this.calculMontantPaye()>0){
            this.cours.removeAll(this.cours);
            this.typeCoursAvecNiveau="";
            this.lTypeCours.removeAll(this.lTypeCours);
            boo=true;
            System.out.println("Vous avez été retiré de vos cours pour non paiement");
            System.out.println(this.cours);
        }
        else{
            System.out.println("RAS");
        }
        return boo;
    }

    public void ajouterCours(Cours c){
        if(c == null){
            System.out.println("impossible : cours nul");
        }
        else{
            this.addCours(c);
            this.verifTypeCoursAvecNiveau(c);
        }
    }

    private void addCours(Cours c){
        cours.add(c);
    }


    public void verifTypeCoursAvecNiveau(Cours c){
        if (!this.lTypeCours.contains(c.getType()+" "+c.getNiveau()+" ")){
            this.lTypeCours.add(c.getType()+" "+c.getNiveau()+" ");
            this.typeCoursAvecNiveau="";
            for (String s : this.lTypeCours){
                this.typeCoursAvecNiveau+=s;
            }
        }
    }

    private void removePaiement(Paiement p){
        paiements.remove(p);
    }

    public void ajouterPaiement(Paiement p){
        if(p == null){
            System.out.println("impossible : paiement nul");
        }
        else{
            this.addPaiement(p);
        }
    }

    public void supprimerPaiement(Paiement p){
        if(p == null){
            System.out.println("impossible : paiement nul");
        }
        else if (paiements.contains(p)){
            this.removePaiement(p);
        }else{
            System.out.println("impossible : paiement n'appartient pas à la liste des paiements du membre");
        }
    }

    private void addPaiement(Paiement p){
        paiements.add(p);
    }



    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Getter et Setter %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

    public String getNom() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom = nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public void setPrenom(String prenom) {
        this.prenom = prenom;
    }

    public String getCoordonnees() {
        return coordonnees;
    }

    public void setCoordonnees(String coordonnees) {
        this.coordonnees = coordonnees;
    }

    public double getMontantDu() {
        return this.calculMontantDu();
    }

    // public void setMontantDu(double montantDu) {
    //     this.montantDu = montantDu;
    // }

    public double getMontantPaye() {
        return montantPaye;
    }

    public void setMontantPaye(double montantPaye) {
        this.montantPaye = montantPaye;
    }

    public static int getId() {
        return id;
    }

    public int getNumero() {
        return numero;
    }

    public Saison getSaison(){
        return this.saisonInscription;
    }

    public String getValTraitementPourListe() {
        return valTraitementPourListe;
    }

    public void setValTraitementPourListe(String valTraitementPourListe) {
        this.valTraitementPourListe = valTraitementPourListe;
    }

    public int getCompteJour() {
        return compteJour;
    }

    public void setCompteJour(int compteJour) {
        this.compteJour = compteJour;
    }

    public ArrayList<Cours> getCours() {
        return cours;
    }

    public void setCours(ArrayList<Cours> cours) {
        this.cours = cours;
    }

    public void setPaiement(ArrayList<Paiement> p) {
        this.paiements = p;
        this.calculMontantTotPaiements();
        this.calculMontantDu();
        this.calculMontantPaye();
    }

    public String getTypeCoursAvecNiveau(){
        return this.typeCoursAvecNiveau;
    }

    public ArrayList<Paiement> getPaiements(){
        return this.paiements;
    }

    public String getTarifApplique(){
        return tarifApplique;
    }
    

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% hashCode et différents equals %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((numero == 0) ? 0 : numero);
        return result;
    }


    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Membre other = (Membre) obj;
        if (numero != other.numero)
            return false;
        return true;
    }

    public boolean equalsNomPrenom(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Membre other = (Membre) obj;
        if (nom == null) {
            if (other.nom != null)
                return false;
        } else if (!nom.equals(other.nom))
            return false;
        if (prenom == null) {
            if (other.prenom != null)
                return false;
        } else if (!prenom.equals(other.prenom))
            return false;
        return true;
    }



    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Main %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

    // public static void main(String[] args) {
    //     Membre m1 = new Membre("Jean", "Pierre", "Lannion", 125.0, 15.0, new Saison("1984","2010"));
    //     System.out.println(m1.affiche());        
    // }   
}