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
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.beans.binding.Bindings;

import modele.*;

public class CtrlAfficheMembre {
	@FXML private Label lbTitre;
	@FXML private Label lbDu;
	@FXML private Label lbPaye;
	@FXML private Label lbSaison;
	@FXML private Label lbResteACharge;
	@FXML private Label lbTypeCours;
	@FXML private Label lbCoordonees;
	
	@FXML private Button bnModif;
	@FXML private Button bnSupprimer;
	@FXML private Button bnEnvoie;
	@FXML private Button bnGenererFacture;
	@FXML private Button bnFermer;
	@FXML private Button bnDesinscription;

	@FXML private TableView<Paiement> tvListe;

	private Membre membre;
	private boolean rappelEnvoye;
	
    
    // clic sur bouton Modifier paiement
    @FXML void selectionnerPaiement(ActionEvent event) {
    	ihm.Main.selectionnerPaiement(tvListe.getSelectionModel().getSelectedItem(),membre.getNumero());
    	membre.calculMontantTotPaiements();
		for (Membre m : Liste.getMembres()) {
			if (m.getNumero()==membre.getNumero()){
				m.setPaiement(membre.getPaiements());
			}
		}
    	tvListe.setItems(conversion(membre.getPaiements()));
		this.lbDu.setText(""+membre.getMontantDu()+" €");
		this.lbPaye.setText(""+membre.getMontantPaye()+" €");
		this.lbSaison.setText(""+membre.getSaison().getDebut());
		this.lbResteACharge.setText(""+membre.calculMontantPaye()+" €");
    }

	// clic sur bouton Supprimer paiement
    @FXML void supprimerPaiement(ActionEvent event) {
		Alert alert = new Alert(
    			AlertType.CONFIRMATION,
    			"Voulez-vous vraiment supprimer ce paiement ?",
    			ButtonType.YES,
    			ButtonType.NO
    			);
    	alert.setTitle("Confirmation de suppression");
    	Optional<ButtonType> b = alert.showAndWait();
    	if (b.get().equals(ButtonType.YES)) {
    		Paiement p =tvListe.getSelectionModel().getSelectedItem();
			this.membre.supprimerPaiement(p);
			this.membre.calculMontantTotPaiements();
			for (Membre m : Liste.getMembres()) {
				if (m.getNumero()==membre.getNumero()){
					m.setPaiement(membre.getPaiements());
				}
			}
			tvListe.setItems(conversion(membre.getPaiements()));
			tvListe.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
			this.lbDu.setText(""+membre.getMontantDu()+" €");
			this.lbPaye.setText(""+membre.getMontantPaye()+" €");
			this.lbSaison.setText(""+membre.getSaison().getDebut());
			this.lbResteACharge.setText(""+membre.calculMontantPaye()+" €");
			Main.recharcherListe();
    	}
		this.lbDu.setText(""+membre.getMontantDu()+" €");
		this.lbPaye.setText(""+membre.getMontantPaye()+" €");
		this.lbSaison.setText(""+membre.getSaison().getDebut());
		this.lbResteACharge.setText(""+membre.calculMontantPaye()+" €");
    }
     
	//clic sur bouton Fermer
	@FXML void clicFermer(ActionEvent event) {
		Main.fermerAfficheMembre();
	}

	@FXML void genererFacture(ActionEvent event) {
		Main.genererFacture(this.membre);
	}

	// clic sur bouton Desinscrire
    @FXML void desinscrire(ActionEvent event) {
		Alert alert = new Alert(
    			AlertType.CONFIRMATION,
    			"Plus aucun cours en sera lié à cet élève. Voulez-vous vraiment continuer ? ",
    			ButtonType.YES,
    			ButtonType.NO
    			);
    	alert.setTitle("Confirmation de désinscription");
    	Optional<ButtonType> b = alert.showAndWait();
    	if (b.get().equals(ButtonType.YES)) {
    		this.membre.desinscription(this.membre);
    		tvListe.setItems(conversion(membre.getPaiements()));
			tvListe.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
			this.lbDu.setText(""+membre.getMontantDu()+" €");
			this.lbPaye.setText(""+membre.getMontantPaye()+" €");
			this.lbSaison.setText(""+membre.getSaison().getDebut());
			this.lbResteACharge.setText(""+membre.calculMontantPaye()+" €");
			Main.recharcherListe();
    	}
    }

