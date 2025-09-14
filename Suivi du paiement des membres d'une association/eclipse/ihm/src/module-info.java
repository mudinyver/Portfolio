/**
 * 
 */
/**
 * 
 */
module ihm {
	requires javafx.base;
	requires javafx.controls;
	requires javafx.graphics;
	requires javafx.fxml;
	
	opens ihm to javafx.base, javafx.controls, javafx.graphics, javafx.fxml;
	opens modele to javafx.base, javafx.controls, javafx.graphics, javafx.fxml;
}