package Evaluation;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;


public class SolutionEvaluator {
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ArrayList<ArrayList<Float>> pathSober = ReadPaths("datd.csv");
		ArrayList<ArrayList<Float>> pathDrunk = ReadPaths("dats.csv");
		

		ArrayList<ArrayList<Float>> pathSoberT = ReadPaths("datdt.csv");
		ArrayList<ArrayList<Float>> pathDrunkT = ReadPaths("datst.csv");
		
		
		Solution solution = new Solution();
		solution.train(pathDrunk, pathSober);
		
		int good = 0, bad = 0;
		for (ArrayList<Float> path : pathDrunkT) {
			if (solution.evaluate(path)){
				++good;
			}
			else
			{
				System.out.println("miss");
				++bad;
			}
		}
		
		for (ArrayList<Float> path : pathSoberT) {
			if (solution.evaluate(path)){
				++bad;
				System.out.println("false positive");
			}
			else
			{
				++good;
			}
		}
		
		System.out.println("good :" + good);
		System.out.println("bad :" + bad);
		
		System.out.println(((float)good / (float)(good + bad)) * 100 + "% efficient");
	}
	
	public static ArrayList<ArrayList<Float>> ReadPaths(String filename)
	{
		ArrayList<ArrayList<Float>> paths = new ArrayList<ArrayList<Float>>();
		
		BufferedReader br = null;
		String line = "";
		String cvsSplitBy = ",";
		try {
			URL url = SolutionEvaluator.class.getResource(filename);
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
