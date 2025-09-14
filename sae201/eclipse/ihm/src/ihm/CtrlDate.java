package ihm;

import java.util.Date;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextField;
import modele.Liste;
import modele.Membre;
import modele.Paiement;

public class CtrlDate {
	@FXML private DatePicker dpDate;
	@FXML private TextField txtMontant;
	@FXML private Button bnValider;
	@FXML private Button bnAnnuler;

	private int numeroMembre;
	
	private Paiement paiement;
	
	public void afficherPaiement(Paiement p, int numeroMembre) {
		this.paiement=p;
		this.numeroMembre=numeroMembre;
		txtMontant.setText(""+p.getMontant());
	}
	
	private void estDecimal(String str) throws Exception{
		if (str.matches("\\d*(\\.\\d+)?")==false) {
			throw new Exception("Mauvais format de matricule.");
		}
	}
	
	private void estUneDate(String str) throws Exception{
		if (str.matches("dd-MM-yyyy")==false) {
			throw new Exception("Mauvais format de matricule.");
		}
	}
	
	@FXML public void valider(ActionEvent event) throws Exception{
		this.paiement.modifDate(new Date(dpDate.getValue().getYear()+"/"+
				dpDate.getValue().getMonthValue()+"/"+
				dpDate.getValue().getDayOfMonth())
				);
		this.estDecimal(txtMontant.getText());
		this.paiement.modifMontant(Float.parseFloat(txtMontant.getText()));
		for (Membre m : Liste.getMembres()) {
			if (m.getNumero()==this.numeroMembre){
				for (Paiement p : m.getPaiements()) {
					if (p.getNum()==this.paiement.getNum()){
						p.modifPaiement(this.paiement.getDateFormatDate(),this.paiement.getMontant());
					}
				}
			}
		}
		Main.rafraichirMembre();
		Main.fermerAfficheDate();
	}
	
	@FXML void fermer(ActionEvent event) {
		Main.fermerAfficheDate();
	}
	
	void initialize() {}
	
	
	
}