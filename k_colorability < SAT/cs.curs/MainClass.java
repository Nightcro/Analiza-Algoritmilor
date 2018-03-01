import input_output.HomeworkReader;
import input_output.HomeworkWriter;
import input_output.ProblemData;

/**
 * The Class MainClass.
 *
 * @author Mindru Alexandru-Ionut Grupa 321CB
 */
public class MainClass {

	public static void main(String[] args) {

		HomeworkReader in = new HomeworkReader("test.in");
		ProblemData input = in.readData();
		in.close();

		HomeworkWriter out = new HomeworkWriter("test.out");
		k_colorability_SAT transform = new k_colorability_SAT(input, out);
		transform.generate_Variables();
		transform.generate_ALOC();
		transform.generate_AMOC();
		transform.generate_DCOL();
		transform.print_SAT();
		out.close();
	}
}
