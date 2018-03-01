package input_output;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * The Class HomeworkWriter.
 *
 * @author Mindru Alexandru-Ionut Grupa 321CB
 */
public class HomeworkWriter {

	/** The writer. */
	private PrintWriter writer;

	/**
	 * Instantiates a new homework writer.
	 *
	 * @param filename
	 *            the filename
	 */
	public HomeworkWriter(String filename) {
		try {
			writer = new PrintWriter(new File(filename));
		} catch (FileNotFoundException ex) {
			Logger.getLogger(HomeworkWriter.class.getName()).log(Level.SEVERE, null, ex);
		}
	}

	/**
	 * Prints the text.
	 *
	 * @param text
	 *            the text
	 */
	public void print(String text) {
		writer.print(text);
	}

	/**
	 * Close.
	 */
	public void close() {
		writer.close();
	}
}
