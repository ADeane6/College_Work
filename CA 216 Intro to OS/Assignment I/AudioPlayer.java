import javax.sound.sampled.*;
import java.applet.Applet;
import java.io.*;
class BoundedBuffer
{
	int nextIn;
	int nextOut;
	int size;
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
	BoundedBuffer()
	{
		roomAvailable = true;
		nextIn = 0;
		nextOut = 0;
		occupied = 0;
		ins = 0;
		outs = 0;
	}
	void getinfo()
	{
		try
		{
			AudioInputStream song = AudioSystem.getAudioInputStream(new File("song.wav"));
			format=song.getFormat();
			info = new DataLine.Info(SourceDataLine.class, format);
			
			System.out.println("Audio format: "+format.toString());
			
			chunkSize = (int)(format.getChannels()*format.getSampleRate() * format.getSampleSizeInBits()/8);
			System.out.println("Chunk Size is: "+chunkSize);
			buffer = new byte[chunkSize*10];
			size=chunkSize*10;
			long frames = song.getFrameLength();
			duration = (int)(frames+0.0) / (int)(format.getFrameRate());
			System.out.println("Song Duration is: "+duration);
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

	boolean over()
	{
		return !(outs <= duration);
	}

	void insertChunk(byte[] chunk)
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
		nextIn += chunkSize;
		nextIn = nextIn%size;
		occupied++;
		if(occupied == 0)
		{
			dataAvailable = false;
		}
		ins++;
	}
	
	byte[] removeChunk()
	{
		byte[] chunk = new byte[chunkSize];
		for (int i = nextOut, k = 0; k < chunkSize; i++, k++)
		{
			chunk[k] = buffer[i];
		}
		nextOut += chunkSize;
		nextOut = nextOut%size;
		occupied--;
		outs++;
		return chunk;
	}

}
class Producer extends Thread
{
	BoundedBuffer bBuffer;

	Producer(BoundedBuffer buffer) {
    bBuffer = buffer;
	}

	public synchronized void run()
	{
		try
		{
			byte[] currentChunk = new byte[bBuffer.chunkSize];
			AudioInputStream song = AudioSystem.getAudioInputStream(new File("song.wav"));
			while(true)
			{
				int temp = song.read(currentChunk);
				bBuffer.insertChunk(currentChunk);
			}
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
	
	
	}

}

class Consumer extends Thread
{
	BoundedBuffer bBuffer;

	Consumer(BoundedBuffer buffer) {
    bBuffer = buffer;
	}

	public synchronized void run()
	{
		try
		{

			SourceDataLine line = (SourceDataLine) AudioSystem.getLine(bBuffer.info);
			line.open(bBuffer.format);
			line.start();
			while(!bBuffer.over())
			{
				byte[] audioChunk = bBuffer.removeChunk();
				line.write(audioChunk, 0, bBuffer.chunkSize);
				wait(1);

			}			
			line.drain();
			line.stop();
			line.close();
			System.out.println("Bye Bye from DJ");
			return;
		}
		catch (InterruptedException e)
		{
			System.out.println("Bye Bye from DJ");
			return;
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
		BoundedBuffer stream= new BoundedBuffer();
		stream.getinfo();
		

		Producer reader = new Producer(stream);
		Consumer dj = new Consumer(stream);

		reader.start();
		dj.start();





	
	}
	
}