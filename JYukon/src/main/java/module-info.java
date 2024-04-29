module com.solitaire.yukon {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.solitaire.yukon to javafx.fxml;
    exports com.solitaire.yukon;
}