import java.io.*;
import java.util.*;

public class Test
{
	public static String read(String fn)
	{
		StringBuilder sb = new StringBuilder("");
		File file = new File(fn);
		try
		{
			FileReader reader = new FileReader(file);
			int input = reader.read();
			while(input != -1)
			{
				sb.append((char)input);
				input = reader.read();
			}
		} catch(Exception e) {e.printStackTrace();}
		return sb.toString();
	}
	public static void write(String fn, String data)
	{
		if(fn.equals("")) {throw new IllegalArgumentException();}
		try
		{
			File file = new File(fn);
			FileWriter writer = new FileWriter(file);
			writer.write(data);
			writer.close();
		} catch(Exception e) {e.printStackTrace();}
	}
	/*public static void consoleOut()
	{
		try
		{
			Process p = Runtime.getRuntime().exec("cmd /c start java.bat", null, new File("C:\\Users\\jwolf\\Documents\\code\\cpp\\program-test\\src"));
		} catch(Exception e) {e.printStackTrace();}
	}*/
	public static void main(String args[])
	{
		long start = System.currentTimeMillis(), end;
		String fn = args[0], destination = args[1];
		int testCount = Integer.parseInt(args[2]);
		String bool = args[3];
		//boolean destroyAfter = false;
		//if(bool.equals("1")) {destroyAfter = true;}
		System.out.println("new file name: "+fn);
		System.out.println("Starting test, reading file "+fn+" "+Integer.toString(testCount)+" times\n-----------------------\n");
		for(int i = 0; i < testCount; i++)
		{
			String data = read(fn);
			if(data != "")
			{
				write(destination, data);
				//if(destroyAfter) {consoleOut();}
			}
			else {System.out.println("Data is null!");}
		}
		end = System.currentTimeMillis();
		System.out.print("Time elapsed: ");
		System.out.println((end-start)/1000);
	}
}

