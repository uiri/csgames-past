package MachineLearningChallenge;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;


public class SolutionLauncher {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ArrayList<ArrayList<Float>> pathSober = ReadPaths("dats.csv");
		ArrayList<ArrayList<Float>> pathDrunk = ReadPaths("datd.csv");
		ArrayList<ArrayList<Float>> pathTest = ReadPaths("datt.csv");
		
		Solution solution = new Solution();
		solution.train(pathDrunk, pathSober);
		
		if (!solution.evaluate(pathTest.get(0)))
		{
			System.out.println("your code executed successfuly, and it was right on this sample");
		}
		else
		{
			System.out.println("your code executed successfuly, but it was wrong on this sample. This guy is not drunk at all");
		}
	}

	public static ArrayList<ArrayList<Float>> ReadPaths(String filename)
	{
		ArrayList<ArrayList<Float>> paths = new ArrayList<ArrayList<Float>>();
		
		BufferedReader br = null;
		String line = "";
		String cvsSplitBy = ",";
		try {
			URL url = SolutionLauncher.class.getResource(filename);
			br = new BufferedReader(new FileReader(url.getPath()));
			while ((line = br.readLine()) != null) {
				ArrayList<Float> path = new ArrayList<Float>();
			        // use comma as separator
				String[] pathStr = line.split(cvsSplitBy);
				
				for (int i = 0; i < pathStr.length; ++i){
					path.add(Float.parseFloat(pathStr[i]));
				}
				
				paths.add(path);
			}
	 
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (br != null) {
				try {
					br.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		
		return paths;
	}
}
