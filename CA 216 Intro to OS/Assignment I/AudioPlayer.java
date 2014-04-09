import javax.sound.sampled.*;
import java.applet.Applet;
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
	bool dataAvailable; //for consumer
	bool roomAvailable; //for producer
	BoundedBuffer()
	{
		nextIn = 0;
		nextOut = 0;
		occupied = 0;
		ins = 0;
		outs = 0;
  }
	}
	void getinfo()
	{
		AudioInputStream s;
		s.getAudioInputStream(new File('song.wav');
		format=s.getFormat();
		info = new DataLine.Info(SourceDataLine.class, format);
		
		System.out.prinln("Audio format: "+format.toString());
		
		chunks = (int)(format.getChannels()*format.getSampleRate() * format.getSampleSizeInBits()/8);
		buffer = new byte[chunks*10];
		size=chunks*10;
		long frames = audioInputStream.getFrameLength();
		duration = (int)(frames+0.0) / format.getFrameRate();
		*/
	
	}

	boolean over()
	{
		return !(out <= duration);
	}

	void insertChunk(byte[] chunk)
	{
		byte[] chunk = new byte[chunkSize];
		for (int i = nextIn, int k = 0; i <=(chunkSize+nextIn); i++, k++)
		{
			buffer[i] = chunk[k];
		}
		nextIn += chunkSize;
		nextIn = nextIn%size;
		occupied++;
		ins++;
	}
	
	byte[] removeChunk()
	{
		byte[] chunk = new byte[chunkSize];
		for (int i = nextOut, int k = 0; i <=(chunkSize+nextOut); i++, k++)
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
class Producer implements Runnable
{
	BoundedBuffer bBuffer;

	Producer(BoundedBuffer buffer) {
    bBuffer = buffer;
	}

	public void run()
	{
		try
		{
			while(bBufer.roomAvailable)
		}
		catch (InterruptedException e)
		{
			System.out.println("Bye Bye from Producer");
			return;
		}
	
	
	}

}

class Consumer implements Runnable
{
	BoundedBuffer bBuffer;

	Consumer(BoundedBuffer buffer) {
    bBuffer = buffer;
	}

	public void run()
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
	
	
	}

}
class AudioPlayer
{
	public static void main(String[]args)
	{
		Buffer stream= new Buffer();
		stream.getinfo();
		

		Producer reader = new Producer(stream);
		Consumer dj = new Consumer(stream);

		reader.start();
		dj.start();





	
	}
	
}