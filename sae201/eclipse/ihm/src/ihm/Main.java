package ihm;

import java.util.ArrayList;
import javafx.application.Application;
import javafx.collections.ObservableList;
import javafx.stage.Modality;
import javafx.stage.Stage;
import modele.Membre;
import modele.Paiement;

public class Main extends Application{
//	static private FenNouvelEmploye fNouvEmp;
//	static private FenModifierEmploye fModifierEmp;
	static private FenChxTriage fChxT;
	static private FenFacture fFacture;
	static private FenDate fDate;
	static private FenAfficheMembre fAfficheMembre;
	
	public void start(Stage f) throws Exception {
		
		//Donnees.chargementDonnees();
		//initialisation des fenêtres
//		fNouvEmp = new FenNouvelEmploye();
//		fModifierEmp = new FenModifierEmploye();
		fChxT = new FenChxTriage();
		fFacture = new FenFacture();
		fDate = new FenDate();
		fAfficheMembre = new FenAfficheMembre();
		
		fChxT.show();
//		fFacture.show();
//		fDate.show();
//		fAfficheMembre.show();
	} 
	
	static public void main(String args[]) { 
		Application.launch(args); 
	}
	
	static public void fermerAppli() {
		System.exit(0);
	}
	
	
	///////////////////////
	// gestion des fenêtres
	///////////////////////
//	static public void ouvrirNouvelEmploye() {
//		fNouvEmp.effacer();
//		fNouvEmp.show();
//	}
//	
//	
//	static public void fermerNouvelEmploye() {
//		fNouvEmp.close();
//	}
//	
	static public void selectionnerMembre(Membre m) {
		fAfficheMembre.afficherMembre(m);
		fAfficheMembre.show();
	}
//	
//	static public void fermerModifierEmploye() {
//		fModifierEmp.close();
//	}
//	

	static void selectionnerPaiement(Paiement p, int numeroMembre) {
		fDate.afficherPaiement(p,numeroMembre);
		fDate.show();
	}
	 
	//clic sur bouton Fermer
	static void fermerAfficheMembre() {
		fAfficheMembre.close();
	}
	
	static void fermerAfficheDate() {
		fDate.close();
	}

	static void genererFacture(Membre m) {
		fFacture.genererFacture(m);
		fFacture.show();
	}
	
	static void rafraichirMembre() {
		fAfficheMembre.rafraichir();
	}
		

	static void envoyerRappel(Membre m) {
		System.out.println("Bonjour, "+ m.getNom() + " " + m.getPrenom() +".\r\n" + //
                "Nous vous informons que vous êtes en retard sur le paiement de votre cotisation suite a votre inscription au(x) cour(s) suivant(s): "+ m.getCours() +". Il vous reste "+ m.getMontantDu() +" euros à payer durant les prochains "+ m.getCompteJour() +" jours sous peine d'être désinscrit. Nous vous prions de régulariser votre situation dans les plus brefs délais.\r\n" + //
                "\r\n" + //
                "Cordialement,\r\n" + //
                "\r\n" + //
                "Ella danse, 7 rue Jean Pillard, Lannion"); //Corps mail à faire);
	}

	static void recharcherListe() {
		System.out.println("####### RECHARGE ##########");
		fChxT.lancerTri();
	}
}
