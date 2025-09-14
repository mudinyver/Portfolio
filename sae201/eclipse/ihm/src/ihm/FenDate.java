package ihm;

import java.io.File;
import modele.*;

import java.io.IOException;

import javafx.fxml.FXMLLoader;
import javafx.scene.*;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

public class FenDate extends Stage {
	private CtrlDate ctrl;
	
	public FenDate() throws IOException {
		this.setTitle("Liste des membres");
		this.setMinHeight(250.0);
		this.setMinWidth(500.0);
		this.minWidthProperty();
		this.setResizable(true);
		Scene laScene = new Scene(creerSceneGraph());
		this.setScene(laScene);
	}
	
	public void afficherPaiement(Paiement p,int numeroMembre) {
		ctrl.afficherPaiement(p,numeroMembre);
	}

	private Pane creerSceneGraph() throws IOException{ 
		File f = new File("FenPaiement.fxml");
		FXMLLoader loader;
		loader = new FXMLLoader(f.toURI().toURL());
		Pane racine = loader.load();
		ctrl = loader.getController();
		return racine;
	}

}
