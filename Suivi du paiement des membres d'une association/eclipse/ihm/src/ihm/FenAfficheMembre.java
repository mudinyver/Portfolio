package ihm;

import java.io.File;
import modele.*;
import javafx.fxml.FXML;

import java.io.IOException;

import javafx.fxml.FXMLLoader;
import javafx.scene.*;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class FenAfficheMembre extends Stage {
	private CtrlAfficheMembre ctrl;
	
	public FenAfficheMembre() throws IOException {
		this.setTitle("Fiche d'information d'un membre");
		this.setMinHeight(300.0);
		this.setMinWidth(750.0);
		this.minWidthProperty();
		this.setResizable(false);
		Scene laScene = new Scene(creerSceneGraph());
		this.setScene(laScene);
	}

	private BorderPane creerSceneGraph() throws IOException{ 
		File f = new File("afficheMembre.fxml");
		FXMLLoader loader;
		loader = new FXMLLoader(f.toURI().toURL());
		BorderPane racine = loader.load();
		ctrl = loader.getController();
		return racine;
	}
	
	public void rafraichir() {
		ctrl.rafraichir();
	}
	
	public void afficherMembre(Membre m) {
		ctrl.afficherMembre(m);
	}

}
