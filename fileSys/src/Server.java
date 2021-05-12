import com.sun.source.tree.WhileLoopTree;

import java.io.*;
import java.net.*;
import java.io.File;

class Server {


	public static void main(String[] args) {
		try {

			//FileSystem fs = new FileSystem();

			// Create server Socket that listens/bonds to port/endpoint address 6666 (any port id of your choice, should be >=1024, as other port addresses are reserved for system use)
			// The default maximum number of queued incoming connections is 50 (the maximum number of clients to connect to this server)
			// There is another constructor that can be used to specify the maximum number of connections
			ServerSocket mySocket = new ServerSocket(6666);

			
			System.out.println("Startup the server side over port 6666 ....");

			while (true){
				// use the created ServerSocket and accept() to start listening for incoming client requests targeting this server and this port
				// accept() blocks the current thread (server application) waiting until a connection is requested by a client.
				// the created connection with a client is represented by the returned Socket object.
				Socket connectedClient = mySocket.accept();


				// reaching this point means that a client established a connection with your server and this particular port.
				System.out.println("Connection established");


				// to interact (read incoming data / send data) with the connected client, we need to create the following:

				// BufferReader object to read data coming from the client
				BufferedReader br = new BufferedReader(new InputStreamReader(connectedClient.getInputStream()));

				// PrintStream object to send data to the connected client
				PrintStream ps = new PrintStream(connectedClient.getOutputStream());

				ps.println("Connection established to FileSystem Server");

				// Let's keep reading data from the client, as long as the client does't send "exit".
				String inputData;
				while (!(inputData = br.readLine()).equals("Exit")) {

					System.out.println("received a message from client: " + inputData);   //print the incoming data from the client

					String command = "";
					if (inputData.length() > 0 && inputData.contains(" ")) {
						command = inputData.substring(0, inputData.indexOf(" "));
						inputData = inputData.substring(inputData.indexOf(" ") + 1);
					} else {
						ps.println("Invalid Command");
						continue;
					}

					if (command.equals("NewClient")) {
						if (!inputData.contains(" ")) {
							File Dir = new File(inputData);
							if (!Dir.exists()) {
								if (Dir.mkdir()) {
									ps.println("welcome to our file system, you are added as a new client");
								} else {
									ps.println("Error");
								}
							} else {
								ps.println("CID already existed");
							}
							continue;
						}
					}

					if (command.equals("CreateDirectory")) {
						if (inputData.contains(";")) {
							String CID = inputData.substring(0, inputData.indexOf(";"));
							String path = CID + "/" + inputData.substring(inputData.indexOf(" ") + 1);
							if (!path.contains(" ")) {
								File cidir = new File(CID);
								if (cidir.exists()) {
									File Dir = new File(path);
									if (!Dir.exists()) {
										if (Dir.mkdir()) {
											ps.println("the  directory  is  successfully created");
										} else {
											ps.println("Invalid Path");
										}
									} else {
										ps.println("Dir already exists");
									}
								} else {
									ps.println("This CID does not exist");
								}
								continue;
							}
						}
					}

					if (command.equals("MoveFile")) {
						if (inputData.length() == 0 || !inputData.contains(";")) {
							ps.println("Invalid Command");
							continue;
						}

						String CID = inputData.substring(0, inputData.indexOf(";"));

						if (inputData.length() <= inputData.indexOf(" ") + 1) {
							ps.println("Invalid Command");
							continue;
						}

						inputData = inputData.substring(inputData.indexOf(" ") + 1);
						String path = inputData.substring(0, inputData.indexOf(";"));

						if (inputData.length() <= inputData.indexOf(" ") + 1) {
							ps.println("Invalid Command");
							continue;
						}

						inputData = inputData.substring(inputData.indexOf(" ") + 1);
						String filePath = "/" + inputData.substring(0);
						String fileName = filePath.substring(inputData.lastIndexOf("/") + 1);

						if (filePath.contains(" ")) {
							ps.println("Invalid Filepath");
							continue;
						}

						File file = new File(System.getProperty("user.home") + filePath);

						File cidir = new File(CID);
						if (!cidir.exists()) {
							ps.println("This CID does not exist");
							continue;
						}

						File newFile;
						if (path.length() > 0)
							newFile = new File(CID + "/" + path + "/" + fileName);
						else
							newFile = new File(CID + "/" + fileName);

						if (!file.exists()) {
							ps.println("file does not exist");
							continue;
						}

						if (file.renameTo(newFile)) {
							ps.println("the file is successfully moved under your directory");
							continue;
						}

						ps.println("The directory does not exist for this client");
						continue;

					}

					if (command.equals("DeleteFile")) {
						if (inputData.length() == 0 || !inputData.contains(";")) {
							ps.println("Invalid Command");
							continue;
						}

						String CID = inputData.substring(0, inputData.indexOf(";"));

						if (inputData.length() <= inputData.indexOf(" ") + 1) {
							ps.println("Invalid Command");
							continue;
						}

						inputData = inputData.substring(inputData.indexOf(" ") + 1);

						if (!inputData.contains(";")) {
							ps.println("Invalid Command");
							continue;
						}

						String path = inputData.substring(0, inputData.indexOf(";"));

						if (inputData.length() <= inputData.indexOf(" ") + 1) {
							ps.println("Invalid Command");
							continue;
						}

						inputData = inputData.substring(inputData.indexOf(" ") + 1);
						String filePath = "/" + inputData.substring(0);
						String fileName = filePath.substring(inputData.lastIndexOf("/") + 1);

						if (filePath.contains(" ")) {
							ps.println("Invalid Filepath");
							continue;
						}

						File cidir = new File(CID);
						if (!cidir.exists()) {
							ps.println("This CID does not exist");
							continue;
						}

						File file = new File(CID + "/" + path + "/" + fileName);

						if (!file.exists()) {
							ps.println("file does not exist");
							continue;
						}

						if (file.delete()) {
							ps.println("The file was successfully removed from this directory");
							continue;
						}

						ps.println("The directory does not exist for this client");
						continue;
					}

					ps.println("Invalid Command");

					//ps.println(command);

				}

				System.out.println("Closing the connection and the sockets");
				ps.println("Logging out");

				// close the input/output streams and the created client/server sockets
				ps.close();
				br.close();
				connectedClient.close();
			}

		} catch (Exception exc) {
			System.out.println("Error :" + exc.toString());
		}

	}
}