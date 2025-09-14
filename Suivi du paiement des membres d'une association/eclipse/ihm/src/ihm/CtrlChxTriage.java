package ihm;

import java.util.ArrayList;
import java.util.Date;
import java.util.Optional;

import javafx.beans.binding.Binding;
import javafx.beans.binding.BooleanBinding;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.beans.binding.Bindings;
//import modele.Membre;
//import modele.Liste;
//import modele.Cours;
//import modele.Saison;
//import modele.SvgListe;
//import modele.svgRechercheRes;
import modele.*;

public class CtrlChxTriage {
	@FXML private CheckBox cbFiltrePaye;
	@FXML private CheckBox cbDansesStandards = new CheckBox();
	@FXML private CheckBox cbDansesLatines = new CheckBox();
	@FXML private CheckBox cbDansesRock = new CheckBox();
	@FXML private CheckBox cbDanses1 = new CheckBox();
	@FXML private CheckBox cbDanses2 = new CheckBox();
	@FXML private CheckBox cbDanses3 = new CheckBox();
	@FXML private ComboBox<String> cbPrincipal;
	@FXML private ComboBox<String> cbAuxiliaire;
	@FXML private ComboBox<String> cbAuxiliaire2;
	@FXML private CheckBox principalDecroit = new CheckBox();
	@FXML private CheckBox auxiliaire1Decroit = new CheckBox();
	@FXML private CheckBox auxiliaire2Decroit = new CheckBox();
	@FXML private Button bnLancerTri;
	@FXML private Button bnSelectionner;
	@FXML private TableView<Membre> tvListe; //= new TableView<>();
	
    
    // clic sur bouton Sélectionner
    @FXML void selectionnerMembre(ActionEvent event) {
    	Membre m =tvListe.getSelectionModel().getSelectedItem();
    	ihm.Main.selectionnerMembre(m);
    }
     
    // clic sur bouton Fermer
//    @FXML void clicFermer(ActionEvent event) {
//    	Main.fermerAppli();
//    }

	public static ObservableList<Membre> conversion(ArrayList<Membre> aConvertir){
        ObservableList<Membre> lesMembres = FXCollections.observableArrayList();
		for (Membre m : aConvertir){
			lesMembres.add(m);
		}
		return lesMembres;
    }
    
    @FXML void lancerTri() {
    	//choix ordre tri
    	System.out.println("------------TRI-------------");
    	ArrayList<String> ordrePrep = new ArrayList<>();
    	ArrayList<Integer> ordre = new ArrayList<>();
    	ordrePrep.removeAll(ordrePrep);
    	ordrePrep.add(cbPrincipal.getSelectionModel().getSelectedItem());
    	ordrePrep.add(cbAuxiliaire.getSelectionModel().getSelectedItem());
    	ordrePrep.add(cbAuxiliaire2.getSelectionModel().getSelectedItem());
    	int i = 0;
    	boolean bool;
    	for (String s : ordrePrep) {
    		if(i==0) {
    			bool = principalDecroit.isSelected();
    		}else if(i==1) {
    			bool = auxiliaire1Decroit.isSelected();
    		}else {
    			bool = auxiliaire2Decroit.isSelected();
    		}
    		if (s.equals("Nom et prénom des membres")) {
    			if (bool) {
    				ordre.add(-2);
    			}else {
    				ordre.add(2);
    			}
    		}else if (s.equals("Saison d'inscription des membres")) {
    			if (bool) {
    				ordre.add(-3);
    			}else {
    				ordre.add(3);
    			}
    		}else if (s.equals("Cours")) {
    			if (bool) {
    				ordre.add(-7);
    			}else {
    				ordre.add(7);
    			}
    		}
    		i++;
    	}
    	
    	
    	System.out.println(ordre);


	    ArrayList<String> checkBoxType = new ArrayList<>();
		ArrayList<Integer> checkBoxNiveau= new ArrayList<>();
	
		if (cbDansesStandards.isSelected()){
			checkBoxType.add("Danse classique");
		}
		if (cbDansesLatines.isSelected()){
			checkBoxType.add("Danse latine");
		}
		if (cbDansesRock.isSelected()){
			checkBoxType.add("Danse rock");
		}
		if (cbDanses1.isSelected()){
			checkBoxNiveau.add(1);
		}
		if (cbDanses2.isSelected()){
			checkBoxNiveau.add(2);
		}
		if (cbDanses3.isSelected()){
			checkBoxNiveau.add(3);
		}
		System.out.println(cbFiltrePaye.isSelected());
		System.out.println(checkBoxType);
		System.out.println(checkBoxNiveau);
	
		ArrayList<Membre> li2 = new ArrayList<>();
        if (checkBoxType.size()!=0 && checkBoxNiveau.size()!=0) {
        	li2 = Liste.multiTriPrep(Liste.getMembres(), this.cbFiltrePaye.isSelected()==false, checkBoxType, checkBoxNiveau, ordre);
        	for (Membre m : li2) {
    			System.out.println(m.getNom() + " " + m.getPrenom() + " | " + m.getSaison().getDebut() + " | "+m.getCours() + "\n");
//    			m.calculMontantDu();
    	    }
        }
		
        tvListe.setItems(conversion(li2));
		tvListe.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
	
		BooleanBinding rien = Bindings.equal(tvListe.getSelectionModel().selectedIndexProperty(), -1);
		bnSelectionner.disableProperty().bind(
				rien
			);

    }
    
