package Evaluation;

import java.util.ArrayList;
import java.util.Comparator;

public class Solution {
	private final static int LENGTH_EVAL = 10;
	private final static int K = 1;
	
	private ArrayList<ArrayList<Float>> speedsDrunk = new ArrayList<ArrayList<Float>>();
	private ArrayList<ArrayList<Float>> speedsSober = new ArrayList<ArrayList<Float>>();

	/**
	 * will be called once with two datasets of 500 paths. Each path contains
	 * 100 positions.
	 * 
	 * @return
	 */
	public void train(ArrayList<ArrayList<Float>> samplesDrunk,
			ArrayList<ArrayList<Float>> samplesSober) {
		for (ArrayList<Float> path : samplesDrunk) {
			speedsDrunk.add(this.ConvertToSpeeds(path));
		}
		for (ArrayList<Float> path : samplesSober) {
			speedsSober.add(this.ConvertToSpeeds(path));
		}
	}

	/**
	 * return true if you give it a drunk guy's path, false otherwise Will be
	 * called once automatically when you run SolutionTest after train, so you
	 * know it is called correctly and work as expected. we STRONGLY suggest you
	 * to test more than one sample to know if your suggestions work ;)
	 * 
	 * @return
	 */
	public boolean evaluate(ArrayList<Float> sample) {

		ArrayList<Float> speedSample = this.ConvertToSpeeds(sample);

		ArrayList<Float> distS = new ArrayList<Float>();
		ArrayList<Float> distD = new ArrayList<Float>();

		for (ArrayList<Float> sampleSober : speedsSober) {
			distS.add(this.ComputeDistance(speedSample, sampleSober));
		}

		for (ArrayList<Float> sampleDrunk : speedsDrunk) {
			distD.add(this.ComputeDistance(speedSample, sampleDrunk));
		}
		
		distD.sort(new Comparator<Float>() {
			public int compare(Float o1, Float o2) {
				if (o1 < o2){return -1;}
				else if (o1 == o2){return 0;}
				return 1;
			}
		});
		distS.sort(new Comparator<Float>() {
			public int compare(Float o1, Float o2) {
				if (o1 < o2){return -1;}
				else if (o1 == o2){return 0;}
				return 1;
			}
		});
		int votes = 0;
		
		for (int i = 0; i < K; ++i){
			if (distS.get(0) > distD.get(0)){
				++votes;
				distD.remove(0);
			}
			else {
				--votes;
				distS.remove(0);
			}
		}

		return votes > 0;
	}

	private ArrayList<Float> ConvertToSpeeds(ArrayList<Float> path) {
		ArrayList<Float> speeds = new ArrayList<Float>();

		for (int i = 0; i < path.size() - 1; ++i) {
			speeds.add(path.get(i + 1) - path.get(i));
		}

		return speeds;
	}

	private float ComputeDistance(ArrayList<Float> path1, ArrayList<Float> path2) {
		float dist = 0;

		for (int i = 0; i < LENGTH_EVAL; ++i) {
			dist += Math.abs(path1.get(i) - path2.get(i));
		}

		return dist;
	}
}