	@FXML void envoyerRappel(ActionEvent event) {
		System.out.println("envoyer rappel reçu");
		Alert alert = new Alert(
    			AlertType.INFORMATION,
    			"Le mail de rappel a été envoyé",
    			ButtonType.OK
    			);
    	alert.setTitle("Envoi effectué");
    	Optional<ButtonType> b = alert.showAndWait();
		Main.envoyerRappel(this.membre);
		this.rappelEnvoye=true;
	}

	public static ObservableList<Paiement> conversion(ArrayList<Paiement> aConvertir){
        ObservableList<Paiement> lesPaiements = FXCollections.observableArrayList();
		for (Paiement p : aConvertir){
			lesPaiements.add(p);
		}
		return lesPaiements;
    }
	
	public void rafraichir() {
		tvListe.setItems(conversion(membre.getPaiements()));
        tvListe.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
	}
    
    public void afficherMembre(Membre m) {
		this.membre=m;
		this.lbTitre.setText(""+membre.getNom()+" "+membre.getPrenom()+", membre n° "+membre.getNumero());
		this.lbDu.setText(""+membre.getMontantDu()+" €");
		this.lbPaye.setText(""+membre.getMontantPaye()+" €");
		this.lbSaison.setText(""+membre.getSaison().getDebut());
		this.lbResteACharge.setText(""+membre.calculMontantPaye()+" €");
		this.lbTypeCours.setText(membre.getTypeCoursAvecNiveau());
		this.lbCoordonees.setText(membre.getCoordonnees());
		tvListe.setItems(conversion(membre.getPaiements()));
        tvListe.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
	}
    
    @FXML void initialize() {
		this.rappelEnvoye=false;
		this.membre= new Membre("DELERUE","Maël","6 rue Jean Pillard",30.0,new Saison("2023", "2024"));
		
		this.lbTitre.setText(""+membre.getNom()+" "+membre.getPrenom()+", membre n° "+membre.getNumero());
		this.lbDu.setText(""+membre.getMontantDu());
		this.lbPaye.setText(""+membre.getMontantPaye());
		this.lbSaison.setText(""+membre.getSaison().getDebut());
		this.lbResteACharge.setText(""+membre.calculMontantPaye());
		this.lbTypeCours.setText(membre.getTypeCoursAvecNiveau());
		//this.lbCoordonnees.setText(membre.getCoordonnees());
		
		TableColumn<Paiement,Integer> colonne1 = new TableColumn<Paiement,Integer>("Date");
		colonne1.setCellValueFactory(new PropertyValueFactory<Paiement,Integer>("date"));	
		tvListe.getColumns().set(0, colonne1);

		TableColumn<Paiement,Integer> colonne2 = new TableColumn<Paiement,Integer>("Montant (en €)");
		colonne2.setCellValueFactory(new PropertyValueFactory<Paiement,Integer>("montant"));	
		tvListe.getColumns().set(1, colonne2);
        
		tvListe.setItems(conversion(membre.getPaiements()));
        tvListe.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
	
		BooleanBinding rien = Bindings.equal(tvListe.getSelectionModel().selectedIndexProperty(), -1);
		bnModif.disableProperty().bind(rien);
		bnSupprimer.disableProperty().bind(rien);

//		BooleanBinding verifPourDesinscription = (this.membre.calculMontantPaye()<0)
//                            .or(this.membre.getCours().size()==0)
//                                      .or(this.rappelEnvoye==false);
//		bnDesinscription.disableProperty().bind(verifPourDesinscription);
//		BooleanBinding verifPourRappel = (this.membre.calculMontantPaye()<0)
//                            .or(this.membre.getCours().size()==0);
		//bnEnvoie.disableProperty().bind(verifPourRappel);
    }
}