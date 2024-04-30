package com.solitaire.yukon;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Objects;
import java.util.stream.Collectors;


public class Main extends Application {
   static TextField text;
    static DatagramSocket socket;
    static InetAddress serverAddress; // Change this to the actual server address
    static int serverPort = 8080;
    static VBox root;
    static Label status;
    static ArrayList<ArrayList<String>> colsAndFound = new ArrayList<>();
    static GridPane cardGround = new GridPane();
    static Button button;
    static  VBox interactionPanel;
    @Override
    public void start(Stage stage) throws IOException {
        serverAddress = InetAddress.getByName("127.0.0.1"); // Change this to the actual server address
        int serverPort = 8080;

        // Create UDP socket
        socket = new DatagramSocket();

        root = new VBox();
        root.setSpacing(500);
        root.setPadding(new Insets(10, 10, 10, 10));

        button = new Button("send");
        button.setPadding(new Insets(10, 10, 10, 10));
        button.setOnAction(e -> onButtonPressed());

        status = new Label("awaiting for input: ");

        text = new TextField();
        text.setPromptText("Enter Command");

        interactionPanel = new VBox(button,text,status);

        root.getChildren().addAll(interactionPanel);

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
                    String relativePath = "state.txt"; // Example relative path
                    File file = new File(relativePath);

                    colsAndFound = Files.lines(Path.of(file.getPath()))
                                        .map(x-> new ArrayList<>(Arrays.asList(x.split(" "))))
                                        .collect(Collectors.toCollection(ArrayList::new));

                    updateView();
                }

            } else{

                status.setText("Error: " + response);
            }
        } catch(IOException _) {

        }

    }

    public void updateView() {
        root.getChildren().clear();
        GridPane grid = new GridPane();
        grid.setHgap(30); // Set horizontal gap between columns
        grid.setVgap(20); // Set vertical gap between rows
        ArrayList<VBox> vboxes = new ArrayList<>();


        colsAndFound.forEach(x -> {
            VBox vbox = new VBox();
            x.forEach(y -> {
                // Card card = y.equals(".") ? new Card("turned") : new Card(y);
                Card card = new Card("turned");
                card.setTranslateY(50);
                vbox.getChildren().add(card);
            });
            vboxes.add(vbox);
        });

        vboxes.forEach(x-> {
            ColumnConstraints column = new ColumnConstraints();
            column.setPercentWidth(100.0 / 13.0);
            grid.getColumnConstraints().add(column);
            grid.addColumn(vboxes.indexOf(x), x);
        });

        VBox foundations = new VBox();
        foundations.setSpacing(50);
        foundations.setPadding(new Insets(0, 0, 0, 200));
        for(int i = 7; i< 11;i++){
            int counter = 0;
            if(! (i > colsAndFound.size() - 1)){
                String name = colsAndFound.get(i).getLast();
                Card card = new Card(name);
                foundations.getChildren().add(card);
                card.setTranslateY(50 +(counter*0.25*50));

            } else{
                Card card = new Card();
                foundations.getChildren().add(card);

                card.setTranslateY(50 +(counter*0.25*50));

            }

        }

        grid.add(foundations,7,0);
        // Add the GridPane and other nodes back to the root VBox
        root.getChildren().addAll(grid,interactionPanel);
    }
    public static void main(String[] args) {
        launch();
    }

  static class Card extends Pane {
        private static final double WIDTH = 100;
        private static final double HEIGHT = 150;
        Image image ;

        public Card(String name) {
            setPrefSize(WIDTH, HEIGHT);

            image = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/" + name + ".png")));

            ImageView imageView = new ImageView(image);
            imageView.setFitHeight(HEIGHT);
            imageView.setFitWidth(WIDTH);

            getChildren().addAll(imageView);
        }

        public Card(){
            setPrefSize(WIDTH, HEIGHT);
            Rectangle rect = new Rectangle(WIDTH, HEIGHT);
            rect.setFill(Color.WHITE);
            rect.setStroke(Color.BLACK);
            getChildren().add(rect);
        }
    }
}