    @FXML void initialize() {
    	System.out.println("------------ INIT T -------------");
    	Liste.getMembres().removeAll(Liste.getMembres());
    	System.out.println(Liste.getMembres());
    	
    	ArrayList<String> chxDeTri = new ArrayList<>();
    	chxDeTri.add("Nom et prénom des membres");
    	chxDeTri.add("Saison d'inscription des membres");
    	chxDeTri.add("Cours");
    	
    	this.cbPrincipal.getItems().clear();
    	this.cbAuxiliaire.getItems().clear();
    	this.cbAuxiliaire2.getItems().clear();
    	this.cbAuxiliaire.getItems().add("--------------");
		this.cbAuxiliaire2.getItems().add("--------------");
		for (int i=0; i<3 ; i++) {
			this.cbPrincipal.getItems().add(chxDeTri.get(i));
			this.cbAuxiliaire.getItems().add(chxDeTri.get(i));
			this.cbAuxiliaire2.getItems().add(chxDeTri.get(i));
		}
		this.cbPrincipal.getSelectionModel().selectFirst();
		this.cbAuxiliaire.getSelectionModel().selectFirst();
		this.cbAuxiliaire2.getSelectionModel().selectFirst();
		
		TableColumn<Membre,Integer> colonne1 = new TableColumn<Membre,Integer>("Numéro");
		colonne1.setCellValueFactory(new PropertyValueFactory<Membre,Integer>("numero"));	
		tvListe.getColumns().set(0, colonne1);

		TableColumn<Membre,Integer> colonne2 = new TableColumn<Membre,Integer>("Nom");
		colonne2.setCellValueFactory(new PropertyValueFactory<Membre,Integer>("nom"));	
		tvListe.getColumns().set(1, colonne2);

		TableColumn<Membre,Integer> colonne3 = new TableColumn<Membre,Integer>("Prénom");
		colonne3.setCellValueFactory(new PropertyValueFactory<Membre,Integer>("prenom"));	
		tvListe.getColumns().set(2, colonne3);

		TableColumn<Membre,Integer> colonne4 = new TableColumn<Membre,Integer>("Inscription");
		colonne4.setCellValueFactory(new PropertyValueFactory<Membre,Integer>("saison"));	
		tvListe.getColumns().set(3, colonne4);

		TableColumn<Membre,Integer> colonne5 = new TableColumn<Membre,Integer>("Montant dû (en €)");
		colonne5.setCellValueFactory(new PropertyValueFactory<Membre,Integer>("montantDu"));	
		tvListe.getColumns().set(4, colonne5);

		TableColumn<Membre,Integer> colonne6 = new TableColumn<Membre,Integer>("Montant payé (en €)");
		colonne6.setCellValueFactory(new PropertyValueFactory<Membre,Integer>("montantPaye"));	
		tvListe.getColumns().set(5, colonne6);
		
		TableColumn<Membre,Integer> colonne7 = new TableColumn<Membre,Integer>("Type de cours (avec niveau)");
		colonne7.setCellValueFactory(new PropertyValueFactory<Membre,Integer>("typeCoursAvecNiveau"));	
		tvListe.getColumns().set(6, colonne7);
		
		
		if (Liste.getMembres().size()==0) {
			Membre a = new Membre("DELERUE","Maël","6 rue Foulinfo Guy",50.0,new Saison("2023", "2024"));
	        Membre b = new Membre("UDIN--YVER","Mael","6 rue Baptiste la Pierre",0.0,new Saison("1984", "2024"));
	        Membre c = new Membre("LEFRANÇOIS","Julien","6 rue Jean Pillard",30.0,new Saison("2007", "2022"));
	        Membre e = new Membre("DELERUE","Maël","2 rue Jean Larivière",0.0,new Saison("2003", "2004"));
	        Membre f = new Membre("UDIN--YVER","Ethan","6 rue Baptiste la Pierre",90.0,new Saison("1984", "2024"));
	        Membre g = new Membre("LEFRANÇOIS","Jules","6 rue Jean Laillard",3.0,new Saison("2007", "2008"));
	        Membre ella = new Membre("Danse","Ella","6 rue Jean Pillard",3000.0,new Saison("2000", "2001"));
	        a.ajouterCours(new Cours("Ballet", "1h00","Danse classique",1));
	        a.ajouterCours(new Cours("Travolta",  "1h45","Danse latine",2));
	        a.ajouterCours(new Cours("Ballet",  "1h30","Danse classique",3));
	        b.ajouterCours(new Cours("Travolta",  "0h45","Danse latine",1));
	        f.ajouterCours(new Cours("Disco",  "7h00","Danse rock",1));
	        c.ajouterCours(new Cours("Disco",  "2h00","Danse rock",3));
	        c.ajouterCours(new Cours("Travolta",  "3h00","Danse latine",2));
	        g.ajouterCours(new Cours("Ballet",  "4h00","Danse classique",2));
	        ella.ajouterCours(new Cours("Ballet",  "4h00","Danse classique",3));
	        ella.ajouterCours(new Cours("Travolta",  "4h00","Danse latine",3));
	        ella.ajouterCours(new Cours("Disco",  "4h00","Danse rock",3));
	        
	        c.ajouterPaiement(new Paiement(new Date("07/04/2019"),30.0));
	        a.ajouterPaiement(new Paiement(new Date("09/04/2024"),50.0));
	        f.ajouterPaiement(new Paiement(new Date("09/06/2024"),80.0));
	        f.ajouterPaiement(new Paiement(new Date("09/05/2024"),10.0));
	        g.ajouterPaiement(new Paiement(new Date("09/04/2010"),3.0));
	        ella.ajouterPaiement(new Paiement(new Date("09/04/2002"),3000.0));

//	        Liste l = new Liste();
	        
	        Liste.ajouterMembre(a);
	        Liste.ajouterMembre(b);
	        Liste.ajouterMembre(c);
	        Liste.ajouterMembre(e);
	        Liste.ajouterMembre(f);
	        Liste.ajouterMembre(g);
	        Liste.ajouterMembre(ella);
	        
	        for (Membre m : Liste.getMembres()) {
	        	m.calculMontantTotPaiements();
	        }
		}
		
    	
//		ArrayList<String> lTypeCours = new ArrayList<>();
//		lTypeCours.add("Danse classique");
//        ArrayList<Integer> lNiveauCours = new ArrayList<>();
//        lTypeCours.add("Danse classique");
//        lTypeCours.add("Danse latine");
//        lTypeCours.add("Danse rock");
//        lNiveauCours.add(1);
//        lNiveauCours.add(2);
//        lNiveauCours.add(3);
//        ArrayList<Integer> ordre = new ArrayList<>();
//        ordre.add(2);
//        ArrayList<Membre> li = new ArrayList<>();
//        
////        System.out.println(Liste.getMembres());
//        
//        if (lTypeCours.size()!=0 && lNiveauCours.size()!=0) {
//        	li = Liste.multiTriPrep(Liste.getMembres(), true, lTypeCours, lNiveauCours, ordre);
//        	tvListe.setItems(conversion(li));
//        }
//        for (Membre m : li) {
//        	System.out.println(m.getNom() + " " + m.getPrenom() + " | " + m.getSaison().getDebut() + " | "+m.getCours() + "\n");
//			m.calculMontantDu();
//        }
        
		
		tvListe.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
	
		BooleanBinding rien = Bindings.equal(tvListe.getSelectionModel().selectedIndexProperty(), -1);
		bnSelectionner.disableProperty().bind(
				rien
			);
		System.out.println(Liste.getMembres());
    }
}
