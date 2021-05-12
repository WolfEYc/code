import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.*;
import java.util.Scanner;
import javax.swing.*;
import javax.swing.border.Border;

class Client {


	public static void main(String[] args) {
		try {

			// Create client socket to connect to certain server (Server IP, Port address)
			// we use either "localhost" or "127.0.0.1" if the server runs on the same device as the client
			final Socket[] mySocket = new Socket[1]; //= new Socket("127.0.0.1", 6666);


			// to interact (send data / read incoming data) with the server, we need to create the following:

			//DataOutputStream object to send data through the socket

			final DataOutputStream[] outStream = new DataOutputStream[1];// = new DataOutputStream(mySocket.getOutputStream());

			// BufferReader object to read data coming from the server through the socket
			final BufferedReader[] inStream = new BufferedReader[1]; // = new BufferedReader(new InputStreamReader(mySocket.getInputStream()));

			//Creating the Frame
			JFrame frame = new JFrame("FileSystem GUI");
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.setSize(500, 300);

			//Creating the panel at bottom and adding components
			JPanel panel = new JPanel(); // the panel is not visible in output

			JLabel label = new JLabel("ClientID:");
			JTextField tf = new JTextField(10); // accepts upto 10 characters
			JLabel labelIP = new JLabel("ServerIP:");
			JTextField textzone = new JTextField(10); // accepts upto 10 characters
			JLabel labelPort = new JLabel("Port:");
			JTextField textport = new JTextField(4); // accepts upto 10 characters
			JButton connectButton = new JButton("connect");
			JButton disconnectButton = new JButton("disconnect");

			panel.add(label); // Components Added using Flow Layout
			panel.add(tf);
			panel.add(labelIP); // Components Added using Flow Layout
			panel.add(textzone);
			panel.add(labelPort);
			panel.add(textport);
			panel.add(connectButton);
			panel.add(disconnectButton);

			JPanel reqres = new JPanel();
			reqres.setBorder(BorderFactory.createEmptyBorder(0, 0, 80, 0));
			JLabel commandLabel = new JLabel("Command: ");
			JTextField commandField = new JTextField(30);
			JButton runbutton = new JButton("run");

			JLabel resultsLabel = new JLabel("Accumulated Results:");
			JTextArea resultsTextBox = new JTextArea(7,39);
			JScrollPane scrollPane = new JScrollPane(resultsTextBox);
			resultsTextBox.setEditable(false);

			JButton clearButton = new JButton("clear");

			connectButton.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent actionEvent) {
					try{
						mySocket[0] = new Socket(textzone.getText(),Integer.parseInt(textport.getText()));
						outStream[0] = new DataOutputStream(mySocket[0].getOutputStream());
						inStream[0] = new BufferedReader(new InputStreamReader(mySocket[0].getInputStream()));
						String fromserv = inStream[0].readLine();     	// receive response from server
						resultsTextBox.append(fromserv+"\n");
					}catch (Exception exc) {
						System.out.println("Error is : " + exc.toString());
					}
				}
			});

			disconnectButton.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent actionEvent) {
					try {
						outStream[0].writeBytes("Exit"+"\n");
						String fromserv = inStream[0].readLine();     	// receive response from server
						resultsTextBox.append(fromserv+"\n");
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			});

			runbutton.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent actionEvent) {
					String statement = commandField.getText();
					try {
						outStream[0].writeBytes(statement+"\n");
						String fromserv = inStream[0].readLine();     	// receive response from server
						resultsTextBox.append(fromserv+"\n");

					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			});

			clearButton.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent actionEvent) {
					resultsTextBox.setText("");
				}
			});

			reqres.add(commandLabel);
			reqres.add(commandField);
			reqres.add(runbutton);
			reqres.add(resultsLabel);
			reqres.add(scrollPane);
			reqres.add(clearButton);

			//Adding Components to the frame.
			frame.getContentPane().add(panel);
			frame.getContentPane().add(BorderLayout.SOUTH,reqres);
			frame.setVisible(true);
		
		} catch (Exception exc) {
			System.out.println("Error is : " + exc.toString());

		}
	}

}