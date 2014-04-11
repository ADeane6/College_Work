import javax.sound.sampled.*;
import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

class Player extends Panel{
	private static final long serialVersionUID = 1L;
	private TextField textfield;
	private TextArea textarea;
	private Font font;
	private String filename;
	private DataLine.Info info;
	private FloatControl volume; 
	private BooleanControl mute;
	int duration, chunkSize;
	boolean pause, end, pClosed;
	SourceDataLine output;
	AudioInputStream song;
	AudioFormat format;
	


	public Player(String filename){

		font = new Font(Font.SANS_SERIF, Font.PLAIN, 12);
		textfield = new TextField();
		textarea = new TextArea();
		textarea.setFont(font);
		textfield.setFont(font);
		setLayout(new BorderLayout());
		add(BorderLayout.SOUTH, textfield);
		add(BorderLayout.CENTER, textarea);

		try{
			song = AudioSystem.getAudioInputStream(new File(filename));
			format = song.getFormat(); 
			info = new DataLine.Info(SourceDataLine.class, format);
			output = (SourceDataLine) AudioSystem.getLine(info);
			output.open(format);
		}catch(UnsupportedAudioFileException |IOException|LineUnavailableException e){}
		long frames = song.getFrameLength();
		duration = (int)((frames+0.0) / format.getFrameRate());
		chunkSize =  (int) (format.getChannels() * format.getSampleRate() * format.getSampleSizeInBits() / 8); 

		volume = (FloatControl) output.getControl(FloatControl.Type.MASTER_GAIN); 
		mute =  (BooleanControl) output.getControl(BooleanControl.Type.MUTE);

		output.start();
		pause = false;
		end = false;
		pClosed = false;

		this.filename = filename;


		textfield.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String vol = String.format("%.0f",volume.getValue());
				switch(e.getActionCommand())
				{
					case "q":
						if((volume.getValue()+1.0f)>0)
						{
							textarea.append("MAX Volume\n");
							textfield.setText("");
							break;
						}
						volume.shift(volume.getValue(),volume.getValue()+1.0f,1);
						textarea.append("The current Volume is: "+vol+"\n");
						textfield.setText("");
						break;
					case "a":
						if((volume.getValue()-1.0f)<-80f)
						{
							textarea.append("MIN Volume\n");
							textfield.setText("");
							break;
						}
						volume.shift(volume.getValue(),volume.getValue()-1.0f,1);
						textarea.append("The current Volume is: "+vol+"\n");
						textfield.setText("");
						break;
					case "m":
						mute.setValue(true);
						textarea.append("Song Muted\n");
						textfield.setText("");
						break;
					case "u":
						mute.setValue(false);
						textarea.append("Song Un-Muted\n");
						textfield.setText("");
						break;
					case "p":
						pause = true;
						textarea.append("Song Paused\n");
						break;
					case "r":
						pause = false;
						textarea.append("Song Resumed\n");
						break;
					case "x":

						textarea.append("Shutting Down\n");
						textfield.setText("");
						end = true;
						break;

				}
			}
		});
	}

	public void write(String words)
	{
		textarea.append(words+"\n");
	}
	
}

//init is main for applet
public class AudioPlayer extends Applet implements Runnable
{
	private static final long serialVersionUID = 1L;
	Player audioP;
	Producer reader;
	Consumer dj;
	BoundedBuffer audioBuffer;
	Thread main;

	public void init() 
	{

		setLayout(new BorderLayout());
		audioP = new Player(getParameter("file"));
		add(BorderLayout.CENTER, audioP);

	}

	public void start()
	{
		main = new Thread (this);
		main.start();
	}

	public void run(){

		audioBuffer = new BoundedBuffer(audioP.chunkSize);

		reader = new Producer(audioBuffer,audioP);
		dj = new Consumer(audioBuffer,audioP);

		reader.start();
		dj.start();

	}
}
class BoundedBuffer
{
	int nextIn;
	int nextOut;
	final int slots = 10;
	int size;
	int occupied;
	int ins;
	int outs;
	int chunkSize;
	byte [] buffer;
	
	
	boolean dataAvailable; //for consumer
	boolean roomAvailable; //for producer
	BoundedBuffer(int chunk)
	{
		chunkSize = chunk;
		size = chunkSize*slots;
		buffer = new byte[size];
		roomAvailable = true;
		dataAvailable = false;
		nextIn = 0;
		nextOut = 0;
		occupied = 0;
		ins = 0;
		outs = 0;
	}

	synchronized void insertChunk(byte[] chunk)
	{
		while(!roomAvailable) 
		{
			try 
			{
				wait();
			} catch (InterruptedException e) 
			{}
		}
		for (int i = nextIn, k = 0; k < chunkSize; i++, k++)
		{
			buffer[i] = chunk[k];
		}
		nextIn = (nextIn+chunkSize)%size;
		occupied++;
		ins++;
		dataAvailable = true;
		if(occupied==slots)
			roomAvailable = false;
		notifyAll();
	}
	
	synchronized byte[] removeChunk()
	{
		while(!dataAvailable) 
		{
			try 
			{
				wait();
			} catch (InterruptedException e) 
			{}
		}
		byte[] chunk = new byte[chunkSize];
		for (int i = nextOut, k = 0; k < chunkSize; i++, k++)
		{
			chunk[k] = buffer[i];
		}
		nextOut = (nextOut+chunkSize)%size;
		occupied--;
		outs++;
		roomAvailable = true;
		if(occupied==0)
			dataAvailable = false;
		notifyAll();
		return chunk;
	}

}
class Producer extends Thread
{
	BoundedBuffer bBuffer;
	Player audioP;

	Producer(BoundedBuffer buffer, Player audioP) 
	{
		bBuffer = buffer;
		this.audioP = audioP;
	}

	public synchronized void run()
	{
		try
		{	
				audioP.write("Audio format: "+audioP.format.toString());
				audioP.write("Chunk Size is: "+bBuffer.chunkSize);
				audioP.write("Song Duration is: "+audioP.duration+"s");


				byte[] currentChunk = new byte[bBuffer.chunkSize];
				while(bBuffer.ins <= audioP.duration && !audioP.end)
				{
					audioP.song.read(currentChunk);
					bBuffer.insertChunk(currentChunk);
				}
				audioP.write("Goodbye from reader ");
				audioP.pClosed = true;
		}
		catch (IOException e) {
			audioP.write("Player initialisation failed");
			e.printStackTrace();
			System.exit(1);
		}
	}

}

class Consumer extends Thread
{
	private BoundedBuffer bBuffer;
	Player audioP;

	Consumer(BoundedBuffer buffer, Player audioP) 
	{
   		bBuffer = buffer;
   		this.audioP = audioP;
	}

	public synchronized void run()
	{	
		while(!audioP.pClosed && bBuffer.outs <= audioP.duration)
		{
			while((!audioP.pClosed && !audioP.pause) || (!audioP.pause && bBuffer.outs <= audioP.duration))
			{
				byte[] audioChunk = bBuffer.removeChunk();
				audioP.output.write(audioChunk, 0, bBuffer.chunkSize);
			}
		}

		audioP.output.drain();
		audioP.output.stop();
		audioP.output.close();
		audioP.write("Goodbye from dj ");		
	}
}
