package ihm;

import java.io.File;
import modele.*;

import java.io.IOException;

import javafx.fxml.FXMLLoader;
import javafx.scene.*;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class FenChxTriage extends Stage {
	private CtrlChxTriage ctrl;
	
	public FenChxTriage() throws IOException {
		this.setTitle("Liste des membres");
		this.setMinHeight(600.0);
		this.setMinWidth(700.0);
		this.minWidthProperty();
		this.setResizable(false);
		Scene laScene = new Scene(creerSceneGraph());
		this.setScene(laScene);
	}

	private BorderPane creerSceneGraph() throws IOException{ 
		File f = new File("choixTriage.fxml");
		FXMLLoader loader;
		loader = new FXMLLoader(f.toURI().toURL());
		BorderPane racine = loader.load();
		ctrl = loader.getController();
		return racine;
	}
	public void lancerTri() {
		ctrl.lancerTri();
	}

}
