package com.solitaire.yukon;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Path;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


public class HelloApplication extends Application {
   static TextField text;
    static DatagramSocket socket;
    static InetAddress serverAddress; // Change this to the actual server address
    static int serverPort = 8080;
    static  VBox root;
    static Label status;
    static String[][] colsAndFound = new String[11][];
    static GridPane cardGround = new GridPane();
    static Button button;
    @Override
    public void start(Stage stage) throws IOException {



         serverAddress = InetAddress.getByName("127.0.0.1"); // Change this to the actual server address
        int serverPort = 8080;

        // Create UDP socket
         socket = new DatagramSocket();




        root = new VBox();
        root.setSpacing(0);
        root.setPadding(new Insets(20, 20, 20, 20));








        button = new Button("send");
        button.setPadding(new Insets(10, 10, 10, 10));
        button.setOnAction(e -> onButtonPressed());



        //


        //
        status = new Label("awaiting for input: ");


        //


        text = new TextField();
        text.setPromptText("Enter Command");

        root.getChildren().addAll(button,text,status);

        Scene scene = new Scene(root);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }



    public void onButtonPressed() {
        String message = text.getText();


        try {
            byte[] sendData = message.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, serverAddress, serverPort);
            socket.send(sendPacket);

            // Receive response from the server
            byte[] receiveData = new byte[1024];
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            socket.receive(receivePacket);
            String response = new String(receivePacket.getData(), 0, receivePacket.getLength());
            if (response.equals("OK")) {
                status.setText("Response Received: " + response);

                if(message.equals("LD")){
                    status.setText("Deck Loaded");
                } else {
                    int counter = 0;
                    String relativePath = "state.txt"; // Example relative path
                    File file = new File(relativePath);
                    try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
                        String line;

                        while ((line = reader.readLine()) != null && counter < 7) {
                            System.out.println(line);

                            // Split the line into an array of strings based on spaces
                            String[] split = line.split(" ");

                            // Assign the split array to the corresponding row in colsAndFound
                            colsAndFound[counter] = split;

                            counter++;
                        }
                    } catch (IOException e) {
                        System.err.println("Error occurred while reading the file: " + e.getMessage());
                    }
                    updateView();
                }

            } else{

                status.setText("Error: " + response);
            }
        } catch(IOException e) {

        }

    }

    public void updateView() {
        root.getChildren().clear();
        GridPane grid = new GridPane();
        grid.setHgap(30); // Set horizontal gap between columns
        grid.setVgap(20); // Set vertical gap between rows
        VBox[] vboxes = new VBox[7];
        double verticalOffset = 1000 / 13;

        // Initialize VBox containers and populate them with Card objects
        for (int i = 0; i < 7; i++) {
            String[] cards = colsAndFound[i];
            vboxes[i] = new VBox();

            // Populate each VBox with Card objects
            for (int j = 0; j < cards.length; j++) {
                String name = cards[j];
                Card card = new Card("turned");
                vboxes[i].getChildren().add(card);
                card.setTranslateY(50);
            }




            // Add the populated VBox to the GridPane
            grid.add(vboxes[i], i, 0); // Add VBox to the corresponding column (i)
        }

        // Add the GridPane and other nodes back to the root VBox
        root.getChildren().addAll(grid, button, text, status);
    }
    public static void main(String[] args) {
        launch();
    }

  class Card extends Pane {

        private static final double WIDTH = 100;
        private static final double HEIGHT = 150;
        Image image ;

        public Card(String name) {
            setPrefSize(WIDTH, HEIGHT);
            Rectangle cardShape = new Rectangle(WIDTH, HEIGHT, Color.WHITE);
            cardShape.setStroke(Color.BLACK);
            image = new Image(getClass().getResourceAsStream("/" + name + ".png"));

            ImageView imageView = new ImageView(image);

            getChildren().addAll(cardShape,imageView);
        }
    }
}