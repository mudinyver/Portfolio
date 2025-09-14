package modele;

import java.io.Serializable;

public class Saison implements Serializable{
    
    //Attributs
    private String debut;
    private String fin;

    // Constructeur
    public Saison(String debut, String fin) {
        this.debut = debut;
        this.fin = fin;
    }

    // Méthodes
    public String getDebut() {
        return debut;
    }

    public void setDebut(String debut) {
        this.debut = debut;
    }

    public String getFin() {
        return fin;
    }

    public void setFin(String fin) {
        this.fin = fin;
    }

    @Override
    public String toString() {
        return debut;
    }

    
}
