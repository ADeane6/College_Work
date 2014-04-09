import javax.sound.sampled.*;
import java.applet.Applet;
import java.io.*;
class BoundedBuffer
{
	int nextIn;
	int nextOut;
	final int size = 10;
    int occupied;
	int ins;
	int outs;
	int chunkSize;
	byte [] buffer;
	int duration;
	AudioFormat format;
	DataLine.Info info;
	
	
	boolean dataAvailable; //for consumer
	boolean roomAvailable; //for producer
	BoundedBuffer(int chunk)
	{
		chunkSize = chunk;
		buffer = new byte[chunkSize*10];
		roomAvailable = true;
		nextIn = 0;
		nextOut = 0;
		occupied = 0;
		ins = 0;
		outs = 0;
	}

	boolean over()
	{
		return !(outs <= duration);
	}

	synchronized void insertChunk(byte[] chunk)
	{
		while(occupied == size) 
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
		nextIn += chunkSize;
		nextIn = (nextIn+1)%size;
		occupied++;
		ins++;
		notifyAll();
	}
	
	synchronized byte[] removeChunk()
	{
		while(occupied == 0) 
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
		nextOut += chunkSize;
		nextOut = (nextOut+1)%size;
		occupied--;
		outs++;
		notifyAll();
		return chunk;
	}

}
class Producer extends Thread
{
	BoundedBuffer bBuffer;

	Producer(BoundedBuffer buffer) 
	{
    	bBuffer = buffer;
	}

	public synchronized void run()
	{
		try
		{	
			AudioInputStream song = AudioSystem.getAudioInputStream(new File("song.wav"));
			bBuffer.format = song.getFormat();
			bBuffer.info = new DataLine.Info(SourceDataLine.class, bBuffer.format);
		
			System.out.println("Audio format: "+bBuffer.format.toString());

			System.out.println("Chunk Size is: "+bBuffer.chunkSize);

			long frames = song.getFrameLength();
			bBuffer.duration = (int)(frames+0.0) / (int)(bBuffer.format.getFrameRate());

			System.out.println("Song Duration is: "+bBuffer.duration);


			byte[] currentChunk = new byte[bBuffer.chunkSize];
			SourceDataLine line = (SourceDataLine) AudioSystem.getLine(bBuffer.info);
			line.open(bBuffer.format);
			line.start();
			while(line.available()!=0)
			{
				int temp = song.read(currentChunk);
				bBuffer.insertChunk(currentChunk);
				System.out.println(2);
			}
			line.drain();
			line.stop();
			line.close();
		}
		catch (IOException e) {
			System.out.println("Player initialisation failed");
			e.printStackTrace();
			System.exit(1);
		} 
		catch (UnsupportedAudioFileException e ) {
			System.out.println("Player initialisation failed");
			e.printStackTrace();
			System.exit(1);
		}
		catch (LineUnavailableException e) 
		{
			System.out.println("Player initialisation failed");
			e.printStackTrace();
			System.exit(1);
		}
	
	
	}

}

class Consumer extends Thread
{
	private BoundedBuffer bBuffer;
	AudioFormat format;
	DataLine.Info info;

	Consumer(BoundedBuffer buffer) 
	{
   		bBuffer = buffer;
   		format = bBuffer.format;
   		info = bBuffer.info;
	}

	public synchronized void run()
	{
		try
		{
			AudioInputStream song = AudioSystem.getAudioInputStream(new File("song.wav"));
			AudioFormat format = song.getFormat();
			DataLine.Info info = new DataLine.Info(SourceDataLine.class, format);
			SourceDataLine line = (SourceDataLine) AudioSystem.getLine(info);
			line.open(format);
			line.start();
			while(line.available()!=0)
			{
				byte[] audioChunk = bBuffer.removeChunk();
				line.write(audioChunk, 0, bBuffer.chunkSize);
				System.out.println(1);

			}			
			line.drain();
			line.stop();
			line.close();
			System.out.println("Bye Bye from DJ");
			return;
		} 
		catch (IOException e) {
			System.out.println("Player initialisation failed");
			e.printStackTrace();
			System.exit(1);
		} 
		catch (UnsupportedAudioFileException e ) {
			System.out.println("Player initialisation failed");
			e.printStackTrace();
			System.exit(1);
		}
		catch (LineUnavailableException e) 
		{
			System.out.println("Player initialisation failed");
			e.printStackTrace();
			System.exit(1);
		}
	
	
	}

}
class AudioPlayer
{
	public static void main(String[]args)
	{
		try
		{
			AudioInputStream song = AudioSystem.getAudioInputStream(new File("song.wav"));
			AudioFormat format = song.getFormat();
			int chunkSize = (int)(format.getChannels()*format.getSampleRate() * format.getSampleSizeInBits()/8);
			BoundedBuffer stream= new BoundedBuffer(chunkSize);
			
			Producer reader = new Producer(stream);
			Consumer dj = new Consumer(stream);

			reader.start();
			dj.start();
		}

		catch (UnsupportedAudioFileException e ) {
			System.out.println("Player initialisation failed");
			e.printStackTrace();
			System.exit(1);
		}
		catch (IOException e) {
			System.out.println("Player initialisation failed");
			e.printStackTrace();
			System.exit(1);
		}
		





	
	}
	
}