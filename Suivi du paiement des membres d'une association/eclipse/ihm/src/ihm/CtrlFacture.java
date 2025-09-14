package ihm;

import java.util.ArrayList;
import java.util.Optional;
import java.time.LocalDate;

import javafx.beans.binding.Binding;
import javafx.beans.binding.BooleanBinding;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
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

public class CtrlFacture {
	@FXML private Label id_facture;
	@FXML private Label id_date;
	@FXML private Label id_nom;
	@FXML private Label id_prenom;
	@FXML private Label id_coordonnees;
	@FXML private Label id_total;
	@FXML private Label id_montant_paye;
	@FXML private Label id_mode_de_paiement;

	@FXML private Label id_prix_1;
	@FXML private Label id_nb_heure_1;
	@FXML private Label id_description_1;
	@FXML private Label id_prix_2;
	@FXML private Label id_nb_heure_2;
	@FXML private Label id_description_2;
	@FXML private Label id_prix_3;
	@FXML private Label id_nb_heure_3;
	@FXML private Label id_description_3;

	private ArrayList<Label> prix;
	private ArrayList<Label> nb_heure;
	private ArrayList<Label> description;

	private static int id=1;
	
    
    
     
	//clic sur bouton Fermer
	// @FXML void clicFermer(ActionEvent event) {
	// 	Main.fermerAfficheMembre();
	// }
    
    public void genererFacture(Membre m) {
		this.id_facture.setText(""+this.id);
		this.id++;
		LocalDate myObj = LocalDate.now();
		this.id_date.setText(myObj.getDayOfMonth()+" "+myObj.getMonth()+" "+myObj.getYear());
		this.id_nom.setText(""+m.getNom());
		this.id_prenom.setText(" "+m.getPrenom());
		
		this.id_montant_paye.setText(""+m.getMontantPaye()+" €");
		this.id_mode_de_paiement.setText("chèque");
		this.id_coordonnees.setText(m.getCoordonnees());

		this.id_total.setText(""+m.calculMontantDu()+" €");

		this.prix = new ArrayList<>();
		this.nb_heure = new ArrayList<>();
		this.description = new ArrayList<>();

		this.prix.add(this.id_prix_1);
		this.prix.add(this.id_prix_2);
		this.prix.add(this.id_prix_3);

		this.nb_heure.add(this.id_nb_heure_1);
		this.nb_heure.add(this.id_nb_heure_2);
		this.nb_heure.add(this.id_nb_heure_3);

		this.description.add(this.id_description_1);
		this.description.add(this.id_description_2);
		this.description.add(this.id_description_3);
		
		int nbBoucles;

		if (m.getCours().size()>3){
			nbBoucles=3;
		}
		for (int i=0;i<3;i++){
			this.description.get(i).setText("");
			this.nb_heure.get(i).setText("");
			this.prix.get(i).setText("");
		}
		if (m.getCours().size()>0){
			nbBoucles=m.getCours().size();
			for (int i=0;i<nbBoucles;i++){
				this.description.get(i).setText(m.getCours().get(i).getIntitule());
				this.nb_heure.get(i).setText(m.getCours().get(i).getHeure());
				this.prix.get(i).setText(""+m.getCours().get(i).calculPrix(m.getTarifApplique()));
			}
		}
	}
    
    @FXML void initialize() {}
}
