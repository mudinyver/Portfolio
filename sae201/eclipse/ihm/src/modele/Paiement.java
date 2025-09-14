package modele;

import java.util.Calendar;
import java.util.Date;
import java.util.Locale;
import java.text.DateFormat;
import java.time.LocalDate;


public class Paiement {

    // Attributs
    private Date date;
    private double montant;
    private static int id=0;
    private int num;

    // Constructeur
    public Paiement(Date date, double montant) {
        this.modifDate(date);
        this.modifMontant(montant);
        this.num=Paiement.id;
        Paiement.id++;
    }

    // Méthodes
    public void modifDate(Date nouvD){
        setDate(nouvD);
    }

    public boolean modifMontant(double newM){
        boolean boo;
        if (newM > 0) {
            this.montant = newM;
            boo=true;

        } else {
            System.out.println("Erreur: Le montant ne peut pas être nul ou négatif");
            boo=false;
        }
        return boo;
    }

    public String getDate() {
    	Locale locale = new Locale("fr", "FR");
    	DateFormat dateFormat = DateFormat.getDateInstance(DateFormat.DEFAULT, locale);
    	return dateFormat.format(date);
    }

    public Date getDateFormatDate(){
        return this.date;
    }

    public double getMontant() {
        return montant;
    }

    private void setDate(Date date) {
        this.date = date;
    }

    public void setMontant(double montant) {
        this.montant = montant;
    }

    public void modifPaiement(Date d, double m){
        this.montant=m;
        this.date=d;
    }

    public int getNum(){
        return this.num;
    }

    @Override
    public String toString() {
        return "Date du paiement:" + date + " Montant du paiement" + montant;
    }
}