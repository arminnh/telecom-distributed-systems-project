package client;
import message.*;
import java.net.*;
import java.lang.reflect.*;
import server.*; // for SayHelloObject

public class Client {

	public static void main(String[] args) {
		try {			
			InetAddress addr = InetAddress.getByName(args[0]);
			Socket socket = new Socket(addr, Integer.parseInt(args[1]));
			CommunicationModule comm = new CommunicationModule(socket);
			
			Class<?> sayHelloObjectClass = Class.forName("server.SayHelloObject");
			SayHelloObjectInterface sayHelloProxy = (SayHelloObjectInterface) ProxyLookup.lookup(sayHelloObjectClass, comm);

			System.out.println(sayHelloProxy.sayHello("Josse"));
			System.out.println(sayHelloProxy.add(2, 3));
			
			socket.close();
			
		} catch (UnknownHostException e) {
            System.err.println("Don't know about host " + args[0]);
            e.printStackTrace();
            System.exit(1);
        } catch (Exception e) {
			e.printStackTrace();
		}

	}

}