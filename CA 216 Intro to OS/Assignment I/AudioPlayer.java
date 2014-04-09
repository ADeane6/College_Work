import javax.sound.sampled.*;
import java.applet.Applet;
class Buffer
{
	int nextIn ;
	int nextOut ;
	int size ;
    int occupied ;
	int ins ;
	int outs ;
	int chunks;
	byte [] buffer;
	bool dataAvailable; //for consumer
	bool roomAvailable; //for producer
	void getinfo()
	{
		AudioInputStream s;
		s.getAudioInputStream(new File('song.wav');
		AudioFormat f=s.getFormat();
		
		System.out.prinln("Audio format: "+f.toString());
		
		chunks = (int)(f.getChannels()*f.getSampleRate() * f.getSampleSizeInBits()/8);
		buffer = new byte[chunks*10];
		size=chunks*10;
	
	}

}
class Produce implements runnable
{
	
	public void run()
	{
	
	
	
	}

}

class Consumer implements Runnable
{
	public void run()
	{
	
	
	
	}

}
class AudioPlayer
{
	public static void main(String[]args)
	{
		File f = new File('song.wav');
		Buffer stream= new Buffer();
		stream.getinfo();

	
	}
	
}