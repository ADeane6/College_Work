import java.net.*;
import java.util.*;
import java.io.*;
class ChatServer
{
	public static void main(String[] args)  
	{
		try
		{
			ServerSocket ss = new ServerSocket(7777);
			Activity [] clients = new Activity[10];
			int count=0;
			boolean l=true;
			while(l)
			{
			
				Socket s = new Socket();
				s=ss.accept();
				
				Activity t = new Activity(s,clients);
				clients[count]=t;
				count++;
				t.start();
			}
			
		}
		catch(Throwable t)
		{

		}
	}
}
class Activity extends Thread{
	Socket connect = null;
	BufferedReader dis;
	PrintWriter dos;
	Activity[] cl;
	String name;
	int current=1;
	int counter=0;
	int counter2=0;
	Activity(Socket s, Activity[] t)
	{
		connect=s;
		cl=t;
	}

	public void run()  
	{
		try
		{
			for(int k=0;k<9;k++)
			{
				if(cl[k]!=null)
					counter2+=1;
			}
			if(counter2==0)
			{
				current=1;
			}
			else
			{
				current=counter2;
			}
			dis=new  BufferedReader(new InputStreamReader(connect.getInputStream()));
			 
			name=dis.readLine();
			System.out.println("Client number "+current);
			dos =new PrintWriter(connect.getOutputStream(), true);
			
			for(int i=0;i<9;i++)
			{	
				if( cl[i]!=null)
					cl[i].dos.println( name +" joined the chat");
			}
			int loop =0;
			while(loop==0)
			{
				
				String k = dis.readLine();
				for(int i=0;i<9;i++)
				{
				if(cl[i]!=null)
					cl[i].dos.println(name +" says : "+k);
				}
				
				
			}
		}
		catch(Throwable t)
		{

		}
		finally
		{
			for(int i=0;i<9;i++)
			{
					if( cl[i]!=null)
					cl[i].dos.println( name +" left the chat");
					if(cl[i]==this)
					cl[i]=null;
					
			}
			for(int k=0;k<9;k++)
			{
					if(cl[k]!=null)
							counter+=1;
			}
				System.out.println("Client number "+(counter));

		}
		
		
	}
	

}