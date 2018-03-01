package input_output;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * The Class HomeworkReader.
 *
 * @author Mindru Alexandru-Ionut Grupa 321CB
 */
public class HomeworkReader {

	/** The reader. */
	private BufferedReader reader;

	/**
	 * Instantiates a new homework reader.
	 *
	 * @param filename
	 *            the filename
	 */
	public HomeworkReader(String filename) {
		try {
			reader = new BufferedReader(new FileReader(new File(filename)));
		} catch (FileNotFoundException ex) {
			Logger.getLogger(HomeworkReader.class.getName()).log(Level.SEVERE, null, ex);
		}
	}

	/**
	 * Read data.
	 *
	 * @return the problem data
	 */
	public ProblemData readData() {
		ProblemData result = null;

		try {
			String[] line = reader.readLine().split(" ");

			int nr_nodes = Integer.parseInt(line[0]);
			int nr_edges = Integer.parseInt(line[1]);
			int nr_colors = Integer.parseInt(line[2]);
			int[][] edges = null;

			if (nr_edges != 0) {
				edges = new int[nr_edges][2];

				for (int i = 0; i < nr_edges; ++i) {
					line = reader.readLine().split(" ");

					edges[i][0] = Integer.parseInt(line[0]);
					edges[i][1] = Integer.parseInt(line[1]);
				}
			}

			result = new ProblemData(nr_nodes, nr_edges, nr_colors, edges);

		} catch (IOException ex) {
			Logger.getLogger(HomeworkReader.class.getName()).log(Level.SEVERE, null, ex);
		}

		return result;
	}

	/**
	 * Close.
	 */
	public void close() {
		try {
			reader.close();
		} catch (IOException ex) {
			Logger.getLogger(HomeworkReader.class.getName()).log(Level.SEVERE, null, ex);
		}
	}
}
