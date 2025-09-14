package ihm;

import java.io.File;
import modele.*;

import java.io.IOException;

import javafx.fxml.FXMLLoader;
import javafx.scene.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import modele.*;

public class FenFacture extends Stage {
	private CtrlFacture ctrl;
	
	public FenFacture() throws IOException {
		this.setTitle("Facture de côtisation annuelle");
		this.setMinHeight(600.0);
		this.setMinWidth(400.0);
		this.minWidthProperty();
		this.setResizable(true);
		Scene laScene = new Scene(creerSceneGraph());
		this.setScene(laScene);
	}

	private Pane creerSceneGraph() throws IOException{ 
		File f = new File("FunFacture.fxml");
		FXMLLoader loader;
		loader = new FXMLLoader(f.toURI().toURL());
		Pane racine = loader.load();
		ctrl = loader.getController();
		return racine;
	}
	
	public void genererFacture(Membre m) {
		ctrl.genererFacture(m);
	}

}
