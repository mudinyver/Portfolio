package modele;

import java.io.Serializable;

public class Cours implements Serializable{
    
    //Attributs
    private String intitule;
    private String type;
    private int niveau;
    private String heure;
    private String valTraitementPourListe; //Ne pas modifier


    public Cours(String intitule, String heure, String type, int niveau) {
        this.intitule = intitule;
        this.type = type;
        this.niveau = niveau;
        this.heure = heure;
        this.valTraitementPourListe=type+niveau+intitule;
    }

    public double calculPrix(String typeTarif){
        double aRetourner;
        if (typeTarif.equals("Plein tarif")){
            if (this.heure.equals("0h45")){
                aRetourner=91.0;
            } else if (this.heure.equals("1h00")){
                aRetourner=112.0;
            } else if (this.heure.equals("1h15")){
                aRetourner=133.0;
            } else if (this.heure.equals("1h30")){
                aRetourner=150.0;
            } else if (this.heure.equals("1h45")){
                aRetourner=168.0;
            } else if (this.heure.equals("2h00")){
                aRetourner=185.0;
            } else if (this.heure.equals("2h15")){
                aRetourner=199.0;
            } else if (this.heure.equals("2h30")){
                aRetourner=213.0;
            } else if (this.heure.equals("2h45")){
                aRetourner=227.0;
            } else if (this.heure.equals("3h00")){
                aRetourner=241.0;
            } else if (this.heure.equals("3h15")){
                aRetourner=255.0;
            } else if (this.heure.equals("3h30")){
                aRetourner=269.0;
            } else if (this.heure.equals("3h45")){
                aRetourner=279.0;
            } else if (this.heure.equals("4h00")){
                aRetourner=290.0;
            } else if (this.heure.equals("4h15")){
                aRetourner=300.0;
            } else if (this.heure.equals("4h30")){
                aRetourner=310.0;
            } else if (this.heure.equals("4h45")){
                aRetourner=321.0;
            } else if (this.heure.equals("5h00")){
                aRetourner=331.0;
            } else if (this.heure.equals("5h30")){
                aRetourner=352.0;
            } else if (this.heure.equals("6h00")){
                aRetourner=372.0;
            } else if (this.heure.equals("6h30")){
                aRetourner=393.0;
            } else if (this.heure.equals("7h00")){
                aRetourner=413.0;
            } else if (this.heure.equals("7h30")){
                aRetourner=434.0;
            } else{
                aRetourner=0.00;
            }
        }else{
            if (this.heure.equals("0h45")){
                aRetourner=74.0;
            } else if (this.heure.equals("1h00")){
                aRetourner=83.0;
            } else if (this.heure.equals("1h15")){
                aRetourner=101.0;
            } else if (this.heure.equals("1h30")){
                aRetourner=110.0;
            } else if (this.heure.equals("1h45")){
                aRetourner=122.0;
            } else if (this.heure.equals("2h00")){
                aRetourner=134.0;
            } else if (this.heure.equals("2h15")){
                aRetourner=146.0;
            } else if (this.heure.equals("2h30")){
                aRetourner=158.0;
            } else if (this.heure.equals("2h45")){
                aRetourner=167.0;
            } else if (this.heure.equals("3h00")){
                aRetourner=176.0;
            } else if (this.heure.equals("3h15")){
                aRetourner=185.0;
            } else if (this.heure.equals("3h30")){
                aRetourner=194.0;
            } else if (this.heure.equals("3h45")){
                aRetourner=200.0;
            } else if (this.heure.equals("4h00")){
                aRetourner=206.0;
            } else if (this.heure.equals("4h15")){
                aRetourner=212.0;
            } else if (this.heure.equals("4h30")){
                aRetourner=214.0;
            } else if (this.heure.equals("5h00")){
                aRetourner=226.0;
            } else{
                aRetourner=0.00;
            }
        }
        return aRetourner;
    }


    public String getIntitule() {
        return intitule;
    }
    public String getType() {
        return type;
    }
    public int getNiveau() {
        return niveau;
    }
    public String getValTraitementPourListe() {
        return valTraitementPourListe;
    }
    
    public String getHeure() {
    	return this.heure;
    }
    
    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((intitule == null) ? 0 : intitule.hashCode());
        result = prime * result + ((type == null) ? 0 : type.hashCode());
        result = prime * result + niveau;
        return result;
    }
    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Cours other = (Cours) obj;
        if (intitule == null) {
            if (other.intitule != null)
                return false;
        } else if (!intitule.equals(other.intitule))
            return false;
        if (type == null) {
            if (other.type != null)
                return false;
        } else if (!type.equals(other.type))
            return false;
        if (niveau != other.niveau)
            return false;
        return true;
    }
    @Override
    public String toString() {
        return "Cours [intitule=" + intitule + ", type=" + type + ", niveau=" + niveau + "]";
    }
    

    

    
}
