package modele;

public class Facture extends DocsGeneres{

    public Facture(Membre membreConcerne,String  debutSaison, String  finSaison) {
        super(membreConcerne, debutSaison, finSaison);
    }

    public String afficheS(){
        return "Membre concerné : "+this.membreConcerne+" , date de début et de fin de la saison : "+this.debutSaison+" | "+this.finSaison;
    }

    public void affiche(){
        System.out.println(this.afficheS());
    }

    @Override
    public String genDoc(){
        return ""; //Corps facture à faire
    }




    @Override
    public String toString() {
        return "Facture [debutSaison=" + debutSaison + ", finSaison=" + finSaison + "]";
    }

    public String  getDebutSaison() {
        return debutSaison;
    }

    public void setDebutSaison(String  debutSaison) {
        this.debutSaison = debutSaison;
    }

    public String  getFinSaison() {
        return finSaison;
    }

    public void setFinSaison(String  finSaison) {
        this.finSaison = finSaison;
    }



    

    
    
}
