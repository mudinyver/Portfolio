package modele;

public class DocsGeneres{
    protected Membre membreConcerne;
    protected static final String COORDONNEES_ELLADANCE="5 rue jean Pillard, 3????? Lannion";
    protected String  debutSaison;
    protected String  finSaison;

    
    



    public DocsGeneres(Membre membreConcerne) {
        this.membreConcerne = membreConcerne;
    }

    public DocsGeneres(Membre membreConcerne, String debutSaison, String finSaison) {
        this.membreConcerne = membreConcerne;
        this.debutSaison = debutSaison;
        this.finSaison = finSaison;
    }

    public String afficheS(){
        return "Membre concerné : "+this.membreConcerne;
    }

    public void affiche(){
        System.out.println(this.afficheS());
    }

    public String genDoc(){
        return "";
    }


    


    @Override
    public String toString() {
        return "DocsGeneres [membreConcerne=" + membreConcerne + "]";
    }

    public Membre getMembreConcerne() {
        return membreConcerne;
    }
    public void setMembreConcerne(Membre membreConcerne) {
        this.membreConcerne = membreConcerne;
    }

    
}