package modele;

public class Mail extends DocsGeneres{
    
    public Mail(Membre membreConcerne) {
        super(membreConcerne);
    }
    
    public Mail(Membre membreConcerne, String debutSaison, String finSaison) {
            super(membreConcerne, debutSaison, finSaison);
    }

    public String afficheS(){
        return "Membre concerné : "+this.membreConcerne;
    }

    public void affiche(){
        System.out.println(this.afficheS());
    }
    
    @Override
    public String toString() {
        return "Mail []";
    }

    @Override
    public String genDoc(){
        return "Bonjour, "+ membreConcerne.getNom() + " " + membreConcerne.getPrenom() +".\r\n" + //
                        "Nous vous informons que vous êtes en retard sur le paiement de votre cotisation sur la période du "+ debutSaison +" au "+ finSaison + " suite a votre inscription au cour(s) suivant(s): "+ membreConcerne.getCours() +". Il vous reste "+ membreConcerne.getMontantDu() +" euros à payer durant les prochains "+ membreConcerne.getCompteJour() +" jours sous peine d'être désinscrit. Nous vous prions de régulariser votre situation dans les plus brefs délais.\r\n" + //
                        "\r\n" + //
                        "Cordialement,\r\n" + //
                        "\r\n" + //
                        COORDONNEES_ELLADANCE; //Corps mail à faire
    }
    
    // public static void main(String[] args) {
    //     Membre m1 = new Membre("Jean", "Pierre", "Lannion", 125.0, 15.0, new Saison("1984","2010"));
    //     Mail mail = new Mail(m1, "06/2008", "09/2008");
    //     System.out.println(mail.genDoc());
    // }
}
