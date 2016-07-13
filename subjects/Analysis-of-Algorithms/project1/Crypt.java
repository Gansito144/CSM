import java.io.*;
import java.util.*;
import java.lang.*;

public class Crypt{
	public static ArrayList<Integer> z_algorithm(
		ArrayList<Integer> P, ArrayList< Integer > T)
	{
		ArrayList<Integer> z, matches, S=new ArrayList<Integer>(P);
		int m = P.size();
		S.add(-1); S.addAll(T);
		
		int L = 0, R = 0, n = S.size();
		z = new ArrayList<Integer>( S );
		matches = new ArrayList<Integer>();

		for (int i = 1; i<n; i++) {
			if (i > R) {
				L = R = i;
				while ( R < n && S.get(R-L) == S.get(R) ) {
					R++;
				}
				z.set(i,R-L);
				R--;
			} else {
				int k = i-L;
				if (z.get(k) < R-i+1) z.set(i,z.get(k));
				else {
					L = i;
					while (R < n && S.get(R-L) == S.get(R)) R++;
					z.set(i,R-L);
					R--;
				}
			}
			if( z.get(i) == m )
			{
				matches.add(i-m-1);
			}
		}
		return matches;
	}
	public static void main(String[] args) {
		BufferedReader in = null, in2 = null;
	try {
		// Files which we will work with
		String file_name;
		try
		{
			file_name = args[0];
		} catch(Exception e) {
			file_name = "stdin";
		}

		File km_dir = new File("known_message.txt");
		File fm_dir = new File(file_name);
		
		// Some Utils variables
		String line;
		ArrayList<Integer> sizes_known = new ArrayList<Integer>();
		ArrayList<String> old_msg = new ArrayList<String>();

		// First process the known message	
		in = new BufferedReader( new InputStreamReader(
               	new FileInputStream(km_dir), "UTF8"));
		while ((line = in.readLine()) != null)
		{
			
		   String[] splited = line.split("\\s+");
        	for (String word : splited) {
            	sizes_known.add(word.length());
            	old_msg.add(word.toLowerCase());
        	}
		}
		// First process the known message
		in2 = new BufferedReader( new InputStreamReader(
                new FileInputStream(fm_dir), "UTF8"));
		int testCases = Integer.parseInt(in2.readLine());
		line = in2.readLine();
		for(int test=1; test<=testCases; test++)
		{
			if(test>1) System.out.println(""); //Print the line between cases
			ArrayList<Integer> sizes_msg = new ArrayList<Integer>();
			ArrayList<String> new_msg = new ArrayList<String>();
			while ((line = in2.readLine()) != null )
			{
				if(line.length() == 0) break;
			    String[] splited = line.split("\\s+");
	        	for (String word : splited) {
	            	sizes_msg.add(word.length());
	            	new_msg.add(word.toLowerCase());
	        	}
			}
			// We get the message and split it in words, now we have to look for
			// posibles matches at least in size words
			ArrayList<Integer> matches = z_algorithm(sizes_known,sizes_msg);
			boolean answer = false;
			for(int i=0; i<matches.size() && !answer; i++)
			{
				HashMap <Character,Character> map;
				map = new HashMap<Character,Character> ();
				boolean candidate = true;
				int new_id = matches.get(i);
				int old_id = 0;
				while( old_id < old_msg.size() && candidate )
				{
					int j = 0;
					String nWord = new_msg.get(new_id);
					String oWord = old_msg.get(old_id);
					while(j < new_msg.get(new_id).length() && candidate)
					{
						Character next = nWord.charAt(j);
						Character prev = oWord.charAt(j);
						if( map.containsKey(next) )
						{
							if( map.get(next) != prev )
							{
								candidate = false;
								break;
							}
						}
						map.put(next,prev);
						j++;
					}
					new_id++;
					old_id++;
				}
				if(candidate) {
					// Now we have to iterate over all the words in array excluding 
					// the indices which are part of the encrypted message 

					ArrayList< String > decrypted_msg = new ArrayList< String >();
					int L = matches.get(i), R = matches.get(i) + old_msg.size()-1;
					for(int id = 0; id < new_msg.size() && candidate; id++)
					{
						if(id>=L && id<=R) continue;
						String dWord = "", eWord = new_msg.get(id);
						for(int j = 0; j < new_msg.get(id).length(); j++)
						{
							Character next = eWord.charAt(j);
							if( !map.containsKey(next) )
							{
								candidate = false;
								break;
							}
							dWord += map.get(next);
						}
						if(candidate) decrypted_msg.add(dWord);
					}
					if(candidate)
					{
						int charPrinted = 0;
						for(int kk=0; kk<decrypted_msg.size(); kk++)
						{
							if(charPrinted > 0) System.out.print(" ");
							System.out.print(decrypted_msg.get(kk).toUpperCase());
							charPrinted += decrypted_msg.get(kk).length();
							if( charPrinted > 65 ) // Adjusted to 65 columns
							{
								charPrinted = 0;
								System.out.println("");
							}
						}
						answer = true;
						System.out.println("");
					} else {
						System.out.println("NO SE ENCONTRO SOLUCIÓN");
					}
				}
			}
			if(!answer)
			{
				System.out.println("NO SE ENCONTRO SOLUCIÓN");
			}
		}	
    } catch (UnsupportedEncodingException e) {
		System.out.println(e.getMessage());
    } catch (IOException e) {
		System.out.println(e.getMessage());
    } catch (Exception e) {
		System.out.println(e.getMessage());
    } finally {
    	try{
    		in.close();
    		in2.close();
    	}catch (Exception e)
    	{
			System.out.println(e.getMessage());
    	}
    }
	}
}