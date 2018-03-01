package input_output;

/**
 * The Class ProblemData.
 *
 * @author Mindru Alexandru-Ionut Grupa 321CB
 */
public class ProblemData {

	/** The nr nodes. */
	private int nr_nodes;

	/** The nr edges. */
	private int nr_edges;

	/** The nr colors. */
	private int nr_colors;

	/** The edges. */
	private int[][] edges;

	/**
	 * Instantiates a new problem data.
	 *
	 * @param nr_nodes
	 *            the nr nodes
	 * @param nr_edges
	 *            the nr edges
	 * @param nr_colors
	 *            the nr colors
	 * @param edges
	 *            the edges
	 */
	public ProblemData(int nr_nodes, int nr_edges, int nr_colors, int[][] edges) {
		this.nr_nodes = nr_nodes;
		this.nr_edges = nr_edges;
		this.nr_colors = nr_colors;
		this.edges = edges;
	}

	public int getNr_nodes() {
		return nr_nodes;
	}

	public void setNr_nodes(int nr_nodes) {
		this.nr_nodes = nr_nodes;
	}

	public int getNr_edges() {
		return nr_edges;
	}

	public void setNr_edges(int nr_edges) {
		this.nr_edges = nr_edges;
	}

	public int getNr_colors() {
		return nr_colors;
	}

	public void setNr_colors(int nr_colors) {
		this.nr_colors = nr_colors;
	}

	public int[][] getEdges() {
		return edges;
	}

	public void setEdges(int[][] edges) {
		this.edges = edges;
	}

}
