package com.solitaire.yukon;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {

        try {
            // Define server address and port
            InetAddress serverAddress = InetAddress.getByName("127.0.0.1"); // Change this to the actual server address
            int serverPort = 8080; // Change this to the actual server port

            // Create UDP socket
            DatagramSocket socket = new DatagramSocket();

            // Create scanner to read user input
            Scanner scanner = new Scanner(System.in);

            // Loop to continuously send messages
            while (true) {
                // Prompt user for input
                System.out.print("Enter message to send to server (enter 'qq' to quit): ");
                String message = scanner.nextLine();

                // Check if user wants to quit
                if (message.equalsIgnoreCase("qq")) {
                    System.out.println("Client exiting...");
                    break;
                }

                // Send data to the server
                byte[] sendData = message.getBytes();
                DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, serverAddress, serverPort);
                socket.send(sendPacket);

                // Receive response from the server
                byte[] receiveData = new byte[1024];
                DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                socket.receive(receivePacket);
                String response = new String(receivePacket.getData(), 0, receivePacket.getLength());
                System.out.println("Response from server: " + response);

            }

            // Close scanner and socket
            scanner.close();
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 320, 240);
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}