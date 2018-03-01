import input_output.HomeworkWriter;
import input_output.ProblemData;

/**
 * The Class k_colorability_SAT.
 *
 * @author Mindru Alexandru-Ionut Grupa 321CB
 */
public class k_colorability_SAT {

	/** The out. */
	private HomeworkWriter out;

	/** The nr nodes. */
	private int nr_nodes;

	/** The nr colors. */
	private int nr_colors;

	/** The nr edges. */
	private int nr_edges;

	/** The edges. */
	private int[][] edges;

	/** The Variables. */
	private int[] Variables;

	/** The ALO C clause. */
	private String ALOC_Clause;

	/** The AMO C clause. */
	private String AMOC_Clause;

	/** The DCO L clause. */
	private String DCOL_Clause;

	/**
	 * Instantiates a new k colorability SAT.
	 *
	 * @param input
	 *            the input
	 * @param out
	 *            the out
	 */
	public k_colorability_SAT(ProblemData input, HomeworkWriter out) {
		nr_nodes = input.getNr_nodes();
		nr_colors = input.getNr_colors();
		nr_edges = input.getNr_edges();
		edges = input.getEdges();
		this.out = out;
	}

	/**
	 * Generate variables.
	 */
	public void generate_Variables() {
		Variables = new int[nr_nodes * nr_colors];

		for (int i = 0; i < nr_nodes * nr_colors; i++) {
			Variables[i] = i;
		}
	}

	/**
	 * Generate ALOC.
	 */
	public void generate_ALOC() {
		ALOC_Clause = "";

		for (int i = 0; i < nr_nodes; i++) {
			if (nr_colors > 1) {
				ALOC_Clause += "(";
			}

			for (int j = 0; j < nr_colors; j++) {
				ALOC_Clause += "x" + (Variables[i] * nr_colors + j);

				if (nr_colors - 1 > j) {
					ALOC_Clause += "V";
				}
			}

			if (nr_colors > 1) {
				ALOC_Clause += ")";
			}

			if (nr_nodes - 1 > i) {
				ALOC_Clause += "^";
			}
		}
	}

	/**
	 * Generate AMOC.
	 */
	public void generate_AMOC() {
		AMOC_Clause = "";

		for (int i = 0; i < nr_nodes; i++) {
			for (int j = 0; j < nr_colors; j++) {
				for (int k = j + 1; k < nr_colors; k++) {
					AMOC_Clause += "^(~x" + (i * nr_colors + j) + "V~x" + (i * nr_colors + k) + ")";
				}
			}
		}
	}

	/**
	 * Generate DCOL.
	 */
	public void generate_DCOL() {
		DCOL_Clause = "";

		for (int i = 0; i < nr_edges; i++) {
			int nod1 = edges[i][0] * nr_colors;
			int nod2 = edges[i][1] * nr_colors;

			for (int j = 0; j < nr_colors; j++) {
				DCOL_Clause += "^(~x" + nod1++ + "V~x" + nod2++ + ")";
			}
		}
	}

	/**
	 * Prints the SAT.
	 */
	public void print_SAT() {
		out.print(ALOC_Clause + AMOC_Clause + DCOL_Clause);
	}
}
