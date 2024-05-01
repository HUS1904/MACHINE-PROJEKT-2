package com.solitaire.yukon;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.*;
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
import java.util.concurrent.atomic.AtomicInteger;
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
    static VBox home;
    static Image logo;
    static VBox mainInteractionPanel;
    static HBox InteractionPanel;
    @Override
    public void start(Stage stage) throws IOException {
        serverAddress = InetAddress.getByName("127.0.0.1"); // Change this to the actual server address
        int serverPort = 8080;

        // Create UDP socket
        socket = new DatagramSocket();

        root = new VBox();
        root.setId("root");
        root.setSpacing(500);
        root.setPadding(new Insets(10, 10, 10, 10));

        button = new Button("RUN");
        button.setId("button");
        button.setPadding(new Insets(10, 10, 10, 10));
        button.setOnAction(e -> onButtonPressed());

        status = new Label("AWAITING INPUT");
        status.setId("status");

        text = new TextField();
        text.setId("text");
        text.setPromptText("ENTER COMMAND");




        InteractionPanel = new HBox(button, text);
        InteractionPanel.setMargin(button, new Insets(0, 10, 0, 0));
        InteractionPanel.setId("interactionPanel");
        mainInteractionPanel = new VBox(status, InteractionPanel);
        mainInteractionPanel.setId("mainInteractionPanel");

        logo = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/logo.png")));
        ImageView logoView = new ImageView(logo);
        logoView.setId("logo");

        home = new VBox();
        home.setId("home");
        home.getChildren().addAll(logoView, mainInteractionPanel);

        root.getChildren().addAll(home);

        Scene scene = new Scene(root);
        scene.getStylesheets().add(getClass().getResource("/stylesheet.css").toExternalForm());
        stage.setTitle("YUKON");
        stage.setScene(scene);
        stage.setMaximized(true);
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
                status.setText("MESSAGE: " + response);

                if(message.startsWith("LD")){
                    status.setText(response);
                } else {
                    String relativePath = "state.txt"; // Example relative path
                    File file = new File(relativePath);

                    colsAndFound = Files.lines(Path.of(file.getPath()))
                                        .map(x-> new ArrayList<>(Arrays.asList(x.split(" "))))
                                        .collect(Collectors.toCollection(ArrayList::new));

                    updateView();
                }

            } else{

                status.setText(response);
            }
        } catch(IOException _) {

        }
        text.clear();
    }

    public void updateView() {
        root.getChildren().clear();
        root.getStylesheets().add(getClass().getResource("/stylesheet2.css").toExternalForm());
        GridPane grid2 = new GridPane();
        grid2.setHgap(30); // Set horizontal gap between columns
        grid2.setVgap(20); // Set vertical gap between rows

        ArrayList<VBox> vboxes = new ArrayList<>();

        AtomicInteger colNumber = new AtomicInteger(1);
        colsAndFound.forEach(x -> {
            VBox vbox = new VBox();
            Label label = new Label("COLUMN " + colNumber.getAndIncrement());
            label.setId("headers");
            vbox.setMargin(label, new Insets(40, 0, -40, 5));
            vbox.getChildren().add(label);

            x.forEach(y -> {
                Card card = y.equals(".") ? new Card("turned") : new Card(y);
                card.setTranslateY(50);
                vbox.getChildren().add(card);

            });
            vboxes.add(vbox);
        });

        vboxes.forEach(x-> {
            ColumnConstraints column = new ColumnConstraints();
            column.setPercentWidth(100.0 / 17.0);
            grid2.getColumnConstraints().add(column);
            grid2.addColumn(vboxes.indexOf(x), x);
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
                Card card = new Card(i-6);
                foundations.getChildren().add(card);

                card.setTranslateY(50 +(counter*0.25*50));

            }

        }

        grid2.add(foundations,7,0);
        // Add the GridPane and other nodes back to the root VBox
        root.getChildren().addAll(grid2, mainInteractionPanel);

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

        public Card(int i){
            setPrefSize(WIDTH, HEIGHT);
            image = new Image(Objects.requireNonNull(getClass().getResourceAsStream("/F" + String.valueOf(i) + ".png")));
            ImageView imageView = new ImageView(image);
            imageView.setFitHeight(HEIGHT);
            imageView.setFitWidth(WIDTH);

            getChildren().addAll(imageView);
        }
    }
}